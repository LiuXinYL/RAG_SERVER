import os
import sys
import json
from config import LLM_CONFIG, PROJECT_PATH, VECTOR_SAVE_PATH, INDEX_FILE_PATH
from custom_faiss import FAISSCUSTOM

# 获取当前项目目录的绝对路径
current_dir = os.path.abspath(os.path.dirname(__file__))
# 添加到 sys.path
sys.path.append(current_dir)

def get_knowledge_base_names(faiss_custom):
    """
    统计 vector_store 文件夹下的知识库名称
    """


    vector_store_path = os.path.join(PROJECT_PATH, VECTOR_SAVE_PATH)
    base_names = []
    for root, dirs, files in os.walk(str(vector_store_path), topdown=True):
        # 限制最多 3 级目录
        depth = root[len(vector_store_path):].count(os.sep)
        if depth > 2:
            del dirs[:]
            continue
        for dir_name in dirs:
            full_dir_path = os.path.join(root, dir_name)
            try:
                # 尝试加载 faiss 索引
                index_file = os.path.join(full_dir_path, "index.faiss")
                if os.path.exists(index_file):

                    faiss_custom.load(full_dir_path, allow_dangerous = True)
                    base_names.append(os.path.join(root, dir_name).replace(str(vector_store_path) + os.sep, ''))
            except Exception as e:
                print(f"无法加载 {full_dir_path} 作为 faiss 索引，原因: {str(e)}")
    return base_names

def save_knowledge_base_index(index_data):
    """
    将知识库索引列表保存到本地文件
    """

    try:
        with open(INDEX_FILE_PATH, 'w', encoding='utf-8') as f:
            json.dump(index_data, f, ensure_ascii=False, indent=4)
        print(f"知识库索引 已保存到 {INDEX_FILE_PATH}")
    except Exception as e:
        print(f"保存知识库索引时出错: {str(e)}")


def update_knowledge_base_index(faiss_custom):
    """
    更新知识库索引列表
    """
    base_names = get_knowledge_base_names(faiss_custom)
    # 构建字典格式数据
    index_data = {name: False for name in base_names}  # key 为知识库名称，value 为是否父子切分的标记
    save_knowledge_base_index(index_data)
    return index_data


def load_knowledge_base_index():
    """
    从本地文件加载知识库索引列表
    """
    try:
        if os.path.exists(INDEX_FILE_PATH):
            with open(INDEX_FILE_PATH, 'r', encoding='utf-8') as f:
                index_data = json.load(f)
            print(f"知识库索引已从 {INDEX_FILE_PATH} 加载")
            return index_data
        else:
            print("未找到知识库索引文件，使用空数据")
            return {"knowledge": [], "parent_child": {}}
    except Exception as e:
        print(f"加载知识库索引时出错: {str(e)}")
        return {"knowledge": {}}


def change_knowledge_base_index(index_data, knowledge_repository_names: str):
    """
    更改知识库索引列表-更改父子切分标记
    """

    index_data.update({knowledge_repository_names: True})

    save_knowledge_base_index(index_data)

    return index_data


if __name__ == '__main__':

    faiss_custom = FAISSCUSTOM()

    # 根据当前的 vector_store 文件夹初始化知识库索引
    print("开始初始化知识库索引...")
    update_knowledge_base_index(faiss_custom)
    print("知识库索引初始化完成。")

    # change_knowledge_base_index('ww')
