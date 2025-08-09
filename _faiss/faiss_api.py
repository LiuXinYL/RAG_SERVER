import os
import sys
import json
from fastapi import FastAPI, File, UploadFile, Form, HTTPException
from typing import Optional
from langchain_openai import OpenAIEmbeddings
from custom_faiss import FAISSCUSTOM
import uvicorn
import pymysql
from pymysql.cursors import DictCursor
from config import LLM_CONFIG, MYSQL_CONFIG, VECTOR_SAVE_PATH, PROJECT_PATH
app = FastAPI(
    title="数据向量化",
    description="操作 FAISS 数据库向量化",
    version="1.0.0"
)


# def update_db_status(file_id: str, status: str = "init", message: str = ""):
#     """更新 MySQL 数据库中的文件状态"""
#
#     status_dict = {
#         "init": "0",  # 未处理
#         "error": "1",  # 失败
#         "processing": "2",  # 处理中
#         "success": "3",  # 成功
#     }
#     status = status_dict.get(status, "0")  # 默认值为 "未处理"
#
#     # 初始化 connection 为 None
#     connection = None
#
#     try:
#         # 从配置中获取数据库连接信息
#         connection = pymysql.connect(
#             host=MYSQL_CONFIG['host'],
#             user=MYSQL_CONFIG['user'],
#             password=MYSQL_CONFIG['password'],
#             database=MYSQL_CONFIG['database'],
#             cursorclass=DictCursor,
#         )
#
#         with connection.cursor() as cursor:
#             # 更新状态的 SQL 语句
#             sql = f"UPDATE sor_libraryfile_chile set flag = '{status}' WHERE id = {int(file_id)}"
#             cursor.execute(sql)
#
#         # 提交事务
#         connection.commit()
#         return True
#
#     except Exception as e:
#         print(f"更新数据库失败: {str(e)}")
#         return False
#
#     finally:
#         if connection:
#             connection.close()


# 封装删除临时文件的函数
def remove_temp_file(file_path):
    if file_path and os.path.exists(file_path):
        try:
            os.remove(file_path)
        except Exception as e:
            print(f"删除临时文件失败: {str(e)}")


@app.post("/vectorize")
async def vectorize_file(file_id: str = Form(...), file: UploadFile = File(...), knowledge_name: str = Form(...),
                         split_type: str = Form(...),):
    """接收 JSON 格式的文件 ID 和 Excel 文件，向量化后更新数据库状态"""

    # 初始化 FAISSCUSTOM 类
    faiss_custom = FAISSCUSTOM(
        knowledge_name=knowledge_name,
        max_tokens=LLM_CONFIG["max_tokens"],
        temperature=LLM_CONFIG["temperature"]
    )

    temp_file_path = None
    try:
        # # 从 JSON 中提取 file_id
        # if not file_id:
        #     return {"success": False, "message": "缺少必要的 file_id 参数"}

        if not file:
            return {"success": False, "message": "缺少必要的 file_content 参数"}

        # 确定文件类型
        print("file.filename", file.filename)
        file_name, file_type = os.path.splitext(file.filename)
        if file_type not in ['.xlsx', '.xls', '.csv', '.xml', '.txt', '.md', '.pdf', '.docx', 'doc']:
            return {"message": f"不支持的文件类型: {file_type}", "success": False}

        # # 保存上传的文件到临时目录
        temp_dir = os.path.join(PROJECT_PATH, "_faiss/faiss_temp_data")
        os.makedirs(temp_dir, exist_ok=True)
        # 将上传的文件保存到临时文件
        temp_file_path = os.path.join(temp_dir, f"{file.filename}")
        with open(temp_file_path, "wb") as buffer:
            contents = await file.read()
            buffer.write(contents)

        # # 更新数据库状态为 "处理中"
        # update_db_status(file_id, "processing", "正在向量化")

        # 创建向量存储
        if faiss_custom.create_vector(temp_file_path, file_type, split_type=split_type):
            # 保存向量存储到本地
            # todo 可按照知识库名称存储 knowledge, 若存在数据库需要追加写入
            vector_store_save_path = os.path.join(VECTOR_SAVE_PATH, knowledge_name)
            # vector_store_save_path = os.path.join(VECTOR_SAVE_PATH, str(file_id), file_name)

            if isinstance(vector_store_save_path, bytes):
                vector_store_save_path = vector_store_save_path.decode('utf-8')

            if faiss_custom.save(vector_store_save_path):
                # 更新数据库状态为 "成功"
                # update_db_status(file_id, "success", f"向量库已保存至: {vector_store_save_path}")

                if temp_file_path and os.path.exists(temp_file_path):
                    os.remove(temp_file_path)

                return {"success": True, "message": f"{split_type}切分 向量化成功，向量库已保存至: {knowledge_name} 知识库中！"}
            else:
                # 更新数据库状态为 "失败"
                # update_db_status(file_id, "failed", "保存向量库失败")

                return {"success": False, "message": "保存向量库失败"}

        else:
            # 更新数据库状态为 "失败"
            # update_db_status(file_id, "failed", "创建向量存储失败")
            return {"success": False, "message": "创建向量存储失败"}

    except Exception as e:
        # 更新数据库状态为 "错误"
        error_msg = f"处理文件时出错: {str(e)}"
        # update_db_status(file_id, "error", error_msg)
        return {"success": False, "message": error_msg}

    finally:
        # 调用删除临时文件的函数
        remove_temp_file(temp_file_path)


if __name__ == "__main__":

    uvicorn.run(
        "faiss_api:app",
        host="0.0.0.0",
        port=9802,
        reload=True  # 开发模式下启用热重载
    )