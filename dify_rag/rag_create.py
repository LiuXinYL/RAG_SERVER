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





if __name__ == '__main__':
    # 配置信息
    # file_path = "C:/Users/16000/Desktop/小红小明测试.docx"
    file_path = "C:/Users/16000/Desktop/小红小明测试.docx"
    api_key = "app-ZcFbaRALNo8pPhqQHb792zxn"
    user = "abc-123"