"""
优化后的FAISS向量库使用示例
展示各种功能的使用方法
"""
import os
from pathlib import Path
from custom_faiss_optimized import FAISSManager, FAISSConfig, SearchConfig, SearchType, SplitType
from data2faiss_optimized import DocumentManager, SplitConfig

# 配置路径
VECTOR_SAVE_PATH = "../vector_store"
DATA_PATH = "../data/bids_data"


def example_basic_usage():
    """基础使用示例"""
    print("=== 基础使用示例 ===\n")
    
    # 1. 创建FAISS管理器
    manager = FAISSManager(
        knowledge_name="example_knowledge",
        config=FAISSConfig(
            max_tokens=4096,
            temperature=0.7,
            batch_size=50,
            enable_cache=True
        )
    )
    
    # 2. 创建向量存储（单个文件）
    file_path = "../data/bids_data/PHM机载系统综合监控与处理样机技术方案.docx"
    success = manager.create_vector_store(file_path, SplitType.SIMPLE)
    print(f"创建向量存储: {'成功' if success else '失败'}")
    
    # 3. 保存向量存储
    if success:
        manager.save()
        print("向量存储已保存")
    
    # 4. 加载向量存储
    manager2 = FAISSManager(knowledge_name="example_knowledge")
    loaded = manager2.load(allow_dangerous=True)
    print(f"加载向量存储: {'成功' if loaded else '失败'}")
    
    # 5. 搜索
    if loaded:
        results = manager2.similarity_search("系统功能", SearchConfig(k=3))
        print(f"搜索结果: 找到 {len(results)} 个相关文档")


def example_advanced_splitting():
    """高级切分示例"""
    print("\n=== 高级切分示例 ===\n")
    
    # 创建文档管理器
    doc_manager = DocumentManager(
        config=SplitConfig(
            chunk_size=300,
            chunk_overlap=50,
            semantic_threshold=0.8
        )
    )
    
    file_path = "../data/bids_data/PHM系统平台整体设计方案_20240611.docx"
    
    # 1. 简单切分
    print("1. 简单切分:")
    simple_docs = doc_manager.process_document(file_path, SplitType.SIMPLE)
    print(f"   文档数: {len(simple_docs)}")
    
    # 2. 递归切分
    print("\n2. 递归切分:")
    recursive_docs = doc_manager.process_document(file_path, SplitType.RECURSION)
    print(f"   块数: {len(recursive_docs)}")
    
    # 3. 语义切分
    print("\n3. 语义切分:")
    semantic_docs = doc_manager.process_document(file_path, SplitType.SEMANTIC)
    print(f"   语义段落数: {len(semantic_docs)}")
    
    # 4. 父子切分
    print("\n4. 父子切分:")
    result = doc_manager.process_document(file_path, SplitType.PARENT_CHILD)
    if isinstance(result, tuple):
        small, large, store, mapping = result
        print(f"   小块数: {len(small)}")
        print(f"   大块数: {len(large)}")
        print(f"   映射关系数: {len(mapping)}")


def example_batch_processing():
    """批量处理示例"""
    print("\n=== 批量处理示例 ===\n")
    
    # 创建管理器
    manager = FAISSManager(
        knowledge_name="batch_example",
        config=FAISSConfig(batch_size=100)
    )
    
    # 从目录初始化
    success = manager.init_from_directory(
        DATA_PATH,
        split_type=SplitType.PARENT_CHILD,
        extensions=['.docx', '.pdf', '.txt'],
        recursive=True
    )
    
    if success:
        # 获取统计信息
        stats = manager.get_statistics()
        print("向量库统计信息:")
        print(f"  文档总数: {stats['document_count']}")
        print(f"  父子映射: {stats['has_parent_child_mapping']}")
        print(f"  映射数量: {stats['mapping_count']}")


def example_enhanced_search():
    """增强搜索示例"""
    print("\n=== 增强搜索示例 ===\n")
    
    # 创建并加载管理器
    manager = FAISSManager(knowledge_name="search_example")
    
    # 假设已有向量存储
    if manager.load(allow_dangerous=True):
        query = "健康管理系统的主要功能"
        
        # 1. 普通相似度搜索
        print("1. 普通相似度搜索:")
        docs = manager.similarity_search(query, SearchConfig(k=5))
        print(f"   找到 {len(docs)} 个结果")
        
        # 2. MMR搜索（最大边际相关性）
        print("\n2. MMR搜索:")
        mmr_docs = manager.mmr_search(
            query,
            SearchConfig(k=5, fetch_k=20, lambda_mult=0.5)
        )
        print(f"   找到 {len(mmr_docs)} 个结果")
        
        # 3. 增强搜索（带重排序）
        print("\n3. 增强搜索（带重排序）:")
        enhanced_docs, scores = manager.enhanced_search(
            query,
            search_type=SearchType.SIMILARITY,
            config=SearchConfig(k=5),
            use_rerank=True
        )
        print(f"   找到 {len(enhanced_docs)} 个结果")
        for i, (doc, score) in enumerate(zip(enhanced_docs[:3], scores[:3])):
            print(f"   结果{i+1} (分数: {score:.3f}): {doc.page_content[:50]}...")


def example_filter_search():
    """过滤搜索示例"""
    print("\n=== 过滤搜索示例 ===\n")
    
    manager = FAISSManager(knowledge_name="filter_example")
    
    if manager.load(allow_dangerous=True):
        # 使用元数据过滤
        filter_dict = {
            "file_path": "../data/bids_data/PHM系统平台整体设计方案_20240611.docx"
        }
        
        results = manager.similarity_search(
            "系统架构",
            config=SearchConfig(k=3),
            filter_dict=filter_dict
        )
        
        print(f"过滤搜索结果: {len(results)} 个")
        for i, doc in enumerate(results):
            print(f"  结果{i+1}: 来自 {doc.metadata.get('file_path', 'unknown')}")


def example_custom_processing():
    """自定义处理示例"""
    print("\n=== 自定义处理示例 ===\n")
    
    from langchain_core.documents import Document
    
    # 创建管理器
    manager = FAISSManager(knowledge_name="custom_example")
    
    # 创建自定义文档
    custom_docs = [
        Document(
            page_content="这是第一个自定义文档的内容",
            metadata={"source": "custom", "category": "test", "id": 1}
        ),
        Document(
            page_content="这是第二个自定义文档的内容",
            metadata={"source": "custom", "category": "test", "id": 2}
        ),
        Document(
            page_content="这是第三个自定义文档的内容",
            metadata={"source": "custom", "category": "demo", "id": 3}
        )
    ]
    
    # 创建向量存储
    manager.vector_store = manager.embeddings_model.from_documents(
        custom_docs,
        manager.embeddings_model
    )
    
    # 添加更多文档
    more_docs = [
        Document(
            page_content="追加的文档内容",
            metadata={"source": "append", "category": "test", "id": 4}
        )
    ]
    
    success = manager.add_documents(more_docs)
    print(f"添加文档: {'成功' if success else '失败'}")
    
    # 保存
    if success:
        manager.save()
        print("自定义向量库已保存")


def example_performance_optimization():
    """性能优化示例"""
    print("\n=== 性能优化示例 ===\n")
    
    import time
    
    # 1. 启用缓存的管理器
    manager_with_cache = FAISSManager(
        knowledge_name="perf_with_cache",
        config=FAISSConfig(
            enable_cache=True,
            cache_size=1000,
            batch_size=200
        )
    )
    
    # 2. 不启用缓存的管理器
    manager_no_cache = FAISSManager(
        knowledge_name="perf_no_cache",
        config=FAISSConfig(
            enable_cache=False,
            batch_size=200
        )
    )
    
    # 假设都已加载数据
    query = "系统性能优化方案"
    
    # 测试缓存效果
    if manager_with_cache.load(allow_dangerous=True):
        # 第一次搜索
        start = time.time()
        results1 = manager_with_cache.similarity_search(query)
        time1 = time.time() - start
        
        # 第二次搜索（应该从缓存获取）
        start = time.time()
        results2 = manager_with_cache.similarity_search(query)
        time2 = time.time() - start
        
        print(f"启用缓存:")
        print(f"  第一次搜索: {time1:.3f}秒")
        print(f"  第二次搜索: {time2:.3f}秒 (从缓存)")
        print(f"  加速比: {time1/time2:.1f}x")


def example_backward_compatibility():
    """向后兼容示例"""
    print("\n=== 向后兼容示例 ===\n")
    
    from custom_faiss_optimized import FAISSCUSTOM
    
    # 使用旧的类名和接口
    old_style = FAISSCUSTOM(
        max_tokens=4096,
        temperature=0.7,
        knowledge_name="old_style_example"
    )
    
    # 使用旧的方法
    file_path = "../data/bids_data/PHM系统平台整体设计方案_20240611.docx"
    success = old_style.create_vector(file_path, ".docx", "simple")
    print(f"旧接口创建向量: {'成功' if success else '失败'}")
    
    # 使用旧的初始化方法
    old_style.init_data(DATA_PATH, split_type='parent_child')
    print("旧接口批量处理完成")


if __name__ == "__main__":
    # 运行示例
    examples = [
        ("基础使用", example_basic_usage),
        ("高级切分", example_advanced_splitting),
        ("批量处理", example_batch_processing),
        ("增强搜索", example_enhanced_search),
        ("过滤搜索", example_filter_search),
        ("自定义处理", example_custom_processing),
        ("性能优化", example_performance_optimization),
        ("向后兼容", example_backward_compatibility)
    ]
    
    print("FAISS向量库优化版本使用示例\n")
    print("可用示例:")
    for i, (name, _) in enumerate(examples):
        print(f"{i+1}. {name}")
    
    # 选择要运行的示例
    choice = input("\n请选择要运行的示例 (1-8, 或 'all' 运行全部): ")
    
    if choice.lower() == 'all':
        for name, func in examples:
            print(f"\n{'='*50}")
            func()
    else:
        try:
            idx = int(choice) - 1
            if 0 <= idx < len(examples):
                examples[idx][1]()
            else:
                print("无效的选择")
        except ValueError:
            print("请输入数字或 'all'")