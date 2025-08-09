import os
import asyncio

os.environ['http_proxy'] = "http://127.0.0.1:7890"
os.environ['https_proxy'] = "http://127.0.0.1:7890"

from langchain_mcp_adapters.client import MultiServerMCPClient
from langgraph.prebuilt import create_react_agent
from langgraph.checkpoint.memory import MemorySaver

from langchain_openai import ChatOpenAI
from langchain_core.messages import HumanMessage, SystemMessage

from llm_init import LLM_INIT

async def tools_test(chat_model, messages, config):

    async with MultiServerMCPClient(
        {
            "math": {
                "command": "python",
                # Make sure to update to the full absolute path to your math_server.py file
                "args": ["E:/python_project/大模型/RAG_test_new/mcp_tools/math_server_mcp.py"],
                "transport": "stdio",
            },
            "weather": {
                # make sure you start your weather server on port 8300
                "url": "http://localhost:8300/weather",
                "transport": "weather",
            }
        }
    ) as client:

        # 在内存中管理对话历史
        memory = MemorySaver()


        agent = create_react_agent(
            model=chat_model,
            tools=client.get_tools(),
            # prompt=messages,
            checkpointer=memory, debug=False
        )

        response = await agent.ainvoke(messages, config=config)
        # math_response = await agent.ainvoke({"messages": "what's the result devided by 6?"}, config=config)
        # weather_response = await agent.ainvoke({"messages": "what is the weather in nyc?"}, config=config)

        return response



if __name__ == "__main__":

    ds_32b = LLM_INIT.create_llm_client
    config = {"configurable": {"thread_id": "226"}}
    system_prompt = """
            你是一个有用的助手，能够根据需要自动决定调用哪个工具回答问题。 
            """

    user_input = "what's (3 + 5) x 12?"
    messages = [
        SystemMessage(content=system_prompt),
        HumanMessage(content=user_input)
    ]

    response = asyncio.run(tools_test(ds_32b, messages, config))

    print(response)