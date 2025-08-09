import os
# pd.set_option('display.max_rows', 200)  # 最大显示行数
# pd.set_option('display.max_columns', 50)  # 最大显示列数
# pd.set_option('display.width', 1000)  # 显示宽度
# pd.set_option('display.max_colwidth', 200)  # 每列最大宽度

DIFY_API = "http://10.1.5.196:8050/v1"
SERVE_ADDRESS = "http://10.1.5.196:8050"

PROJECT_PATH = 'E:/python_project/D_large_models/RAG_SERVER'
# PROJECT_PATH = "/home/yftest/llm_project/RAG_SERVER"


# LLM模型配置
LLM_CONFIG = {
    "chat_url": "http://10.1.5.196:8010/v1",
    "embedding_url": "http://10.1.5.196:9010/v1",
    "xin_url": "http://10.1.5.196:9997",
    "api_key": "token_abc123",

    # "model_name": "Qwen3-32b",
    "chat_model_name": "DeepSeek-R1-Distill-Qwen-32b",
    # "chat_model_name": "DeepSeek-R1-Distill-Qwen-14b",
    # "chat_model_name": "deepseek-r1:14b",
    # "model_name": "Qwen2.5-7b-Instruct",
    "embeddings_model_name": "custom-bge-m3",
    "rerank_model_name": "custom-bge-reranker-large",

    "temperature": 0.7,
    "max_tokens": 4096
}

OLLAMA_CONFIG = {
    "base_url": "http://0.0.0.0:11434",
    "model": "deepseek-r1:14b",
}

NEO4J_CONFIG = {
    # "url": "bolt://localhost:7687",
    "url": "bolt://10.1.5.196:7687",
    "username": "neo4j",
    "password": "123456789",
}


MYSQL_CONFIG = {
    "host": "10.1.5.196",
    "port": 3306,
    "user": "root",
    "password": "123456",
    "database": "filesystem",
}
# RAG检索配置
ORGIN_DATA_PATH = os.path.join(PROJECT_PATH, "qac_data")  # 数据路径
RAG_CONFIG = {
    "safeguard": os.path.join(ORGIN_DATA_PATH, "safeguard"),  # 保障数据
    "maintenance_proposal": os.path.join(ORGIN_DATA_PATH, "maintenance_proposal"),  # 维修数据
    "xml": os.path.join(ORGIN_DATA_PATH, "xml_data"),  # xml关系
    "sql": os.path.join(ORGIN_DATA_PATH, "sql_data"),  # text2sql
    "bids": os.path.join(ORGIN_DATA_PATH, "bids_data"),  # 招投标
}


VECTOR_SAVE_PATH = os.path.join(PROJECT_PATH, "vector_store")  # 向量路径
# 索引文件路径
INDEX_FILE_PATH = os.path.join(VECTOR_SAVE_PATH, "knowledge_repository_and_flag.json")
VECTOR_CONFIG = {
    "top_k": 8,  # 检索文档数量
    "safeguard": os.path.join(VECTOR_SAVE_PATH, "safeguard"),  # 保障数据
    "maintenance_proposal": os.path.join(VECTOR_SAVE_PATH, "maintenance_proposal"),  # 维修维护数据
}

# API服务配置
API_CONFIG = {
    "host": "0.0.0.0",
    "port": 8000,
    "reload": True  # 是否启用热重载
}

PROMPT_PATH = os.path.join(PROJECT_PATH, "prompt")  # 模板路径
SYSTEM_PROMPT_PATH = os.path.join(PROMPT_PATH, 'system_prompt.json')
XML_PROMPT_PATH = os.path.join(PROMPT_PATH, 'xml_prompt.json')
NEO4J_PROMPT_PATH = os.path.join(PROMPT_PATH, 'neo4j_prompt.json')

