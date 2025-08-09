import os
import sys
import json
from fastapi import FastAPI, File, UploadFile, Form, HTTPException, Query
from fastapi.responses import JSONResponse, StreamingResponse
from typing import Optional, Dict, Any, Generator
from pydantic import BaseModel
from langchain_openai import OpenAIEmbeddings
import asyncio

import uvicorn
import pymysql
from pymysql.cursors import DictCursor

# 添加项目根目录到路径
current_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.dirname(current_dir)
sys.path.append(project_root)

from config import LLM_CONFIG, MYSQL_CONFIG, VECTOR_SAVE_PATH, PROJECT_PATH
from qac_chat_rag import QACChatRAG
app = FastAPI(
    title="QAC代码质量分析系统",
    description="基于AI的代码质量分析和建议系统，整合代码解析、错误检测和知识库",
    version="1.0.0"
)

# 全局QAC RAG系统实例
qac_rag_system = None

# 数据模型
class SingleIssueRequest(BaseModel):
    """单个问题分析请求"""
    file_name: str
    line_number: int
    error_id: str
    rule_violated: str
    error_message: str
    error_type: Optional[str] = "unknown"
    severity_level: Optional[str] = "medium"

class ComprehensiveAnalysisRequest(BaseModel):
    """综合分析请求"""
    file_name: str

class ChatRequest(BaseModel):
    """聊天请求"""
    question: str
    file_name: Optional[str] = None
    line_number: Optional[int] = None

class AnalysisResponse(BaseModel):
    """分析响应"""
    success: bool
    data: Optional[str] = None
    error: Optional[str] = None
    metadata: Optional[Dict[str, Any]] = None


def get_qac_rag_system():
    """获取QAC RAG系统实例"""
    global qac_rag_system
    if qac_rag_system is None:
        try:
            qac_rag_system = QACChatRAG()
        except Exception as e:
            print(f"初始化QAC RAG系统失败: {e}")
            qac_rag_system = None
    return qac_rag_system


@app.get("/health")
async def health_check():
    """健康检查接口"""
    rag_system = get_qac_rag_system()
    return {
        "status": "healthy",
        "qac_rag_system": "initialized" if rag_system else "failed",
        "version": "1.0.0"
    }


@app.post("/analyze/single-issue")
async def analyze_single_issue(request: SingleIssueRequest, stream: bool = Query(False)):
    """
    分析单个代码问题
    
    基于提供的错误信息、代码上下文和知识库，给出详细的分析和修复建议
    支持流式返回（通过stream参数控制）
    """
    try:
        rag_system = get_qac_rag_system()
        if not rag_system:
            raise HTTPException(status_code=503, detail="QAC RAG系统未初始化")
        
        if stream:
            # 流式返回
            async def generate_response():
                try:
                    result_generator = rag_system.analyze_single_issue(
                        file_name=request.file_name,
                        line_number=request.line_number,
                        error_id=request.error_id,
                        rule_violated=request.rule_violated,
                        error_message=request.error_message,
                        error_type=request.error_type,
                        severity_level=request.severity_level,
                        stream=True
                    )
                    
                    # 发送开始标记
                    yield f"data: {json.dumps({'type': 'start', 'metadata': {'analysis_type': 'single_issue', 'file_name': request.file_name, 'line_number': request.line_number, 'rule': request.rule_violated}})}\n\n"
                    
                    # 发送内容块
                    for chunk in result_generator:
                        chunk_data = {
                            'type': 'chunk',
                            'content': chunk
                        }
                        yield f"data: {json.dumps(chunk_data, ensure_ascii=False)}\n\n"
                    
                    # 发送结束标记
                    yield f"data: {json.dumps({'type': 'end'})}\n\n"
                    
                except Exception as e:
                    error_data = {
                        'type': 'error',
                        'error': str(e)
                    }
                    yield f"data: {json.dumps(error_data)}\n\n"
            
            return StreamingResponse(
                generate_response(),
                media_type="text/plain",
                headers={
                    "Cache-Control": "no-cache",
                    "Connection": "keep-alive",
                    "Content-Type": "text/plain; charset=utf-8"
                }
            )
        else:
            # 非流式返回
            result = rag_system.analyze_single_issue(
                file_name=request.file_name,
                line_number=request.line_number,
                error_id=request.error_id,
                rule_violated=request.rule_violated,
                error_message=request.error_message,
                error_type=request.error_type,
                severity_level=request.severity_level,
                stream=False
            )
            
            return AnalysisResponse(
                success=True,
                data=result,
                metadata={
                    "analysis_type": "single_issue",
                    "file_name": request.file_name,
                    "line_number": request.line_number,
                    "rule": request.rule_violated
                }
            )
    
    except Exception as e:
        return AnalysisResponse(
            success=False,
            error=str(e)
        )


@app.post("/analyze/comprehensive", response_model=AnalysisResponse)
async def analyze_comprehensive(request: ComprehensiveAnalysisRequest):
    """
    对文件进行综合代码质量分析
    
    分析整个文件的代码质量，包括所有检测到的问题、函数复杂度、依赖关系等
    """
    try:
        rag_system = get_qac_rag_system()
        if not rag_system:
            raise HTTPException(status_code=503, detail="QAC RAG系统未初始化")
        
        result = rag_system.analyze_file_comprehensive(request.file_name)
        
        return AnalysisResponse(
            success=True,
            data=result,
            metadata={
                "analysis_type": "comprehensive",
                "file_name": request.file_name
            }
        )
    
    except Exception as e:
        return AnalysisResponse(
            success=False,
            error=str(e)
        )


@app.post("/chat")
async def chat_with_context(request: ChatRequest, stream: bool = Query(False)):
    """
    基于上下文的智能对话
    
    支持针对特定文件和行号的代码相关问题咨询
    支持流式返回（通过stream参数控制）
    """
    try:
        rag_system = get_qac_rag_system()
        if not rag_system:
            raise HTTPException(status_code=503, detail="QAC RAG系统未初始化")
        
        if stream:
            # 流式返回
            async def generate_response():
                try:
                    result_generator = rag_system.chat_with_context(
                        question=request.question,
                        file_name=request.file_name,
                        line_number=request.line_number,
                        stream=True
                    )
                    
                    # 发送开始标记
                    yield f"data: {json.dumps({'type': 'start', 'metadata': {'analysis_type': 'chat', 'file_name': request.file_name, 'line_number': request.line_number}})}\n\n"
                    
                    # 发送内容块
                    for chunk in result_generator:
                        chunk_data = {
                            'type': 'chunk',
                            'content': chunk
                        }
                        yield f"data: {json.dumps(chunk_data, ensure_ascii=False)}\n\n"
                    
                    # 发送结束标记
                    yield f"data: {json.dumps({'type': 'end'})}\n\n"
                    
                except Exception as e:
                    error_data = {
                        'type': 'error',
                        'error': str(e)
                    }
                    yield f"data: {json.dumps(error_data)}\n\n"
            
            return StreamingResponse(
                generate_response(),
                media_type="text/plain",
                headers={
                    "Cache-Control": "no-cache",
                    "Connection": "keep-alive",
                    "Content-Type": "text/plain; charset=utf-8"
                }
            )
        else:
            # 非流式返回
            result = rag_system.chat_with_context(
                question=request.question,
                file_name=request.file_name,
                line_number=request.line_number,
                stream=False
            )
            
            return AnalysisResponse(
                success=True,
                data=result,
                metadata={
                    "analysis_type": "chat",
                    "file_name": request.file_name,
                    "line_number": request.line_number
                }
            )
    
    except Exception as e:
        return AnalysisResponse(
            success=False,
            error=str(e)
        )


@app.post("/proposal")
async def legacy_proposal_endpoint(
        file: UploadFile = File(...),
        user: str = Form(...),
        question: str = Form(...)
):
    """
    传统聊天接口（兼容性保留）
    
    Args:
        file: 上传的文件
        user: 用户标识  
        question: 用户问题
    
    Returns:
        分析结果
    """
    try:
        rag_system = get_qac_rag_system()
        if not rag_system:
            raise HTTPException(status_code=503, detail="QAC RAG系统未初始化")
        
        # 处理上传的文件（如果需要）
        file_content = None
        if file:
            content = await file.read()
            file_content = content.decode('utf-8', errors='ignore')
        
        # 使用聊天功能回答问题
        result = rag_system.chat_with_context(
            question=question,
            file_name=file.filename if file else None
        )
        
        return {
            "success": True,
            "user": user,
            "question": question,
            "answer": result,
            "file_name": file.filename if file else None
        }

    except Exception as e:
        raise HTTPException(
            status_code=500,
            detail=str(e)
        )


@app.get("/system/status")
async def get_system_status():
    """获取系统状态信息"""
    try:
        rag_system = get_qac_rag_system()
        
        status = {
            "qac_rag_initialized": rag_system is not None,
            "vector_store_available": False,
            "enhanced_data_loaded": False,
            "code_info_available": False
        }
        
        if rag_system:
            status["vector_store_available"] = rag_system.vector_store is not None
            status["enhanced_data_loaded"] = rag_system.enhanced_data is not None
            status["code_info_available"] = rag_system.code_info_json_dir.exists()
            
            if rag_system.enhanced_data is not None:
                status["enhanced_data_records"] = len(rag_system.enhanced_data)
        
        return status
    
    except Exception as e:
        return {"error": str(e)}


@app.get("/files/list")
async def list_available_files():
    """列出可用的代码文件"""
    try:
        rag_system = get_qac_rag_system()
        if not rag_system:
            raise HTTPException(status_code=503, detail="QAC RAG系统未初始化")
        
        files = []
        if rag_system.enhanced_data is not None:
            unique_files = rag_system.enhanced_data['File'].dropna().unique().tolist()
            files = sorted(unique_files)
        
        return {
            "available_files": files,
            "total_count": len(files)
        }
    
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/files/{file_name}/issues")
async def get_file_issues(file_name: str):
    """获取指定文件的所有问题"""
    try:
        rag_system = get_qac_rag_system()
        if not rag_system:
            raise HTTPException(status_code=503, detail="QAC RAG系统未初始化")
        
        if rag_system.enhanced_data is None:
            return {"issues": [], "total_count": 0}
        
        file_issues = rag_system.enhanced_data[
            rag_system.enhanced_data['File'] == file_name
        ]
        
        issues = file_issues.to_dict('records')
        
        return {
            "file_name": file_name,
            "issues": issues,
            "total_count": len(issues)
        }
    
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


# 专门的流式端点（使用标准的Server-Sent Events格式）
@app.post("/stream/analyze/single-issue")
async def stream_analyze_single_issue(request: SingleIssueRequest):
    """
    流式分析单个代码问题 - 专用SSE端点
    
    返回Server-Sent Events格式的流式响应
    """
    try:
        rag_system = get_qac_rag_system()
        if not rag_system:
            raise HTTPException(status_code=503, detail="QAC RAG系统未初始化")
        
        async def generate_sse():
            try:
                result_generator = rag_system.analyze_single_issue(
                    file_name=request.file_name,
                    line_number=request.line_number,
                    error_id=request.error_id,
                    rule_violated=request.rule_violated,
                    error_message=request.error_message,
                    error_type=request.error_type,
                    severity_level=request.severity_level,
                    stream=True
                )
                
                # 发送开始事件
                start_data = {
                    'type': 'start',
                    'metadata': {
                        'analysis_type': 'single_issue',
                        'file_name': request.file_name,
                        'line_number': request.line_number,
                        'rule': request.rule_violated
                    }
                }
                yield f"event: start\ndata: {json.dumps(start_data, ensure_ascii=False)}\n\n"
                
                # 发送内容流
                for chunk in result_generator:
                    if chunk.strip():  # 忽略空白块
                        chunk_data = {
                            'type': 'content',
                            'content': chunk
                        }
                        yield f"event: content\ndata: {json.dumps(chunk_data, ensure_ascii=False)}\n\n"
                
                # 发送结束事件
                yield f"event: end\ndata: {json.dumps({'type': 'end'})}\n\n"
                
            except Exception as e:
                error_data = {
                    'type': 'error',
                    'error': str(e)
                }
                yield f"event: error\ndata: {json.dumps(error_data, ensure_ascii=False)}\n\n"
        
        return StreamingResponse(
            generate_sse(),
            media_type="text/event-stream",
            headers={
                "Cache-Control": "no-cache",
                "Connection": "keep-alive",
                "Content-Type": "text/event-stream; charset=utf-8",
                "Access-Control-Allow-Origin": "*",
                "Access-Control-Allow-Headers": "*"
            }
        )
    
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.post("/stream/chat")
async def stream_chat_with_context(request: ChatRequest):
    """
    流式智能对话 - 专用SSE端点
    
    返回Server-Sent Events格式的流式响应
    """
    try:
        rag_system = get_qac_rag_system()
        if not rag_system:
            raise HTTPException(status_code=503, detail="QAC RAG系统未初始化")
        
        async def generate_sse():
            try:
                result_generator = rag_system.chat_with_context(
                    question=request.question,
                    file_name=request.file_name,
                    line_number=request.line_number,
                    stream=True
                )
                
                # 发送开始事件
                start_data = {
                    'type': 'start',
                    'metadata': {
                        'analysis_type': 'chat',
                        'question': request.question,
                        'file_name': request.file_name,
                        'line_number': request.line_number
                    }
                }
                yield f"event: start\ndata: {json.dumps(start_data, ensure_ascii=False)}\n\n"
                
                # 发送内容流
                for chunk in result_generator:
                    if chunk.strip():  # 忽略空白块
                        chunk_data = {
                            'type': 'content',
                            'content': chunk
                        }
                        yield f"event: content\ndata: {json.dumps(chunk_data, ensure_ascii=False)}\n\n"
                
                # 发送结束事件
                yield f"event: end\ndata: {json.dumps({'type': 'end'})}\n\n"
                
            except Exception as e:
                error_data = {
                    'type': 'error',
                    'error': str(e)
                }
                yield f"event: error\ndata: {json.dumps(error_data, ensure_ascii=False)}\n\n"
        
        return StreamingResponse(
            generate_sse(),
            media_type="text/event-stream",
            headers={
                "Cache-Control": "no-cache",
                "Connection": "keep-alive",
                "Content-Type": "text/event-stream; charset=utf-8",
                "Access-Control-Allow-Origin": "*",
                "Access-Control-Allow-Headers": "*"
            }
        )
    
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


if __name__ == "__main__":
    uvicorn.run(
        "qac_api:app",
        host="0.0.0.0",
        port=9803,
        reload=True  # 开发模式下启用热重载
    )
