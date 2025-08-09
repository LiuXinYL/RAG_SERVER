import json
import os
import sys
from pathlib import Path
from typing import List, Optional, Tuple
from typing import Union

import tqdm
from langchain_community.vectorstores import FAISS
from langchain_core.documents import Document
from langchain_openai import OpenAIEmbeddings

# 获取当前项目目录的绝对路径
current_dir = os.path.abspath(os.path.dirname(__file__))
# 添加到 sys.path
sys.path.append(current_dir)

from llm_init import LLM_INIT
from data2faiss import check_and_create_dir, process_document
from config import LLM_CONFIG, VECTOR_SAVE_PATH


class FAISSCUSTOM:
    """
    文件的FAISS向量存储管理类
    可处理: Excel, XML, Word, PDF, TXT, Markdown等文件类型
    excel为人工整理的key:value,
    XML 为特殊处理的嵌套结构,
    其他可通过大模型语义分割。
    """

    def __init__(self, max_tokens: int = LLM_CONFIG["max_tokens"], temperature: float = LLM_CONFIG["temperature"],
                 embedding_client: Optional[OpenAIEmbeddings] = None, rerank_client: Optional[OpenAIEmbeddings] = None,
                 knowledge_name='maintenance_proposal'
                 ):
        """
        初始化FAISS向量存储

        Args:
            embedding_client: Embedding客户端实例，如果不提供则自动创建
        """
        if embedding_client is not None:
            self.embeddings_model = embedding_client
        else:
            self.embeddings_model = LLM_INIT(max_tokens, temperature).create_embeddings_client()

        if rerank_client is not None:
            self.rerank_model = rerank_client
        else:
            self.rerank_model = LLM_INIT(max_tokens, temperature).create_rerank_client()

        self.knowledge_name = knowledge_name

        # 类属性，存储知识库索引列表
        # 避免循环导入
        from index_manager import load_knowledge_base_index
        self.knowledge_base_index = load_knowledge_base_index()

        self.vector_store = None
        self.small_to_large_mapping = {}

    def add_documents(self, documents: List[Document]) -> bool:
        """
        向向量存储添加新文档

        Args:
            documents: 文档列表

        Returns:
            bool: 是否成功添加
        """
        if self.vector_store is None:
            print("错误: 向量存储尚未创建")
            return False

        try:
            self.vector_store.add_documents(documents)
            return True

        except Exception as e:
            print(f"添加文档时出错: {str(e)}")
            return False

    def create_vector(self, file_path: str, _type: str, split_type: str) -> bool:
        """
        用于Excel, XML, Word, PDF, TXT, Markdown等文件集中判断处理，
        其中Word, PDF, TXT, Markdown 将调用embeddings大模型进行语义切分。
        Args:
            :param file_path: 文件路径
            :param _type: 文件类型-后缀
            :param split_type: 分割类型
        Returns:
            bool: 是否成功创建
        """
        try:

            if _type not in ['.xlsx', '.xls', '.csv', '.xml', '.txt', '.md', '.pdf', '.docx', 'doc']:
                print('文件不在支持的类型中！')
                return False

            if split_type == 'parent_child':
                smaller_documents_list, larger_documents_list, parent_vector_store, small_to_large_mapping = process_document(
                    file_path, self.embeddings_model, split_type,
                )

                if small_to_large_mapping is not None:
                    self.small_to_large_mapping.update(small_to_large_mapping)  # 更新父子映射字典

                else:
                    raise ValueError("small_to_large_mapping is None")

                self.vector_store = parent_vector_store
                return True

            else:
                documents = process_document(file_path, self.embeddings_model)

                if documents is None:
                    return False

                self.vector_store = FAISS.from_documents(documents, self.embeddings_model)
                return True

        except Exception as e:
            print(f"创建向量存储时出错: {str(e)}")
            return False

    def save(self, save_path: str | Path) -> bool:
        """
        保存向量存储到本地

        Args:
            save_path: 保存路径

        Returns:
            bool: 是否成功保存
        """
        try:
            if self.vector_store is None:
                print("错误: 向量存储尚未创建")
                return False

            self.vector_store.save_local(folder_path=save_path)

            # 保存小块到大块的映射信息
            mapping_path = os.path.join(save_path, 'small_to_large_mapping.json')
            with open(mapping_path, 'w', encoding='utf-8') as f:
                json.dump(self.small_to_large_mapping, f)

            # 更新父子映射标记
            # 避免循环导入
            from index_manager import change_knowledge_base_index
            self.knowledge_base_index = change_knowledge_base_index(
                index_data=self.knowledge_base_index,
                knowledge_repository_names=self.knowledge_name
            )

            return True

        except Exception as e:
            print(f"保存向量存储时出错: {str(e)}")
            return False

    def load(self, load_path: Union[str, Path], allow_dangerous: bool = False) -> bool:
        """
        从本地加载向量存储

        Args:
            load_path: 加载路径
            allow_dangerous: 是否允许不安全的反序列化，仅在信任数据源时设置为True

        Returns:
            bool: 是否成功加载
        """
        try:

            self.vector_store = FAISS.load_local(
                load_path,
                self.embeddings_model,
                allow_dangerous_deserialization=allow_dangerous
            )
            # 根据 knowledge_repository_and_flag.json, 查看知识库parent_child信息标记情况，并初始化父子映射字典
            if self.knowledge_base_index.get(self.knowledge_name):  # 默认为false， 如果为true，则是父子分割，获取父子分割索引
                index_path = os.path.join(load_path, 'small_to_large_mapping.json')
                with open(index_path, 'r', encoding='utf-8') as file:
                    self.small_to_large_mapping = json.load(file)

            return True

        except Exception as e:
            print(f"加载向量存储时出错: {str(e)}")
            return False

    def get_document_by_id(self, doc_id: str) -> Optional[Document]:
        """
        根据文档 id 索引文档

        Args:
            doc_id: 文档的自定义 id

        Returns:
            Optional[Document]: 找到的文档，若未找到则返回 None
        """
        if self.vector_store is None:
            print("错误: 向量存储尚未创建")
            return None

        # 遍历所有文档
        for doc in self.vector_store.docstore._dict.values():
            if doc.id == doc_id:
                return doc
        return None

    def similarity_search(self, query: str, k: int = 4, filtration: dict = None) -> List[Document]:
        """
        执行相似度搜索

        Args:
            query: 查询文本
            k: 返回结果数量
            filtration: 过滤条件

        Returns:
            List[Document]: 搜索结果文档列表
        """
        if self.vector_store is None:
            print("错误: 向量存储尚未创建")
            return []

        try:

            if filtration:
                results = self.vector_store.similarity_search(query, k=k, filter=filtration)
            else:
                results = self.vector_store.similarity_search(query, k=k)

            # 查看知识库父子信息标记情况
            if self.knowledge_base_index.get(self.knowledge_name):  # 默认为false， 如果为true，则是父子分割，获取父子分割索引

                # 根据小块索引获取对应的大文档id
                enhanced_results = []
                index_show = []
                for result in results:

                    small_chunk_index = result.id
                    if small_chunk_index is not None and str(small_chunk_index) in self.small_to_large_mapping:
                        large_chunk_index = self.small_to_large_mapping[str(small_chunk_index)]
                        # 根据大文档id获取文档
                        enhanced_results.append(self.get_document_by_id(large_chunk_index))

                        index_show.append(large_chunk_index)
                # print(f"小块索引对应的大块索引为 {index_show}")

                return enhanced_results
            else:
                return results

        except Exception as e:
            print(f"搜索时出错: {str(e)}")
            return []

    def enhanced_similarity_search(self, query: str, results_documents: List[Document], k: int = 4) -> Tuple[
        str, List[int], List[float], List[Document]]:
        """
        执行增强的相似度搜索，结合重排模型

        Args:
            :param query: 查询文本
            :param results_documents: embeddings模型返回的文档列表
            :param k: 返回结果数量
        Returns:
            List[Document]: 增强后的搜索结果
        """

        # 提取文档内容为字符串列表
        document_texts = [doc.page_content for doc in results_documents]

        # 调用 rerank 方法（注意参数格式）
        result = self.rerank_model.rerank(query=query, documents=document_texts, top_n=4)

        id_str = result['id']
        index = [item['index'] for item in result["results"]]
        relevance_scores = [item['relevance_score'] for item in result["results"]]
        documents = [results_documents[item['index']] for item in result["results"]]

        return id_str, index, relevance_scores, documents

    def _process_data(self, file_list, split_type):
        """
        处理数据并更新向量存储

        Args:
            file_list: 文件列表,一个或多个
            split_type: 分割类型
        """

        for file_path in tqdm.tqdm(file_list):
            print(f"正在处理: {file_path}")

            if split_type == 'parent_child':
                smaller_documents_list, larger_documents_list, parent_vector_store, small_to_large_mapping = process_document(
                    file_path, self.embeddings_model, split_type
                )
                if small_to_large_mapping is not None:
                    self.small_to_large_mapping.update(small_to_large_mapping)  # 更新父子映射字典
                else:
                    print(f"small_to_large_mapping 为 None，处理 {file_path} 失败")
                    continue

                if self.vector_store is None:
                    self.vector_store = parent_vector_store
                else:
                    # 合并向量存储
                    self.vector_store.merge_from(parent_vector_store)
                    print(f"合并向量库成功！: {file_path}")

            else:
                documents = process_document(file_path, self.embeddings_model)
                if documents is None:
                    print(f"处理 {file_path} 失败，未获取到文档")
                    continue

                if self.vector_store is None:
                    self.vector_store = FAISS.from_documents(documents, self.embeddings_model)
                else:
                    self.vector_store.add_documents(documents)
                print(f"创建向量库成功！: {file_path}")

    def init_data(self, data_dir, split_type='simple'):
        """
        data_dir: 要处理的数据路径，可以是文件或目录
        处理数据存入向量数据库
        """
        if os.path.isfile(data_dir):  # 判断是否为文件
            file_list = [data_dir]
        elif os.path.isdir(data_dir):  # 判断是否为目录
            file_list = [os.path.join(data_dir, file_name) for file_name in os.listdir(data_dir)]
        else:
            print(f"路径 {data_dir} 无效")
            return

        final_save_path = os.path.join(VECTOR_SAVE_PATH, self.knowledge_name)  # 存储向量
        check_and_create_dir(final_save_path)

        self._process_data(file_list, split_type)

        if self.vector_store:
            self.save(final_save_path)  # 保存合并后的向量库
            print(f"保存向量成功！, 保存向量数量：{len(list(self.vector_store.index_to_docstore_id.values()))} ")
        print("\n所有文件处理完成！")


if __name__ == '__main__':


    # file_path = "C:/Users/16000/Desktop/ww.docx"
    # file_path = "C:/Users/16000/Desktop/ww.txt"
    # file_path = "C:/Users/16000/Desktop/ww.md"
    # file_path = "C:/Users/16000/Desktop/ww.pdf"
    # file_path = "C:/Users/16000/Desktop/temp_maintenance_proposal.xlsx"
    # file_path = "C:/Users/16000/Desktop/test.xml"

    file_path = "E:/python_project/D_large_models/RAG_SERVER/data/bids_data"

    knowledge_name = "bid_tender"

    knowledge_load_path = os.path.join(VECTOR_SAVE_PATH, knowledge_name)

    fa = FAISSCUSTOM(
        max_tokens=LLM_CONFIG["max_tokens"], temperature=LLM_CONFIG["temperature"],
        embedding_client=None, knowledge_name=knowledge_name,
    )
    # fa.load(knowledge_save_path, allow_dangerous=True)  # 用于加载数据库和父子映射
    # results_doc = fa.similarity_search("软件功能要求是什么？")
    # print(results_doc)

    fa.init_data(file_path, split_type='parent_child')
