import time
import logging

import pandas as pd
from py2neo import Graph, Node, Relationship, Transaction

from config import NEO4J_CONFIG



class Neo4jHandler:

    def __init__(self, url: str, username: str, password: str):
        """初始化Neo4j连接"""

        self.url = url
        self.username = username
        self.password = password

        self.graph = self.connect_link()

        self.label_color_map = {
            "PROJECT": "#0000FF",
            "ENTERPRISE": "#00FFFF",
            "SITE": "#00FF00",
            "SEGMENT": "#F5A623",
            "ASSET": "#808080",
            "MEASLOC": "#FF0000",
        }

    def connect_link(self):
        max_retries = 3
        retry_delay = 5  # 重试间隔时间（秒）
        retries = 0
        while retries < max_retries:
            try:
                graph = Graph(self.url, auth=(self.username, self.password))
                logging.info("成功连接到 Neo4j 服务。")
                return graph
            except Exception as e:
                logging.error(f"连接 Neo4j 服务时出错: {e}")
                logging.info(f"正在进行第 {retries + 1} 次重试，{retry_delay} 秒后重试...")
                time.sleep(retry_delay)
                retries += 1
        logging.error("达到最大重试次数，无法连接到 Neo4j 服务。")
        return None

    def _get_node_color(self, node_type: str) -> str:
        """获取节点颜色（内部方法）"""
        return self.label_color_map.get(node_type, "#FFFFFF")

    def create_node(self, node_type: str, properties: dict) -> Node:
        """
        创建节点（自动处理唯一性约束：类型+name唯一）
        :param node_type: 节点类型（标签）
        :param properties: 节点属性字典（必须包含name）
        :return: 创建的节点对象
        """
        if 'name' not in properties:
            raise ValueError("节点属性必须包含'name'字段")

        node = Node(node_type, **properties)
        node['color'] = self._get_node_color(node_type)  # 设置颜色属性

        tx = self.graph.begin()
        try:
            tx.merge(node, node_type, 'name')  # 按类型和name唯一约束
            tx.commit()
        except Exception as e:
            tx.rollback()
            raise e
        return node

    def get_node_by_name(self, node_type: str, name: str) -> Node | None:
        """
        按类型和名称检索节点
        :param node_type: 节点类型（标签）
        :param name: 节点名称
        :return: 节点对象或None
        """
        properties = {'name': name}
        property_str = ', '.join([f"{k}: ${k}" for k in properties])
        query = f"MATCH (n:{node_type} {{{property_str}}}) RETURN n"
        result = self.graph.run(query, **properties).data()
        return result[0]['n'] if result else None

    def update_node_property(self, node: Node, property_key: str, new_value) -> None:
        """
        更新节点属性
        :param node: 节点对象
        :param property_key: 要更新的属性名
        :param new_value: 新属性值
        """
        tx = self.graph.begin()
        try:
            node[property_key] = new_value
            tx.push(node)  # 提交属性变更
            tx.commit()
        except Exception as e:
            tx.rollback()
            raise e

    def delete_node(self, node: Node, delete_relationships: bool = True) -> None:
        """
        删除节点（默认级联删除关系）
        :param node: 节点对象
        :param delete_relationships: 是否删除关联关系
        """
        tx = self.graph.begin()
        try:
            if delete_relationships:
                # 先删除所有关系
                tx.run("MATCH (n)-[r]-() WHERE ID(n) = $node_id DELETE r", node_id=id(node))
            tx.delete(node)
            tx.commit()
        except Exception as e:
            tx.rollback()
            raise e

    def create_relationship(self, from_node: Node, rel_type: str, to_node: Node, properties: dict = {}) -> Relationship:
        """
        创建节点间关系
        :param from_node: 起始节点
        :param rel_type: 关系类型
        :param to_node: 结束节点
        :param properties: 关系属性（可选）
        :return: 创建的关系对象
        """
        rel = Relationship(from_node, rel_type, to_node, **properties)

        tx = self.graph.begin()
        try:
            tx.merge(rel)  # 确保关系唯一性（相同类型和两端节点唯一）
            tx.commit()
        except Exception as e:
            tx.rollback()
            raise e
        return rel

    def get_related_nodes_by_relationship(self, rel_type: str, limit: int = 25):
        """
        根据节点间的关系查询路径
        :param rel_type: 关系类型
        :param limit: 返回结果的数量限制
        :return: 路径列表
        """
        query = f"MATCH p=()-[r:`{rel_type}`]->() RETURN p LIMIT {limit}"
        result = self.graph.run(query)
        return [record['p'] for record in result]


    def import_from_dataframe(self, df: pd.DataFrame) -> None:
        """
        从DataFrame批量导入节点和关系（沿用原始逻辑）
        :param df: 包含节点和父级关系的DataFrame
        """

        def process_row(row: pd.Series, tx):
            # 创建当前节点
            current_node = self.create_node(
                node_type=row['type'],
                properties={
                    'name': row['name'],
                    'id': row['id'],
                    'xml': row['xml']
                }
            )

            # 处理父节点关系
            if pd.notna(row['parent_name']) and row['parent_type']:
                parent_node = self.get_node_by_name(row['parent_type'], row['parent_name'])
                if not parent_node:
                    parent_node = self.create_node(
                        node_type=row['parent_type'],
                        properties={'name': row['parent_name']}
                    )
                self.create_relationship(current_node, row['relationship'], parent_node)

        tx = self.graph.begin()
        try:
            df.apply(lambda row: process_row(row, tx), axis=1)
            tx.commit()
        except Exception as e:
            tx.rollback()
            raise e

    def delete_all_data(self) -> None:
        """清空数据库所有数据"""
        tx = self.graph.begin()
        try:
            tx.run("MATCH (n) DETACH DELETE n")
            tx.commit()
        except Exception as e:
            tx.rollback()
            raise e

    def longest_list(self, lst: list) -> list:
        valid_lists = []
        for item in lst:
            if isinstance(item, list):
                valid_lists.append(item)
        if not valid_lists:
            return []
        return max(valid_lists, key=len)

    def get_all_parent_nodes(self, start_node_type: str):
        """
        连续查询父节点直至节点类型为PROJECT
        :param start_node_type: 起始节点类型（如 MEASLOC）
        :return: 父节点链列表（从底层到PROJECT，包含PROJECT节点）
        """

        parent_chain = []

        node_query = f"MATCH (a:{start_node_type}) return a"
        node_list = self.graph.run(node_query).data()

        for node_dicts in node_list:
            start_node = node_dicts['a']

            if not start_node:
                raise ValueError(f"起始节点 {start_node_type}不存在")

            # 检查起始节点是否有有效标签
            if not start_node.labels:
                raise ValueError(f"起始节点 {start_node_type} 无有效标签")

            current_node = start_node

            chain_current = [current_node]
            while "PROJECT" not in current_node.labels:
                # 使用当前节点的实际标签（可能与起始类型不同）
                current_node_type = next(iter(current_node.labels))  # 确保标签存在（初始化已检查）

                # 构造查询：通过节点类型查找父节点（假设关系方向为子节点->父节点）
                query = f"""
                   MATCH (current:{current_node_type})-[r]->(parent)
                   RETURN parent
                   """

                result = self.graph.run(query).data()

                if not result:
                    break  # 无父节点，终止遍历

                parent_node = result[0].get("parent")
                if not parent_node or not parent_node.labels:
                    raise ValueError("父节点数据异常，缺少标签或节点对象")

                current_node = parent_node
                chain_current.append(current_node)

            parent_chain.append(chain_current)

            # 处理顶层PROJECT节点（若未包含）
            if "PROJECT" in current_node.labels and current_node not in parent_chain:
                parent_chain.append(current_node)

        target_node = self.longest_list(parent_chain)

        return target_node


    def get_any_node_by_label(self, label: str):
        """
        根据节点类型（label）返回库中任意一个节点（未指定名称时随机返回一个）
        :param label: 节点类型（如 "PROJECT", "MEASLOC"）
        :return: 匹配的节点对象（Node）或 None（无匹配节点时）
        """
        query = f"MATCH (n:{label}) RETURN n LIMIT 1"
        result = self.graph.run(query).data()

        if not result:
            return None  # 无匹配节点

        # 返回第一个匹配的节点（py2neo.Node 对象）
        return result[0]['n']


if __name__ == '__main__':

    handler = Neo4jHandler(
        url="bolt://10.1.5.196:17687",
        username="neo4j",
        password="123456789"
    )

    # # 1. 创建节点
    # project_node = handler.create_node(
    #     node_type="PROJECT",
    #     properties={'name': 'Project X', 'id': 'P001', 'xml': '<project/>'}
    # )
    # enterprise_node = handler.create_node(
    #     node_type="ENTERPRISE",
    #     properties={'name': 'Company Y', 'id': 'E001', 'xml': '<enterprise/>'}
    # )
    #
    # # 2. 创建关系
    # handler.create_relationship(
    #     from_node=project_node,
    #     rel_type="BELONGS_TO",
    #     to_node=enterprise_node
    # )
    #
    # # 3. 按名称检索节点
    # retrieved_node = handler.get_node_by_name("PROJECT", "Project X")
    # print(f"检索到节点: {retrieved_node['name']}")
    #
    # # 4. 根据关系查询路径
    # related_paths = handler.get_related_nodes_by_relationship("BELONGS_TO")
    # for path in related_paths:
    #     print(path)
    #
    # # 5. 更新节点属性
    # handler.update_node_property(retrieved_node, 'xml', '<updated_project/>')

    # 6. 删除节点（级联删除关系）
    # handler.delete_node(enterprise_node)

    # 7. 批量导入数据（沿用原始CSV导入逻辑）
    # df = pd.read_csv('node_hierarchy.csv')
    # handler.import_from_dataframe(df)

    # 8. 清空数据库
    # handler.delete_all_data()

    # # 9. 连续查询父节点直至PROJECT
    # parent_nodes = handler.get_all_parent_nodes_until_project(
    #     start_node_type="SITE"
    # )
    #
    # print("父节点链（直至PROJECT）:")
    # for node in parent_nodes:
    #     if node:
    #         print(f"节点类型: {', '.join(node.labels)}, 名称: {node['name']}")

    # list_test = handler.get_any_node_by_label('SITE')
    # for node in list_test:
    #     if node:
    #         print(f"节点类型: {', '.join(node.labels)}")
    # print(list_test)