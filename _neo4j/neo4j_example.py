import pandas as pd
from py2neo import Graph, Node, Relationship

# 字段映射字典
mapping_dict = {"发生时间": "occurrence_time",
                "发布时间": "release_time",
                "发生地点": "scene",
                "死亡人数": "death_toll",
                "受伤人数": "injury_toll",
                "直接损失": "direct_loss",
                "事故主体单位": "accident_unit",
                "灾害事故类型": "accident_type",
                "防范与整改": "prevention_rectification",
                "处理建议": "treatment_recommendations",
                "应急措施": "emergency_measure",
                "直接原因": "immediate_cause",
                "严重程度": "order_severity",
                "应急响应": "emergency_response"}
# 读取文件
storage_df = pd.read_csv('E:/XJXXKJ/LLM大模型/neo4j/new.csv', encoding='utf-8')
print(storage_df.head())
# 获取列标签
columns_list = storage_df.columns.tolist()
# 获取数据条数
nums = len(storage_df['title'])
# 删除title列标签
columns_list.remove('title')
# 逆转映射字典
new_dic = dict(zip(mapping_dict.values(), mapping_dict.keys()))

# 连接数据库，输入个人配置
graph = Graph("bolt://localhost:7687", auth=("neo4j", "123456789"))
# 清空全部数据
graph.delete_all()
# 开启一个新的事务
graph.begin()

for i in range(nums):
    data_dict = {}
    title = storage_df['title'][i]
    for columns in columns_list:
        if str(storage_df[columns][i]) != 'nan':
            data_dict[columns] = storage_df[columns][i]
    # 创建事件节点（主节点），节点属性
    node1 = Node("case", name=title, **data_dict)
    graph.merge(node1, 'case', 'name')
    # 删除id列
    data_dict.pop('id')
    # 创建关系与副节点
    for key, value in data_dict.items():
        # 创建副节点
        node2 = Node(key, name=value)
        graph.merge(node2, key, 'name')
        # 创建关系
        rel = Relationship(node1, new_dic[key], node2, type=key)
        graph.merge(rel)

