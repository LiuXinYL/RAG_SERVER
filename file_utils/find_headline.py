from docx import Document
import re


def is_table_caption(paragraph):
    """判断段落是否为表格题注"""
    text = paragraph.text.strip()
    return text.startswith('表') and any(char.isdigit() for char in text)


def is_figure_caption(paragraph):
    """判断段落是否为图片题注"""
    text = paragraph.text.strip()
    return text.startswith('图') and any(char.isdigit() for char in text)


def extract_caption_number(caption_text):
    """从题注文本中提取编号（仅提取首个数字）"""
    numbers = re.findall(r'\d+', caption_text)
    return int(numbers[0]) if numbers else None


def check_continuity(numbers):
    """检查编号列表是否连续（从1开始且无间隔）"""
    if not numbers:
        return True  # 无编号时视为"空连续"
    sorted_nums = sorted(numbers)
    return sorted_nums == list(range(1, len(sorted_nums) + 1))


def identify_and_check_captions(doc):
    """识别题注并检查连续性"""
    try:

        table_captions = []
        figure_captions = []

        # 遍历段落收集题注
        for para in doc.paragraphs:
            if is_table_caption(para):
                num = extract_caption_number(para.text)
                if num:
                    table_captions.append(para.text)
            elif is_figure_caption(para):
                num = extract_caption_number(para.text)
                if num:
                    figure_captions.append(para.text)

        # 提取编号用于连续性检查
        table_nums = [extract_caption_number(caption) for caption in table_captions]
        figure_nums = [extract_caption_number(caption) for caption in figure_captions]

        # 生成结果
        result = {
            "table_captions": table_captions,
            "figure_captions": figure_captions,
            "table_continuous": check_continuity(table_nums),
            "figure_continuous": check_continuity(figure_nums),
            "table_nums": table_nums,
            "figure_nums": figure_nums
        }
        return result

    except Exception as e:
        return f"处理文档时出错: {str(e)}"


def find_missing_numbers(numbers):
    """找出不连续编号中缺失的编号"""
    if not numbers:
        return []
    sorted_nums = sorted(numbers)
    full_range = set(range(1, sorted_nums[-1] + 1))
    existing_nums = set(sorted_nums)
    return sorted(full_range - existing_nums)


def format_result(result):
    """格式化输出结果"""
    if isinstance(result, str):
        return {"checkName": "处理文件时出错", "result": False, "message": result}

    output = []

    # 处理表格题注
    if result["table_continuous"]:
        output.append(
            {"checkName": "表格题注编号检测", "result": True, "message": f"表格题注编号连续。"}
        )
    else:
        missing_table_nums = find_missing_numbers(result["table_nums"])
        missing_table_str = ', '.join([f'表{num}' for num in missing_table_nums])
        output.append(
            {"checkName": "表格题注编号检测", "result": False, "message": f"表格题注编号不连续，缺乏{missing_table_str}。"}
        )
    # 处理图片题注
    if result["figure_continuous"]:
        output.append(
            {"checkName": "图片题注编号检测", "result": True, "message": f"图片题注编号连续。"}
        )
    else:
        missing_figure_nums = find_missing_numbers(result["figure_nums"])
        missing_figure_str = ', '.join([f'图{num}' for num in missing_figure_nums])
        output.append(
            {"checkName": "图片题注编号检测", "result": False, "message": f"图片题注编号不连续，缺乏{missing_figure_str}。"}
        )
    return output



if __name__ == "__main__":

    doc_path = 'C:/Users/16000/Desktop/小红小明测试.docx'
    doc = Document(doc_path)

    result = identify_and_check_captions(doc)
    output_result = format_result(result)
    # print(output_result)