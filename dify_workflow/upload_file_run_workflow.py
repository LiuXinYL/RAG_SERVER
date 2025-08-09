import requests
import json
import sys
import os
import mimetypes

# 获取上级目录的绝对路径
parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
# 将上级目录添加到sys.path
sys.path.append(parent_dir)

from config import DIFY_API, SERVE_ADDRESS

def upload_file(local_file_path, api_key, user):
    """
    上传文件
    """
    # 动态推断文件类型
    file_type, _ = mimetypes.guess_type(local_file_path)
    if not file_type:
        file_type = 'application/octet-stream'  # 默认类型
    # print(f"Detected file type: {file_type}")

    # API 端点
    url = DIFY_API + '/files/upload'

    # 设置请求头
    headers = {
        'Authorization': f'Bearer {api_key}'
    }

    # 提取文件名（不包含路径）
    file_name = os.path.basename(local_file_path)

    # 打开本地文件
    with open(local_file_path, 'rb') as file:
        # 构建表单数据
        files = {
            'file': (file_name, file, file_type)
        }
        data = {
            'user': user
        }

        # 发送 POST 请求
        response = requests.post(url, headers=headers, files=files, data=data)

    # 检查响应状态码
    if response.status_code == 201:
        # print("文件上传成功")
        response_data = response.json()
        # print(f"上传响应: {json.dumps(response_data, indent=2)}")
        file_id = response_data.get('id')
        if not file_id:
            print("警告: 响应中未找到文件ID")
            print(f"完整响应: {response.text}")
        return file_id, response
    else:
        print(f"文件上传失败，状态码: {response.status_code}")
        print(f"错误详情: {response.text}")
        return None, response


def run_workflow(file_id, api_key, user, filename):
    """
    执行工作流

    Args:
        file_id: 文件ID
        api_key: API密钥

    Returns:
        dict: 工作流执行结果
    """

    # 工作流API端点
    workflow_url = DIFY_API + "/workflows/run"
    # 请求头
    headers = {
        "Authorization": f"Bearer {api_key}",
        "Content-Type": "application/json"
    }
    # 准备数据
    data = {
        "inputs": {
            "input_word": {  # 工作流中定义的文件变量名
                "type": "document",
                "transfer_method": "local_file",
                "upload_file_id": file_id
            },
            "user": filename
        },
        "response_mode": "blocking",
        "user": user
    }

    # print(f"工作流请求数据: {json.dumps(qac_data, indent=2)}")

    max_retries = 3
    retry_count = 0
    while retry_count < max_retries:
        try:
            # 发送 POST 请求
            # print(f"尝试执行工作流 (第 {retry_count + 1} 次)")
            response = requests.post(workflow_url, headers=headers, json=data)

            # 检查响应状态码
            response.raise_for_status()

            # 处理响应
            response_data = response.json()
            # print(f"工作流执行成功: {json.dumps(response_data, indent=2)}")

            # 根据实际响应结构提取结果
            output_text = response_data.get('qac_data', {}).get('outputs', {}).get('files')[0]
            status = response_data.get('status')
            if output_text:
                download_url = SERVE_ADDRESS + output_text.get('url')
                return {"qac_data": download_url, "status": status}
            else:
                print("警告: 响应中未找到预期的输出文本")
                print(f"完整响应: {response.text}")
                return {"qac_data": response_data, "status": status}

        except requests.exceptions.HTTPError as e:
            print(f"HTTP错误（状态码 {e.response.status_code}）: {e.response.text}")
            # 非重试性错误（如400、401、403）直接返回
            if 400 <= e.response.status_code < 500:
                print("此错误类型不适合重试")
                return None
            retry_count += 1
        except Exception as e:
            print(f"执行工作流时发生异常: {str(e)}")
            retry_count += 1

    print("达到最大重试次数，工作流执行失败。")
    return None


if __name__ == '__main__':
    # 配置信息
    # file_path = "C:/Users/16000/Desktop/小红小明测试.docx"
    file_path = "C:/Users/16000/Desktop/小红小明测试.docx"
    api_key = "app-ZcFbaRALNo8pPhqQHb792zxn"
    user = "abc-123"

    file_id, upload_response = upload_file(file_path, api_key, user)
    # print('file_id', file_id)

    result = run_workflow(file_id, api_key, user, 'test')
    if result:
        print(result)
    else:
        print("工作流执行失败，未能获取结果")
