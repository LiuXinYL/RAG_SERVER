"""
优化的FAISS向量存储管理模块
提供向量数据库的创建、保存、加载、搜索等核心功能
"""
import json
import os
import sys
from pathlib import Path
from typing import List, Optional, Tuple, Union, Dict, Any
from dataclasses import dataclass, field
from enum import Enum
import logging 
from concurrent.futures import ThreadPoolExecutor, as_completed
import threading

from langchain_community.vectorstores import FAISS
from langchain_core.documents import Document
from langchain_openai import OpenAIEmbeddings
from tqdm import tqdm
import numpy as np

# 添加当前目录到系统路径
current_dir = os.path.abspath(os.path.dirname(__file__))
sys.path.append(current_dir)

from llm_init import LLM_INIT
from data2faiss_optimized import DocumentManager, SplitType, SplitConfig, check_and_create_dir
from config import LLM_CONFIG, VECTOR_SAVE_PATH

# 配置日志
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)


class SearchType(Enum):
    """搜索类型枚举"""
    SIMILARITY = "similarity"
    MMR = "mmr"  # Maximum Marginal Relevance
    SIMILARITY_SCORE = "similarity_score_threshold"


@dataclass
class SearchConfig:
    """搜索配置"""
    k: int = 4
    fetch_k: int = 20
    lambda_mult: float = 0.5
    score_threshold: float = 0.5


@dataclass
class FAISSConfig:
    """FAISS配置"""
    max_tokens: int = field(default_factory=lambda: LLM_CONFIG.get("max_tokens", 4096))
    temperature: float = field(default_factory=lambda: LLM_CONFIG.get("temperature", 0.7))
    batch_size: int = 100
    enable_cache: bool = True
    cache_size: int = 1000


class VectorStoreCache:
    """向量存储缓存管理"""
    
    def __init__(self, max_size: int = 1000):
        self.max_size = max_size
        self.cache: Dict[str, Any] = {}
        self.access_order: List[str] = []
        self.lock = threading.Lock()
    
    def get(self, key: str) -> Optional[Any]:
        """获取缓存项"""
        with self.lock:
            if key in self.cache:
                # 更新访问顺序
                self.access_order.remove(key)
                self.access_order.append(key)
                return self.cache[key]
            return None
    
    def put(self, key: str, value: Any) -> None:
        """添加缓存项"""
        with self.lock:
            if len(self.cache) >= self.max_size and key not in self.cache:
                # 移除最久未使用的项
                oldest = self.access_order.pop(0)
                del self.cache[oldest]
            
            self.cache[key] = value
            if key in self.access_order:
                self.access_order.remove(key)
            self.access_order.append(key)
    
    def clear(self) -> None:
        """清空缓存"""
        with self.lock:
            self.cache.clear()
            self.access_order.clear()


class FAISSManager:
    """FAISS向量存储管理器"""
    
    def __init__(
        self,
        knowledge_name: str,
        config: Optional[FAISSConfig] = None,
        embedding_client: Optional[OpenAIEmbeddings] = None,
        rerank_client: Optional[Any] = None
    ):
        """
        初始化FAISS管理器
        
        Args:
            knowledge_name: 知识库名称
            config: FAISS配置
            embedding_client: 嵌入模型客户端
            rerank_client: 重排序模型客户端
        """
        self.knowledge_name = knowledge_name
        self.config = config or FAISSConfig()
        
        # 初始化模型
        llm_init = LLM_INIT(self.config.max_tokens, self.config.temperature)
        self.embeddings_model = embedding_client or llm_init.create_embeddings_client()
        self.rerank_model = rerank_client or llm_init.create_rerank_client()
        
        # 初始化文档管理器
        self.doc_manager = DocumentManager(self.embeddings_model)
        
        # 向量存储和映射
        self.vector_store: Optional[FAISS] = None
        self.small_to_large_mapping: Dict[str, str] = {}
        
        # 缓存
        self.cache = VectorStoreCache(self.config.cache_size) if self.config.enable_cache else None
        
        # 加载知识库索引
        self._load_knowledge_base_index()
    
    def _load_knowledge_base_index(self) -> None:
        """加载知识库索引"""
        try:
            from index_manager import load_knowledge_base_index
            self.knowledge_base_index = load_knowledge_base_index()
        except ImportError:
            logger.warning("无法导入index_manager，使用默认索引")
            self.knowledge_base_index = {}
    
    def _update_knowledge_base_index(self) -> None:
        """更新知识库索引"""
        try:
            from index_manager import change_knowledge_base_index
            self.knowledge_base_index = change_knowledge_base_index(
                index_data=self.knowledge_base_index,
                knowledge_repository_names=self.knowledge_name
            )
        except ImportError:
            logger.warning("无法更新知识库索引")
    
    def create_vector_store(
        self,
        file_path: Union[str, Path],
        split_type: Union[str, SplitType] = SplitType.SIMPLE
    ) -> bool:
        """
        创建向量存储
        
        Args:
            file_path: 文件路径
            split_type: 切分类型
            
        Returns:
            是否成功创建
        """
        try:
            # 验证文件
            path = Path(file_path)
            if not path.exists():
                logger.error(f"文件不存在: {file_path}")
                return False
            
            # 处理文档
            result = self.doc_manager.process_document(file_path, split_type)
            
            if split_type == SplitType.PARENT_CHILD:
                if not isinstance(result, tuple):
                    logger.error("父子切分返回结果格式错误")
                    return False
                
                smaller_docs, larger_docs, parent_store, mapping = result
                if parent_store is None:
                    logger.error("父子切分失败")
                    return False
                
                self.vector_store = parent_store
                self.small_to_large_mapping = mapping
                logger.info(f"创建父子向量存储成功，包含 {len(mapping)} 个映射关系")
                
            else:
                documents = result
                if not documents:
                    logger.error("未获取到任何文档")
                    return False
                
                self.vector_store = FAISS.from_documents(documents, self.embeddings_model)
                logger.info(f"创建向量存储成功，包含 {len(documents)} 个文档")
            
            return True
            
        except Exception as e:
            logger.error(f"创建向量存储时出错: {str(e)}")
            return False
    
    def add_documents(self, documents: List[Document], batch_size: Optional[int] = None) -> bool:
        """
        批量添加文档到向量存储
        
        Args:
            documents: 文档列表
            batch_size: 批处理大小
            
        Returns:
            是否成功添加
        """
        if self.vector_store is None:
            logger.error("向量存储尚未创建")
            return False
        
        batch_size = batch_size or self.config.batch_size
        
        try:
            # 批量添加文档
            for i in tqdm(range(0, len(documents), batch_size), desc="添加文档"):
                batch = documents[i:i + batch_size]
                self.vector_store.add_documents(batch)
            
            # 清空缓存
            if self.cache:
                self.cache.clear()
            
            logger.info(f"成功添加 {len(documents)} 个文档")
            return True
            
        except Exception as e:
            logger.error(f"添加文档时出错: {str(e)}")
            return False
    
    def save(self, save_path: Optional[Union[str, Path]] = None) -> bool:
        """
        保存向量存储
        
        Args:
            save_path: 保存路径，如果不提供则使用默认路径
            
        Returns:
            是否成功保存
        """
        if self.vector_store is None:
            logger.error("向量存储尚未创建")
            return False
        
        save_path = save_path or Path(VECTOR_SAVE_PATH) / self.knowledge_name
        save_path = Path(save_path)
        
        try:
            # 创建目录
            save_path.mkdir(parents=True, exist_ok=True)
            
            # 保存向量存储
            self.vector_store.save_local(folder_path=str(save_path))
            
            # 保存映射关系
            if self.small_to_large_mapping:
                mapping_path = save_path / 'small_to_large_mapping.json'
                with open(mapping_path, 'w', encoding='utf-8') as f:
                    json.dump(self.small_to_large_mapping, f, ensure_ascii=False, indent=2)
            
            # 更新知识库索引
            self._update_knowledge_base_index()
            
            # 获取文档数量
            doc_count = len(list(self.vector_store.index_to_docstore_id.values()))
            logger.info(f"成功保存向量存储到 {save_path}，包含 {doc_count} 个文档")
            
            return True
            
        except Exception as e:
            logger.error(f"保存向量存储时出错: {str(e)}")
            return False
    
    def load(
        self,
        load_path: Optional[Union[str, Path]] = None,
        allow_dangerous: bool = False
    ) -> bool:
        """
        加载向量存储
        
        Args:
            load_path: 加载路径，如果不提供则使用默认路径
            allow_dangerous: 是否允许不安全的反序列化
            
        Returns:
            是否成功加载
        """
        load_path = load_path or Path(VECTOR_SAVE_PATH) / self.knowledge_name
        load_path = Path(load_path)
        
        if not load_path.exists():
            logger.error(f"加载路径不存在: {load_path}")
            return False
        
        try:
            # 加载向量存储
            self.vector_store = FAISS.load_local(
                str(load_path),
                self.embeddings_model,
                allow_dangerous_deserialization=allow_dangerous
            )
            
            # 检查是否有父子映射
            if self.knowledge_base_index.get(self.knowledge_name):
                mapping_path = load_path / 'small_to_large_mapping.json'
                if mapping_path.exists():
                    with open(mapping_path, 'r', encoding='utf-8') as f:
                        self.small_to_large_mapping = json.load(f)
                    logger.info(f"加载了 {len(self.small_to_large_mapping)} 个父子映射关系")
            
            # 清空缓存
            if self.cache:
                self.cache.clear()
            
            doc_count = len(list(self.vector_store.index_to_docstore_id.values()))
            logger.info(f"成功加载向量存储，包含 {doc_count} 个文档")
            
            return True
            
        except Exception as e:
            logger.error(f"加载向量存储时出错: {str(e)}")
            return False
    
    def get_document_by_id(self, doc_id: str) -> Optional[Document]:
        """
        根据ID获取文档
        
        Args:
            doc_id: 文档ID
            
        Returns:
            文档对象，如果未找到则返回None
        """
        if self.vector_store is None:
            logger.error("向量存储尚未创建")
            return None
        
        # 检查缓存
        if self.cache:
            cached = self.cache.get(f"doc_{doc_id}")
            if cached is not None:
                return cached
        
        # 从存储中获取
        doc = self.vector_store.docstore.search(doc_id)
        
        # 添加到缓存
        if doc and self.cache:
            self.cache.put(f"doc_{doc_id}", doc)
        
        return doc
    
    def similarity_search(
        self,
        query: str,
        config: Optional[SearchConfig] = None,
        filter_dict: Optional[Dict[str, Any]] = None
    ) -> List[Document]:
        """
        相似度搜索
        
        Args:
            query: 查询文本
            config: 搜索配置
            filter_dict: 过滤条件
            
        Returns:
            搜索结果文档列表
        """
        if self.vector_store is None:
            logger.error("向量存储尚未创建")
            return []
        
        config = config or SearchConfig()
        
        try:
            # 检查缓存
            cache_key = f"search_{query}_{config.k}_{str(filter_dict)}"
            if self.cache:
                cached = self.cache.get(cache_key)
                if cached is not None:
                    return cached
            
            # 执行搜索
            if filter_dict:
                results = self.vector_store.similarity_search(
                    query, k=config.k, filter=filter_dict
                )
            else:
                results = self.vector_store.similarity_search(query, k=config.k)
            
            # 处理父子映射
            if self.knowledge_base_index.get(self.knowledge_name) and self.small_to_large_mapping:
                enhanced_results = []
                seen_ids = set()
                
                for result in results:
                    small_id = result.id
                    if small_id and str(small_id) in self.small_to_large_mapping:
                        large_id = self.small_to_large_mapping[str(small_id)]
                        
                        # 避免重复
                        if large_id not in seen_ids:
                            large_doc = self.get_document_by_id(large_id)
                            if large_doc:
                                enhanced_results.append(large_doc)
                                seen_ids.add(large_id)
                
                results = enhanced_results
            
            # 添加到缓存
            if self.cache and results:
                self.cache.put(cache_key, results)
            
            return results
            
        except Exception as e:
            logger.error(f"搜索时出错: {str(e)}")
            return []
    
    def mmr_search(
        self,
        query: str,
        config: Optional[SearchConfig] = None,
        filter_dict: Optional[Dict[str, Any]] = None
    ) -> List[Document]:
        """
        最大边际相关性搜索
        
        Args:
            query: 查询文本
            config: 搜索配置
            filter_dict: 过滤条件
            
        Returns:
            搜索结果文档列表
        """
        if self.vector_store is None:
            logger.error("向量存储尚未创建")
            return []
        
        config = config or SearchConfig()
        
        try:
            results = self.vector_store.max_marginal_relevance_search(
                query,
                k=config.k,
                fetch_k=config.fetch_k,
                lambda_mult=config.lambda_mult,
                filter=filter_dict
            )
            
            # 处理父子映射（同similarity_search）
            if self.knowledge_base_index.get(self.knowledge_name) and self.small_to_large_mapping:
                enhanced_results = []
                seen_ids = set()
                
                for result in results:
                    small_id = result.id
                    if small_id and str(small_id) in self.small_to_large_mapping:
                        large_id = self.small_to_large_mapping[str(small_id)]
                        if large_id not in seen_ids:
                            large_doc = self.get_document_by_id(large_id)
                            if large_doc:
                                enhanced_results.append(large_doc)
                                seen_ids.add(large_id)
                
                results = enhanced_results
            
            return results
            
        except Exception as e:
            logger.error(f"MMR搜索时出错: {str(e)}")
            return []
    
    def enhanced_search(
        self,
        query: str,
        search_type: Union[str, SearchType] = SearchType.SIMILARITY,
        config: Optional[SearchConfig] = None,
        filter_dict: Optional[Dict[str, Any]] = None,
        use_rerank: bool = True
    ) -> Tuple[List[Document], List[float]]:
        """
        增强搜索（支持重排序）
        
        Args:
            query: 查询文本
            search_type: 搜索类型
            config: 搜索配置
            filter_dict: 过滤条件
            use_rerank: 是否使用重排序
            
        Returns:
            (文档列表, 相关性分数列表)
        """
        # 转换搜索类型
        if isinstance(search_type, str):
            search_type = SearchType(search_type)
        
        # 执行初始搜索
        if search_type == SearchType.MMR:
            results = self.mmr_search(query, config, filter_dict)
        else:
            results = self.similarity_search(query, config, filter_dict)
        
        if not results:
            return [], []
        
        # 如果不使用重排序，返回默认分数
        if not use_rerank or not self.rerank_model:
            return results, [1.0] * len(results)
        
        try:
            # 提取文档内容
            document_texts = [doc.page_content for doc in results]
            
            # 执行重排序
            rerank_result = self.rerank_model.rerank(
                query=query,
                documents=document_texts,
                top_n=len(results)
            )
            
            # 重新排序文档
            reranked_docs = []
            scores = []
            
            for item in rerank_result["results"]:
                idx = item["index"]
                score = item["relevance_score"]
                
                reranked_docs.append(results[idx])
                scores.append(score)
            
            return reranked_docs, scores
            
        except Exception as e:
            logger.error(f"重排序时出错: {str(e)}")
            return results, [1.0] * len(results)
    
    def batch_process_files(
        self,
        file_paths: List[Union[str, Path]],
        split_type: Union[str, SplitType] = SplitType.SIMPLE,
        max_workers: int = 4
    ) -> bool:
        """
        批量处理文件
        
        Args:
            file_paths: 文件路径列表
            split_type: 切分类型
            max_workers: 最大并发数
            
        Returns:
            是否全部成功
        """
        if not file_paths:
            logger.warning("没有提供任何文件")
            return True
        
        logger.info(f"开始批量处理 {len(file_paths)} 个文件")
        
        # 处理结果
        all_documents = []
        all_mappings = {}
        failed_files = []
        
        # 使用线程池并发处理
        with ThreadPoolExecutor(max_workers=max_workers) as executor:
            # 提交任务
            future_to_file = {
                executor.submit(
                    self.doc_manager.process_document,
                    file_path,
                    split_type
                ): file_path
                for file_path in file_paths
            }
            
            # 处理结果
            for future in tqdm(as_completed(future_to_file), total=len(file_paths), desc="处理文件"):
                file_path = future_to_file[future]
                
                try:
                    result = future.result()
                    
                    if split_type == SplitType.PARENT_CHILD:
                        if isinstance(result, tuple) and result[2] is not None:
                            smaller_docs, larger_docs, parent_store, mapping = result
                            all_mappings.update(mapping)
                            
                            # 合并向量存储
                            if self.vector_store is None:
                                self.vector_store = parent_store
                            else:
                                self.vector_store.merge_from(parent_store)
                        else:
                            failed_files.append(file_path)
                    else:
                        if result:
                            all_documents.extend(result)
                        else:
                            failed_files.append(file_path)
                            
                except Exception as e:
                    logger.error(f"处理文件 {file_path} 时出错: {str(e)}")
                    failed_files.append(file_path)
        
        # 创建或更新向量存储
        if split_type != SplitType.PARENT_CHILD and all_documents:
            if self.vector_store is None:
                self.vector_store = FAISS.from_documents(all_documents, self.embeddings_model)
            else:
                self.add_documents(all_documents)
        
        # 更新映射
        if all_mappings:
            self.small_to_large_mapping.update(all_mappings)
        
        # 报告结果
        success_count = len(file_paths) - len(failed_files)
        logger.info(f"批量处理完成: 成功 {success_count}/{len(file_paths)} 个文件")
        
        if failed_files:
            logger.warning(f"失败的文件: {failed_files}")
        
        return len(failed_files) == 0
    
    def init_from_directory(
        self,
        data_dir: Union[str, Path],
        split_type: Union[str, SplitType] = SplitType.SIMPLE,
        extensions: Optional[List[str]] = None,
        recursive: bool = True
    ) -> bool:
        """
        从目录初始化向量存储
        
        Args:
            data_dir: 数据目录
            split_type: 切分类型
            extensions: 文件扩展名列表
            recursive: 是否递归搜索子目录
            
        Returns:
            是否成功
        """
        data_path = Path(data_dir)
        
        if not data_path.exists():
            logger.error(f"目录不存在: {data_dir}")
            return False
        
        # 获取文件列表
        if data_path.is_file():
            file_list = [data_path]
        else:
            # 默认扩展名
            if extensions is None:
                extensions = ['.xlsx', '.xls', '.csv', '.xml', '.txt', '.md', '.pdf', '.docx', '.doc']
            
            # 搜索文件
            file_list = []
            pattern = "**/*" if recursive else "*"
            
            for ext in extensions:
                file_list.extend(data_path.glob(f"{pattern}{ext}"))
        
        if not file_list:
            logger.warning(f"在 {data_dir} 中未找到任何支持的文件")
            return False
        
        logger.info(f"找到 {len(file_list)} 个文件")
        
        # 批量处理文件
        success = self.batch_process_files(file_list, split_type)
        
        # 保存结果
        if success and self.vector_store:
            return self.save()
        
        return success
    
    def get_statistics(self) -> Dict[str, Any]:
        """获取向量存储统计信息"""
        if self.vector_store is None:
            return {"status": "未初始化"}
        
        try:
            doc_count = len(list(self.vector_store.index_to_docstore_id.values()))
            
            stats = {
                "status": "已加载",
                "knowledge_name": self.knowledge_name,
                "document_count": doc_count,
                "has_parent_child_mapping": bool(self.small_to_large_mapping),
                "mapping_count": len(self.small_to_large_mapping),
                "cache_enabled": self.config.enable_cache,
                "cache_size": self.cache.cache.__len__() if self.cache else 0
            }
            
            return stats
            
        except Exception as e:
            logger.error(f"获取统计信息时出错: {str(e)}")
            return {"status": "错误", "error": str(e)}


# 保留向后兼容的类名
class FAISSCUSTOM(FAISSManager):
    """向后兼容类"""
    
    def __init__(
        self,
        max_tokens: int = None,
        temperature: float = None,
        embedding_client: Optional[OpenAIEmbeddings] = None,
        rerank_client: Optional[Any] = None,
        knowledge_name: str = 'maintenance_proposal'
    ):
        config = FAISSConfig(
            max_tokens=max_tokens or LLM_CONFIG["max_tokens"],
            temperature=temperature or LLM_CONFIG["temperature"]
        )
        super().__init__(knowledge_name, config, embedding_client, rerank_client)
    
    def create_vector(self, file_path: str, _type: str, split_type: str) -> bool:
        """向后兼容方法"""
        return self.create_vector_store(file_path, split_type)
    
    def enhanced_similarity_search(
        self,
        query: str,
        results_documents: List[Document],
        k: int = 4
    ) -> Tuple[str, List[int], List[float], List[Document]]:
        """向后兼容方法"""
        # 使用新的增强搜索
        docs, scores = self.enhanced_search(
            query,
            search_type=SearchType.SIMILARITY,
            config=SearchConfig(k=k),
            use_rerank=True
        )
        
        # 构造兼容的返回格式
        if docs:
            indices = list(range(len(docs)))
            return "compatibility", indices, scores, docs
        else:
            return "compatibility", [], [], []
    
    def init_data(self, data_dir: Union[str, Path], split_type: str = 'simple') -> None:
        """向后兼容方法"""
        self.init_from_directory(data_dir, split_type)


if __name__ == '__main__':
    # 测试代码
    import time
    
    # 测试配置
    test_knowledge = "test_knowledge"
    test_file = "E:/python_project/D_large_models/RAG_SERVER/data/bids_data"
    
    # 创建管理器
    print("=== 创建FAISS管理器 ===")
    manager = FAISSManager(
        knowledge_name=test_knowledge,
        config=FAISSConfig(enable_cache=True, cache_size=500)
    )
    
    # 获取统计信息
    print("\n=== 初始统计信息 ===")
    print(json.dumps(manager.get_statistics(), indent=2, ensure_ascii=False))
    
    # 从目录初始化
    print("\n=== 从目录初始化 ===")
    start_time = time.time()
    success = manager.init_from_directory(
        test_file,
        split_type=SplitType.PARENT_CHILD,
        extensions=['.docx', '.txt', '.pdf']
    )
    print(f"初始化{'成功' if success else '失败'}，耗时: {time.time() - start_time:.2f}秒")
    
    # 获取更新后的统计信息
    print("\n=== 更新后的统计信息 ===")
    print(json.dumps(manager.get_statistics(), indent=2, ensure_ascii=False))
    
    # 测试搜索
    if success:
        print("\n=== 测试搜索功能 ===")
        test_queries = [
            "软件功能要求是什么？",
            "系统架构设计",
            "健康管理"
        ]
        
        for query in test_queries:
            print(f"\n查询: {query}")
            
            # 普通搜索
            start_time = time.time()
            results = manager.similarity_search(query, config=SearchConfig(k=3))
            print(f"普通搜索: 找到 {len(results)} 个结果，耗时: {time.time() - start_time:.3f}秒")
            
            # 增强搜索
            start_time = time.time()
            docs, scores = manager.enhanced_search(query, use_rerank=True)
            print(f"增强搜索: 找到 {len(docs)} 个结果，耗时: {time.time() - start_time:.3f}秒")
            
            if docs:
                print(f"最相关结果 (分数: {scores[0]:.3f}):")
                print(f"内容预览: {docs[0].page_content[:100]}...")
    
    # 测试向后兼容性
    print("\n=== 测试向后兼容性 ===")
    old_style = FAISSCUSTOM(
        knowledge_name="backward_compat_test",
        max_tokens=4096,
        temperature=0.7
    )
    print(f"向后兼容类创建成功: {type(old_style).__name__}")