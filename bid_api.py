import os
import sys
from fastapi import FastAPI, HTTPException, Form
from fastapi.responses import StreamingResponse
from fastapi import File, UploadFile
import uvicorn
import docx
import io

from dify_workflow.upload_file_run_workflow import upload_file, run_workflow
# 获取上级目录的绝对路径
parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
# 将上级目录添加到sys.path
sys.path.append(parent_dir)

from file_utils.bid_word_parse import work_flow


app = FastAPI(
    title="招投标工作流",
    description="基于dify生成的投标agent",
    version="1.0.0"
)


@app.get("/health")
async def health_check():
    """健康检查接口"""
    return {"status": "healthy"}


@app.post("/generate")
async def generate(file: UploadFile = File(...), user: str = Form(...)):
    """
    聊天接口

    Args:
        :param file:
        :param user:
    Returns:
        StreamingResponse: 以字节流方式返回工作流执行结果
    """
    try:
        # 配置信息
        api_key = "app-Yru9ywikBd5v3nRvT8KHjfFN"
        file_name = user
        user = "generate"

        # 将上传的文件保存到临时文件
        temp_file_path = f"temp_{file.filename}"
        with open(temp_file_path, "wb") as buffer:
            contents = await file.read()
            buffer.write(contents)

        # 调用上传文件函数
        file_id, upload_response = upload_file(temp_file_path, api_key, user)
        # print('file_id', file_id)

        # 删除临时文件
        os.remove(temp_file_path)

        if file_id is None:
            raise HTTPException(status_code=500, detail="文件上传失败")

        # 调用执行工作流函数
        result = run_workflow(file_id, api_key, user, file_name)

        return result

    except Exception as e:
        raise HTTPException(
            status_code=500,
            detail=str(e)
        )


async def generate_test(file: UploadFile = File(...)):
    """
    聊天接口

    Args:
        file: 上传的文件

    Returns:
        StreamingResponse: 以字节流方式返回工作流执行结果
    """
    try:

        # 将上传的文件保存到临时文件
        temp_file_path = f"temp_{file.filename}"
        with open(temp_file_path, "wb") as buffer:
            contents = await file.read()
            buffer.write(contents)

        # 调用上传文件函数
        file_id, upload_response = upload_file(temp_file_path)
        # 删除临时文件
        os.remove(temp_file_path)

        if file_id is None:
            raise HTTPException(status_code=500, detail="文件上传失败")



        return result

    except Exception as e:
        raise HTTPException(
            status_code=500,
            detail=str(e)
        )
@app.post("/detection")
async def detection(file: UploadFile = File(...), user: str = Form(...)):
    """
    聊天接口

    Args:
        file: 上传的文件

    Returns:
        StreamingResponse: 以字节流方式返回工作流执行结果
    """
    try:

        # 检查文件类型是否为Word文档
        if not file.filename.endswith(('.docx', '.doc')):
            raise HTTPException(status_code=400, detail="请上传Word文档(.docx或.doc格式)")

        # 读取文件内容
        contents = await file.read()

        # 直接从内存中处理Word文档，不需要保存到临时文件
        doc_dectetion = docx.Document(io.BytesIO(contents))

        check_list = work_flow(doc_dectetion)

        return check_list

    except Exception as e:
        raise HTTPException(
            status_code=500,
            detail=str(e)
        )


if __name__ == "__main__":
    uvicorn.run(
        "bid_api:app",
        host="0.0.0.0",
        port=9801,
        reload=True  # 开发模式下启用热重载
    )
