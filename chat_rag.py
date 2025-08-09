import json
import os
import sys
import time
from string import Template
from typing import List, Optional

from fastapi import HTTPException
from langchain_core.documents import Document
from langchain_core.messages import HumanMessage, SystemMessage

from _faiss.custom_faiss import FAISSCUSTOM
from _neo4j.custom_neo4j import Neo4jHandler
from config import (
    VECTOR_CONFIG, NEO4J_CONFIG, LLM_CONFIG,
    SYSTEM_PROMPT_PATH, XML_PROMPT_PATH, NEO4J_PROMPT_PATH, VECTOR_SAVE_PATH
)
from llm_init import LLM_INIT
from prompt.prompt_init import show_prompt

# 获取当前项目目录的绝对路径
current_dir = os.path.abspath(os.path.dirname(__file__))
# 添加到 sys.path
sys.path.append(current_dir)


class ChatBot:
    """基于RAG的交互式聊天机器人"""

    def __init__(self, knowledge_name: str = None, model_name_flag: Optional[str] = 'base',
                 roles=None, max_tokens=LLM_CONFIG["max_tokens"], temperature=LLM_CONFIG["temperature"]):
        """
        初始化聊天机器人

        Args:
            vector_store_name: 向量存储路径，如果不提供则使用配置文件中的路径
        """

        self.model_name_flag = model_name_flag
        # 初始化LLM
        self.llm = LLM_INIT(max_tokens, temperature).create_chat_client()
        # self.llm = LLM_INIT(max_tokens, temperature).create_ollama_client()

        # 初始化faiss检索
        self.faiss = FAISSCUSTOM(max_tokens, temperature, knowledge_name=knowledge_name)

        print('vector_store_name', knowledge_name)
        if knowledge_name is not None:
            # 验证 vector_store_name 是否在知识库索引中
            if self.faiss.knowledge_base_index.get(knowledge_name) is None:
                raise HTTPException(
                    status_code=400,
                    detail=f"未找到名为 {knowledge_name} 的知识库，请检查名称是否正确。"
                )

            self.vector_store_path = os.path.join(VECTOR_SAVE_PATH, knowledge_name)

            self.faiss.load(self.vector_store_path, allow_dangerous=True)  # 用于加载数据库和父子映射

        self.SYSTEM_PROMPT = show_prompt(SYSTEM_PROMPT_PATH)
        self.XML_PROMPT = show_prompt(XML_PROMPT_PATH)
        self.NEO4J_PROMPT = show_prompt(NEO4J_PROMPT_PATH)

        if roles is not None:
            self.roles = roles
        # 对话历史
        self.chat_history = []

    def chat_prompt(self, query: str, context: List[Document] = None, nodes_relations_dict=None,
                    node_dict_list=None) -> List[SystemMessage | HumanMessage]:
        """
        生成带有上下文的提示

        Args:
            :param query:
            :param context:
            :param nodes_relations_dict:
            :param node_dict_list: 用于xml文件的节点信息
        Returns:
            List[SystemMessage | HumanMessage]: 消息列表
        """

        if self.model_name_flag == 'base':
            system_cont = self.roles['system']

        # elif self.model_name_flag == LLM_CONFIG['chat_model_name']:
        #     system_cont = self.roles['system']

        elif self.model_name_flag == 'xml':
            system_cont = Template(self.XML_PROMPT).substitute(
                user_info=nodes_relations_dict, neo4j_info=node_dict_list
            )

        else:
            # 将检索结果组合成上下文
            context_text = "\n\n".join([doc.page_content for doc in context])
            system_cont = self.SYSTEM_PROMPT.format(context_text)

        prompt = [
            SystemMessage(content=system_cont),
            HumanMessage(content=query),

        ]

        return prompt

    def base_message_prompt(self, query: str) -> List[SystemMessage | HumanMessage]:

        messages = [
            SystemMessage(content=self.NEO4J_PROMPT),
            HumanMessage(content=query)
        ]

        return messages

    def xml_relations_nodes(self, prompt: List[SystemMessage | HumanMessage]):

        node_list_str = self.llm.invoke(prompt).content

        if "</think>" in node_list_str:
            # 以 `</think>` 分割，取后半部分
            json_part = node_list_str.split("</think>", 1)[1].strip()
            # 进一步去除可能的 ```json 和 ``` 标记（如果存在）
            json_part = "\n".join([line for line in json_part.split("\n") if line.strip() and "```" not in line])

            # 将修正后的字符串转换为Python列表
            node_dict_list = json.loads(json_part)
        else:
            node_dict_list = json.loads(node_list_str)

        node_xml = node_dict_list[-1]

        start = time.time()
        # 初始化neo4j连接
        Handler = Neo4jHandler(NEO4J_CONFIG['url'], NEO4J_CONFIG['username'], NEO4J_CONFIG['password'])

        # 检查 Neo4j 连接是否成功
        if Handler.graph is None:
            raise HTTPException(
                status_code=500,
                detail="无法连接到 Neo4j 服务，请检查配置或服务状态。"
            )
        print('end1', time.time() - start)
        nodes_list = Handler.get_all_parent_nodes(node_xml['user_type'])
        print('end2', time.time() - start)

        relations_dict_list = []
        for curr_node in nodes_list:
            node_info = {
                'node_labels': curr_node['name'],
                'node_type': curr_node['labels'],
                'node_xml': curr_node['xml']
            }
            relations_dict_list.append(node_info)

        return relations_dict_list, node_dict_list

    def chat(self, query: str, stream: bool = True):
        """
        聊天方法，支持流式和非流式返回

        :param query: 用户问题
        :param stream: 是否流式返回
        :return: 聊天结果
        """
        try:
            if hasattr(self, 'vector_store_path'):
                # 检索相关文档
                relevant_docs = self.faiss.similarity_search(
                    query,
                    k=VECTOR_CONFIG["top_k"]
                )

                re_id, re_index, re_relevance_scores, re_documents = self.faiss.enhanced_similarity_search(
                    query, relevant_docs, k=4
                )

                if self.model_name_flag == 'xml':
                    neo4j_prompt = self.base_message_prompt(query)
                    nodes_relations_dict, node_dict_list = self.xml_relations_nodes(neo4j_prompt)
                    prompt = self.chat_prompt(query, re_documents, nodes_relations_dict, node_dict_list)
                else:
                    prompt = self.chat_prompt(query, re_documents)

                if stream:
                    response = self.llm.stream(prompt, generate_config={"max_tokens": 1024, "stream": True})
                else:
                    response = self.llm.invoke(prompt)
                return response

            else:
                # 获取LLM回答
                if stream:
                    response = self.llm.stream(query, generate_config={"max_tokens": 1024, "stream": True})
                else:
                    response = self.llm.invoke(query)
                return response

        except Exception as e:
            raise HTTPException(
                status_code=500,
                detail=str(e)
            )


def chat_():
    # 创建聊天机器人实例
    chatbot = ChatBot()

    print("欢迎使用DeepSeek聊天助手！输入 'quit' 或 'exit' 结束对话。")

    while True:
        # 获取用户输入
        user_input = input("\n请输入您的问题: ").strip()

        # 检查是否退出
        if user_input.lower() in ['quit', 'exit']:
            print("感谢使用DeepSeek，再见！")
            break

        # 获取助手回答
        response = chatbot.chat(user_input, stream=True)

        if hasattr(response, '__iter__'):
            for chunk in response:
                content = chunk.content if hasattr(chunk, 'content') else str(chunk)
                print(content, end="", flush=True)  # 直接打印字符串
        else:
            content = response.content if hasattr(response, 'content') else str(response)
            print(content)


if __name__ == "__main__":
    chat_()
    # chatbot = ChatBot()
    # chatbot.streaming_chat("天空为什么是蓝色的？")
