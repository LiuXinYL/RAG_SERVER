# Create server parameters for stdio connection
import json

from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client

from langchain_mcp_adapters.tools import load_mcp_tools
from langgraph.prebuilt import create_react_agent

from langchain_openai import ChatOpenAI
from langchain_core.messages import HumanMessage, SystemMessage
from llm_init import LLM_INIT

import asyncio  # 导入asyncio库

from config import (
    VLLM_CONFIG,
    LLM_CONFIG,
    OLLAMA_CONFIG,
    EMBEDDING_CONFIG,
    XINFERENCE_CONFIG,
)

chat_model = ChatOpenAI(
    model=LLM_CONFIG["model"],
    openai_api_key=VLLM_CONFIG["api_key"],
    openai_api_base=VLLM_CONFIG["llm_url"],
    streaming=True,


)

server_params = StdioServerParameters(
    command="python",
    # Make sure to update to the full absolute path to your math_server.py file
    args=["E:/python_project/大模型/RAG_test_new/mcp_tools/math_server_mcp.py"],
)

async def main(messages):
    async with stdio_client(server_params) as (read, write):
        async with ClientSession(read, write) as session:
            # Initialize the connection
            await session.initialize()

            # Get tools
            tools = await load_mcp_tools(session)

            # Create and run the agent
            agent = create_react_agent(
                model=chat_model,
                tools=tools

            )

            agent_response = await agent.ainvoke({"messages": user_input})
            # agent_response = await agent.ainvoke(messages)

    return agent_response

# 使用asyncio运行异步主函数
if __name__ == "__main__":

    # user_input = "(3 + 5) x 12=?"
    user_input = "(3 + 5) x 12 等于多少？"

    messages = "使用中文回答一下问题:{}".format(user_input)

    response = asyncio.run(main(messages))

    contents = response['messages'][-1].content
    print(contents)