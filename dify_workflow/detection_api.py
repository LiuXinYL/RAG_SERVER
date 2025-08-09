import os
import io
import sys
from fastapi import FastAPI, HTTPException
from fastapi.responses import StreamingResponse
from fastapi import File, UploadFile
import uvicorn
import docx

# 获取上级目录的绝对路径
parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
# 将上级目录添加到sys.path
sys.path.append(parent_dir)

from file_utils.bid_word_parse_backup import work_flow
from file_utils.find_headline import identify_and_check_captions, format_result


app = FastAPI(
    title="招投标工作流",
    description="基于dify生成的投标agent",
    version="1.0.0"
)


@app.get("/health")
async def health_check():
    """健康检查接口"""
    return {"status": "healthy"}



@app.post("/detection/data_preprocess")
async def data_preprocess(file: UploadFile = File(...)):
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

        # 检测图号、表号是否连续
        result = identify_and_check_captions(doc_dectetion)
        captions_list = format_result(result)

        # 标题、正文：字体、字号、间距
        head_body_list = work_flow(doc_dectetion)

        check_list = captions_list + head_body_list
        return check_list

    except Exception as e:
        raise HTTPException(
            status_code=500,
            detail=str(e)
        )

# @app.post("/dify_workflow/detection/data_preprocess")
# async def data_preprocess(file):
#
#     print('success')
#     return 'sadafggdfafsafg'

if __name__ == "__main__":
    uvicorn.run(
        "detection_api:app",
        host="0.0.0.0",
        port=9803,
        reload=True  # 开发模式下启用热重载
    )