import pandas as pd
from py2neo import Graph, Node, Relationship


# 定义标签与颜色的映射
label_color_map = {
    "PROJECT": "#0000FF",   # 纯蓝色
    "ENTERPRISE": "#00FFFF",  # 青蓝色（水绿色）
    "SITE": "#00FF00",       # 纯绿色
    "SEGMENT": "#F5A623",     # 橙色
    "ASSET": "#808080",       # 中灰色
    "MEASLOC": "#FF0000",       # 纯红色
}

def create_node(row, tx):
    """在事务中创建节点并确保唯一性"""
    node_type = row['type']

    node_color = label_color_map.get(node_type, "#FFFFFF")

    node = Node(labels=node_type, name=row['name'], id=row['id'], xml=row['xml'], color=node_color)
    tx.merge(node, node_type, 'name')  # 按类型和名称唯一约束
    return node

def create_relationship(df, tx):

    try:
        for index, row in df.iterrows():
            # 创建当前节点
            current_node = create_node(row, tx)

            # 处理父节点
            parent_name = row['parent_name']
            parent_type = row['parent_type']

            # graph.merge(current_node, 'case', 'name')

            if pd.notna(parent_name) and parent_type:

                parent_node = Node(parent_type, name=parent_name)
                tx.merge(parent_node, parent_type, 'name')  # 创建父节点（若不存在）
                # rel = Relationship(current_node, row['relationship'], parent_node)
                rel = Relationship(current_node, "嵌套", parent_node)
                tx.merge(rel)  # 创建关系
        # 提交事务
        graph.commit(tx)
    except Exception as e:
        # 事务回滚
        graph.rollback(tx)
        raise e


if __name__ == '__main__':

    # 读取文件
    # df = pd.read_csv('E:/python_project/大模型/RAG_test_new/xml_data/node_hierarchy.csv')
    df = pd.read_csv('/xml_data/result_test.csv')
    print(df.head())

    # 连接数据库（py2neo 3.x语法）
    graph = Graph("bolt://localhost:7687", auth=("neo4j", "123456789"))
    # 清空数据（py2neo 3.x直接删除）
    graph.delete_all()
    # 启动事务（py2neo 3.x语法）
    tx = graph.begin()

    create_relationship(df, tx)