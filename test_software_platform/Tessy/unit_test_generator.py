#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
单元测试生成器
完整的C代码单元测试生成系统
"""

import os
import sys
import json
import pandas as pd
from pathlib import Path
from typing import Dict, List, Any, Optional, Tuple
from dataclasses import dataclass
import logging

# 添加项目根目录到路径
project_root = Path(__file__).parent.parent
sys.path.append(str(project_root))

# 添加当前工作目录到路径
current_dir = Path.cwd()
sys.path.append(str(current_dir))

# 导入必要的模块
try:
    # 尝试从项目根目录导入
    sys.path.append(str(Path(__file__).parent.parent.parent))
    from llm_init import LLM_INIT
    from config import LLM_CONFIG
    LLM_AVAILABLE = True
except ImportError as e:
    LLM_AVAILABLE = False
    print(f"警告: 无法导入LLM模块 - {e}")
    print("提示: 这不会影响核心功能，但LLM相关功能将被禁用")

try:
    # 尝试多种导入方式
    try:
        from test_software_platform.QAC.enhanced_c_parser import EnhancedCParser
        ENHANCED_PARSER_AVAILABLE = True
    except ImportError:
        # 尝试相对导入
        sys.path.append(str(Path(__file__).parent.parent))
        from QAC.enhanced_c_parser import EnhancedCParser
        ENHANCED_PARSER_AVAILABLE = True
except ImportError as e:
    ENHANCED_PARSER_AVAILABLE = False
    print(f"警告: 无法导入增强版C解析器 - {e}")
    print("提示: 将使用基础解析功能")

# 在导入部分添加prompt管理器的导入
try:
    from .prompt_manager import UnitTestPromptManager
    PROMPT_MANAGER_AVAILABLE = True
except ImportError:
    try:
        from prompt_manager import UnitTestPromptManager
        PROMPT_MANAGER_AVAILABLE = True
    except ImportError as e:
        PROMPT_MANAGER_AVAILABLE = False
        print(f"警告: 无法导入单元测试Prompt管理器 - {e}")
        print("提示: 将使用默认prompt构建逻辑")

# 配置日志
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)

@dataclass
class TestCase:
    """测试用例数据结构"""
    test_name: str
    input_values: Dict[str, Any]
    expected_output: Any
    description: str
    test_id: str = ""
    boundary_type: str = "normal"  # normal, boundary, edge_case
    coverage_target: str = ""
    priority: str = ""

class FilePairMatcher:
    """文件对匹配器"""
    
    @staticmethod
    def find_matching_files(base_name: str, code_dir: str, excel_dir: str) -> Tuple[Optional[str], Optional[str]]:
        """
        第一步：判断C文件和Excel文件是否为名字统一的文件对
        
        Args:
            base_name: 基础文件名（不含扩展名）
            code_dir: C代码目录
            excel_dir: Excel文件目录
            
        Returns:
            (c_file_path, excel_file_path) 元组
        """
        code_path = Path(code_dir)
        excel_path = Path(excel_dir)
        
        # 查找C文件
        c_file = code_path / f"{base_name}.c"
        if not c_file.exists():
            logger.error(f"找不到C文件: {c_file}")
            return None, None
        
        # 尝试多种可能的Excel文件名
        possible_excel_names = [
            f"{base_name}.xlsx",
            f"{base_name.replace('_', '').replace('-', '')}.xlsx",
            f"{base_name.replace('val', 'value')}.xlsx",
            f"{base_name.replace('value', 'val')}.xlsx",
            f"{base_name}_test.xlsx",
            f"{base_name}_cases.xlsx"
        ]
        
        excel_file = None
        for excel_name in possible_excel_names:
            temp_excel_file = excel_path / excel_name
            if temp_excel_file.exists():
                excel_file = temp_excel_file
                break
        
        if excel_file is None:
            logger.warning(f"找不到对应的Excel文件，尝试了: {possible_excel_names}")
            return str(c_file), None
        
        logger.info(f"找到匹配的文件对:")
        logger.info(f"  C文件: {c_file}")
        logger.info(f"  Excel文件: {excel_file}")
        
        return str(c_file), str(excel_file)
    
    @staticmethod
    def find_folder_pairs(code_dir: str, excel_dir: str) -> List[Tuple[str, str, str]]:
        """
        查找文件夹对，每个文件夹包含一组测试数据
        
        Args:
            code_dir: C代码根目录
            excel_dir: Excel文件根目录
            
        Returns:
            文件夹对列表，每个元素为 (folder_name, code_folder_path, excel_folder_path)
        """
        code_path = Path(code_dir)
        excel_path = Path(excel_dir)
        
        if not code_path.exists():
            logger.error(f"C代码目录不存在: {code_path}")
            return []
        
        if not excel_path.exists():
            logger.error(f"Excel目录不存在: {excel_path}")
            return []
        
        # 获取code目录下的所有子文件夹
        code_folders = [f for f in code_path.iterdir() if f.is_dir()]
        logger.info(f"在C代码目录中发现 {len(code_folders)} 个文件夹")
        
        folder_pairs = []
        
        for code_folder in code_folders:
            folder_name = code_folder.name
            
            # 查找对应的Excel文件夹
            excel_folder = excel_path / folder_name
            if excel_folder.exists():
                folder_pairs.append((folder_name, str(code_folder), str(excel_folder)))
                logger.info(f"找到文件夹对: {folder_name}")
            else:
                logger.warning(f"找不到对应的Excel文件夹: {excel_folder}")
        
        logger.info(f"总共找到 {len(folder_pairs)} 个文件夹对")
        return folder_pairs
    
    @staticmethod
    def find_files_in_folder(code_folder: str, excel_folder: str) -> List[Tuple[str, str, str]]:
        """
        在文件夹对中查找所有匹配的文件对
        
        Args:
            code_folder: C代码文件夹路径
            excel_folder: Excel文件夹路径
            
        Returns:
            文件对列表，每个元素为 (base_name, c_file_path, excel_file_path)
        """
        code_path = Path(code_folder)
        excel_path = Path(excel_folder)
        
        if not code_path.exists():
            logger.error(f"C代码文件夹不存在: {code_path}")
            return []
        
        if not excel_path.exists():
            logger.error(f"Excel文件夹不存在: {excel_path}")
            return []
        
        # 查找所有C文件
        c_files = list(code_path.glob("*.c")) + list(code_path.glob("*.h"))
        logger.info(f"在C代码文件夹中发现 {len(c_files)} 个文件")
        
        file_pairs = []
        
        for c_file in c_files:
            base_name = c_file.stem
            
            # 尝试多种可能的Excel文件名
            possible_excel_names = [
                f"{base_name}.xlsx",
                f"{base_name.replace('_', '').replace('-', '')}.xlsx",
                f"{base_name.replace('val', 'value')}.xlsx",
                f"{base_name.replace('value', 'val')}.xlsx",
                f"{base_name}_test.xlsx",
                f"{base_name}_cases.xlsx"
            ]
            
            excel_file = None
            for excel_name in possible_excel_names:
                temp_excel_file = excel_path / excel_name
                if temp_excel_file.exists():
                    excel_file = temp_excel_file
                    break
            
            if excel_file:
                file_pairs.append((base_name, str(c_file), str(excel_file)))
                logger.info(f"找到文件对: {base_name}")
            else:
                logger.warning(f"找不到对应的Excel文件: {base_name}")
        
        logger.info(f"在文件夹对中找到 {len(file_pairs)} 个文件对")
        return file_pairs

class CCodeAnalyzer:
    """C代码分析器"""
    
    def __init__(self):
        self.parser_available = ENHANCED_PARSER_AVAILABLE
    
    def analyze_folder(self, code_folder: str, output_dir: str) -> Dict[str, Any]:
        """
        第一步：使用enhanced_c_parser.py解析文件夹下的所有C文件和H文件
        
        Args:
            code_folder: C代码文件夹路径
            output_dir: 输出目录
            
        Returns:
            解析结果字典
        """
        logger.info(f"开始解析文件夹: {code_folder}")
        
        if not self.parser_available:
            logger.error("增强版C解析器不可用")
            return {}
        
        try:
            # 创建输出目录
            output_path = Path(output_dir)
            output_path.mkdir(parents=True, exist_ok=True)
            
            # 创建code_info_json目录
            code_info_dir = Path("code_info_json")
            code_info_dir.mkdir(exist_ok=True)
            
            # 查找所有C和H文件
            code_path = Path(code_folder)
            c_files = list(code_path.glob("*.c")) + list(code_path.glob("*.h"))
            
            if not c_files:
                logger.error(f"在文件夹 {code_folder} 中找不到C或H文件")
                return {}
            
            logger.info(f"找到 {len(c_files)} 个C/H文件")
            
            all_functions = []
            folder_name = code_path.name
            
            # 解析每个文件
            for c_file in c_files:
                logger.info(f"解析文件: {c_file.name}")
                
                # 创建解析器实例
                parser = EnhancedCParser(
                    code_dir=str(c_file.parent),
                    output_dir=str(output_path),
                    timeout=30
                )
                
                # 解析单个文件
                success = parser.parse_single_file(c_file)
                
                if success:
                    # 读取解析结果
                    safe_suffix = c_file.suffix.replace('.', '_')
                    result_file = output_path / f"{c_file.stem}{safe_suffix}_analysis.json"
                    
                    if result_file.exists():
                        with open(result_file, 'r', encoding='utf-8') as f:
                            file_analysis = json.load(f)
                        
                        # 提取函数信息
                        functions = file_analysis.get('functions', [])
                        for func in functions:
                            # 添加文件信息
                            func['source_file'] = c_file.name
                            func['folder_name'] = folder_name
                            
                            # 分析分支信息
                            func['branch_info'] = self._analyze_branches(func.get('body_content', ''))
                            
                        all_functions.extend(functions)
                        logger.info(f"从文件 {c_file.name} 中提取了 {len(functions)} 个函数")
                    else:
                        logger.warning(f"解析器未为文件 {c_file.name} 生成结果文件")
                else:
                    logger.warning(f"文件 {c_file.name} 解析失败")
            
            # 保存合并的解析结果
            combined_result = {
                'folder_name': folder_name,
                'source_folder': code_folder,
                'total_files': len(c_files),
                'total_functions': len(all_functions),
                'functions': all_functions,
                'analysis_timestamp': pd.Timestamp.now().isoformat()
            }
            
            # 保存到code_info_json目录
            result_file = code_info_dir / f"{folder_name}_analysis.json"
            with open(result_file, 'w', encoding='utf-8') as f:
                json.dump(combined_result, f, ensure_ascii=False, indent=2)
            
            logger.info(f"成功解析文件夹 {folder_name}，发现 {len(all_functions)} 个函数")
            return combined_result
                
        except Exception as e:
            logger.error(f"解析文件夹时出错: {e}")
            return {}
    
    def _analyze_branches(self, function_body: str) -> Dict[str, Any]:
        """分析函数中的分支信息"""
        branch_info = {
            'if_statements': 0,
            'switch_statements': 0,
            'for_loops': 0,
            'while_loops': 0,
            'branch_coverage_target': 90  # 目标覆盖率90%
        }
        
        try:
            # 简单的分支统计
            branch_info['if_statements'] = function_body.count('if (')
            branch_info['switch_statements'] = function_body.count('switch (')
            branch_info['for_loops'] = function_body.count('for (')
            branch_info['while_loops'] = function_body.count('while (')
            
            # 计算总分支数
            total_branches = (branch_info['if_statements'] + 
                            branch_info['switch_statements'] + 
                            branch_info['for_loops'] + 
                            branch_info['while_loops'])
            
            branch_info['total_branches'] = total_branches
            
            # 估算需要的测试用例数以达到90%覆盖率
            if total_branches > 0:
                branch_info['estimated_test_cases'] = max(3, int(total_branches * 1.5))
            else:
                branch_info['estimated_test_cases'] = 3
                
        except Exception as e:
            logger.warning(f"分析分支信息时出错: {e}")
        
        return branch_info
    
    def analyze_file(self, c_file_path: str, output_dir: str) -> Dict[str, Any]:
        """
        解析单个C文件（保持向后兼容）
        
        Args:
            c_file_path: C文件路径
            output_dir: 输出目录
            
        Returns:
            解析结果字典
        """
        logger.info(f"开始解析C文件: {c_file_path}")
        
        if not self.parser_available:
            logger.info("增强版C解析器不可用，使用基础解析功能")
            return self._basic_parse_c_file(c_file_path, output_dir)
        
        try:
            # 创建输出目录
            output_path = Path(output_dir)
            output_path.mkdir(parents=True, exist_ok=True)
            
            # 创建解析器实例
            parser = EnhancedCParser(
                code_dir=str(Path(c_file_path).parent),
                output_dir=str(output_path),
                timeout=30
            )
            
            # 解析单个文件
            file_path_obj = Path(c_file_path)
            success = parser.parse_single_file(file_path_obj)
            
            if success:
                # 读取解析结果
                safe_suffix = file_path_obj.suffix.replace('.', '_')
                result_file = output_path / f"{file_path_obj.stem}{safe_suffix}_analysis.json"
                
                if result_file.exists():
                    with open(result_file, 'r', encoding='utf-8') as f:
                        analysis_result = json.load(f)
                    
                    logger.info(f"成功解析C文件，发现 {len(analysis_result.get('functions', []))} 个函数")
                    return analysis_result
                else:
                    logger.error("解析器未生成结果文件")
                    return self._basic_parse_c_file(c_file_path, output_dir)
            else:
                logger.error("C文件解析失败，使用基础解析功能")
                return self._basic_parse_c_file(c_file_path, output_dir)
                
        except Exception as e:
            logger.error(f"解析C文件时出错: {e}")
            logger.info("回退到基础解析功能")
            return self._basic_parse_c_file(c_file_path, output_dir)
    
    def _basic_parse_c_file(self, c_file_path: str, output_dir: str) -> Dict[str, Any]:
        """基础C文件解析功能"""
        logger.info("使用基础C文件解析功能")
        
        try:
            # 读取C文件内容
            with open(c_file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            # 简单的函数解析
            functions = []
            
            # 查找函数定义
            import re
            
            # 匹配函数定义的正则表达式
            function_pattern = r'(\w+)\s+(\w+)\s*\([^)]*\)\s*\{'
            matches = re.finditer(function_pattern, content)
            
            for match in matches:
                return_type = match.group(1)
                function_name = match.group(2)
                
                # 提取函数体
                start_pos = match.end()
                brace_count = 1
                end_pos = start_pos
                
                for i in range(start_pos, len(content)):
                    if content[i] == '{':
                        brace_count += 1
                    elif content[i] == '}':
                        brace_count -= 1
                        if brace_count == 0:
                            end_pos = i + 1
                            break
                
                function_body = content[start_pos:end_pos]
                
                # 分析参数（简化版本）
                params_match = re.search(r'\(([^)]*)\)', match.group(0))
                parameters = []
                if params_match:
                    params_str = params_match.group(1).strip()
                    if params_str:
                        param_list = [p.strip() for p in params_str.split(',')]
                        for i, param in enumerate(param_list):
                            if param:
                                # 简单的参数解析
                                param_parts = param.split()
                                if len(param_parts) >= 2:
                                    param_type = param_parts[0]
                                    param_name = param_parts[1]
                                    parameters.append({
                                        'name': param_name,
                                        'type': 'input',
                                        'index': i
                                    })
                
                # 分析分支信息
                branch_info = self._analyze_branches(function_body)
                
                function_info = {
                    'name': function_name,
                    'return_type': return_type,
                    'parameters': parameters,
                    'body_content': function_body,
                    'source_file': Path(c_file_path).name,
                    'branch_info': branch_info
                }
                
                functions.append(function_info)
                logger.info(f"发现函数: {function_name}")
            
            analysis_result = {
                'functions': functions,
                'total_functions': len(functions),
                'source_file': c_file_path
            }
            
            logger.info(f"基础解析完成，发现 {len(functions)} 个函数")
            return analysis_result
            
        except Exception as e:
            logger.error(f"基础解析C文件时出错: {e}")
            return {'functions': [], 'total_functions': 0, 'source_file': c_file_path}

class ExcelDataProcessor:
    """Excel数据处理器"""
    
    def __init__(self):
        self.properties_sheet = "Properties"
        self.values_sheet = "Values"
        self.description_field = "Description"
    

    def extract_function_parameters(self, values_data: List[Dict[str, Any]]) -> Dict[str, Any]:
        """从Values工作表提取函数参数信息"""
        if not values_data:
            return {}
        
        # 第一行：参数名称
        param_names = []
        first_row = values_data[0] if values_data else {}
        
        for key, value in first_row.items():
            if key and key != 'nan' and str(value).strip():
                param_names.append(str(value))
        
        # 第二行：i/o类型
        io_types = []
        if len(values_data) > 1:
            second_row = values_data[1]
            for key, value in second_row.items():
                if key and key != 'nan' and str(value).strip():
                    io_types.append(str(value).lower())
        
        # 构建参数信息
        parameters = []
        for i, (name, io_type) in enumerate(zip(param_names, io_types)):
            param_info = {
                'name': name,
                'type': 'input' if io_type == 'i' else 'output',
                'index': i
            }
            parameters.append(param_info)
        
        return {
            'parameters': parameters,
            'input_params': [p for p in parameters if p['type'] == 'input'],
            'output_params': [p for p in parameters if p['type'] == 'output']
        }
    
    
    def _parse_input_values(self, input_values_str: str) -> Dict[str, Any]:
        """解析输入值字符串"""
        try:
            if isinstance(input_values_str, str):
                return json.loads(input_values_str)
            elif isinstance(input_values_str, dict):
                return input_values_str
            else:
                return {}
        except Exception as e:
            logger.warning(f"解析输入值时出错: {e}")
            return {}

class LLMTestGenerator:
    """大模型测试用例生成器"""
    
    def __init__(self):
        self.llm_available = LLM_AVAILABLE
        self.llm_client = None
        self.prompt_manager = None
        
        if self.llm_available:
            try:
                # 第三步：初始化大模型
                self.llm_client = LLM_INIT(
                    max_tokens=LLM_CONFIG.get("max_tokens", 2000),
                    temperature=LLM_CONFIG.get("temperature", 0.7)
                ).create_chat_client()
                logger.info("大模型初始化成功")
            except Exception as e:
                logger.error(f"大模型初始化失败: {e}")
                self.llm_available = False
        
        if PROMPT_MANAGER_AVAILABLE:
            try:
                self.prompt_manager = UnitTestPromptManager()
                logger.info("Prompt管理器初始化成功")
            except Exception as e:
                logger.error(f"Prompt管理器初始化失败: {e}")
    
    def generate_test_cases(self, function_info: Dict[str, Any]) -> List[TestCase]:
        """
        第五步：生成测试用例，重点测试if分支、switch分支，覆盖率90%以上
        
        Args:
            function_info: 函数详细信息
            function_properties: 函数属性信息
            
        Returns:
            生成的测试用例列表
        """
        if not self.llm_available or not self.llm_client:
            logger.warning("大模型不可用，使用模拟测试用例")
            return self._generate_mock_test_cases(function_info)
        
        try:
            # 获取分支信息
            branch_info = function_info.get('branch_info', {})
            target_coverage = branch_info.get('branch_coverage_target', 90)
            estimated_cases = branch_info.get('estimated_test_cases', 5)
            
            logger.info(f"目标覆盖率: {target_coverage}%")
            logger.info(f"估算测试用例数: {estimated_cases}")
            logger.info(f"分支信息: {branch_info}")
            
            # 构建prompt - 使用新的prompt管理器
            if self.prompt_manager:
                try:
                    logger.info("使用prompt管理器创建综合测试prompt")
                    prompt = self.prompt_manager.create_comprehensive_test_prompt(
                        function_info=function_info,
                        branch_info=branch_info,
                    )
                except Exception as e:
                    logger.warning(f"使用prompt管理器创建prompt失败: {e}")
                    logger.info("回退到默认prompt构建逻辑")
                    prompt = self._build_comprehensive_test_prompt(
                        function_info, branch_info
                    )
            else:
                logger.info("使用默认prompt构建逻辑")
                prompt = self._build_comprehensive_test_prompt(
                    function_info, branch_info
                )
            
            # 调用大模型生成测试用例
            from langchain_core.messages import HumanMessage, SystemMessage
            
            # 使用prompt_manager中的系统prompt
            system_prompt = "你是一个专业的C代码单元测试生成专家，专门负责生成高覆盖率的单元测试用例。你的核心任务是分析C函数的if分支和switch分支，生成能够达到90%以上分支覆盖率的测试用例。你具备深入的代码分析能力，能够识别关键执行路径和边界条件。"
            if self.prompt_manager:
                try:
                    system_prompt = self.prompt_manager.get_system_prompt()
                    if not system_prompt:
                        system_prompt = "你是一个专业的C代码单元测试生成专家，专门负责生成高覆盖率的单元测试用例。你的核心任务是分析C函数的if分支和switch分支，生成能够达到90%以上分支覆盖率的测试用例。你具备深入的代码分析能力，能够识别关键执行路径和边界条件。"
                except Exception as e:
                    logger.warning(f"获取系统prompt失败: {e}")
            
            messages = [
                SystemMessage(content=system_prompt),
                HumanMessage(content=prompt)
            ]

            logger.info(f"大模型生成测试用例")
            response = self.llm_client.invoke(messages)
            
            # 处理不同的响应格式
            response_content = self._extract_response_content(response)
            logger.info(f"响应内容长度: {len(response_content)} 字符")
            
            # 解析响应生成测试用例
            test_cases = self._parse_test_cases_response(response_content, function_info)
            
            # 验证覆盖率
            coverage_analysis = self._analyze_test_coverage(test_cases, branch_info)
            logger.info(f"测试覆盖率分析: {coverage_analysis}")
            
            logger.info(f"成功生成 {len(test_cases)} 个测试用例")
            return test_cases
            
        except Exception as e:
            logger.error(f"生成测试用例时出错: {e}")
            return []
    
    def _build_comprehensive_test_prompt(self, function_info: Dict[str, Any],
                                       branch_info: Dict[str, Any]) -> str:
        """构建全面的测试用例生成prompt"""
        
        # 优先使用prompt管理器构建prompt
        if self.prompt_manager:
            try:
                logger.info("使用prompt管理器构建全面测试用例生成prompt")
                return self.prompt_manager.format_comprehensive_test_prompt(
                    function_name=function_info.get('name', 'unknown'),
                    return_type=function_info.get('return_type', 'unknown'),
                    parameters=function_info.get('parameters', []),
                    function_body=function_info.get('body_content', ''),
                    branch_info=branch_info,
                )
            except Exception as e:
                logger.warning(f"使用prompt管理器构建prompt失败: {e}")
                logger.info("回退到默认prompt构建逻辑")
        
        # 回退到原来的prompt构建逻辑
        logger.info("使用默认prompt构建逻辑")
        prompt_lines = []
        prompt_lines.append("## 🎯 高覆盖率单元测试生成")
        prompt_lines.append("")
        prompt_lines.append("### 📍 目标函数信息")
        prompt_lines.append(f"- **函数名**: {function_info.get('name', 'unknown')}")
        prompt_lines.append(f"- **返回类型**: {function_info.get('return_type', 'unknown')}")
        prompt_lines.append(f"- **参数列表**: {self._format_parameters(function_info.get('parameters', []))}")
        prompt_lines.append(f"- **源文件**: {function_info.get('name', 'unknown')}.c")
        prompt_lines.append("")
        
        prompt_lines.append("### 💻 函数代码详情")
        prompt_lines.append("#### 函数体:")
        prompt_lines.append(f"```c\n{function_info.get('body_content', '')}\n```")
        prompt_lines.append("")
        
        # 分支信息
        if branch_info:
            prompt_lines.append("### 🔍 分支分析信息")
            prompt_lines.append("#### 分支统计:")
            prompt_lines.append(f"- **if语句数量**: {branch_info.get('if_statements', 0)}")
            prompt_lines.append(f"- **switch语句数量**: {branch_info.get('switch_statements', 0)}")
            prompt_lines.append(f"- **for循环数量**: {branch_info.get('for_loops', 0)}")
            prompt_lines.append(f"- **while循环数量**: {branch_info.get('while_loops', 0)}")
            prompt_lines.append(f"- **总分支数**: {branch_info.get('total_branches', 0)}")
            prompt_lines.append("- **目标覆盖率**: 90%+")
            prompt_lines.append(f"- **预估测试用例数**: {branch_info.get('estimated_test_cases', 5)}")
            prompt_lines.append("")
        
        # 参数信息
        parameters = function_info.get('parameters', [])
        input_parameters = []
        output_parameters = []
        
        for param in parameters:
            if param.get('type', '').lower() == 'input':
                input_parameters.append(f"- **{param.get('name', 'unknown')}**: {param.get('type', 'unknown')}")
            elif param.get('type', '').lower() == 'output':
                output_parameters.append(f"- **{param.get('name', 'unknown')}**: {param.get('type', 'unknown')}")
        
        input_params_str = '\n'.join(input_parameters) if input_parameters else "无输入参数"
        output_params_str = '\n'.join(output_parameters) if output_parameters else "无输出参数"
        
        prompt_lines.append("### 📊 参数信息")
        prompt_lines.append("#### 输入参数 (i):")
        prompt_lines.append(input_params_str)
        prompt_lines.append("")
        prompt_lines.append("#### 输出参数 (o):")
        prompt_lines.append(output_params_str)
        prompt_lines.append("")
        
        # 生成要求
        prompt_lines.append("### 🎯 生成要求")
        prompt_lines.append("请生成能够达到**90%以上分支覆盖率**的测试用例，重点关注：")
        prompt_lines.append("")
        prompt_lines.append("1. **if分支测试** - 覆盖所有if条件的不同分支")
        prompt_lines.append("   - 条件为真时的执行路径")
        prompt_lines.append("   - 条件为假时的执行路径")
        prompt_lines.append("   - 复合条件的各种组合")
        prompt_lines.append("")
        prompt_lines.append("2. **switch分支测试** - 覆盖所有case分支")
        prompt_lines.append("   - 每个case分支的测试")
        prompt_lines.append("   - default分支的测试")
        prompt_lines.append("   - 边界case值的测试")
        prompt_lines.append("")
        prompt_lines.append("3. **边界值测试** - 测试边界条件和临界值")
        prompt_lines.append("   - 参数的最小值、最大值")
        prompt_lines.append("   - 临界值附近的测试")
        prompt_lines.append("   - 特殊值（0、-1、NULL等）")
        prompt_lines.append("")
        prompt_lines.append("4. **异常情况测试** - 测试错误处理路径")
        prompt_lines.append("   - 无效输入的处理")
        prompt_lines.append("   - 异常状态的恢复")
        prompt_lines.append("   - 错误返回值的验证")
        prompt_lines.append("")
        
        # 输出格式要求
        prompt_lines.append("### 📝 输出格式要求")
        prompt_lines.append("请以JSON格式返回测试用例，格式如下：")
        prompt_lines.append("```json")
        prompt_lines.append("{")
        prompt_lines.append("  \"branch_coverage\": {")
        prompt_lines.append("    \"target_coverage\": 90,")
        prompt_lines.append("    \"estimated_coverage\": \"预估覆盖率百分比\",")
        prompt_lines.append("    \"critical_branches\": [\"关键分支列表\"],")
        prompt_lines.append("    \"coverage_strategy\": \"覆盖率策略说明\"")
        prompt_lines.append("  },")
        prompt_lines.append("  \"test_cases\": [")
        prompt_lines.append("    {")
        prompt_lines.append("      \"test_id\": \"唯一测试ID\",")
        prompt_lines.append("      \"test_name\": \"测试用例名称\",")
        prompt_lines.append("      \"input_values\": {\"参数名\": \"参数值\"},")
        prompt_lines.append("      \"expected_output\": \"期望输出值\",")
        prompt_lines.append("      \"description\": \"测试描述\",")
        prompt_lines.append("      \"branch_type\": \"if/switch/for/while\",")
        prompt_lines.append("      \"coverage_target\": \"覆盖的具体分支\",")
        prompt_lines.append("      \"priority\": \"high/medium/low\"")
        prompt_lines.append("    }")
        prompt_lines.append("  ],")
        prompt_lines.append("  \"coverage_analysis\": {")
        prompt_lines.append("    \"if_branches_covered\": \"if分支覆盖情况\",")
        prompt_lines.append("    \"switch_branches_covered\": \"switch分支覆盖情况\",")
        prompt_lines.append("    \"total_branches_covered\": \"总分支覆盖情况\",")
        prompt_lines.append("    \"coverage_gaps\": [\"覆盖率缺口\"],")
        prompt_lines.append("    \"additional_cases_needed\": \"是否需要额外测试用例\"")
        prompt_lines.append("  }")
        prompt_lines.append("}")
        prompt_lines.append("```")
        prompt_lines.append("")
        
        # 质量标准
        prompt_lines.append("### ✅ 质量标准")
        prompt_lines.append("- **覆盖率要求**: 确保90%以上的分支覆盖率")
        prompt_lines.append("- **分支完整性**: 覆盖所有if和switch分支")
        prompt_lines.append("- **边界完整性**: 包含所有边界条件测试")
        prompt_lines.append("- **可执行性**: 生成的测试用例可以直接执行")
        prompt_lines.append("- **可验证性**: 期望输出必须准确且可验证")
        
        return "\n".join(prompt_lines)
    
    def _analyze_test_coverage(self, test_cases: List[TestCase], branch_info: Dict[str, Any]) -> Dict[str, Any]:
        """分析测试用例的覆盖率"""
        coverage_analysis = {
            'total_test_cases': len(test_cases),
            'total_branches': branch_info.get('total_branches', 0),
            'estimated_coverage': 0,
            'coverage_details': {}
        }
        
        if branch_info.get('total_branches', 0) > 0:
            # 简单估算覆盖率
            estimated_coverage = min(95, len(test_cases) * 15)  # 每个测试用例约覆盖15%的分支
            coverage_analysis['estimated_coverage'] = estimated_coverage
            
            # 分析不同类型的测试用例
            normal_cases = len([tc for tc in test_cases if tc.boundary_type == 'normal'])
            boundary_cases = len([tc for tc in test_cases if tc.boundary_type == 'boundary'])
            edge_cases = len([tc for tc in test_cases if tc.boundary_type == 'edge_case'])
            
            coverage_analysis['coverage_details'] = {
                'normal_cases': normal_cases,
                'boundary_cases': boundary_cases,
                'edge_cases': edge_cases
            }
        
        return coverage_analysis
    
    def _build_test_generation_prompt(self, function_info: Dict[str, Any],
                                    example_cases: List[Dict[str, Any]],
                                    function_properties: Dict[str, Any]) -> str:
        """构建测试用例生成prompt"""
        
        # 优先使用prompt管理器构建prompt
        if self.prompt_manager:
            try:
                logger.info("使用prompt管理器构建测试用例生成prompt")
                return self.prompt_manager.format_single_function_test_prompt(
                    function_name=function_info.get('name', 'unknown'),
                    return_type=function_info.get('return_type', 'unknown'),
                    parameters=function_info.get('parameters', []),
                    function_body=function_info.get('body_content', ''),
                    function_properties=function_properties,
                    example_test_cases=example_cases
                )
            except Exception as e:
                logger.warning(f"使用prompt管理器构建prompt失败: {e}")
                logger.info("回退到默认prompt构建逻辑")
        
        # 回退到原来的prompt构建逻辑
        logger.info("使用默认prompt构建逻辑")
        prompt_lines = []
        prompt_lines.append("请为以下C函数生成全面的单元测试用例：")
        prompt_lines.append("")
        
        # 函数基本信息
        prompt_lines.append("=== 函数基本信息 ===")
        prompt_lines.append(f"函数名: {function_info.get('name', 'unknown')}")
        prompt_lines.append(f"返回类型: {function_info.get('return_type', 'unknown')}")
        prompt_lines.append(f"参数: {self._format_parameters(function_info.get('parameters', []))}")
        prompt_lines.append(f"函数体: {function_info.get('body_content', '')}")
        prompt_lines.append("")
        
        # 函数属性信息
        if function_properties:
            prompt_lines.append("=== 函数属性信息 ===")
            for key, value in function_properties.items():
                prompt_lines.append(f"{key}: {value}")
            prompt_lines.append("")
        
        # 示例测试用例
        if example_cases:
            prompt_lines.append("=== 现有测试用例示例 ===")
            for i, case in enumerate(example_cases, 1):
                prompt_lines.append(f"示例{i}:")
                prompt_lines.append(f"  测试用例名称: {case['test_case_name']}")
                prompt_lines.append(f"  输入值: {case['input_values']}")
                prompt_lines.append(f"  期望输出: {case['expected_output']}")
                prompt_lines.append(f"  测试类型: {case['test_type']}")
                prompt_lines.append(f"  描述: {case['description']}")
                prompt_lines.append("")
        
        # 生成要求
        prompt_lines.append("=== 生成要求 ===")
        prompt_lines.append("请生成以下类型的测试用例：")
        prompt_lines.append("1. 正常情况测试用例（normal）")
        prompt_lines.append("2. 边界值测试用例（boundary）")
        prompt_lines.append("3. 异常情况测试用例（edge_case）")
        prompt_lines.append("")
        prompt_lines.append("请参考现有示例，生成更多样化和全面的测试用例。")
        prompt_lines.append("请以JSON格式返回，格式如下：")
        prompt_lines.append("""
            {
                "test_cases": [
                    {
                        "test_name": "测试用例名称",
                        "input_values": {"参数名": "参数值"},
                        "expected_output": "期望输出",
                        "description": "测试描述",
                        "boundary_type": "normal/boundary/edge_case"
                    }
                ]
            }
        """)
        
        return "\n".join(prompt_lines)
    
    def _format_parameters(self, parameters: List[Dict]) -> str:
        """格式化函数参数"""
        if not parameters:
            return "无参数"
        
        param_strs = []
        for param in parameters:
            param_type = param.get('type', 'unknown')
            param_name = param.get('name', 'unnamed')
            param_strs.append(f"{param_type} {param_name}")
        
        return ', '.join(param_strs)
    
    def _parse_test_cases_response(self, response: str, function_info: Dict[str, Any]) -> List[TestCase]:
        """解析大模型响应生成测试用例"""
        test_cases = []
        
        try:
            # 尝试提取JSON部分
            import re
            json_match = re.search(r'\{.*\}', response, re.DOTALL)
            if json_match:
                data = json.loads(json_match.group())
                for i, tc_data in enumerate(data.get('test_cases', []), 1):
                    print("第", i, "个测试用例")
                    test_case = TestCase(
                        test_id=f"{function_info.get('name', 'unknown')}_TC_{i:03d}",
                        test_name=tc_data.get('test_name', f'Generated_Test_{i}'),
                        input_values=tc_data.get('input_values', {}),
                        expected_output=tc_data.get('expected_output', ''),
                        description=tc_data.get('description', ''),
                        boundary_type=tc_data.get('boundary_type', 'normal'),
                        coverage_target=tc_data.get('coverage_target', ''),
                        priority=tc_data.get('priority', ''),
                    )
                    test_cases.append(test_case)
                logger.info(f"成功解析 {len(test_cases)} 个测试用例")
            else:
                logger.warning("响应中没有找到有效的JSON格式")
        except Exception as e:
            logger.error(f"解析测试用例响应时出错: {e}")
        
        return test_cases
    
    def _extract_response_content(self, response) -> str:
        """提取响应内容，支持多种响应格式"""
        try:
            logger.info(f"响应类型: {type(response)}")
            
            # 尝试不同的响应格式
            if hasattr(response, 'content'):
                # 标准LangChain格式
                content = response.content
                logger.info(f"使用content属性，内容长度: {len(content)}")
                return content
            elif hasattr(response, 'text'):
                # 某些LLM客户端使用text属性
                text = response.text
                logger.info(f"使用text属性，内容长度: {len(text)}")
                return text
            elif hasattr(response, 'message'):
                # 某些客户端使用message属性
                if hasattr(response.message, 'content'):
                    content = response.message.content
                    logger.info(f"使用message.content属性，内容长度: {len(content)}")
                    return content
                else:
                    message = str(response.message)
                    logger.info(f"使用message属性，内容长度: {len(message)}")
                    return message
            elif hasattr(response, 'choices') and len(response.choices) > 0:
                # OpenAI格式
                content = response.choices[0].message.content
                logger.info(f"使用choices格式，内容长度: {len(content)}")
                return content
            elif isinstance(response, dict):
                # JSON格式响应
                logger.info(f"响应是字典格式: {list(response.keys())}")
                if 'content' in response:
                    return response['content']
                elif 'text' in response:
                    return response['text']
                elif 'message' in response:
                    return response['message']
                elif 'response' in response:
                    return response['response']
                elif 'result' in response:
                    return response['result']
                else:
                    logger.warning(f"字典响应中没有找到内容字段，返回整个响应")
                    return str(response)
            elif isinstance(response, str):
                # 直接字符串响应
                logger.info(f"响应是字符串格式，长度: {len(response)}")
                return response
            else:
                # 其他格式，转换为字符串
                logger.warning(f"未知的响应格式: {type(response)}")
                logger.info(f"响应内容: {response}")
                return str(response)
                
        except Exception as e:
            logger.error(f"提取响应内容时出错: {e}")
            logger.info(f"原始响应: {response}")
            return str(response)
    
    def _generate_mock_test_cases(self, function_info: Dict[str, Any]) -> List[TestCase]:
        """生成模拟测试用例（当LLM不可用时使用）"""
        logger.info("生成模拟测试用例")
        
        function_name = function_info.get('name', 'unknown')
        parameters = function_info.get('parameters', [])
        branch_info = function_info.get('branch_info', {})
        
        test_cases = []
        
        # 根据函数名生成不同的测试用例
        if function_name == 'is_value_in_range':
            # 为 is_value_in_range 函数生成测试用例
            test_cases = [
                TestCase(
                    test_name="正常范围测试",
                    input_values={"value": 5, "min": 1, "max": 10},
                    expected_output=1,
                    description="测试值在正常范围内的情况",
                    boundary_type="normal",
                    test_id=f"{function_name}_TC_001"
                ),
                TestCase(
                    test_name="边界值测试-最小值",
                    input_values={"value": 1, "min": 1, "max": 10},
                    expected_output=1,
                    description="测试值等于最小值的情况",
                    boundary_type="boundary",
                    test_id=f"{function_name}_TC_002"
                ),
                TestCase(
                    test_name="边界值测试-最大值",
                    input_values={"value": 10, "min": 1, "max": 10},
                    expected_output=1,
                    description="测试值等于最大值的情况",
                    boundary_type="boundary",
                    test_id=f"{function_name}_TC_003"
                ),
                TestCase(
                    test_name="超出范围测试-小于最小值",
                    input_values={"value": 0, "min": 1, "max": 10},
                    expected_output=0,
                    description="测试值小于最小值的情况",
                    boundary_type="edge_case",
                    test_id=f"{function_name}_TC_004"
                ),
                TestCase(
                    test_name="超出范围测试-大于最大值",
                    input_values={"value": 11, "min": 1, "max": 10},
                    expected_output=0,
                    description="测试值大于最大值的情况",
                    boundary_type="edge_case",
                    test_id=f"{function_name}_TC_005"
                )
            ]
        else:
            # 为其他函数生成通用测试用例
            for i in range(3):
                test_case = TestCase(
                    test_name=f"测试用例_{i+1}",
                    input_values={param.get('name', f'param_{i}'): i for param in parameters},
                    expected_output=i,
                    description=f"通用测试用例 {i+1}",
                    boundary_type="normal" if i == 0 else "boundary" if i == 1 else "edge_case",
                    test_id=f"{function_name}_TC_{i+1:03d}"
                )
                test_cases.append(test_case)
        
        logger.info(f"生成了 {len(test_cases)} 个模拟测试用例")
        return test_cases

class ExcelUpdater:
    """Excel文件更新器"""
    
    def __init__(self):
        self.properties_sheet = "Properties"
        self.values_sheet = "Values"
        self.description_field = "Description"
    
    def update_excel_with_test_cases(self, excel_path: str, test_cases: List[TestCase], 
                                   function_name: str, output_dir: str) -> str:
        """
        第六步：更新Excel文件，支持双表头格式
        
        Args:
            excel_path: 原始Excel文件路径
            test_cases: 生成的测试用例
            function_name: 函数名
            output_dir: 输出目录
            
        Returns:
            更新后的Excel文件路径
        """
        logger.info(f"开始更新Excel文件: {excel_path}")
        
        try:
            # 读取现有Excel文件
            excel_file = pd.ExcelFile(excel_path)
            
            # 只读取Properties和Values两个工作表
            all_sheets = {}
            required_sheets = [self.properties_sheet, self.values_sheet]
            
            for sheet_name in excel_file.sheet_names:
             
                try:
                    # 尝试读取为双表头格式（不设置header）
                    df = pd.read_excel(excel_path, sheet_name=sheet_name, header=None)
                    all_sheets[sheet_name] = df
                    logger.info(f"成功读取工作表: {sheet_name}")
                except Exception as e:
                    logger.warning(f"读取工作表 {sheet_name} 时出错: {e}")
                    # 创建空的工作表
                    all_sheets[sheet_name] = pd.DataFrame()
            
            # 检查必需的工作表是否存在
            missing_sheets = []
            for sheet_name in required_sheets:
                if sheet_name not in all_sheets:
                    missing_sheets.append(sheet_name)
                    # 创建空的工作表
                    all_sheets[sheet_name] = pd.DataFrame()
                    logger.warning(f"工作表 {sheet_name} 不存在，将创建空工作表")
            
            if missing_sheets:
                logger.warning(f"缺少必需的工作表: {missing_sheets}")
            
            # 更新Values工作表
            if self.values_sheet in all_sheets:
                updated_values_df, case_step_list = self._update_values_sheet(
                    all_sheets[self.values_sheet], test_cases, function_name
                )
                all_sheets[self.values_sheet] = updated_values_df
                logger.info(f"已更新Values工作表")
            else:
                logger.error(f"Values工作表不存在且无法创建")
            
            # 更新Properties工作表
            if self.properties_sheet in all_sheets:
                updated_properties_df = self._update_properties_sheet(
                    all_sheets[self.properties_sheet], test_cases, function_name, case_step_list
                )
                all_sheets[self.properties_sheet] = updated_properties_df
                logger.info(f"已更新Properties工作表")
            else:
                logger.error(f"Properties工作表不存在且无法创建")
            
            # 保存更新后的Excel文件
            output_path = self._save_updated_excel(excel_path, all_sheets, function_name, output_dir)
            
            logger.info(f"已更新Excel文件: {output_path}")
            return output_path
            
        except Exception as e:
            logger.error(f"更新Excel文件时出错: {e}")
            return excel_path
    
    def _update_values_sheet(self, values_df: pd.DataFrame, 
                           test_cases: List[TestCase], function_name: str) -> pd.DataFrame:
        """更新Values工作表，支持双表头格式并保持原有格式"""
        try:
            # 检查是否为双表头格式（至少有两行数据）
            if len(values_df) >= 2:
                # 保留前两行作为表头
                header_rows = values_df.iloc[:2].copy()
                
                case_num = 0
                step_num = 1
                case_step_list = []
                # 创建新的测试用例数据，从第三行开始
                new_test_cases = []
                for i, test_case in enumerate(test_cases, 1):
                    # 构建测试用例行，对应参数名称
                    test_case_row = {}
                    
                    # 第一列为测试用例ID
                    case_num = i
                    test_case_row[values_df.columns[0]] = f"tc{case_num}.{step_num}"
                    
                    case_step_list.append({"case_num": case_num, "step_num": step_num})
                    # 根据参数名称填充输入值
                    param_names = header_rows.iloc[0].dropna().tolist()
                    io_types = header_rows.iloc[1].dropna().tolist()
                    
                    for j, (param_name, io_type) in enumerate(zip(param_names, io_types)):
                        if io_type.lower() == 'i':  # 输入参数
                            # 从测试用例的输入值中获取对应参数的值
                            input_value = test_case.input_values.get(param_name, '')
                            test_case_row[values_df.columns[j+1]] = input_value
                        elif io_type.lower() == 'o':  # 输出参数
                            # 使用期望输出
                            test_case_row[values_df.columns[j+1]] = test_case.expected_output
                    
                    new_test_cases.append(test_case_row)
                
                # 创建新的DataFrame
                new_df = pd.DataFrame(new_test_cases)
                
                # 合并数据：保留前两行表头，添加新的测试用例行
                combined_df = pd.concat([header_rows, new_df], ignore_index=True)
                
                logger.info(f"Values工作表已更新，保持双表头格式，添加了 {len(test_cases)} 个测试用例")
                return combined_df, case_step_list
            else:
                # 如果数据不足两行，使用默认方法
                logger.warning("Values工作表格式不符合双表头要求，使用默认更新方法")
                return self._update_values_sheet_default(values_df, test_cases, function_name)
            
        except Exception as e:
            logger.error(f"更新Values工作表时出错: {e}")
            return values_df
    
    def _update_values_sheet_default(self, values_df: pd.DataFrame, 
                                   test_cases: List[TestCase], function_name: str) -> pd.DataFrame:
        """默认的Values工作表更新方法"""
        try:
            # 创建新的测试用例数据
            new_test_cases = []
            
            for test_case in test_cases:
                test_case_row = {
                    'Test_Case_ID': test_case.test_id,
                    'Test_Case_Name': test_case.test_name,
                    'Function_Name': function_name,
                    'Input_Values': json.dumps(test_case.input_values, ensure_ascii=False),
                    'Expected_Output': str(test_case.expected_output),
                    'Test_Type': test_case.boundary_type,
                    'Description': test_case.description,
                    'Status': 'Generated',
                    'Created_Date': pd.Timestamp.now().strftime('%Y-%m-%d %H:%M:%S')
                }
                new_test_cases.append(test_case_row)
            
            # 创建新的DataFrame
            new_df = pd.DataFrame(new_test_cases)
            
            # 合并数据
            if not values_df.empty:
                common_columns = list(set(values_df.columns) & set(new_df.columns))
                if common_columns:
                    combined_df = pd.concat([values_df[common_columns], new_df[common_columns]], 
                                          ignore_index=True)
                else:
                    combined_df = new_df
            else:
                combined_df = new_df
            
            logger.info(f"Values工作表已更新，添加了 {len(test_cases)} 个测试用例")
            return combined_df
            
        except Exception as e:
            logger.error(f"更新Values工作表时出错: {e}")
            return values_df
    
    def _update_properties_sheet(self, properties_df: pd.DataFrame, 
                               test_cases: List[TestCase], 
                               function_name: str, 
                               case_step_list: List[Dict[str, Any]]) -> pd.DataFrame:
        """更新Properties工作表，支持双表头格式"""
        try:
            # 检查是否为双表头格式（至少有两行数据）
            if len(properties_df) >= 2:
  
                # 构建测试用例描述
                test_info, test_case_summary = self._build_test_case_summary(test_cases)
                
                # 创建新行
                if properties_df.iloc[3,4] == 'Description':
                    
                    # 确保DataFrame有足够的行来容纳新的测试用例信息
                    required_rows = 4 + len(test_info)  # 4行表头 + 测试用例数量
                    if len(properties_df) < required_rows:
                        # 扩展DataFrame的大小
                        additional_rows = required_rows - len(properties_df)
                        empty_rows = pd.DataFrame(index=range(additional_rows), columns=properties_df.columns)
                        properties_df = pd.concat([properties_df, empty_rows], ignore_index=True)
                        logger.info(f"扩展Properties工作表，添加了 {additional_rows} 行")
                    
                    # 确保新行有所有必要的列
                    for i, info_dict in enumerate(test_info):
                        
                        properties_df.iloc[4 + i, 0] = case_step_list[i]['case_num']
                        properties_df.iloc[4 + i, 1] = case_step_list[i]['step_num']
                        properties_df.iloc[4 + i, 4] = info_dict['description']
                
                logger.info(f"Properties工作表已更新，为函数 {function_name} 添加了测试用例描述")
                return properties_df
            else:
                # 如果数据不足两行，使用默认方法
                logger.warning("Properties工作表格式不符合双表头要求，使用默认更新方法")
                return self._update_properties_sheet_default(properties_df, test_cases, function_name)
            
        except Exception as e:
            logger.error(f"更新Properties工作表时出错: {e}")
            return properties_df
    
    def _update_properties_sheet_default(self, properties_df: pd.DataFrame, 
                                       test_cases: List[TestCase], function_name: str) -> pd.DataFrame:
        """默认的Properties工作表更新方法"""
        try:
            # 查找或创建函数相关的属性行
            function_row_index = None
            
            for i, row in properties_df.iterrows():
                if 'Function_Name' in row and row['Function_Name'] == function_name:
                    function_row_index = i
                    break
            
            # 构建测试用例描述
            test_info, test_case_summary = self._build_test_case_summary(test_cases)
            
            if function_row_index is not None:
                # 更新现有行
                if 'Description' in properties_df.columns:
                    current_desc = str(properties_df.at[function_row_index, 'Description'])
                    new_desc = f"{current_desc}\n\n=== 自动生成的测试用例 ===\n{test_case_summary}"
                    properties_df.at[function_row_index, 'Description'] = new_desc
            else:
                # 创建新行
                new_row = {
                    'Function_Name': function_name,
                    'Description': f"=== 自动生成的测试用例 ===\n{test_case_summary}",
                    'Test_Case_Count': len(test_cases),
                    'Generated_Date': pd.Timestamp.now().strftime('%Y-%m-%d %H:%M:%S')
                }
                
                new_df = pd.DataFrame([new_row])
                properties_df = pd.concat([properties_df, new_df], ignore_index=True)
            
            logger.info(f"Properties工作表已更新，为函数 {function_name} 添加了测试用例描述")
            return properties_df
            
        except Exception as e:
            logger.error(f"更新Properties工作表时出错: {e}")
            return properties_df
    

    
    def _build_test_case_summary(self, test_cases: List[TestCase]) -> str:
        """构建测试用例摘要，包含test_id和description的提取信息"""
        summary_lines = []
        
        # 统计信息
        normal_count = len([tc for tc in test_cases if tc.boundary_type == 'normal'])
        boundary_count = len([tc for tc in test_cases if tc.boundary_type == 'boundary'])
        edge_count = len([tc for tc in test_cases if tc.boundary_type == 'edge_case'])
        
        summary_lines.append(f"总测试用例数: {len(test_cases)}")
        summary_lines.append(f"- 正常测试用例: {normal_count}")
        summary_lines.append(f"- 边界测试用例: {boundary_count}")
        summary_lines.append(f"- 异常测试用例: {edge_count}")
        summary_lines.append("")
        
        # 提取test_id和description信息
        test_info = []
        for test_case in test_cases:
            test_info.append({
                'description': test_case.description
            })
        
        # 记录提取的test_id和description信息
        summary_lines.append("=== 提取的测试用例信息 ===")
        summary_lines.append(f"提取到 {len(test_info)} 个测试用例的test_id和description:")
        summary_lines.append("")
        
        for i, info in enumerate(test_info, 1):
            summary_lines.append(f"{i}. Test ID: {info['test_id']}")
            summary_lines.append(f"   Description: {info['description']}")
            summary_lines.append("")
        
        # 显示列表格式的提取结果
        test_ids = [info['test_id'] for info in test_info]
        descriptions = [info['description'] for info in test_info]
        
        summary_lines.append("=== 列表格式提取结果 ===")
        summary_lines.append(f"Test IDs: {test_ids}")
        summary_lines.append(f"Descriptions: {descriptions}")
        summary_lines.append("")
        
        # 详细测试用例列表
        summary_lines.append("=== 详细测试用例列表 ===")
        for i, test_case in enumerate(test_cases, 1):
            summary_lines.append(f"{i}. {test_case.test_name} ({test_case.boundary_type})")
            summary_lines.append(f"   Test ID: {test_case.test_id}")
            summary_lines.append(f"   输入: {test_case.input_values}")
            summary_lines.append(f"   期望输出: {test_case.expected_output}")
            summary_lines.append(f"   描述: {test_case.description}")
            if test_case.coverage_target:
                summary_lines.append(f"   覆盖目标: {test_case.coverage_target}")
            if test_case.priority:
                summary_lines.append(f"   优先级: {test_case.priority}")
            summary_lines.append("")
        
        return test_info, "\n".join(summary_lines)
    
    def _save_updated_excel(self, original_path: str, all_sheets: Dict[str, pd.DataFrame], 
                           function_name: str, output_dir: str) -> str:
        """保存更新后的Excel文件，保存所有工作表"""
        try:
            # 生成新的文件名
            original_path_obj = Path(original_path)
            timestamp = pd.Timestamp.now().strftime('%Y%m%d_%H%M%S')
            new_filename = f"{original_path_obj.stem}_{function_name}_{timestamp}.xlsx"
            output_path = Path(output_dir) / new_filename
            
            # 确保输出目录存在
            output_path.parent.mkdir(parents=True, exist_ok=True)
            
            # 使用ExcelWriter保存所有工作表
            with pd.ExcelWriter(output_path, engine='openpyxl') as writer:
                saved_sheets = 0
                skipped_sheets = 0
                
                for sheet_name, df in all_sheets.items():
                    if not df.empty:
                        # 保存时保持原有格式，不设置索引
                        df.to_excel(writer, sheet_name=sheet_name, index=False, header=False)
                        logger.info(f"已保存工作表: {sheet_name}，保持原有格式")
                        saved_sheets += 1
                    else:
                        logger.warning(f"工作表 {sheet_name} 为空，跳过保存")
                        skipped_sheets += 1
                
                logger.info(f"保存完成: {saved_sheets} 个工作表已保存，{skipped_sheets} 个工作表被跳过")
            
            logger.info(f"已保存更新后的Excel文件: {output_path}")
            return str(output_path)
            
        except Exception as e:
            logger.error(f"保存Excel文件时出错: {e}")
            return original_path

class UnitTestGenerator:
    """单元测试生成器主类"""
    
    def __init__(self):
        self.file_matcher = FilePairMatcher()
        self.code_analyzer = CCodeAnalyzer()
        self.excel_processor = ExcelDataProcessor()
        self.test_generator = LLMTestGenerator()
        self.excel_updater = ExcelUpdater()
    
    def process_file_pair(self, base_name: str, code_dir: str, excel_dir: str, 
                         output_dir: str = "result") -> Dict[str, Any]:
        """
        处理单个文件对
        
        Args:
            base_name: 基础文件名
            code_dir: C代码目录
            excel_dir: Excel文件目录
            output_dir: 输出目录
            
        Returns:
            处理结果字典
        """
        logger.info(f"开始处理文件对: {base_name}")
        
        result = {
            'base_name': base_name,
            'success': False,
            'c_file_path': None,
            'excel_file_path': None,
            'analysis_result': {},
            'excel_data': {},
            'updated_excel_path': None,
            'error': None
        }
        
        try:
            # 第一步：匹配文件对
            c_file_path, excel_file_path = self.file_matcher.find_matching_files(
                base_name, code_dir, excel_dir
            )
            
            if not c_file_path:
                result['error'] = "找不到C文件"
                return result
            
            result['c_file_path'] = c_file_path
            result['excel_file_path'] = excel_file_path
            
            # 第二步：解析C文件
            analysis_result = self.code_analyzer.analyze_file(c_file_path, output_dir)
            if not analysis_result:
                result['error'] = "C文件解析失败"
                return result
            
            result['analysis_result'] = analysis_result
            
            # 处理每个函数
            functions = analysis_result.get('functions', [])
            all_test_cases = []
            
            for function_info in functions:
                function_name = function_info.get('name', 'unknown')
                logger.info(f"处理函数: {function_name}")
                
                # 生成测试用例
                test_cases = self.test_generator.generate_test_cases(
                    function_info
                )
                
                all_test_cases.extend(test_cases)
            
            result['test_cases'] = all_test_cases
            
            # 第六步：更新Excel文件
            if excel_file_path and all_test_cases:
                updated_excel_path = self.excel_updater.update_excel_with_test_cases(
                    excel_file_path, all_test_cases, functions[0].get('name', 'unknown'), output_dir
                )
                result['updated_excel_path'] = updated_excel_path
            
            result['success'] = True
            logger.info(f"文件对处理完成: {base_name}")
            
        except Exception as e:
            result['error'] = str(e)
            logger.error(f"处理文件对时出错: {e}")
        
        return result
    
    def process_folder_pair(self, code_folder: str, excel_folder: str, 
                          output_dir: str = "result") -> Dict[str, Any]:
        """
        处理文件夹对，按照新的六步流程
        
        Args:
            code_folder: C代码文件夹路径
            excel_folder: Excel文件夹路径
            output_dir: 输出目录
            
        Returns:
            处理结果字典
        """
        logger.info(f"开始处理文件夹对:")
        logger.info(f"  C代码文件夹: {code_folder}")
        logger.info(f"  Excel文件夹: {excel_folder}")
        
        result = {
            'folder_name': Path(code_folder).name,
            'success': False,
            'file_results': [],
            'total_test_cases': 0,
            'total_files_processed': 0,
            'error': None
        }
        
        try:
            # 第一步：解析文件夹下的所有C和H文件
            logger.info("=== 第一步：解析C代码文件 ===")
            analysis_result = self.code_analyzer.analyze_folder(code_folder, output_dir)
            if not analysis_result:
                result['error'] = "C代码文件夹解析失败"
                return result
            
            logger.info(f"成功解析文件夹，发现 {analysis_result.get('total_functions', 0)} 个函数")
            
            # 查找文件夹中的所有Excel文件
            excel_files = list(Path(excel_folder).glob("*.xlsx"))
            if not excel_files:
                result['error'] = "在Excel文件夹中找不到Excel文件"
                return result
            
            logger.info(f"找到 {len(excel_files)} 个Excel文件")
            
            # 处理每个Excel文件
            for excel_file in excel_files:
                logger.info(f"处理Excel文件: {excel_file.name}")
                
                file_result = {
                    'excel_file': str(excel_file),
                    'success': False,
                    'test_cases': [],
                    'updated_excel_path': None,
                    'error': None
                }
                
                try:
                    
                    # 第三步：初始化大模型
                    logger.info("=== 第三步：初始化大模型 ===")
                    if not self.test_generator.llm_available:
                        file_result['error'] = "大模型不可用"
                        result['file_results'].append(file_result)
                        continue
                    
                    # 第四步：构建prompt
                    logger.info("=== 第四步：构建prompt ===")
                    # 这一步在generate_test_cases中完成
                    
                    # 处理每个函数
                    functions = analysis_result.get('functions', [])
                    all_test_cases = []
                    
                    for function_info in functions:
                        function_name = function_info.get('name', 'unknown')
                        logger.info(f"处理函数: {function_name}")
                        
                        # 第五步：生成测试用例
                        logger.info("=== 第五步：生成测试用例 ===")
                        test_cases = self.test_generator.generate_test_cases(
                            function_info
                        )
                        
                        all_test_cases.extend(test_cases)
                    
                    file_result['test_cases'] = all_test_cases
                    result['total_test_cases'] += len(all_test_cases)
                    
                    # 第六步：更新Excel文件
                    logger.info("=== 第六步：更新Excel文件 ===")
                    if all_test_cases:
                        updated_excel_path = self.excel_updater.update_excel_with_test_cases(
                            str(excel_file), all_test_cases, functions[0].get('name', 'unknown'), output_dir
                        )
                        file_result['updated_excel_path'] = updated_excel_path
                    
                    file_result['success'] = True
                    result['total_files_processed'] += 1
                    
                except Exception as e:
                    file_result['error'] = str(e)
                    logger.error(f"处理Excel文件 {excel_file.name} 时出错: {e}")
                
                result['file_results'].append(file_result)
            
            result['success'] = True
            logger.info(f"文件夹对处理完成，成功处理 {result['total_files_processed']} 个文件，生成 {result['total_test_cases']} 个测试用例")
            
        except Exception as e:
            result['error'] = str(e)
            logger.error(f"处理文件夹对时出错: {e}")
        
        return result
    
    def process_all_folders(self, code_dir: str, excel_dir: str, 
                           output_dir: str = "result") -> Dict[str, Any]:
        """
        处理所有文件夹对
        
        Args:
            code_dir: C代码根目录
            excel_dir: Excel文件根目录
            output_dir: 输出目录
            
        Returns:
            处理结果字典
        """
        logger.info(f"开始处理所有文件夹对:")
        logger.info(f"  C代码根目录: {code_dir}")
        logger.info(f"  Excel根目录: {excel_dir}")
        
        result = {
            'success': False,
            'folder_results': [],
            'total_folders_processed': 0,
            'total_files_processed': 0,
            'total_test_cases': 0,
            'error': None
        }
        
        try:
            # 查找所有文件夹对
            folder_pairs = self.file_matcher.find_folder_pairs(code_dir, excel_dir)
            
            if not folder_pairs:
                result['error'] = "找不到匹配的文件夹对"
                return result
            
            logger.info(f"找到 {len(folder_pairs)} 个文件夹对")
            
            # 处理每个文件夹对
            for folder_name, code_folder, excel_folder in folder_pairs:
                logger.info(f"处理文件夹对: {folder_name}")
                
                folder_result = self.process_folder_pair(code_folder, excel_folder, output_dir)
                result['folder_results'].append(folder_result)
                
                if folder_result['success']:
                    result['total_folders_processed'] += 1
                    result['total_files_processed'] += folder_result['total_files_processed']
                    result['total_test_cases'] += folder_result['total_test_cases']
            
            result['success'] = True
            logger.info(f"所有文件夹对处理完成，成功处理 {result['total_folders_processed']} 个文件夹，{result['total_files_processed']} 个文件，生成 {result['total_test_cases']} 个测试用例")
            
        except Exception as e:
            result['error'] = str(e)
            logger.error(f"处理所有文件夹对时出错: {e}")
        
        return result

def main():
    """主函数"""

    file_mode="is_val_in_range"
    folder_mode="is_val_in_range"

    # 获取当前脚本所在目录
    script_dir = Path(__file__).parent
    
    code_dir=str(script_dir / "code/is_val_in_range")
    excel_dir=str(script_dir / "context/is_val_in_range")
    output_dir=str(script_dir / "result/is_val_in_range")

    import argparse
    
    parser = argparse.ArgumentParser(description="单元测试生成器")
    parser.add_argument("--mode", choices=["file", "folder", "all"], default="file", 
                       help="处理模式: file(单个文件对), folder(文件夹对), all(所有文件夹)")
    parser.add_argument("--base-name", help="基础文件名（不含扩展名），仅在file模式下使用", default=file_mode)
    parser.add_argument("--code-dir", default=code_dir, help="C代码目录")
    parser.add_argument("--excel-dir", default=excel_dir, help="Excel文件目录")
    parser.add_argument("--output-dir", default=output_dir, help="输出目录")
    parser.add_argument("--folder-name", help="文件夹名称，仅在folder模式下使用", default=folder_mode)
    
    args = parser.parse_args()
    
    # 创建生成器
    generator = UnitTestGenerator()
    
    if args.mode == "file":
        # 处理单个文件对
        if not args.base_name:
            print("❌ 错误: file模式下必须指定--base-name参数")
            return
        
        result = generator.process_file_pair(
            args.base_name, args.code_dir, args.excel_dir, args.output_dir
        )
        
        # 输出结果
        if result['success']:
            print(f"✅ 处理成功: {args.base_name}")
            print(f"  生成的测试用例数: {len(result['test_cases'])}")
            if result['updated_excel_path']:
                print(f"  更新的Excel文件: {result['updated_excel_path']}")
        else:
            print(f"❌ 处理失败: {args.base_name}")
            print(f"  错误: {result['error']}")
    
    elif args.mode == "folder":
        # 处理文件夹对
        if args.folder_name:
            # 指定文件夹名称
            code_folder = Path(args.code_dir) / args.folder_name
            excel_folder = Path(args.excel_dir) / args.folder_name
            
            if not code_folder.exists():
                print(f"❌ 错误: C代码文件夹不存在: {code_folder}")
                return
            
            if not excel_folder.exists():
                print(f"❌ 错误: Excel文件夹不存在: {excel_folder}")
                return
            
            result = generator.process_folder_pair(
                str(code_folder), str(excel_folder), args.output_dir
            )
        else:
            # 自动查找文件夹对
            folder_pairs = generator.file_matcher.find_folder_pairs(args.code_dir, args.excel_dir)
            if not folder_pairs:
                print("❌ 错误: 找不到匹配的文件夹对")
                return
            
            if len(folder_pairs) == 1:
                # 只有一个文件夹对，自动处理
                folder_name, code_folder, excel_folder = folder_pairs[0]
                print(f"自动处理文件夹对: {folder_name}")
                result = generator.process_folder_pair(code_folder, excel_folder, args.output_dir)
            else:
                # 多个文件夹对，需要用户选择
                print("找到多个文件夹对:")
                for i, (folder_name, _, _) in enumerate(folder_pairs, 1):
                    print(f"  {i}. {folder_name}")
                print("请使用 --folder-name 参数指定要处理的文件夹")
                return
        
        # 输出结果
        if result['success']:
            print(f"✅ 文件夹处理成功: {result['folder_name']}")
            print(f"  处理的文件数: {result['total_files_processed']}")
            print(f"  生成的测试用例数: {result['total_test_cases']}")
        else:
            print(f"❌ 文件夹处理失败: {result.get('folder_name', 'unknown')}")
            print(f"  错误: {result['error']}")
    
    elif args.mode == "all":
        # 处理所有文件夹对
        result = generator.process_all_folders(args.code_dir, args.excel_dir, args.output_dir)
        
        # 输出结果
        if result['success']:
            print(f"✅ 所有文件夹处理成功")
            print(f"  处理的文件夹数: {result['total_folders_processed']}")
            print(f"  处理的文件数: {result['total_files_processed']}")
            print(f"  生成的测试用例数: {result['total_test_cases']}")
        else:
            print(f"❌ 所有文件夹处理失败")
            print(f"  错误: {result['error']}")

if __name__ == "__main__":
    main() 