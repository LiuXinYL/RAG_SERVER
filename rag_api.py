import os
import sys
import time
from fastapi import FastAPI, HTTPException
from fastapi.responses import StreamingResponse, JSONResponse
from pydantic import BaseModel
from typing import Optional, List, Tuple
import uvicorn
from chat_rag import ChatBot
from config import RAG_CONFIG, VECTOR_CONFIG, LLM_CONFIG

# 获取当前项目目录的绝对路径
current_dir = os.path.abspath(os.path.dirname(__file__))
# 添加到 sys.path
sys.path.append(current_dir)

app = FastAPI(
    title="RAG API",
    description="基于vLLM和FAISSCUSTOM的检索增强生成对话系统",
    version="1.0.0"
)


class DocumentResponse(BaseModel):
    """文档响应模型"""
    content: str
    metadata: dict


class ResultResponseMessage(BaseModel):
    # role: str
    content: str


class ResultChoices(BaseModel):
    """聊天响应模型"""
    # index: Optional[int] = 0
    delta: ResultResponseMessage
    # text: str
    logprobs: Optional[bool] = None
    finish_reason: Optional[str] = None
    # stop_reason: Optional[bool] = None


class UsageMessage(BaseModel):
    prompt_tokens: Optional[int] = None
    completion_tokens: Optional[int] = None
    total_tokens: Optional[int] = None


class ChatResponse(BaseModel):
    """聊天响应模型"""
    id: Optional[str] = None
    object: Optional[str] = None
    created: Optional[int] = 0
    model: Optional[str] = None
    choices: List[ResultChoices]  # 关键嵌套
    usage: UsageMessage


class ChatMessages(BaseModel):
    content: str
    role: str


class ChatRequest(BaseModel):
    frequency_penalty: Optional[float] = None
    max_tokens: Optional[int] = None
    messages: Optional[List[ChatMessages]] = None
    model: Optional[str] = None
    n: Optional[int] = None
    presence_penalty: Optional[float] = None
    stream: Optional[bool] = None
    temperature: Optional[float] = None
    top_p: Optional[float] = None
    knowledgeName: Optional[str] = None


def extract_roles(messages):
    # 初始化四种角色的字典，值默认为空列表
    roles = {
        "system": None,
        "user": None,
        "assistant": None,
        "function": None
    }

    # 遍历消息列表，按角色提取内容（每个角色仅取第一个匹配项，如需保留多个可改为列表）
    for msg in messages:
        role = msg.role
        if role in roles:
            # 直接存储整个消息对象（或仅提取content，根据需求调整）
            # roles[role] = msg  # 存储完整消息对象

            # 或仅存储content：
            roles[role] = msg.content

    return roles


def format_response(response, stream):
    created_time = time.time_ns()

    def generate_streaming_response():
        for _token in response:
            _finish_reason = None if not hasattr(_token, 'response_metadata') or len(
                _token.response_metadata) == 0 else _token.response_metadata['finish_reason']
            _model_name = None if not hasattr(_token, 'response_metadata') or len(
                _token.response_metadata) == 0 else _token.response_metadata['model_name']

            _input_tokens = None if not hasattr(_token, 'usage_metadata') or _token.usage_metadata is None else \
                _token.usage_metadata['input_tokens']
            _output_tokens = None if not hasattr(_token, 'usage_metadata') or _token.usage_metadata is None else \
                _token.usage_metadata['output_tokens']
            _total_tokens = None if not hasattr(_token, 'usage_metadata') or _token.usage_metadata is None else \
                _token.usage_metadata['total_tokens']

            result_response_message = {
                "role": "assistant",
                "content": _token.content if hasattr(_token, 'content') else str(_token)
            }

            chat_data = ChatResponse(
                id=getattr(_token, 'id', None),
                object=None,
                created=created_time,
                model=_model_name,
                choices=[ResultChoices(
                    delta=result_response_message,
                    logprobs=None,
                    finish_reason=_finish_reason,
                )],
                usage={
                    "prompt_tokens": _input_tokens,
                    "completion_tokens": _output_tokens,
                    "total_tokens": _total_tokens
                },
            )

            yield f"data: {chat_data.model_dump_json()}\n\n"
        yield f"data: [DONE]\n\n"

    if stream:
        return StreamingResponse(generate_streaming_response(), media_type="text/event-stream")
    else:
        _finish_reason = None if not hasattr(response, 'response_metadata') or len(
            response.response_metadata) == 0 else response.response_metadata['finish_reason']
        _model_name = None if not hasattr(response, 'response_metadata') or len(
            response.response_metadata) == 0 else response.response_metadata['model_name']

        _input_tokens = None if not hasattr(response, 'usage_metadata') or response.usage_metadata is None else \
            response.usage_metadata['input_tokens']
        _output_tokens = None if not hasattr(response, 'usage_metadata') or response.usage_metadata is None else \
            response.usage_metadata['output_tokens']
        _total_tokens = None if not hasattr(response, 'usage_metadata') or response.usage_metadata is None else \
            response.usage_metadata['total_tokens']

        result_response_message = {
            "role": "assistant",
            "content": response.content if hasattr(response, 'content') else str(response)
        }

        chat_data = ChatResponse(
            id=getattr(response, 'id', None),
            object=None,
            created=created_time,
            model=_model_name,
            choices=[ResultChoices(
                delta=result_response_message,
                logprobs=None,
                finish_reason=_finish_reason,
            )],
            usage={
                "prompt_tokens": _input_tokens,
                "completion_tokens": _output_tokens,
                "total_tokens": _total_tokens
            },
        )
        return JSONResponse(chat_data.model_dump())


@app.get("/health")
async def health_check():
    """健康检查接口"""
    return {"status": "healthy"}


@app.post("/chat", response_model=ChatResponse)
async def chat(request: ChatRequest):
    """
    聊天接口

    Args:
        request: 包含用户问题的请求体

    Returns:
        ChatResponse: 包含助手回答和相关文档的响应体
    """
    try:
        roles = extract_roles(request.messages)
        model_name_flag = request.model
        model_stream_flag = request.stream if request.stream is not None else True
        knowledge_name = request.knowledgeName
        print("knowledge_name", knowledge_name)
        # max_tokens = request.max_tokens
        # temperature = request.temperature

        # todo 输入模型名字则支持自定义模板，但不支持指定知识库, base为聊天机器人模板
        if model_name_flag == LLM_CONFIG['chat_model_name']:
            chatbot = ChatBot(knowledge_name, model_name_flag, roles)
        else:
            chatbot = ChatBot()

        # # 获取检索结果
        # relevant_docs = chatbot.faiss.similarity_search(
        #     roles['user'],
        #     k=VECTOR_CONFIG["top_k"]
        # )

        # 获取回答
        response = chatbot.chat(roles['user'], stream=model_stream_flag)

        return format_response(response, model_stream_flag)

    except Exception as e:
        raise HTTPException(
            status_code=500,
            detail=str(e)
        )


if __name__ == "__main__":
    uvicorn.run(
        "rag_api:app",
        host="0.0.0.0",
        port=9800,
        reload=True  # 开发模式下启用热重载
    )