import xml.etree.ElementTree as ET
import csv
import os
from glob import glob

NODE_TYPE_MAPPING = {
    'PROJECT': 'PROJECT',
    'ENTERPRISE': 'ENTERPRISE',
    'SITE': 'SITE',
    'SEGMENT': 'SEGMENT',
    'ASSET': 'ASSET',
    'MEASLOC': 'MEASLOC'
}

HIERARCHY = ["PROJECT", "ENTERPRISE", "SITE", "SEGMENT", "ASSET", "MEASLOC"]


def get_node_xml(element):
    # 获取当前节点的类型
    current_node_type = NODE_TYPE_MAPPING.get(element.tag, 'UNKNOWN')
    # 找到当前节点类型在层级关系中的索引
    current_index = HIERARCHY.index(current_node_type) if current_node_type in HIERARCHY else -1
    # 确定下个层级节点的类型
    next_level_type = HIERARCHY[current_index + 1] if current_index < len(HIERARCHY) - 1 else None

    new_element = ET.Element(element.tag)
    new_element.attrib = element.attrib.copy()
    for child in element:
        child_tag = child.tag
        child_type = NODE_TYPE_MAPPING.get(child_tag, 'UNKNOWN')
        # 过滤掉下个层级的节点
        if child_type != next_level_type:
            child_copy = ET.Element(child_tag)
            child_copy.attrib = child.attrib.copy()
            new_element.append(child_copy)

    xml_str = '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>\n'
    xml_str += ET.tostring(new_element, encoding='unicode', method='xml')

    return xml_str


def build_node_hierarchy(root_element, file_id):
    hierarchy = []
    stack = [(root_element, None, None)]

    while stack:
        current_node, parent_name, parent_type = stack.pop()
        node_tag = current_node.tag

        # 跳过 WTICD 节点及其子节点
        if node_tag == 'WTICD':
            continue

        node_type = NODE_TYPE_MAPPING.get(node_tag, 'UNKNOWN')
        node_name = current_node.get('NodeName', '')

        if node_type != 'UNKNOWN':
            hierarchy.append({
                'id': file_id,
                'parent_name': parent_name or 'None',
                'parent_type': parent_type or 'None',
                'name': node_name,
                'type': node_type,
                'xml': get_node_xml(current_node)
            })

        for child in reversed(current_node):
            if child.tag == 'WTICD':
                continue
            child_name = child.get('NodeName', '')
            child_type = NODE_TYPE_MAPPING.get(child.tag, None)
            if child_type is not None:
                stack.append((child, node_name, node_type))

    return hierarchy


def save_to_csv(records, csv_path, header):
    with open(csv_path, 'a', newline='', encoding='UTF-8') as csvfile:
        writer = csv.writer(csvfile)
        if os.path.getsize(csv_path) == 0:
            writer.writerow(header)
        for record in records:
            writer.writerow([
                record['id'],
                record['parent_name'],
                record['parent_type'],
                record['name'],
                record['type'],
                record['xml']
            ])


def process_xml_file(xml_path, output_dir):
    file_name = os.path.basename(xml_path)
    file_id = os.path.splitext(file_name)[0]

    try:
        with open(xml_path, 'r', encoding='UTF-8') as f:
            xml_content = f.read()
        xml_content = xml_content.replace("&#x0A;", "\n")

        root = ET.fromstring(xml_content)

        if root.tag != 'PROJECT':
            print(f"警告：{file_name} 根节点不是 PROJECT，跳过")
            return []

        return build_node_hierarchy(root, file_id)

    except ET.ParseError as e:
        print(f"解析错误在文件 {file_name} 的第 {e.lineno} 行，列 {e.offset}:")
        print(f"错误详情: {e.msg}")
        print(f"附近内容: {xml_content[max(0, e.offset - 50):e.offset + 50]}...")
        return []

    except UnicodeDecodeError as e:
        print(f"文件编码错误：{file_name} 无法使用 GBK 解码（错误位置：第 {e.start} 字节）")
        print(f"请检查文件是否为 GBK/UTF-8 编码，或尝试修改代码中的 encoding 参数")
        return []
    except Exception as e:
        print(f"处理 {file_name} 出错：{str(e)}")
        return []


def batch_process_xml(input_dir, output_dir, csv_filename="node_hierarchy.csv"):
    os.makedirs(output_dir, exist_ok=True)
    csv_path = os.path.join(output_dir, csv_filename)
    header = [
        "id",
        "parent_name",
        "parent_type",
        "name",
        "type",
        "xml"
    ]

    xml_files = glob(os.path.join(input_dir, "*.xml"))
    for xml_path in xml_files:
        print(f"处理文件：{os.path.basename(xml_path)}")
        records = process_xml_file(xml_path, output_dir)
        if records:
            save_to_csv(records, csv_path, header)

    print(f"处理完成，结果保存至 {csv_path}")


if __name__ == "__main__":
    input_folder = "E:/XJXXKJ/LLM大模型/XML_RAG/一院一部弹箱健康管理系统/test"  # 输入目录（存放 XML 文件）
    output_file = "../data/xml_data"  # 输出目录

    batch_process_xml(input_folder, output_file, 'result_test.csv')