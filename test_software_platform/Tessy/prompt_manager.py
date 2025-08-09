#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
单元测试生成器Prompt管理器
用于管理和格式化各种prompt模板
"""

import json
import os
from typing import Dict, List, Optional, Any
from pathlib import Path


class UnitTestPromptManager:
    """单元测试生成器Prompt管理器"""
    
    def __init__(self, prompt_config_path: Optional[str] = None):
        """
        初始化Prompt管理器
        
        Args:
            prompt_config_path: prompt配置文件路径，默认使用同目录下的配置文件
        """
        if prompt_config_path is None:
            current_dir = Path(__file__).parent
            prompt_config_path = current_dir / "prompt" / "unit_test_generation_prompt.json"
        
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
    
    def format_comprehensive_test_prompt(self,
                                         function_name: str,
                                         return_type: str,
                                         parameters: List[Dict[str, str]],
                                         function_body: str,
                                         branch_info: Dict[str, Any] = None) -> str:
        """
        格式化全面测试用例生成的prompt
        
        Args:
            function_name: 函数名
            return_type: 返回类型
            parameters: 参数列表
            function_body: 函数体内容
            branch_info: 分支信息
            function_properties: 函数属性信息
            
        Returns:
            格式化后的prompt字符串
        """
        # 格式化参数信息
        parameters_str = self._format_parameters(parameters)
        
        # 提取输入和输出参数
        input_parameters = []
        output_parameters = []
        for param in parameters:
            if param.get('type', '').lower() == 'input':
                input_parameters.append(f"- **{param.get('name', 'unknown')}**: {param.get('type', 'unknown')}")
            elif param.get('type', '').lower() == 'output':
                output_parameters.append(f"- **{param.get('name', 'unknown')}**: {param.get('type', 'unknown')}")
        
        input_params_str = '\n'.join(input_parameters) if input_parameters else "无输入参数"
        output_params_str = '\n'.join(output_parameters) if output_parameters else "无输出参数"
        
        # 分支信息处理
        if branch_info:
            if_count = branch_info.get('if_statements', 0)
            switch_count = branch_info.get('switch_statements', 0)
            for_count = branch_info.get('for_loops', 0)
            while_count = branch_info.get('while_loops', 0)
            total_branches = branch_info.get('total_branches', 0)
            estimated_test_cases = branch_info.get('estimated_test_cases', 5)
        else:
            if_count = switch_count = for_count = while_count = total_branches = 0
            estimated_test_cases = 5
        
        # 函数属性信息处理
        test_case_idea = "基于函数结构和分支分析，生成高覆盖率的测试用例"
        
        # 使用branch_coverage_prompt_template模板
        template = self.prompts.get("branch_coverage_prompt_template", "")
        if template:
            return template.format(
            function_name=function_name,
            return_type=return_type,
            parameters=parameters_str,
            source_file=function_name + ".c",  # 默认源文件名
            function_body=function_body,
                if_count=if_count,
                switch_count=switch_count,
                for_count=for_count,
                while_count=while_count,
                total_branches=total_branches,
                estimated_test_cases=estimated_test_cases,
                input_parameters=input_params_str,
                output_parameters=output_params_str,
                test_case_idea=test_case_idea
            )
        else:
            # 如果模板不存在，使用默认格式
            return self._build_default_comprehensive_prompt(
                function_name, return_type, parameters_str, function_body,
            )
    
    def format_comprehensive_branch_analysis_prompt(self,
                                                function_info: Dict[str, Any],
                                                  branch_info: Dict[str, Any] = None,
                                                  existing_test_cases: List[Dict[str, Any]] = None) -> str:
        """
        格式化综合分支覆盖率分析的prompt
        
        Args:
            function_info: 函数信息
            branch_info: 分支信息
            existing_test_cases: 现有测试用例
            
        Returns:
            格式化后的prompt字符串
        """
        function_name = function_info.get('name', 'unknown')
        return_type = function_info.get('return_type', 'unknown')
        parameters = function_info.get('parameters', [])
        parameter_count = len(parameters)
        code_lines = function_info.get('end_line', 0) - function_info.get('start_line', 0) + 1
        complexity_score = function_info.get('complexity_score', 'unknown')
        
        # 分支信息处理
        if branch_info:
            if_count = branch_info.get('if_statements', 0)
            switch_count = branch_info.get('switch_statements', 0)
            for_count = branch_info.get('for_loops', 0)
            while_count = branch_info.get('while_loops', 0)
            total_branches = branch_info.get('total_branches', 0)
        else:
            if_count = switch_count = for_count = while_count = total_branches = 0
        
        # 关键分支识别
        critical_branches = self._identify_critical_branches(branch_info)
        
        # 覆盖率缺口分析
        coverage_gaps = self._analyze_coverage_gaps(existing_test_cases, branch_info)
        
        # 使用comprehensive_branch_analysis_template模板
        template = self.prompts.get("comprehensive_branch_analysis_template", "")
        if template:
            return template.format(
            function_name=function_name,
            return_type=return_type,
            parameter_count=parameter_count,
                code_lines=code_lines,
            complexity_score=complexity_score,
                if_count=if_count,
                switch_count=switch_count,
                for_count=for_count,
                while_count=while_count,
                total_branches=total_branches,
                critical_branches=critical_branches,
                coverage_gaps=coverage_gaps
            )
        else:
            return self._build_default_branch_analysis_prompt(
                function_info, branch_info, existing_test_cases
            )
    
    def format_function_parameter_analysis_prompt(self,
                                                parameters: List[Dict[str, str]],
                                                function_name: str) -> str:
        """
        格式化函数参数分析的prompt
        
        Args:
            parameters: 参数列表
            function_name: 函数名
            
        Returns:
            格式化后的prompt字符串
        """
        # 分离输入和输出参数
        input_parameters = []
        output_parameters = []
        parameter_types = []
        
        for param in parameters:
            param_name = param.get('name', 'unknown')
            param_type = param.get('type', 'unknown')
            
            if param.get('type', '').lower() == 'input':
                input_parameters.append(f"- **{param_name}**: {param_type}")
            elif param.get('type', '').lower() == 'output':
                output_parameters.append(f"- **{param_name}**: {param_type}")
            
            parameter_types.append(f"- **{param_name}**: {param_type}")
        
        input_params_str = '\n'.join(input_parameters) if input_parameters else "无输入参数"
        output_params_str = '\n'.join(output_parameters) if output_parameters else "无输出参数"
        param_types_str = '\n'.join(parameter_types) if parameter_types else "无参数"
        
        # 使用function_parameter_analysis_template模板
        template = self.prompts.get("function_parameter_analysis_template", "")
        if template:
            return template.format(
                input_parameters=input_params_str,
                output_parameters=output_params_str,
                parameter_types=param_types_str
            )
        else:
            return self._build_default_parameter_analysis_prompt(parameters, function_name)
    
    def format_test_case_idea_prompt(self, function_info: Dict[str, Any] ) -> str:
        """
        格式化测试用例构建思路的prompt
        
        Args:
            function_info: 函数信息
            function_properties: 函数属性信息
            
        Returns:
            格式化后的prompt字符串
        """
        function_name = function_info.get('name', 'unknown')
        
        # 确定测试目标
        test_objective = f"为函数 {function_name} 生成高覆盖率的单元测试用例，确保90%以上的分支覆盖率"
        
        # 使用test_case_idea_template模板
        template = self.prompts.get("test_case_idea_template", "")
        if template:
            return template.format(test_objective=test_objective)
        else:
            return self._build_default_test_case_idea_prompt(function_info)
    
    def get_rag_context(self) -> str:
        """
        获取RAG上下文信息
        
        Returns:
            RAG上下文字符串
        """
        template = self.prompts.get("rag_context_template", "")
        return template if template else self._build_default_rag_context()
    
    def create_comprehensive_test_prompt(self,
                                       function_info: Dict[str, Any],
                                       branch_info: Dict[str, Any] = None,
                                       existing_test_cases: List[Dict[str, Any]] = None,
                                       rag_context: str = "") -> str:
        """
        创建综合测试prompt，包含所有相关信息
        
        Args:
            function_info: 函数信息
            branch_info: 分支信息
            function_properties: 函数属性信息
            existing_test_cases: 现有测试用例
            rag_context: RAG上下文信息
            
        Returns:
            完整的prompt字符串
        """
        # 获取系统prompt
        system_prompt = self.get_system_prompt()
        
        # 构建主要测试prompt
        main_prompt = self.format_comprehensive_test_prompt(
            function_name=function_info.get('name', 'unknown'),
            return_type=function_info.get('return_type', 'unknown'),
            parameters=function_info.get('parameters', []),
            function_body=function_info.get('body_content', ''),
            branch_info=branch_info,
        )
        
        # 添加分支分析
        if branch_info:
            branch_analysis = self.format_comprehensive_branch_analysis_prompt(
                function_info, branch_info, existing_test_cases
            )
            main_prompt += "\n\n" + branch_analysis
        
        # 添加参数分析
        if function_info.get('parameters'):
            param_analysis = self.format_function_parameter_analysis_prompt(
                function_info.get('parameters', []),
                function_info.get('name', 'unknown')
            )
            main_prompt += "\n\n" + param_analysis
        
        # 添加测试用例构建思路
        test_idea = self.format_test_case_idea_prompt(function_info)
        main_prompt += "\n\n" + test_idea
        
        # 添加RAG上下文
        if not rag_context:
            rag_context = self.get_rag_context()
        
        if rag_context:
            main_prompt += "\n\n" + rag_context
        
        return f"{system_prompt}\n\n{main_prompt}"
    
    def _identify_critical_branches(self, branch_info: Dict[str, Any]) -> str:
        """识别关键分支"""
        if not branch_info:
            return "分支信息不可用"
        
        critical_branches = []
        
        if branch_info.get('if_statements', 0) > 0:
            critical_branches.append("if分支 - 需要覆盖所有条件分支")
        
        if branch_info.get('switch_statements', 0) > 0:
            critical_branches.append("switch分支 - 需要覆盖所有case分支")
        
        if branch_info.get('for_loops', 0) > 0:
            critical_branches.append("for循环分支 - 需要覆盖循环进入、执行、退出条件")
        
        if branch_info.get('while_loops', 0) > 0:
            critical_branches.append("while循环分支 - 需要覆盖循环进入、执行、退出条件")
        
        return '\n'.join([f"- {branch}" for branch in critical_branches]) if critical_branches else "无关键分支"
    
    def _analyze_coverage_gaps(self, existing_test_cases: List[Dict[str, Any]], 
                              branch_info: Dict[str, Any]) -> str:
        """分析覆盖率缺口"""
        if not existing_test_cases:
            return "暂无现有测试用例，需要生成完整的测试用例集"
        
        if not branch_info:
            return "分支信息不可用，无法分析覆盖率缺口"
        
        gaps = []
        total_branches = branch_info.get('total_branches', 0)
        
        if total_branches > 0:
            estimated_coverage = min(95, len(existing_test_cases) * 15)
            if estimated_coverage < 90:
                gaps.append(f"当前预估覆盖率 {estimated_coverage}% 低于目标90%")
            
            # 分析不同类型分支的覆盖情况
            if branch_info.get('if_statements', 0) > 0:
                gaps.append("if分支可能需要更多测试用例")
            
            if branch_info.get('switch_statements', 0) > 0:
                gaps.append("switch分支需要覆盖所有case")
        
        return '\n'.join([f"- {gap}" for gap in gaps]) if gaps else "覆盖率缺口分析完成"
    
    def _format_parameters(self, parameters: List[Dict[str, str]]) -> str:
        """格式化函数参数列表"""
        if not parameters:
            return "无参数"
        
        param_strs = []
        for param in parameters:
            param_type = param.get('type', 'unknown')
            param_name = param.get('name', 'unnamed')
            param_strs.append(f"{param_type} {param_name}")
        
        return ', '.join(param_strs)
    
    def _build_default_comprehensive_prompt(self,
                                          function_name: str,
                                          return_type: str,
                                          parameters_str: str,
                                          function_body: str,
                                          branch_info: Dict[str, Any] = None) -> str:
        """构建默认的全面测试prompt"""
        prompt_lines = []
        prompt_lines.append("## 🎯 高覆盖率单元测试生成")
        prompt_lines.append("")
        prompt_lines.append("### 📍 目标函数信息")
        prompt_lines.append(f"- **函数名**: {function_name}")
        prompt_lines.append(f"- **返回类型**: {return_type}")
        prompt_lines.append(f"- **参数列表**: {parameters_str}")
        prompt_lines.append(f"- **源文件**: {function_name}.c")
        prompt_lines.append("")
        
        prompt_lines.append("### 💻 函数代码详情")
        prompt_lines.append("#### 函数体:")
        prompt_lines.append(f"```c\n{function_body}\n```")
        prompt_lines.append("")
        
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
        
        prompt_lines.append("### ✅ 质量标准")
        prompt_lines.append("- **覆盖率要求**: 确保90%以上的分支覆盖率")
        prompt_lines.append("- **分支完整性**: 覆盖所有if和switch分支")
        prompt_lines.append("- **边界完整性**: 包含所有边界条件测试")
        prompt_lines.append("- **可执行性**: 生成的测试用例可以直接执行")
        prompt_lines.append("- **可验证性**: 期望输出必须准确且可验证")
        
        return "\n".join(prompt_lines)
    
    def _build_default_branch_analysis_prompt(self,
                                            function_info: Dict[str, Any],
                                            branch_info: Dict[str, Any],
                                            existing_test_cases: List[Dict[str, Any]]) -> str:
        """构建默认的分支分析prompt"""
        prompt_lines = []
        prompt_lines.append("## 🔬 综合分支覆盖率分析")
        prompt_lines.append("")
        prompt_lines.append("### 函数结构分析")
        prompt_lines.append("#### 基本信息:")
        prompt_lines.append(f"- **函数名**: {function_info.get('name', 'unknown')}")
        prompt_lines.append(f"- **返回类型**: {function_info.get('return_type', 'unknown')}")
        prompt_lines.append(f"- **参数数量**: {len(function_info.get('parameters', []))}")
        prompt_lines.append(f"- **代码行数**: {function_info.get('end_line', 0) - function_info.get('start_line', 0) + 1}")
        prompt_lines.append(f"- **函数复杂度**: {function_info.get('complexity_score', 'unknown')}")
        prompt_lines.append("")
        
        if branch_info:
            prompt_lines.append("#### 分支结构:")
            prompt_lines.append(f"- **if语句**: {branch_info.get('if_statements', 0)} 个")
            prompt_lines.append(f"- **switch语句**: {branch_info.get('switch_statements', 0)} 个")
            prompt_lines.append(f"- **for循环**: {branch_info.get('for_loops', 0)} 个")
            prompt_lines.append(f"- **while循环**: {branch_info.get('while_loops', 0)} 个")
            prompt_lines.append(f"- **总分支数**: {branch_info.get('total_branches', 0)}")
            prompt_lines.append("")
        
        prompt_lines.append("### 🎯 分支覆盖率分析")
        prompt_lines.append("#### 当前覆盖率评估:")
        prompt_lines.append("- **if分支覆盖率**: 需要达到90%+")
        prompt_lines.append("- **switch分支覆盖率**: 需要达到90%+")
        prompt_lines.append("- **整体分支覆盖率**: 目标90%+")
        prompt_lines.append("")
        
        # 关键分支识别
        critical_branches = self._identify_critical_branches(branch_info)
        prompt_lines.append("#### 关键分支识别:")
        prompt_lines.append(critical_branches)
        prompt_lines.append("")
        
        # 覆盖率缺口分析
        coverage_gaps = self._analyze_coverage_gaps(existing_test_cases, branch_info)
        prompt_lines.append("#### 覆盖率缺口分析:")
        prompt_lines.append(coverage_gaps)
        prompt_lines.append("")
        
        prompt_lines.append("### 📋 测试策略制定")
        prompt_lines.append("#### 1. if分支测试策略:")
        prompt_lines.append("- 条件组合测试")
        prompt_lines.append("- 边界值测试")
        prompt_lines.append("- 异常值测试")
        prompt_lines.append("")
        prompt_lines.append("#### 2. switch分支测试策略:")
        prompt_lines.append("- 每个case分支测试")
        prompt_lines.append("- default分支测试")
        prompt_lines.append("- 边界case值测试")
        prompt_lines.append("")
        prompt_lines.append("#### 3. 循环分支测试策略:")
        prompt_lines.append("- 循环不执行")
        prompt_lines.append("- 循环执行一次")
        prompt_lines.append("- 循环执行多次")
        prompt_lines.append("- 循环边界条件")
        prompt_lines.append("")
        
        prompt_lines.append("### 📝 输出格式要求")
        prompt_lines.append("请按以下JSON格式输出分析结果和测试用例:")
        prompt_lines.append("```json")
        prompt_lines.append("{")
        prompt_lines.append("  \"branch_analysis\": {")
        prompt_lines.append("    \"if_coverage_required\": \"if分支覆盖率要求\",")
        prompt_lines.append("    \"switch_coverage_required\": \"switch分支覆盖率要求\",")
        prompt_lines.append("    \"total_coverage_target\": \"总体覆盖率目标\",")
        prompt_lines.append("    \"critical_if_branches\": [\"关键if分支\"],")
        prompt_lines.append("    \"critical_switch_branches\": [\"关键switch分支\"],")
        prompt_lines.append("    \"coverage_strategy\": \"覆盖率策略\"")
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
        prompt_lines.append("      \"priority\": \"high/medium/low\",")
        prompt_lines.append("      \"coverage_impact\": \"覆盖率影响\"")
        prompt_lines.append("    }")
        prompt_lines.append("  ],")
        prompt_lines.append("  \"coverage_plan\": {")
        prompt_lines.append("    \"estimated_coverage\": \"预估覆盖率\",")
        prompt_lines.append("    \"coverage_gaps\": [\"覆盖率缺口\"],")
        prompt_lines.append("    \"additional_cases_needed\": \"是否需要额外测试用例\",")
        prompt_lines.append("    \"execution_order\": \"测试执行顺序建议\"")
        prompt_lines.append("  }")
        prompt_lines.append("}")
        prompt_lines.append("```")
        
        return "\n".join(prompt_lines)
    
    def _build_default_parameter_analysis_prompt(self, parameters: List[Dict[str, str]], 
                                               function_name: str) -> str:
        """构建默认的参数分析prompt"""
        prompt_lines = []
        prompt_lines.append("## 📊 函数参数分析模板")
        prompt_lines.append("")
        prompt_lines.append("### 参数结构分析")
        
        # 分离输入和输出参数
        input_parameters = []
        output_parameters = []
        parameter_types = []
        
        for param in parameters:
            param_name = param.get('name', 'unknown')
            param_type = param.get('type', 'unknown')
            
            if param.get('type', '').lower() == 'input':
                input_parameters.append(f"- **{param_name}**: {param_type}")
            elif param.get('type', '').lower() == 'output':
                output_parameters.append(f"- **{param_name}**: {param_type}")
            
            parameter_types.append(f"- **{param_name}**: {param_type}")
        
        input_params_str = '\n'.join(input_parameters) if input_parameters else "无输入参数"
        output_params_str = '\n'.join(output_parameters) if output_parameters else "无输出参数"
        param_types_str = '\n'.join(parameter_types) if parameter_types else "无参数"
        
        prompt_lines.append("#### 输入参数 (i):")
        prompt_lines.append(input_params_str)
        prompt_lines.append("")
        prompt_lines.append("#### 输出参数 (o):")
        prompt_lines.append(output_params_str)
        prompt_lines.append("")
        prompt_lines.append("#### 参数类型分析:")
        prompt_lines.append(param_types_str)
        prompt_lines.append("")
        
        prompt_lines.append("### 🎯 参数测试策略")
        prompt_lines.append("#### 1. 输入参数测试:")
        prompt_lines.append("- 有效值范围测试")
        prompt_lines.append("- 边界值测试")
        prompt_lines.append("- 无效值测试")
        prompt_lines.append("- 特殊值测试")
        prompt_lines.append("")
        prompt_lines.append("#### 2. 输出参数测试:")
        prompt_lines.append("- 返回值验证")
        prompt_lines.append("- 输出参数状态验证")
        prompt_lines.append("- 错误返回值验证")
        prompt_lines.append("")
        
        prompt_lines.append("### 📝 测试用例生成指导")
        prompt_lines.append("基于参数分析，生成以下类型的测试用例：")
        prompt_lines.append("")
        prompt_lines.append("#### 正常值测试:")
        prompt_lines.append("- 使用参数的有效值范围")
        prompt_lines.append("- 验证函数的正常行为")
        prompt_lines.append("")
        prompt_lines.append("#### 边界值测试:")
        prompt_lines.append("- 测试参数的最小值、最大值")
        prompt_lines.append("- 测试临界值")
        prompt_lines.append("")
        prompt_lines.append("#### 异常值测试:")
        prompt_lines.append("- 测试无效输入")
        prompt_lines.append("- 测试NULL指针")
        prompt_lines.append("- 测试超出范围的值")
        prompt_lines.append("")
        prompt_lines.append("#### 组合测试:")
        prompt_lines.append("- 多个参数的组合测试")
        prompt_lines.append("- 参数间的依赖关系测试")
        
        return "\n".join(prompt_lines)
    
    def _build_default_test_case_idea_prompt(self, function_info: Dict[str, Any]) -> str:
        """构建默认的测试用例构建思路prompt"""
        function_name = function_info.get('name', 'unknown')
        
        prompt_lines = []
        prompt_lines.append("## 💡 测试用例构建思路")
        prompt_lines.append("")
        
        # 确定测试目标
        test_objective = f"为函数 {function_name} 生成高覆盖率的单元测试用例，确保90%以上的分支覆盖率"
 
        prompt_lines.append("### 测试目标")
        prompt_lines.append(test_objective)
        prompt_lines.append("")
        
        prompt_lines.append("### 测试重点")
        prompt_lines.append("- **分支覆盖率**: 重点关注if和switch分支")
        prompt_lines.append("- **边界条件**: 测试所有边界值")
        prompt_lines.append("- **异常处理**: 验证错误处理逻辑")
        prompt_lines.append("- **功能完整性**: 确保所有功能路径被测试")
        prompt_lines.append("")
        
        prompt_lines.append("### 测试策略")
        prompt_lines.append("#### 1. 分支覆盖策略:")
        prompt_lines.append("- 识别所有if和switch语句")
        prompt_lines.append("- 为每个分支设计测试用例")
        prompt_lines.append("- 确保90%以上的覆盖率")
        prompt_lines.append("")
        prompt_lines.append("#### 2. 数据驱动策略:")
        prompt_lines.append("- 基于参数类型设计测试数据")
        prompt_lines.append("- 使用等价类划分方法")
        prompt_lines.append("- 包含边界值和异常值")
        prompt_lines.append("")
        prompt_lines.append("#### 3. 场景驱动策略:")
        prompt_lines.append("- 基于函数的使用场景")
        prompt_lines.append("- 模拟真实调用情况")
        prompt_lines.append("- 验证函数的实际行为")
        prompt_lines.append("")
        
        prompt_lines.append("### 预期结果")
        prompt_lines.append("- 生成可执行的测试用例")
        prompt_lines.append("- 达到90%以上的分支覆盖率")
        prompt_lines.append("- 验证所有关键功能路径")
        prompt_lines.append("- 确保测试用例的可维护性")
        
        return "\n".join(prompt_lines)
    
    def _build_default_rag_context(self) -> str:
        """构建默认的RAG上下文"""
        prompt_lines = []
        prompt_lines.append("## 📚 高覆盖率单元测试知识库")
        prompt_lines.append("")
        prompt_lines.append("### 🎯 分支覆盖率测试原则")
        prompt_lines.append("- **if分支测试**: 覆盖所有if条件的不同分支")
        prompt_lines.append("- **switch分支测试**: 覆盖所有case分支和default分支")
        prompt_lines.append("- **循环分支测试**: 覆盖循环的进入、执行、退出条件")
        prompt_lines.append("- **复合条件测试**: 测试复杂逻辑表达式的各种组合")
        prompt_lines.append("")
        
        prompt_lines.append("### 📋 测试用例类型")
        prompt_lines.append("#### 1. 分支覆盖测试用例")
        prompt_lines.append("- **if分支测试**: 条件为真/假的不同路径")
        prompt_lines.append("- **switch分支测试**: 每个case分支的测试")
        prompt_lines.append("- **循环分支测试**: 循环执行0次、1次、多次")
        prompt_lines.append("")
        prompt_lines.append("#### 2. 边界值测试用例")
        prompt_lines.append("- **数值边界**: 最小值、最大值、临界值")
        prompt_lines.append("- **字符串边界**: 空字符串、单字符、最大长度")
        prompt_lines.append("- **指针边界**: NULL指针、有效指针")
        prompt_lines.append("")
        prompt_lines.append("#### 3. 异常情况测试用例")
        prompt_lines.append("- **无效输入**: 超出范围的值、错误类型")
        prompt_lines.append("- **异常状态**: 错误条件、异常处理")
        prompt_lines.append("- **资源异常**: 内存不足、文件不存在")
        prompt_lines.append("")
        
        prompt_lines.append("### 🔧 覆盖率测试技术")
        prompt_lines.append("#### 分支覆盖率计算:")
        prompt_lines.append("- **覆盖率公式**: (已覆盖分支数 / 总分支数) × 100%")
        prompt_lines.append("- **目标覆盖率**: 90%以上")
        prompt_lines.append("- **关键分支**: if、switch、循环控制分支")
        prompt_lines.append("")
        prompt_lines.append("#### 测试数据准备:")
        prompt_lines.append("- **等价类划分**: 有效等价类和无效等价类")
        prompt_lines.append("- **边界值分析**: 边界值和边界值附近的值")
        prompt_lines.append("- **错误推测**: 基于经验推测可能的错误")
        prompt_lines.append("")
        
        prompt_lines.append("### 📝 测试用例质量标准")
        prompt_lines.append("- **覆盖率要求**: 90%以上的分支覆盖率")
        prompt_lines.append("- **分支完整性**: 覆盖所有if和switch分支")
        prompt_lines.append("- **可重复性**: 测试结果应该一致")
        prompt_lines.append("- **独立性**: 测试用例之间不应相互依赖")
        prompt_lines.append("- **可维护性**: 测试用例应该易于理解和修改")
        prompt_lines.append("- **可执行性**: 生成的测试用例可以直接执行")
        prompt_lines.append("- **可验证性**: 期望输出必须准确且可验证")
        prompt_lines.append("")
        
        prompt_lines.append("### ✅ 覆盖率验证方法")
        prompt_lines.append("- **代码覆盖率工具**: 使用覆盖率分析工具验证")
        prompt_lines.append("- **分支路径分析**: 分析每个分支的执行情况")
        prompt_lines.append("- **覆盖率报告**: 生成详细的覆盖率报告")
        prompt_lines.append("- **覆盖率缺口**: 识别未覆盖的分支并补充测试用例")
        
        return "\n".join(prompt_lines)
    
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
    prompt_manager = UnitTestPromptManager()
    
    # 示例1: 全面测试用例生成
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
                            }'''
    }
    
    branch_info = {
        'if_statements': 2,
        'switch_statements': 0,
        'for_loops': 0,
        'while_loops': 0,
        'total_branches': 2,
        'estimated_test_cases': 6
    }
    
    function_properties = {
        'Description': '检查值是否在指定范围内，需要测试边界条件和异常情况'
    }
    
    comprehensive_prompt = prompt_manager.create_comprehensive_test_prompt(
        function_info=function_info,
        branch_info=branch_info,
        function_properties=function_properties
    )
    
    print("=== 全面测试用例生成Prompt ===")
    print(comprehensive_prompt)
    print("\n" + "="*50 + "\n")
    
    # 示例2: 分支分析
    branch_analysis_prompt = prompt_manager.format_comprehensive_branch_analysis_prompt(
        function_info=function_info,
        branch_info=branch_info,
        existing_test_cases=[]
    )
    
    print("=== 分支分析Prompt ===")
    print(branch_analysis_prompt)
    print("\n" + "="*50 + "\n")
    
    # 示例3: 参数分析
    param_analysis_prompt = prompt_manager.format_function_parameter_analysis_prompt(
        parameters=function_info['parameters'],
        function_name=function_info['name']
    )
    
    print("=== 参数分析Prompt ===")
    print(param_analysis_prompt)
    print("\n" + "="*50 + "\n")
    
    # 示例4: RAG上下文
    rag_context = prompt_manager.get_rag_context()
    print("=== RAG上下文 ===")
    print(rag_context)


if __name__ == "__main__":
    example_usage() 