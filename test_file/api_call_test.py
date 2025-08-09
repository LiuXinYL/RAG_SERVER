import requests
import json
from typing import Generator


def stream_chat_response(prompt: str, flag: str = None) -> Generator[str, None, None]:
    """
    向 /chat 接口发送流式请求并逐段获取响应

    Args:
        prompt: 用户输入的提问内容
        flag: 可选参数，默认为 base 模式
    """
    url = "http://localhost:9800/chat"
    headers = {"Content-Type": "application/json"}
    payload = {"prompt": prompt, "flag": flag}  # 构造请求体

    try:

        response = requests.post(url, headers=headers, json=payload, stream=True)
        response.raise_for_status()  # 检查 HTTP 错误状态码

        for line in response.iter_lines():
            if line:  # 过滤空行
                line = line.decode("utf-8")
                if line.startswith("qac_data: "):
                    # 提取 JSON 部分并解析
                    json_str = line[6:]
                    try:
                        data = json.loads(json_str)
                        yield data["choices"][0]["text"]  # 逐段返回文本内容
                    except json.JSONDecodeError as e:
                        print(f"JSON 解析错误: {e}")
                        continue

    except requests.exceptions.RequestException as e:
        print(f"请求发生异常: {e}")


def main(user_prompt):
    """主函数：演示请求流程并拼接完整响应"""
    full_response = ""
    # 遍历流式响应并拼接结果
    for chunk in stream_chat_response(user_prompt["prompt"], flag=user_prompt["flag"]):
        # print(f"接收响应片段: {chunk}")  # 打印实时接收到的内容
        print(chunk, end="", flush=True)

        full_response += chunk

    # print("\n完整响应内容:")
    # print(full_response)


if __name__ == "__main__":

    user_prompt = {
        "prompt": '''
        新建aaa建材王总工程，调试组织，7788站点, 3030设备，我是好还是子系统，下有你是111测试点
        ''',

        # "flag": "xml"
        "flag": "safeguard"
    }
    main(user_prompt)