import os
import sys
from langchain_core.messages import HumanMessage, SystemMessage
from langchain_openai import ChatOpenAI, OpenAIEmbeddings
from langchain_ollama import OllamaLLM
from langchain_community.embeddings import XinferenceEmbeddings
from langchain_community.llms import Xinference
from xinference.client import Client
current_dir = os.path.abspath(os.path.dirname(__file__))
sys.path.append(current_dir)  # 添加到 sys.path

from config import LLM_CONFIG, OLLAMA_CONFIG

class LLM_INIT:

    def __init__(self, max_tokens=4096, temperature=0.7):
        self.max_tokens = max_tokens
        self.temperature = temperature

    def create_chat_client(self, ):
        """
        创建LLM客户端实例
        """
        # llm = ChatOpenAI(
        #     openai_api_base=LLM_CONFIG["chat_url"],
        #
        #     model=LLM_CONFIG["chat_model_name"],
        #     openai_api_key=LLM_CONFIG["api_key"],
        #
        #     temperature=self.temperature,
        #     max_tokens=self.max_tokens,
        #
        #     streaming=True,
        # )
        #

        llm = Xinference(
            server_url=LLM_CONFIG['xin_url'],
            model_uid=LLM_CONFIG["chat_model_name"],
            temperature=self.temperature,
            max_tokens=self.max_tokens,
            streaming=True,
        )

        return llm

    def create_embeddings_client(self,):
        """
        创建Embedding客户端实例
        """
        # embeddings = OpenAIEmbeddings(
        #     openai_api_base=LLM_CONFIG['embedding_url'],
        #     model=LLM_CONFIG["embeddings_model_name"],
        #     openai_api_key=LLM_CONFIG["api_key"],
        # )

        embeddings = XinferenceEmbeddings(
            server_url=LLM_CONFIG['xin_url'],
            model_uid=LLM_CONFIG["embeddings_model_name"]

        )

        return embeddings

    def create_rerank_client(self, ):
        """
        创建Embedding客户端实例
        """
        client = Client(LLM_CONFIG['xin_url'])
        model_uid = LLM_CONFIG['rerank_model_name']  # 替换为你实际的 model_uid
        rerank_model = client.get_model(model_uid)

        return rerank_model

    def create_ollama_client(self, ):

        llm = OllamaLLM(
            base_url="http://localhost:11434",  # 本地服务地址（默认可不改）
            model=LLM_CONFIG["chat_model_name"],
            temperature=self.temperature,
            num_ctx=self.max_tokens
        )

        return llm

    def llm_server(self,):

        chat_model = self.create_chat_client()
        embed_model = self.create_embeddings_client()
        # ollama_model = self.create_ollama_client()
        return chat_model, embed_model


    def llm_streaming(self, ):

        messages = [
            SystemMessage(content="你是一位AI助理"),
            HumanMessage(content="你是谁")
        ]

        # 流式调用
        chunks = []
        for chunk in self.create_chat_client().stream(messages):
            chunks.append(chunk)
            # print(chunk.content, end="", flush=True)
            yield chunk.content


if __name__ == '__main__':

    llm_client = LLM_INIT()
    rerank_model1 = llm_client.create_rerank_client()
    print(rerank_model1)
