import pandas as pd
from docx import Document
import os
import json
import glob
import time
import signal

pd.set_option('display.max_rows', 200)  # 最大显示行数
pd.set_option('display.max_columns', 50)  # 最大显示列数
pd.set_option('display.width', 1000)  # 显示宽度
pd.set_option('display.max_colwidth', 200)  # 每列最大宽度


def create_simplified_file_data(file_name):
    """
    为慢解析或无法解析的文件创建简化的数据结构
    
    Args:
        file_name: 文件名
    
    Returns:
        dict: 简化的文件数据结构
    """
    return {
        'file_info': {
            'filename': file_name,
            'size': 0,
            'lines': 0,
            'parsing_status': 'skipped_slow_parsing',
            'note': '由于解析耗时过长，已跳过详细解析'
        },
        'functions': [],  # 空函数列表
        'statistics': {
            'total_functions': 0,
            'total_lines': 0,
            'complexity_score': 0,
            'parsing_time': 0,
            'status': 'simplified'
        }
    }


def convert_json_data_to_dataframe(json_data_dict):
    """
    将json_data_dict转换为DataFrame
    
    Args:
        json_data_dict: 字典，格式为 {'filename': {'file_info': {...}, 'functions': [...], 'statistics': {...}}}
    
    Returns:
        tuple: (file_info_df, functions_df, statistics_df)
    """
    print("Converting json_data_dict to DataFrames...")
    
    # 1. 提取文件信息
    file_info_data = []
    for filename, data in json_data_dict.items():
        if 'file_info' in data:
            file_info = data['file_info'].copy()
            file_info['filename'] = filename
            file_info_data.append(file_info)
    
    file_info_df = pd.DataFrame(file_info_data) if file_info_data else pd.DataFrame()
    
    # 2. 提取函数信息
    functions_data = []
    for filename, data in json_data_dict.items():
        if 'functions' in data and isinstance(data['functions'], list):
            for func in data['functions']:
                func_info = func.copy()
                func_info['filename'] = filename
                functions_data.append(func_info)
    
    functions_df = pd.DataFrame(functions_data) if functions_data else pd.DataFrame()
    
    # 3. 提取统计信息
    statistics_data = []
    for filename, data in json_data_dict.items():
        if 'statistics' in data:
            stats = data['statistics'].copy()
            stats['filename'] = filename
            statistics_data.append(stats)
    
    statistics_df = pd.DataFrame(statistics_data) if statistics_data else pd.DataFrame()
    
    print(f"创建的DataFrames:")
    print(f"- file_info_df: {len(file_info_df)} 行")
    print(f"- functions_df: {len(functions_df)} 行")
    print(f"- statistics_df: {len(statistics_df)} 行")
    
    return file_info_df, functions_df, statistics_df

def convert_json_data_to_single_dataframe(json_data_dict):
    """
    将json_data_dict转换为单个扁平化的DataFrame
    
    Args:
        json_data_dict: 字典，格式为 {'filename': {'file_info': {...}, 'functions': [...], 'statistics': {...}}}
    
    Returns:
        pd.DataFrame: 包含所有信息的扁平化DataFrame
    """
    print("Converting json_data_dict to single flattened DataFrame...")
    
    all_data = []
    
    for filename, data in json_data_dict.items():
        # 基础行数据
        row_data = {'filename': filename}
        
        # 添加文件信息（加前缀避免冲突）
        if 'file_info' in data:
            for key, value in data['file_info'].items():
                row_data[f'file_info_{key}'] = value
        
        # 添加统计信息（加前缀避免冲突）
        if 'statistics' in data:
            for key, value in data['statistics'].items():
                row_data[f'statistics_{key}'] = value
        
        # 添加函数数量信息
        if 'functions' in data and isinstance(data['functions'], list):
            row_data['functions_count'] = len(data['functions'])
            
            # 如果有函数，为每个函数创建一行
            if data['functions']:
                for i, func in enumerate(data['functions']):
                    func_row = row_data.copy()
                    for key, value in func.items():
                        func_row[f'function_{key}'] = value
                    func_row['function_index'] = i
                    all_data.append(func_row)
            else:
                # 如果没有函数，仍然保留文件级别的信息
                all_data.append(row_data)
        else:
            # 如果没有函数信息，保留文件级别的信息
            row_data['functions_count'] = 0
            all_data.append(row_data)
    
    df = pd.DataFrame(all_data)
    print(f"创建的DataFrame包含 {len(df)} 行，{len(df.columns)} 列")
    
    return df 


def step1_extract_docx_tables(report_path):
    """
    第一步：提取表格中带有ID的表格，将其转为dataframe
    """
    print("Step 1: 提取Word文档中的ID表格...")
    
    # 加载 Word 文档
    doc = Document(report_path)
    
    # 用于存储提取的表格数据
    all_tables = []
    
    # 遍历文档中的所有表格
    for table in doc.tables:
        table_data = []
        # 提取表头（第一行）
        headers = [cell.text.strip() for cell in table.rows[0].cells]
        # 提取表格内容（从第二行开始）
        for row in table.rows[1:]:
            row_data = [cell.text.strip() for cell in row.cells]
            table_data.append(row_data)
        # 将当前表格数据和表头存入列表
        all_tables.append({"headers": headers, "data": table_data})
    
    # 查找包含ID列的表格
    report_df = pd.DataFrame()
    for tbl in all_tables:
        if 'ID' in tbl["headers"] and 'Line' in tbl["headers"]:
            report_df = pd.DataFrame(
                data=tbl["data"],
                columns=tbl["headers"]
            )
            break
    
    if report_df.empty:
        raise ValueError("未找到包含ID和Line列的表格")
    
    print(f"提取到表格，包含 {len(report_df)} 行数据")
    print(f"表格列名: {list(report_df.columns)}")
    return report_df

def step2_read_csv(csv_path):
    """
    第二步：读取output.csv转换为dataframe
    """
    print("Step 2: 读取CSV文件...")
    
    csv_df = pd.read_csv(csv_path)
    
    # 处理数据格式，参考原代码逻辑
    csv_df['id'] = csv_df['id'].astype(str)
    csv_df['file'] = csv_df['file'].apply(lambda x: os.path.basename(x))
    
    # 解析code字段
    csv_df['knowledge_name'] = csv_df['code'].apply(lambda x: x.split('.')[1] if len(x.split('.')) > 1 else '')
    csv_df['knowledge_code'] = csv_df['code'].apply(lambda x: x.split('.')[2] if len(x.split('.')) > 2 else '')
    
    print(f"CSV数据包含 {len(csv_df)} 行")
    print(f"CSV列名: {list(csv_df.columns)}")
    return csv_df

def step3_join_dataframes(report_df, csv_df):
    """
    第三步：根据ID,FILE和id,file关联两表格（left_join）
    """
    print("Step 3: 关联表格数据...")
    
    # 处理文件名，确保一致性
    report_df['File'] = report_df['File'].apply(lambda x: os.path.basename(x))
    
    # 选择需要的列
    report_df_selected = report_df[['ID', 'File', 'Line', 'Rule']]
    csv_df_selected = csv_df[['id', "file", 'knowledge_name', 'knowledge_code', 'title', 'message']]
    
    # 执行left join
    joined_df = pd.merge(report_df_selected, csv_df_selected, 
                        left_on=['ID', 'File'], 
                        right_on=['id', "file"], 
                        how='left')

    joined_df.drop(columns=['id', "file"], inplace=True)
    print(f"关联后数据包含 {len(joined_df)} 行")
    return joined_df

def step4_read_json_files(joined_df, code_info_json_dir):
    """
    第四步：根据FILE字段路径的文件名读取code_info_json下的对应json文件
    """
    print("Step 4: 读取对应的JSON文件...")
    
    # 定义需要特殊处理的慢解析文件列表
    slow_parsing_files = {
        'MC25CM_Dir-1.1-C11.c': '包含大量长标识符和嵌套结构的MISRA测试文件',
        'MC25CM_Dir-1.1-C99-C11-0380.h': '宏定义过多的头文件',
        'MC25CM_Dir-1.1-C99-C11-0388.h': '包含深度嵌套的头文件'
    }
    
    json_data_dict = {}
    unique_files = joined_df['File'].dropna().unique()
    
    for file_name in unique_files:
        # 检查是否为慢解析文件
        if file_name in slow_parsing_files:
            print(f"⚠️  跳过慢解析文件: {file_name} - {slow_parsing_files[file_name]}")
            # 为慢解析文件创建简化的数据结构
            json_data_dict[file_name] = create_simplified_file_data(file_name)
            continue
            
        # 构造对应的JSON文件名
        # 例如：MC25CM_amain.c -> MC25CM_amain_c_analysis.json
        # 只替换最后一个点（文件扩展名前的点）
        if '.' in file_name:
            name_part, ext_part = file_name.rsplit('.', 1)
            json_file_name = f"{name_part}_{ext_part}_analysis.json"
        else:
            json_file_name = f"{file_name}_analysis.json"
        json_file_path = os.path.join(code_info_json_dir, json_file_name)
        
        if os.path.exists(json_file_path):
            try:
                with open(json_file_path, 'r', encoding='utf-8') as f:
                    json_data = json.load(f)
                    json_data_dict[file_name] = json_data
                    print(f"成功读取: {json_file_name}")
            except Exception as e:
                print(f"读取JSON文件失败 {json_file_name}: {e}")
                # 如果读取失败，也创建简化数据
                json_data_dict[file_name] = create_simplified_file_data(file_name)
        else:
            print(f"未找到对应JSON文件: {json_file_name}")
            # 如果文件不存在，创建简化数据
            json_data_dict[file_name] = create_simplified_file_data(file_name)
    
    return json_data_dict

def step5_locate_functions(joined_df, functions_df):
    """
    第五步：根据Line字段和functions_df中的start_line、end_line定位函数代码块，得到functions信息
    """
    print("Step 5: 定位函数代码块...")
    
    function_matches = []
    
    for index, row in joined_df.iterrows():
        file_name = row['File']
        line_number = row['Line']
        
        # 确保line_number是数字
        try:
            line_number = int(line_number)
        except (ValueError, TypeError):
            continue
            
        # 从functions_df中查找对应文件的函数
        file_functions = functions_df[functions_df['filename'] == file_name]
        
        if not file_functions.empty:
            # 查找包含该行号的函数
            for func_index, func_row in file_functions.iterrows():
                start_line = func_row.get('start_line')
                end_line = func_row.get('end_line')
                
                # 确保start_line和end_line是数字
                try:
                    start_line = int(start_line) if start_line is not None else None
                    end_line = int(end_line) if end_line is not None else None
                except (ValueError, TypeError):
                    continue
                
                if start_line and end_line:
                    if start_line <= line_number <= end_line:
                        function_match = {
                            'ID': row['ID'],
                            'File': file_name,
                            'Line': str(line_number),
                            'function_name': func_row.get('name'),
                            'function_return_type': func_row.get('return_type'),
                            'function_start_line': start_line,
                            'function_end_line': end_line,
                            'function_parameters': func_row.get('parameters', []),
                            'function_dependencies': func_row.get('dependencies', []),
                            'function_complexity': func_row.get('complexity_score'),
                            'function_body': func_row.get('body_content', '')
                        }
                        function_matches.append(function_match)
    
    result_functions_df = pd.DataFrame(function_matches)
    print(f"找到 {len(result_functions_df)} 个函数匹配")
    return result_functions_df

def step6_final_join(joined_df, function_df):
    """
    第六步：关联第三步中的dataframe和第五步中的functions
    """
    print("Step 6: 最终关联数据...")
    
    # 检查输入数据的有效性
    if joined_df.empty:
        print("警告：joined_df 为空，无法进行关联")
        return pd.DataFrame()
    
    if function_df.empty:
        print("警告：未找到匹配的函数，返回原始关联数据")
        return joined_df
    
    # 基于index进行关联
    final_df = pd.merge(joined_df.reset_index(), function_df, 
                       left_on=['ID', 'File', 'Line'], 
                       right_on=['ID', 'File', 'Line'],
                       how='left',
                       suffixes=('', '_func'),
                    )
    final_df.drop(columns=['index'], inplace=True)
    
    print(f"最终数据包含 {len(final_df)} 行")
    return final_df

def context_data_flow():
    """主函数：执行完整的6步处理流程"""
    
    # 文件路径配置
    report_path = 'E:/python_project/D_large_models/RAG_SERVER/QAC/context/compliance_report.docx'
    csv_path = 'E:/python_project/D_large_models/RAG_SERVER/QAC/context/output.csv'
    code_info_json_dir = 'E:/python_project/D_large_models/RAG_SERVER/QAC/code_info_json'
    
    try:
        # 第一步：提取Word表格
        report_df = step1_extract_docx_tables(report_path)
        
        # 第二步：读取CSV
        csv_df = step2_read_csv(csv_path)
        
        # 第三步：关联表格
        joined_df = step3_join_dataframes(report_df, csv_df)
        
        # 第四步：读取JSON文件, 转为dataframe
        json_data_dict = step4_read_json_files(joined_df, code_info_json_dir)
        file_info_df, functions_df, statistics_df = convert_json_data_to_dataframe(json_data_dict)
        
        # 第五步：定位函数
        function_df = step5_locate_functions(joined_df, functions_df)

        # 第六步：最终关联
        final_df = step6_final_join(joined_df, function_df)
        
        # 保存结果
        output_path = '/QAC/context/enhanced_analysis_result.csv'
        final_df.to_csv(output_path, index=False, encoding='utf-8-sig')
        print(f"\n处理完成！结果已保存到: {output_path}")
        
        # 显示结果摘要
        print("\n=== 结果摘要 ===")
        print(f"最终数据行数: {len(final_df)}")
        print(f"包含函数信息的行数: {len(final_df[final_df['function_name'].notna()])}")
        
        # 显示前几行结果
        print("\n=== 前5行数据预览 ===")
        display_columns = ['ID', 'File', 'Line', 'Rule', 'function_name', 'function_start_line', 'function_end_line']
        available_columns = [col for col in display_columns if col in final_df.columns]
        print(final_df[available_columns].head())
        
        return final_df
        
    except Exception as e:
        print(f"处理过程中出现错误: {e}")
        raise

if __name__ == '__main__':
    result_df = context_data_flow() 
