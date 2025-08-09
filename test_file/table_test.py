import time
from datetime import datetime
import numpy as np
import pandas as pd
import re
from pydantic import BaseModel
import sys
from langchain_core.messages import HumanMessage, SystemMessage
from langchain_openai import ChatOpenAI, OpenAIEmbeddings
from langchain_community.llms import Xinference
from langchain_community.llms import Ollama
from langchain_core.output_parsers import StrOutputParser

pd.set_option('display.max_rows', 200)  # 最大显示行数
pd.set_option('display.max_columns', 50)  # 最大显示列数
pd.set_option('display.width', 1000)  # 显示宽度
pd.set_option('display.max_colwidth', 200)  # 每列最大宽度


def extract_number(value):
    """
    提取数值部分
    """
    if pd.isna(value):
        return False
    try:
        float(value)
        return True
    except (ValueError, TypeError):
        return False

    # 定义函数检测单元格是否包含"小计"


def contains_subtotal(value):
    if pd.isna(value):
        return False
    return '小计' in str(value)


def contains_total(value):
    if pd.isna(value):
        return False
    return '总计' in str(value)


if __name__ == '__main__':

    # 读取Excel文件
    excel_save_path = 'C:/Users/16000/Desktop/小红小明测试_综合结果.xlsx'
    # df_tb = pd.read_excel(excel_save_path, sheet_name='开标一览表')
    df = pd.read_excel(excel_save_path, sheet_name='投标分项报价表', header=1)
    df.drop(columns=['序号'], inplace=True)

    # 统计每行包含"小计"的单元格数量
    subtotal_count = df.applymap(contains_subtotal).sum(axis=1)
    # 统计每行包含"总计"的单元格数量
    total_count = df.applymap(contains_total).sum(axis=1)
    # 获取"小计"和总计出现频次最多的行索引
    max_subtotal_index = subtotal_count[subtotal_count == subtotal_count.max()].index.tolist()
    max_total_index = total_count[total_count == total_count.max()].index.tolist()

    # 提取每列的数值部分
    float_ratio = df.applymap(extract_number).mean()
    # 获取数字比例超过0%的列
    numeric_columns = float_ratio[float_ratio > 0.5].index.tolist()

    print({'行计算验证': numeric_columns, '小计验证': max_subtotal_index, '总计验证': max_total_index })
