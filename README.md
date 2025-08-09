# RAG服务器 - 企业级检索增强生成系统

[![Python](https://img.shields.io/badge/Python-3.8+-blue.svg)](https://python.org)
[![FastAPI](https://img.shields.io/badge/FastAPI-Latest-green.svg)](https://fastapi.tiangolo.com/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

这是一个基于FastAPI构建的企业级检索增强生成(RAG)系统，集成了多种AI模型和向量数据库，专门用于处理招投标文档、代码质量分析、软件测试等企业级应用场景。

## 🚀 主要特性

### 核心功能
- **智能检索增强生成**: 基于FAISS向量数据库的高效语义搜索
- **多模型支持**: 集成DeepSeek、Qwen等多种大语言模型
- **流式对话**: 支持实时流式响应和上下文对话
- **知识库管理**: 支持多知识库动态切换和管理

### 专业应用场景
- **招投标分析**: 智能解析招投标文档，提供价格一致性分析
- **代码质量检测**: 集成QAC代码质量分析系统
- **单元测试生成**: 基于Tessy的C代码单元测试自动生成
- **文档处理**: 支持Word、PDF、Excel、XML等多种文档格式

### 技术特色
- **图数据库**: 集成Neo4j支持复杂关系查询
- **向量检索**: 基于BGE-M3的高精度向量检索
- **重排序优化**: 集成BGE-Reranker提升检索准确性
- **工作流集成**: 支持Dify工作流自动化处理

## 📋 目录结构

```
RAG_SERVER/
├── 📁 _faiss/                    # FAISS向量存储模块
│   ├── custom_faiss.py           # 自定义FAISS封装
│   ├── data2faiss.py            # 数据预处理和向量化
│   └── index_manager.py         # 索引管理器
├── 📁 _neo4j/                   # Neo4j图数据库模块
│   ├── custom_neo4j.py          # Neo4j连接和操作
│   └── xml2csv.py              # XML数据转换
├── 📁 data/                     # 数据存储目录
│   ├── bids_data/               # 招投标文档
│   ├── qac_data/               # QAC分析数据
│   └── xml_data/               # XML结构化数据
├── 📁 test_software_platform/   # 软件测试平台
│   ├── QAC/                    # 代码质量分析
│   └── Tessy/                  # 单元测试生成
├── 📁 vector_store/            # 向量数据库存储
├── 📁 prompt/                  # 提示词模板
├── 📁 file_utils/              # 文件处理工具
├── rag_api.py                  # 主要API服务
├── chat_rag.py                 # 聊天机器人核心
├── config.py                   # 配置文件
└── llm_init.py                 # LLM初始化
```

## ⚙️ 系统要求

### 基础环境
- Python 3.8+
- 内存: 最少8GB，推荐16GB+
- 存储: 最少50GB可用空间

### 依赖服务
- **LLM服务**: vLLM/Xinference服务器 (端口8010/9997)
- **向量模型**: BGE-M3 embeddings服务 (端口9010)
- **图数据库**: Neo4j (端口7687)
- **MySQL数据库**: (端口3306)

## 🛠️ 安装配置

### 1. 克隆项目
```bash
git clone <repository-url>
cd RAG_SERVER
```

### 2. 安装依赖
```bash
pip install fastapi uvicorn
pip install langchain langchain-openai langchain-community
pip install faiss-cpu pandas numpy
pip install py2neo pymysql
pip install python-docx openpyxl
pip install xinference-client
pip install pydantic sqlparse tqdm
```

### 3. 配置文件
编辑 `config.py` 文件，配置相关服务地址：

```python
# LLM模型配置
LLM_CONFIG = {
    "chat_url": "http://10.1.5.196:8010/v1",      # vLLM服务地址
    "embedding_url": "http://10.1.5.196:9010/v1", # 向量模型地址
    "xin_url": "http://10.1.5.196:9997",          # Xinference地址
    "api_key": "token_abc123",
    "chat_model_name": "DeepSeek-R1-Distill-Qwen-32b",
    "embeddings_model_name": "custom-bge-m3",
    "rerank_model_name": "custom-bge-reranker-large"
}

# Neo4j配置
NEO4J_CONFIG = {
    "url": "bolt://10.1.5.196:7687",
    "username": "neo4j",
    "password": "123456789"
}

# MySQL配置
MYSQL_CONFIG = {
    "host": "10.1.5.196",
    "port": 3306,
    "user": "root",
    "password": "123456",
    "database": "filesystem"
}
```

### 4. 初始化向量数据库
```bash
# 创建知识库索引
python _faiss/data2faiss.py

# 构建Neo4j图数据库
python _neo4j/neo4j_create.py
```

## 🚀 启动服务

### 主RAG服务
```bash
python rag_api.py
# 服务将在 http://localhost:9800 启动
```

### 招投标分析服务
```bash
python bid_api.py
# 服务将在 http://localhost:8080 启动
```

### QAC代码质量分析服务
```bash
cd test_software_platform/QAC
python qac_api.py
# 服务将在配置的端口启动
```

## 📖 API 使用指南

### 1. 聊天对话接口

**接口**: `POST /chat`

**请求示例**:
```json
{
  "messages": [
    {
      "role": "user",
      "content": "请帮我分析这个招投标项目的技术方案"
    }
  ],
  "model": "DeepSeek-R1-Distill-Qwen-32b",
  "stream": true,
  "knowledgeName": "bid_tender"
}
```

**响应格式**:
```json
{
  "id": "chat-123",
  "object": "chat.completion",
  "created": 1234567890,
  "model": "DeepSeek-R1-Distill-Qwen-32b",
  "choices": [
    {
      "delta": {
        "role": "assistant",
        "content": "根据您提供的招投标文档..."
      },
      "finish_reason": null
    }
  ],
  "usage": {
    "prompt_tokens": 150,
    "completion_tokens": 200,
    "total_tokens": 350
  }
}
```

### 2. 文档上传和分析

**接口**: `POST /upload_and_analysis`

```bash
curl -X POST "http://localhost:8080/upload_and_analysis" \
  -F "file=@document.docx" \
  -F "requirement=价格分析"
```

### 3. 健康检查

**接口**: `GET /health`

```bash
curl http://localhost:9800/health
```

## 🔧 知识库管理

### 支持的知识库类型

| 知识库名称 | 数据类型 | 用途 |
|------------|----------|------|
| `bid_tender` | 招投标文档 | 投标分析和价格评估 |
| `safeguard` | 保障数据 | 安全防护知识 |
| `maintenance_proposal` | 维修方案 | 设备维护指导 |
| `qac` | 代码质量 | QAC规则和建议 |
| `xml_data` | 结构化数据 | 系统配置和关系 |

### 知识库切换
```python
# 通过API参数指定知识库
{
  "knowledgeName": "bid_tender",  # 指定使用招投标知识库
  "messages": [...]
}
```

## 🔍 高级功能

### 1. 图查询增强
系统支持基于Neo4j的复杂关系查询，特别适用于XML结构化数据：

```python
# 自动识别查询类型并调用图数据库
query = "查询项目A的所有子组件关系"
# 系统将自动：
# 1. 解析查询意图
# 2. 调用Neo4j查询相关节点
# 3. 结合向量检索提供完整答案
```

### 2. 重排序优化
集成BGE-Reranker对检索结果进行重新排序：

```python
# 检索结果自动重排序
relevant_docs = faiss.similarity_search(query, k=8)
reranked_docs = faiss.enhanced_similarity_search(query, relevant_docs, k=4)
```

### 3. 多文档格式支持
- **Word文档**: 自动提取标题、段落、表格
- **PDF文件**: OCR文本识别和结构分析
- **Excel表格**: 键值对和表格数据处理
- **XML文件**: 层次结构解析和关系提取

### 4. 代码质量分析
QAC集成模块提供：
- C/C++代码静态分析
- MISRA规则检查
- 代码质量评分
- 修复建议生成

## 🧪 测试和开发

### 运行测试
```bash
# 基础功能测试
python test_file/api_call_test.py

# FAISS向量检索测试
python test_file/faiss_test.py

# QAC系统测试
cd test_software_platform/QAC
python test_qac_system.py
```

### 开发环境
```bash
# 开启开发模式（热重载）
python rag_api.py
# 或
uvicorn rag_api:app --reload --host 0.0.0.0 --port 9800
```

## 📊 性能优化

### 向量检索优化
- 使用FAISS IVF索引提升检索速度
- 实现小到大块映射减少存储开销
- 支持增量索引更新

### 内存管理
- 模型懒加载减少内存占用
- 向量索引分片存储
- 自动垃圾回收机制

### 并发处理
- FastAPI异步处理
- 连接池管理数据库连接
- 流式响应降低延迟

## 🛡️ 安全考虑

- API密钥认证机制
- 输入参数验证和清理
- 文件上传安全检查
- 数据库连接加密

## 🔧 故障排除

### 常见问题

1. **服务无法启动**
   ```bash
   # 检查端口占用
   netstat -ano | findstr :9800
   
   # 检查配置文件
   python -c "from config import LLM_CONFIG; print(LLM_CONFIG)"
   ```

2. **向量检索失败**
   ```bash
   # 检查向量库是否存在
   ls vector_store/
   
   # 重建向量索引
   python _faiss/data2faiss.py
   ```

3. **Neo4j连接失败**
   ```bash
   # 检查Neo4j服务状态
   curl http://10.1.5.196:7474
   
   # 测试连接
   python -c "from _neo4j.custom_neo4j import Neo4jHandler; h=Neo4jHandler('bolt://10.1.5.196:7687', 'neo4j', '123456789')"
   ```

### 日志配置
```python
import logging
logging.basicConfig(level=logging.INFO)
```

## 📝 更新日志

### v1.0.0 (当前版本)
- ✅ 基础RAG功能实现
- ✅ 多知识库支持
- ✅ 招投标分析模块
- ✅ QAC代码质量分析
- ✅ Neo4j图数据库集成
- ✅ 流式对话支持

### 计划功能
- 🔄 多语言支持
- 🔄 用户权限管理
- 🔄 知识库可视化管理
- 🔄 批量文档处理
- 🔄 API访问统计

## 🤝 贡献指南

1. Fork 项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 📄 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 📞 支持与联系

- 📧 邮箱: [your-email@example.com]
- 🐛 问题反馈: [GitHub Issues](https://github.com/your-repo/issues)
- 📖 文档: [项目Wiki](https://github.com/your-repo/wiki)

---

## 🙏 致谢

感谢以下开源项目的支持：
- [FastAPI](https://fastapi.tiangolo.com/) - 现代Python Web框架
- [LangChain](https://langchain.com/) - LLM应用开发框架
- [FAISS](https://faiss.ai/) - 向量相似性搜索
- [Neo4j](https://neo4j.com/) - 图数据库
- [DeepSeek](https://deepseek.com/) - 大语言模型

---

*最后更新: 2025年1月20日*
