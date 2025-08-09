#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
QAC代码分析Prompt管理器
用于管理和格式化各种prompt模板
"""

import json
import os
from typing import Dict, List, Optional, Any
from pathlib import Path


class QACPromptManager:
    """QAC代码分析Prompt管理器"""
    
    def __init__(self, prompt_config_path: Optional[str] = None):
        """
        初始化Prompt管理器
        
        Args:
            prompt_config_path: prompt配置文件路径，默认使用同目录下的配置文件
        """
        if prompt_config_path is None:
            current_dir = Path(__file__).parent
            prompt_config_path = current_dir / "prompt" / "qac_comprehensive_analysis_prompt.json"
        
        self.config_path = prompt_config_path
        self.prompts = self._load_prompts()
    
    def _load_prompts(self) -> Dict[str, str]:
        """加载prompt配置"""
        try:
            with open(self.config_path, 'r', encoding='utf-8') as f:
                return json.load(f)
        except Exception as e:
            print(f"加载prompt配置失败: {e}")
            return {}
    
    def format_single_issue_prompt(self, 
                                  file_name: str,
                                  line_number: int,
                                  error_id: str,
                                  rule_violated: str,
                                  error_message: str,
                                  error_type: str = "unknown",
                                  severity_level: str = "medium",
                                  function_info: Optional[Dict] = None,
                                  code_context: str = "",
                                  rag_knowledge: str = "") -> str:
        """
        格式化单个问题分析的prompt
        
        Args:
            file_name: 文件名
            line_number: 错误行号
            error_id: 错误ID
            rule_violated: 违反的规则
            error_message: 错误消息
            error_type: 错误类型
            severity_level: 严重级别
            function_info: 函数信息字典
            code_context: 代码上下文
            rag_knowledge: RAG知识库相关信息
            
        Returns:
            格式化后的prompt字符串
        """
        # 处理函数信息
        if function_info:
            function_signature = f"{function_info.get('return_type', 'unknown')} {function_info.get('name', 'unknown')}(...)"
            function_start_line = function_info.get('start_line', 'unknown')
            function_end_line = function_info.get('end_line', 'unknown')
            function_return_type = function_info.get('return_type', 'unknown')
            function_parameters = self._format_parameters(function_info.get('parameters', []))
            complexity_score = function_info.get('complexity_score', 'unknown')
            function_body = function_info.get('body_content', '// 函数体内容不可用')
        else:
            function_signature = "函数信息不可用"
            function_start_line = "unknown"
            function_end_line = "unknown"
            function_return_type = "unknown"
            function_parameters = "参数信息不可用"
            complexity_score = "unknown"
            function_body = "// 函数体内容不可用"
        
        # 构建完整的prompt
        system_prompt = self.prompts.get("system_prompt", "")
        user_prompt_template = self.prompts.get("user_prompt_template", "")
        
        user_prompt = user_prompt_template.format(
            file_name=file_name,
            line_number=line_number,
            error_id=error_id,
            rule_violated=rule_violated,
            error_message=error_message,
            error_type=error_type,
            severity_level=severity_level,
            function_signature=function_signature,
            function_start_line=function_start_line,
            function_end_line=function_end_line,
            function_return_type=function_return_type,
            function_parameters=function_parameters,
            complexity_score=complexity_score,
            function_body=function_body,
            code_context=code_context,
            rag_knowledge=rag_knowledge
        )
        
        return f"{system_prompt}\n\n{user_prompt}"
    
    def format_comprehensive_analysis_prompt(self,
                                           file_info: Dict,
                                           detected_issues: List[Dict],
                                           function_dependencies: Dict = None) -> str:
        """
        格式化综合分析的prompt
        
        Args:
            file_info: 文件信息
            detected_issues: 检测到的问题列表
            function_dependencies: 函数依赖信息
            
        Returns:
            格式化后的prompt字符串
        """
        # 处理文件信息
        total_functions = len(file_info.get('functions', []))
        total_lines = file_info.get('total_lines', 0)
        includes = ', '.join(file_info.get('includes', []))
        defines = f"{len(file_info.get('defines', []))} 个宏定义"
        
        # 处理检测到的问题
        issues_text = self._format_issues(detected_issues)
        
        # 处理依赖信息
        if function_dependencies:
            called_functions = ', '.join(function_dependencies.get('called_functions', []))
            used_variables = ', '.join(function_dependencies.get('used_variables', []))
            external_dependencies = ', '.join(function_dependencies.get('external_dependencies', []))
        else:
            called_functions = "依赖信息不可用"
            used_variables = "变量信息不可用"
            external_dependencies = "外部依赖信息不可用"
        
        # 构建分析prompt
        analysis_template = self.prompts.get("analysis_prompt_template", "")
        
        return analysis_template.format(
            file_info=file_info.get('file_name', 'unknown'),
            total_functions=total_functions,
            total_lines=total_lines,
            includes=includes,
            defines=defines,
            detected_issues=issues_text,
            called_functions=called_functions,
            used_variables=used_variables,
            external_dependencies=external_dependencies
        )
    
    def _format_parameters(self, parameters: List[Dict]) -> str:
        """格式化函数参数列表"""
        if not parameters:
            return "无参数"
        
        param_strs = []
        for param in parameters[:10]:  # 限制显示前10个参数
            param_type = param.get('type', 'unknown')
            param_name = param.get('name', 'unnamed')
            param_strs.append(f"{param_type} {param_name}")
        
        if len(parameters) > 10:
            param_strs.append(f"... (省略 {len(parameters) - 10} 个参数)")
        
        return ', '.join(param_strs)
    
    def _format_issues(self, issues: List[Dict]) -> str:
        """格式化问题列表"""
        if not issues:
            return "未检测到问题"
        
        formatted_issues = []
        for i, issue in enumerate(issues[:20], 1):  # 限制显示前20个问题
            issue_text = f"{i}. [ID: {issue.get('id', 'unknown')}] " \
                        f"第{issue.get('line', 'unknown')}行: " \
                        f"{issue.get('message', 'unknown error')} " \
                        f"(规则: {issue.get('rule', 'unknown')})"
            formatted_issues.append(issue_text)
        
        if len(issues) > 20:
            formatted_issues.append(f"... (还有 {len(issues) - 20} 个问题)")
        
        return '\n'.join(formatted_issues)
    
    def create_rag_context(self, 
                          rule_name: str = "",
                          rule_description: str = "",
                          best_practices: List[str] = None,
                          examples: Dict[str, str] = None,
                          related_rules: List[str] = None) -> str:
        """
        创建RAG知识库上下文信息
        
        Args:
            rule_name: 规则名称
            rule_description: 规则描述
            best_practices: 最佳实践列表
            examples: 示例代码（good/bad examples）
            related_rules: 相关规则
            
        Returns:
            格式化的知识库信息字符串
        """
        rag_sections = []
        
        if rule_name:
            rag_sections.append(f"**规则名称**: {rule_name}")
        
        if rule_description:
            rag_sections.append(f"**规则描述**: {rule_description}")
        
        if best_practices:
            practices_text = '\n'.join([f"- {practice}" for practice in best_practices])
            rag_sections.append(f"**最佳实践**:\n{practices_text}")
        
        if examples:
            examples_text = ""
            if 'good_example' in examples:
                examples_text += f"**正确示例**:\n```c\n{examples['good_example']}\n```\n"
            if 'bad_example' in examples:
                examples_text += f"**错误示例**:\n```c\n{examples['bad_example']}\n```"
            rag_sections.append(examples_text)
        
        if related_rules:
            related_text = ', '.join(related_rules)
            rag_sections.append(f"**相关规则**: {related_text}")
        
        return '\n\n'.join(rag_sections) if rag_sections else "暂无相关知识库信息"
    
    def get_system_prompt(self) -> str:
        """获取系统prompt"""
        return self.prompts.get("system_prompt", "")
    
    def update_prompts(self, new_prompts: Dict[str, str]):
        """更新prompt配置"""
        self.prompts.update(new_prompts)
        
        # 保存到文件
        try:
            with open(self.config_path, 'w', encoding='utf-8') as f:
                json.dump(self.prompts, f, ensure_ascii=False, indent=2)
        except Exception as e:
            print(f"保存prompt配置失败: {e}")


# 使用示例函数
def example_usage():
    """使用示例"""
    # 初始化管理器
    prompt_manager = QACPromptManager()
    
    # 示例1: 单个问题分析
    function_info = {
        'name': 'calculate_sum',
        'return_type': 'int',
        'start_line': 15,
        'end_line': 25,
        'parameters': [
            {'type': 'int', 'name': 'a'},
            {'type': 'int', 'name': 'b'}
        ],
        'complexity_score': 3,
        'body_content': 'int calculate_sum(int a, int b) {\n    return a + b;\n}'
    }
    
    rag_knowledge = prompt_manager.create_rag_context(
        rule_name="MISRA C 2012 Rule 10.3",
        rule_description="The value of an expression shall not be assigned to an object with a narrower essential type",
        best_practices=[
            "避免隐式类型转换",
            "使用显式类型转换",
            "检查数值范围"
        ],
        examples={
            'good_example': 'uint16_t x = (uint16_t)y;  // 显式转换',
            'bad_example': 'uint16_t x = y;  // 隐式转换'
        }
    )
    
    single_issue_prompt = prompt_manager.format_single_issue_prompt(
        file_name="example.c",
        line_number=20,
        error_id="MISRA-10.3",
        rule_violated="MISRA C 2012 Rule 10.3",
        error_message="Implicit conversion changes signedness",
        error_type="Type conversion",
        severity_level="high",
        function_info=function_info,
        code_context="int result = calculate_sum(a, b);",
        rag_knowledge=rag_knowledge
    )
    
    print("=== 单个问题分析Prompt ===")
    print(single_issue_prompt)
    print("\n" + "="*50 + "\n")
    


    
    # 示例2: 综合分析
    file_info = {
        'file_name': 'example.c',
        'total_lines': 150,
        'functions': [function_info],
        'includes': ['stdio.h', 'stdlib.h'],
        'defines': [{'name': 'MAX_SIZE', 'definition': '100'}]
    }
    
    detected_issues = [
        {
            'id': 'MISRA-10.3',
            'line': 20,
            'message': 'Implicit conversion changes signedness',
            'rule': 'MISRA C 2012 Rule 10.3'
        },
        {
            'id': 'MISRA-11.5',
            'line': 35,
            'message': 'Conversion from pointer to pointer',
            'rule': 'MISRA C 2012 Rule 11.5'
        }
    ]
    
    comprehensive_prompt = prompt_manager.format_comprehensive_analysis_prompt(
        file_info=file_info,
        detected_issues=detected_issues,
        function_dependencies={
            'called_functions': ['malloc', 'free', 'printf'],
            'used_variables': ['global_counter', 'buffer'],
            'external_dependencies': ['libc']
        }
    )
    
    print("=== 综合分析Prompt ===")
    print(comprehensive_prompt)


if __name__ == "__main__":
    example_usage()