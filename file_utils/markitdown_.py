from markitdown import MarkItDown
import markdown
from docx import Document

def use_markdown(md_path, word_path):

    # 读取Markdown文件内容
    with open(md_path, 'r', encoding='utf-8') as f:
        md_text = f.read()

    # 将Markdown文本转换为HTML格式
    md_text = md_text.split('Language: markdown\n')[1]
    html_text = markdown.markdown(md_text)
    # 创建一个新的Word文档
    doc = Document()

    # 将HTML内容添加到Word文档中
    doc.add_paragraph(html_text)

    # 保存Word文档
    doc.save(word_path)

    return doc

if __name__ == '__main__':

    word_path = 'C:/Users/16000/Desktop/算法开发软件-评分标准-20250703.docx'
    md_path = 'C:/Users/16000/Desktop/算法开发软件-评分标准-20250703.md'


    md = MarkItDown()
    result = md.convert(word_path)
    print(result.text_content)
