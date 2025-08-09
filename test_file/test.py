from xinference.client import Client
from langchain_core.documents import Document
from config import LLM_CONFIG
# 初始化客户端
client = Client(LLM_CONFIG['xin_url'])
model_uid = LLM_CONFIG['rerank_model_name']  # 替换为你实际的 model_uid
rerank_model = client.get_model(model_uid)

# 示例文档列表
docs = [
    Document(page_content="人工智能是一种模拟人类智能的技术。"),
    Document(page_content="机器学习是人工智能的一个子领域。"),
    Document(page_content="深度学习是基于神经网络的方法。"),
    Document(page_content="Python 是一种广泛使用的编程语言。")
]

query = "什么是人工智能？"

# 提取文档内容为字符串列表
document_texts = [doc.page_content for doc in docs]

# 调用 rerank 方法（注意参数格式）
result = rerank_model.rerank(query=query, documents=document_texts, top_n=4)

# 输出结果
for i, item in enumerate(result["results"]):
    print(f"Rank {i+1}: Index={item['index']}, Score={item['relevance_score']}")
    print(document_texts[item['index']])
    print("-" * 50)