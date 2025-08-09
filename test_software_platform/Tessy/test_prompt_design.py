#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
测试prompt管理器功能
"""

import sys
import os
from pathlib import Path

# 添加项目根目录到路径
project_root = Path(__file__).parent.parent
sys.path.append(str(project_root))

from prompt_manager import UnitTestPromptManager


def test_prompt_manager():
    """测试prompt管理器功能"""
    print("=== 测试Prompt管理器功能 ===\n")
    
    # 初始化管理器
    prompt_manager = UnitTestPromptManager()
    
    # 测试函数信息
    function_info = {
        'name': 'is_value_in_range',
        'return_type': 'int',
        'parameters': [
            {'type': 'input', 'name': 'value'},
            {'type': 'input', 'name': 'min'},
            {'type': 'input', 'name': 'max'}
        ],
        'body_content': '''int is_value_in_range(int value, int min, int max) {
                                if (value < min) {
                                    return 0;
                                }
                                if (value > max) {
                                    return 0;
                                }
                                return 1;
                            }''',
        'start_line': 1,
        'end_line': 10,
        'complexity_score': 3
    }
    
    # 测试分支信息
    branch_info = {
        'if_statements': 2,
        'switch_statements': 0,
        'for_loops': 0,
        'while_loops': 0,
        'total_branches': 2,
        'estimated_test_cases': 6,
        'branch_coverage_target': 90
    }
    
    # 测试函数属性
    function_properties = {
        'Description': '检查值是否在指定范围内，需要测试边界条件和异常情况',
        'Complexity': 'Low',
        'Lines': '8'
    }
    
    print("1. 测试系统prompt获取")
    system_prompt = prompt_manager.get_system_prompt()
    print(f"系统prompt长度: {len(system_prompt)} 字符")
    print(f"系统prompt前100字符: {system_prompt[:100]}...")
    print()
    
    print("2. 测试RAG上下文获取")
    rag_context = prompt_manager.get_rag_context()
    print(f"RAG上下文长度: {len(rag_context)} 字符")
    print(f"RAG上下文前100字符: {rag_context[:100]}...")
    print()
    
    print("3. 测试参数分析prompt")
    param_prompt = prompt_manager.format_function_parameter_analysis_prompt(
        parameters=function_info['parameters'],
        function_name=function_info['name']
    )
    print(f"参数分析prompt长度: {len(param_prompt)} 字符")
    print(f"参数分析prompt前200字符: {param_prompt[:200]}...")
    print()
    
    print("4. 测试分支分析prompt")
    branch_prompt = prompt_manager.format_comprehensive_branch_analysis_prompt(
        function_info=function_info,
        branch_info=branch_info,
        existing_test_cases=[]
    )
    print(f"分支分析prompt长度: {len(branch_prompt)} 字符")
    print(f"分支分析prompt前200字符: {branch_prompt[:200]}...")
    print()
    
    print("5. 测试测试用例构建思路prompt")
    idea_prompt = prompt_manager.format_test_case_idea_prompt(
        function_info=function_info,
        function_properties=function_properties
    )
    print(f"测试用例构建思路prompt长度: {len(idea_prompt)} 字符")
    print(f"测试用例构建思路prompt前200字符: {idea_prompt[:200]}...")
    print()
    
    print("6. 测试综合测试prompt")
    comprehensive_prompt = prompt_manager.create_comprehensive_test_prompt(
        function_info=function_info,
        branch_info=branch_info,
        function_properties=function_properties
    )
    print(f"综合测试prompt长度: {len(comprehensive_prompt)} 字符")
    print(f"综合测试prompt前300字符: {comprehensive_prompt[:300]}...")
    print()
    
    print("7. 测试默认全面测试prompt")
    default_prompt = prompt_manager.format_comprehensive_test_prompt(
        function_name=function_info['name'],
        return_type=function_info['return_type'],
        parameters=function_info['parameters'],
        function_body=function_info['body_content'],
        branch_info=branch_info,
        function_properties=function_properties
    )
    print(f"默认全面测试prompt长度: {len(default_prompt)} 字符")
    print(f"默认全面测试prompt前300字符: {default_prompt[:300]}...")
    print()
    
    print("=== 测试完成 ===")
    print("所有prompt生成功能正常！")


def test_prompt_templates():
    """测试prompt模板加载"""
    print("=== 测试Prompt模板加载 ===\n")
    
    prompt_manager = UnitTestPromptManager()
    
    # 检查可用的模板
    available_templates = list(prompt_manager.prompts.keys())
    print(f"可用的prompt模板: {available_templates}")
    print()
    
    # 检查每个模板的内容
    for template_name in available_templates:
        template_content = prompt_manager.prompts[template_name]
        print(f"模板 '{template_name}' 长度: {len(template_content)} 字符")
        print(f"模板 '{template_name}' 前100字符: {template_content[:100]}...")
        print()
    
    print("=== 模板加载测试完成 ===")


if __name__ == "__main__":
    print("开始测试Prompt管理器...\n")
    
    try:
        test_prompt_templates()
        print("\n" + "="*50 + "\n")
        test_prompt_manager()
        print("\n所有测试通过！")
    except Exception as e:
        print(f"测试过程中出现错误: {e}")
        import traceback
        traceback.print_exc() 