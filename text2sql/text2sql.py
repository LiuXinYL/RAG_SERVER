import json
import os
import re
import sys
from typing import List

import pandas as pd
import sqlparse
from langchain_core.messages import HumanMessage, SystemMessage
from langchain_openai import ChatOpenAI

from config import (

    LLM_CONFIG,

)

# 获取当前项目目录的绝对路径
current_dir = os.path.abspath(os.path.dirname(__file__))
# 添加到 sys.path
sys.path.append(current_dir)




class SQL2JSON(object):

    def __init__(self, data_path=None):

        self.sql_path = SQLFILE_CONFIG['orgin_sql_path']
        self.save_path = SQLFILE_CONFIG['deal_sql_path']
        self.data_path = data_path

    def extract_create_table_statements(self, ):
        """
        提取SQL文件中的CREATE TABLE语句

        参数：
            sql_file (str): SQL文件路径

        返回：
            list: 包含所有CREATE TABLE语句的列表（字符串形式）
        """
        with open(self.sql_path, 'r', encoding='utf-8') as f:
            content = f.read()

        # 方法一：使用sqlparse库（推荐）
        statements = []
        for stmt in sqlparse.parse(content):
            # 去除注释并标准化格式
            cleaned = sqlparse.format(str(stmt), strip_comments=True, reindent=False)
            if cleaned.upper().startswith("CREATE TABLE"):
                statements.append(cleaned.strip())

        # 方法二：正则表达式备用方案（当不能安装第三方库时）
        if not statements:
            create_table_re = re.compile(r'(CREATE TABLE.*?;)', re.DOTALL | re.IGNORECASE)
            statements = [
                re.sub(r'\s+', ' ', stmt).strip()
                for stmt in create_table_re.findall(content)
            ]

        return statements

    def sql2json_deal(self, ):

        table_list = self.extract_create_table_statements()

        complex_list = []
        for i, table in enumerate(table_list, 1):
            print(f"【表{i}】\n{table}\n{'-' * 50}")
            complex_list.append({"id": i, "sql": table})

        with open(self.save_path, 'w') as f:
            json.dump(complex_list, f, indent=2)  # 美化格式输出

    def read_json_list(self, ):
        """基本文件读取方法[1,4](@ref)"""
        try:

            if self.data_path is None:
                self.data_path = SQLFILE_CONFIG['use_sql_path']

            with open(self.data_path, 'r', encoding='utf-8') as f:
                return json.load(f)['sql']  # 自动转换为字典/列表

        except (FileNotFoundError, json.JSONDecodeError) as e:
            print(f"错误：{str(e)}")
            return None


class SQLTableParser:

    def __init__(self, sql_file_path=None):
        self.sql_path = SQLFILE_CONFIG['orgin_sql_path']
        self.save_path = SQLFILE_CONFIG['deal_sql_path']

        self.use_sql_path = sql_file_path if sql_file_path else SQLFILE_CONFIG['use_sql_path']
        self.df = pd.DataFrame(columns=['TableName', 'Comment', 'SQL'])

    def parse_sql(self):
        with open(self.sql_path, 'r', encoding='GBK') as f:
            content = f.read()

        # 使用正则表达式匹配表结构[1,3](@ref)
        pattern = r"TableName:'(.*?)';\s*Comment:'(.*?)';\s*(CREATE TABLE `.*?`[\s\S]*?;)"
        matches = re.findall(pattern, content)

        # 构造DataFrame[6](@ref)
        data = []
        for match in matches:
            tablename = match[0].strip() or None
            comment = match[1].strip() or None
            create_sql = match[2].strip()

            # # 处理没有表名的情况（使用表定义中的实际表名）[2](@ref)
            # if not tablename:
            #     table_match = re.search(r"CREATE TABLE `(.*?)`", create_sql)
            #     tablename = table_match.group(1) if table_match else "Unknown"

            data.append({
                'TableName': tablename,
                'Comment': comment,
                'SQL': create_sql
            })

        self.df = pd.DataFrame(data)
        return self.df

    def save_csv(self, ):
        # 保存为CSV文件（不保留索引）[7](@ref)
        self.df.to_csv(self.save_path, index=False, encoding='utf-8')
        return self.df

    def load_csv(self):
        df = pd.read_csv(self.use_sql_path)
        sql_list = df['SQL'].values.tolist()
        return sql_list


class Text2SQL:

    def __init__(self, data_path=None):
        self.data_path = data_path

        # 初始化test2sql LLM
        self.text2sql = create_text2sql_client()

        self.query_history = []

    def generate_prompt(self, schemas, question):
        """
        生成带有上下文的提示

        Args:
            query: 用户问题
            schema: 表结构
        Returns:
            List[SystemMessage | HumanMessage]: 消息列表
        """
        # 将检索结果组合成上下文
        schema_str = "\n".join([doc for doc in schemas])

        messages = [
            SystemMessage(content=TEXT2SQL_PROMPT.format(schema_str)),
            HumanMessage(content=question)
        ]

        return messages

    # 6. 完整对话处理函数
    def process_query(self, schemas: List[str], question: str, ):

        messages = self.generate_prompt(schemas, question)

        response = self.text2sql.invoke(messages)

        return response.content



if __name__ == '__main__':

    pass
    # # 初始化json数据
    # sql2json = SQL2JSON()
    # sql2json.sql2json_deal()

    # # 初始化csv数据
    # parser = SQLTableParser()
    # parser.parse_sql().save_csv()


    # schema_str = [
    #     "CREATE TABLE users ( user_id INT PRIMARY KEY, username VARCHAR(50) NOT NULL, email VARCHAR(100) NOT NULL); "
    #     "CREATE TABLE orders ( order_id INT PRIMARY KEY, user_id INT, order_date DATE, amount DECIMAL(10, 2),  product_id INT, FOREIGN KEY (user_id) REFERENCES users(user_id)); "
    #     "CREATE TABLE products ( product_id INT PRIMARY KEY, product_name VARCHAR(100), price DECIMAL(10,2));"
    # ]
