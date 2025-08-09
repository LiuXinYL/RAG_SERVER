from langchain_community.vectorstores import FAISS
from langchain.text_splitter import CharacterTextSplitter
from langchain_community.document_loaders import TextLoader

from llm_init import LLM_INIT


loader = TextLoader("E:/XJXXKJ/LLM大模型/XML_RAG/小明.txt", encoding='utf-8')
documents = loader.load()

text_splitter = CharacterTextSplitter(chunk_size=1000, chunk_overlap=0)

docs = text_splitter.split_documents(documents)

embeddings = LLM_INIT(4096, 0.7).create_embedding_client()

db = FAISS.from_documents(docs, embeddings)

db.save_local(r"C:/Users/16000/Desktop/faiss_vector_test")  # 不能有中文路径
