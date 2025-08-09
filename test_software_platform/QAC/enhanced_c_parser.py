#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
增强版C语言代码解析器
使用libclang解析C代码文件，提取详细的函数信息
每个C文件生成一个对应的JSON详情文件
优化版本 - 支持超时机制和复杂文件处理
"""

import os
import json
import sys
import time
import signal
import threading
from pathlib import Path
from typing import Dict, List, Any, Optional, Union
from dataclasses import dataclass, asdict
from datetime import datetime

try:
    from clang.cindex import Index, CursorKind, TranslationUnit, Config, TypeKind
except ImportError:
    print("错误: 需要安装 libclang")
    print("请运行: pip install libclang")
    sys.exit(1)

# 配置常量
DEFAULT_TIMEOUT = 30  # 默认超时时间（秒）
MAX_RECURSION_DEPTH = 50  # 最大递归深度
MAX_STRUCT_MEMBERS = 500  # 结构体成员数量限制
FAST_MODE_THRESHOLD = 1000  # 超过此行数使用快速模式

class TimeoutError(Exception):
    """超时异常"""
    pass

class ParseTimeoutHandler:
    """解析超时处理器"""
    def __init__(self, timeout_seconds):
        self.timeout_seconds = timeout_seconds
        self.timer = None
        
    def timeout_handler(self):
        raise TimeoutError(f"解析超时: 超过 {self.timeout_seconds} 秒")
    
    def __enter__(self):
        if os.name != 'nt':  # Linux/Mac
            signal.signal(signal.SIGALRM, lambda signum, frame: self.timeout_handler())
            signal.alarm(self.timeout_seconds)
        else:  # Windows
            self.timer = threading.Timer(self.timeout_seconds, self.timeout_handler)
            self.timer.start()
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        if os.name != 'nt':
            signal.alarm(0)
        else:
            if self.timer:
                self.timer.cancel()

@dataclass
class VariableInfo:
    """变量信息数据类"""
    name: str
    var_type: str
    is_global: bool
    is_local: bool
    is_parameter: bool
    line_number: int
    scope: str
    initial_value: Optional[str] = None

@dataclass
class FunctionInfo:
    """增强的函数信息数据类"""
    name: str
    return_type: str
    parameters: List[Dict[str, str]]
    is_static: bool
    is_inline: bool
    is_extern: bool
    start_line: int
    end_line: int
    file_path: str
    dependencies: List[str]
    called_functions: List[str]
    has_return_statement: bool
    return_value_type: Optional[str]
    comment: Optional[str]
    local_variables: List[VariableInfo]
    global_variables: List[VariableInfo]
    complexity_score: int
    body_content: str

@dataclass
class FileInfo:
    """增强的文件信息数据类"""
    file_path: str
    file_name: str
    total_lines: int
    functions: List[FunctionInfo]
    global_variables: List[VariableInfo]
    includes: List[str]
    defines: List[Dict[str, str]]
    typedefs: List[Dict[str, str]]
    structs: List[Dict[str, Any]]
    enums: List[Dict[str, Any]]
    parse_errors: List[str]
    file_hash: str
    parse_time: str

class EnhancedCParser:
    """增强版C语言代码解析器 - 优化版"""
    
    def __init__(self, code_dir: str, output_dir: str, timeout: int = DEFAULT_TIMEOUT):
        self.code_dir = Path(code_dir)
        self.output_dir = Path(output_dir)
        self.index = Index.create()
        self.timeout = timeout
        self.fast_mode = False
        self.recursion_depth = 0
        
        # 确保输出目录存在
        self.output_dir.mkdir(parents=True, exist_ok=True)
        
        # 缓存
        self.parse_cache = {}
        
        # 问题文件列表（使用简化处理）
        self.problematic_files = {
            'MC25CM_Dir-1.1-C11.c',
            'MC25CM_Dir-1.1-C90.c', 
            'MC25CM_Dir-1.1-C99.c',
            'MC25CM_Dir-1.1.c',
            'MC25CM_Dir-1.2-C90.c',
            'MC25CM_Dir-1.2-C99.c',
            'MC25CM_Dir-1.2.c'
        }
        
        # 设置libclang配置
        try:
            if os.name == 'nt':
                # Windows下可能需要手动设置libclang路径
                pass
        except Exception as e:
            print(f"警告: 设置libclang配置时出错: {e}")
    
    def is_problematic_file(self, file_path: Path) -> bool:
        """检查是否为问题文件"""
        return file_path.name in self.problematic_files
    
    def should_use_fast_mode(self, file_path: Path) -> bool:
        """判断是否使用快速模式"""
        try:
            with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                line_count = sum(1 for _ in f)
                return line_count > FAST_MODE_THRESHOLD or self.is_problematic_file(file_path)
        except Exception:
            return False
    
    def get_file_hash(self, file_path: Path) -> str:
        """计算文件哈希值"""
        import hashlib
        try:
            with open(file_path, 'rb') as f:
                return hashlib.md5(f.read()).hexdigest()
        except Exception:
            return ""
    
    def get_file_info(self, file_path: Path) -> FileInfo:
        """解析单个文件并返回增强的文件信息 - 优化版本"""
        print(f"正在解析文件: {file_path}")
        
        # 检查是否需要使用快速模式
        self.fast_mode = self.should_use_fast_mode(file_path)
        if self.fast_mode:
            print(f"  使用快速模式解析 (复杂文件)")
        
        file_info = FileInfo(
            file_path=str(file_path),
            file_name=file_path.name,
            total_lines=0,
            functions=[],
            global_variables=[],
            includes=[],
            defines=[],
            typedefs=[],
            structs=[],
            enums=[],
            parse_errors=[],
            file_hash=self.get_file_hash(file_path),
            parse_time=datetime.now().isoformat()
        )
        
        try:
            # 使用超时机制
            with ParseTimeoutHandler(self.timeout):
                start_time = time.time()
                
                # 读取文件内容
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    file_info.total_lines = len(content.splitlines())
                
                # 对于问题文件，使用简化的解析策略
                if self.is_problematic_file(file_path):
                    return self._parse_problematic_file(file_path, file_info, content)
                
                # 解析文件
                parse_args = ['-x', 'c', '-std=c99', '-I.']
                if self.fast_mode:
                    # 快速模式：禁用详细处理
                    parse_options = TranslationUnit.PARSE_SKIP_FUNCTION_BODIES
                else:
                    parse_options = TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD
                
                tu = self.index.parse(
                    str(file_path),
                    args=parse_args,
                    options=parse_options
                )
                
                if tu.diagnostics:
                    # 限制错误信息数量
                    max_errors = 50 if not self.fast_mode else 10
                    for i, diag in enumerate(tu.diagnostics):
                        if i >= max_errors:
                            file_info.parse_errors.append(f"... (省略 {len(tu.diagnostics) - max_errors} 个错误)")
                            break
                        file_info.parse_errors.append(f"Line {diag.location.line}: {diag.spelling}")
                
                # 重置递归深度
                self.recursion_depth = 0
                
                # 遍历AST
                self._process_cursor(tu.cursor, file_info, content)
                
                elapsed_time = time.time() - start_time
                print(f"  解析完成，耗时: {elapsed_time:.2f}秒")
                
        except TimeoutError as e:
            error_msg = f"解析超时: {e}"
            file_info.parse_errors.append(error_msg)
            print(f"警告: {error_msg}")
            # 对于超时的文件，尝试使用简化解析
            try:
                return self._parse_problematic_file(file_path, file_info, content)
            except Exception:
                pass
        except Exception as e:
            error_msg = f"解析文件时出错: {e}"
            file_info.parse_errors.append(error_msg)
            print(f"错误: {error_msg}")
        
        return file_info
    
    def _parse_problematic_file(self, file_path: Path, file_info: FileInfo, content: str) -> FileInfo:
        """简化解析问题文件"""
        print(f"  使用简化模式解析问题文件")
        
        try:
            lines = content.split('\n')
            
            # 简单的文本分析，提取基本信息
            in_function = False
            current_function = None
            brace_count = 0
            
            for line_num, line in enumerate(lines, 1):
                line = line.strip()
                
                # 检测包含
                if line.startswith('#include'):
                    include_name = line.replace('#include', '').strip().strip('<>"')
                    if include_name and include_name not in file_info.includes:
                        file_info.includes.append(include_name)
                
                # 检测宏定义
                elif line.startswith('#define') and len(file_info.defines) < 100:
                    parts = line.split(None, 2)
                    if len(parts) >= 2:
                        file_info.defines.append({
                            "name": parts[1],
                            "definition": parts[2] if len(parts) > 2 else "",
                            "line": line_num
                        })
                
                # 简单的函数检测
                elif '(' in line and ')' in line and '{' in line and not in_function:
                    # 可能是函数定义
                    if any(keyword in line for keyword in ['int ', 'void ', 'char ', 'float ', 'double ']):
                        func_name = self._extract_simple_function_name(line)
                        if func_name:
                            current_function = {
                                "name": func_name,
                                "return_type": "unknown",
                                "parameters": [],
                                "start_line": line_num,
                                "end_line": line_num,
                                "is_static": "static" in line,
                                "is_inline": "inline" in line,
                                "is_extern": "extern" in line,
                                "file_path": str(file_path),
                                "dependencies": [],
                                "called_functions": [],
                                "has_return_statement": False,
                                "return_value_type": None,
                                "comment": None,
                                "local_variables": [],
                                "global_variables": [],
                                "complexity_score": 1,
                                "body_content": ""
                            }
                            in_function = True
                            brace_count = 1
                
                # 跟踪大括号
                if in_function:
                    brace_count += line.count('{') - line.count('}')
                    if brace_count <= 0:
                        if current_function:
                            current_function["end_line"] = line_num
                            file_info.functions.append(current_function)
                            current_function = None
                        in_function = False
            
            file_info.parse_errors.append("使用简化解析模式")
            
        except Exception as e:
            file_info.parse_errors.append(f"简化解析失败: {e}")
        
        return file_info
    
    def _extract_simple_function_name(self, line: str) -> Optional[str]:
        """从行中提取简单的函数名"""
        try:
            # 移除注释
            if '//' in line:
                line = line[:line.index('//')]
            if '/*' in line:
                line = line[:line.index('/*')]
            
            # 找到函数名模式
            import re
            pattern = r'\b(\w+)\s*\('
            match = re.search(pattern, line)
            if match:
                func_name = match.group(1)
                # 排除关键字
                if func_name not in ['if', 'while', 'for', 'switch', 'sizeof']:
                    return func_name
        except Exception:
            pass
        return None
    
    def _process_cursor(self, cursor, file_info: FileInfo, content: str):
        """处理AST节点 - 优化版本"""
        # 递归深度限制
        if self.recursion_depth > MAX_RECURSION_DEPTH:
            return
        
        # 只处理当前文件中的节点
        if cursor.location.file and str(cursor.location.file) != file_info.file_path:
            return
        
        # 数量限制（避免处理极大的文件时内存溢出）
        max_items = 200 if self.fast_mode else 1000
        
        # 处理不同类型的节点
        if cursor.kind == CursorKind.INCLUSION_DIRECTIVE:
            if len(file_info.includes) < max_items:
                file_info.includes.append(cursor.spelling)
        
        elif cursor.kind == CursorKind.MACRO_DEFINITION:
            if len(file_info.defines) < max_items:
                file_info.defines.append({
                    "name": cursor.spelling,
                    "definition": self._get_macro_definition(cursor) if not self.fast_mode else "...",
                    "line": cursor.location.line
                })
        
        elif cursor.kind == CursorKind.TYPEDEF_DECL:
            if len(file_info.typedefs) < max_items:
                file_info.typedefs.append({
                    "name": cursor.spelling,
                    "underlying_type": cursor.underlying_typedef_type.spelling if cursor.underlying_typedef_type else "unknown",
                    "line": cursor.location.line
                })
        
        elif cursor.kind == CursorKind.STRUCT_DECL:
            if len(file_info.structs) < max_items:
                struct_info = self._extract_struct_info(cursor)
                if struct_info:
                    file_info.structs.append(struct_info)
        
        elif cursor.kind == CursorKind.ENUM_DECL:
            if len(file_info.enums) < max_items:
                enum_info = self._extract_enum_info(cursor)
                if enum_info:
                    file_info.enums.append(enum_info)
        
        elif cursor.kind == CursorKind.VAR_DECL:
            # 全局变量
            if len(file_info.global_variables) < max_items:
                var_info = self._extract_variable_info(cursor, "global")
                if var_info:
                    file_info.global_variables.append(var_info)
        
        elif cursor.kind == CursorKind.FUNCTION_DECL:
            if len(file_info.functions) < max_items:
                func_info = self._extract_enhanced_function_info(cursor, file_info.file_path, content)
                if func_info:
                    file_info.functions.append(func_info)
        
        # 递归处理子节点
        self.recursion_depth += 1
        try:
            for child in cursor.get_children():
                self._process_cursor(child, file_info, content)
        finally:
            self.recursion_depth -= 1
    
    def _get_macro_definition(self, cursor) -> str:
        """获取宏定义内容"""
        try:
            tokens = list(cursor.get_tokens())
            if len(tokens) > 1:
                return ' '.join(token.spelling for token in tokens[1:])
        except Exception:
            pass
        return ""
    
    def _extract_struct_info(self, cursor) -> Optional[Dict[str, Any]]:
        """提取结构体信息 - 优化版本"""
        try:
            members = []
            member_count = 0
            
            for child in cursor.get_children():
                if child.kind == CursorKind.FIELD_DECL:
                    member_count += 1
                    
                    # 限制成员数量，避免处理超大结构体
                    if member_count <= MAX_STRUCT_MEMBERS:
                        members.append({
                            "name": child.spelling,
                            "type": child.type.spelling if child.type else "unknown",
                            "line": child.location.line
                        })
                    elif member_count == MAX_STRUCT_MEMBERS + 1:
                        # 添加省略标记
                        members.append({
                            "name": "...",
                            "type": f"省略 {member_count - MAX_STRUCT_MEMBERS} 个成员",
                            "line": child.location.line
                        })
            
            return {
                "name": cursor.spelling,
                "members": members,
                "line": cursor.location.line,
                "total_members": member_count,
                "size": cursor.type.get_size() if cursor.type and not self.fast_mode else -1
            }
        except Exception as e:
            if not self.fast_mode:
                print(f"提取结构体信息时出错: {e}")
            return {
                "name": cursor.spelling,
                "members": [],
                "line": cursor.location.line,
                "total_members": 0,
                "size": -1,
                "error": str(e)
            }
    
    def _extract_enum_info(self, cursor) -> Optional[Dict[str, Any]]:
        """提取枚举信息 - 优化版本"""
        try:
            values = []
            value_count = 0
            max_enum_values = 200 if self.fast_mode else 500
            
            for child in cursor.get_children():
                if child.kind == CursorKind.ENUM_CONSTANT_DECL:
                    value_count += 1
                    
                    if value_count <= max_enum_values:
                        values.append({
                            "name": child.spelling,
                            "value": child.enum_value if not self.fast_mode else "...",
                            "line": child.location.line
                        })
                    elif value_count == max_enum_values + 1:
                        values.append({
                            "name": "...",
                            "value": f"省略 {value_count - max_enum_values} 个枚举值",
                            "line": child.location.line
                        })
            
            return {
                "name": cursor.spelling,
                "values": values,
                "line": cursor.location.line,
                "total_values": value_count
            }
        except Exception as e:
            if not self.fast_mode:
                print(f"提取枚举信息时出错: {e}")
            return {
                "name": cursor.spelling,
                "values": [],
                "line": cursor.location.line,
                "total_values": 0,
                "error": str(e)
            }
    
    def _extract_variable_info(self, cursor, scope: str) -> Optional[VariableInfo]:
        """提取变量信息"""
        try:
            return VariableInfo(
                name=cursor.spelling,
                var_type=cursor.type.spelling if cursor.type else "unknown",
                is_global=(scope == "global"),
                is_local=(scope == "local"),
                is_parameter=(scope == "parameter"),
                line_number=cursor.location.line,
                scope=scope,
                initial_value=self._get_variable_initial_value(cursor)
            )
        except Exception as e:
            print(f"提取变量信息时出错: {e}")
            return None
    
    def _get_variable_initial_value(self, cursor) -> Optional[str]:
        """获取变量初始值"""
        try:
            for child in cursor.get_children():
                if child.kind in [CursorKind.INTEGER_LITERAL, CursorKind.FLOATING_LITERAL, 
                                 CursorKind.STRING_LITERAL, CursorKind.CHARACTER_LITERAL]:
                    tokens = list(child.get_tokens())
                    if tokens:
                        return tokens[0].spelling
        except Exception:
            pass
        return None
    
    def _extract_enhanced_function_info(self, cursor, file_path: str, content: str) -> Optional[FunctionInfo]:
        """提取增强的函数信息 - 优化版本"""
        try:
            # 基本信息
            name = cursor.spelling
            return_type = cursor.result_type.spelling if cursor.result_type else "void"
            
            # 参数信息
            parameters = []
            max_params = 50 if self.fast_mode else 100
            param_count = 0
            
            for param in cursor.get_arguments():
                param_count += 1
                if param_count <= max_params:
                    param_type = param.type.spelling if param.type else "unknown"
                    param_name = param.spelling if param.spelling else "unnamed"
                    parameters.append({
                        "name": param_name,
                        "type": param_type,
                        "line": param.location.line
                    })
                elif param_count == max_params + 1:
                    parameters.append({
                        "name": "...",
                        "type": f"省略 {param_count - max_params} 个参数",
                        "line": param.location.line
                    })
            
            # 函数修饰符（快速模式下简化）
            if self.fast_mode:
                # 简单的字符串检查，避免tokenization开销
                func_text = self._get_function_signature(cursor, content)
                is_static = "static" in func_text
                is_inline = "inline" in func_text
                is_extern = "extern" in func_text
            else:
                tokens = list(cursor.get_tokens())
                token_strings = [token.spelling for token in tokens]
                is_static = "static" in token_strings
                is_inline = "inline" in token_strings
                is_extern = "extern" in token_strings
            
            # 行号信息
            start_line = cursor.extent.start.line
            end_line = cursor.extent.end.line
            
            # 获取函数体内容（快速模式下限制）
            if self.fast_mode and (end_line - start_line) > 100:
                body_content = f"函数体过大 ({end_line - start_line} 行)，已省略"
            else:
                body_content = self._get_function_body(cursor, content)
            
            # 局部变量和全局变量（快速模式下简化）
            local_variables = []
            global_variables = []
            if not self.fast_mode or (end_line - start_line) <= 50:
                self._extract_function_variables(cursor, local_variables, global_variables)
            
            # 依赖关系和函数调用（快速模式下简化）
            dependencies = []
            called_functions = []
            if not self.fast_mode or (end_line - start_line) <= 50:
                self._extract_function_dependencies(cursor, dependencies, called_functions)
            
            # 其他信息
            has_return_statement = self._has_return_statement(cursor) if not self.fast_mode else False
            return_value_type = self._get_return_value_type(cursor) if not self.fast_mode else None
            comment = self._get_function_comment(cursor, content) if not self.fast_mode else None
            complexity_score = self._calculate_complexity(cursor)
            
            return FunctionInfo(
                name=name,
                return_type=return_type,
                parameters=parameters,
                is_static=is_static,
                is_inline=is_inline,
                is_extern=is_extern,
                start_line=start_line,
                end_line=end_line,
                file_path=file_path,
                dependencies=dependencies,
                called_functions=called_functions,
                has_return_statement=has_return_statement,
                return_value_type=return_value_type,
                comment=comment,
                local_variables=local_variables,
                global_variables=global_variables,
                complexity_score=complexity_score,
                body_content=body_content
            )
            
        except Exception as e:
            if not self.fast_mode:
                print(f"提取函数信息时出错: {e}")
            # 返回简化的函数信息
            return FunctionInfo(
                name=cursor.spelling or "unknown",
                return_type="unknown",
                parameters=[],
                is_static=False,
                is_inline=False,
                is_extern=False,
                start_line=cursor.location.line,
                end_line=cursor.location.line,
                file_path=file_path,
                dependencies=[],
                called_functions=[],
                has_return_statement=False,
                return_value_type=None,
                comment=None,
                local_variables=[],
                global_variables=[],
                complexity_score=1,
                body_content=f"解析错误: {e}"
            )
    
    def _get_function_signature(self, cursor, content: str) -> str:
        """获取函数签名文本（用于快速模式）"""
        try:
            lines = content.split('\n')
            start_line = cursor.extent.start.line - 1
            end_line = min(start_line + 5, len(lines))  # 只取前5行
            
            if start_line >= 0 and start_line < len(lines):
                return '\n'.join(lines[start_line:end_line])
        except Exception:
            pass
        return ""
    
    def _get_function_body(self, cursor, content: str) -> str:
        """获取函数体内容"""
        try:
            lines = content.split('\n')
            start_line = cursor.extent.start.line - 1
            end_line = cursor.extent.end.line
            
            if start_line >= 0 and end_line <= len(lines):
                return '\n'.join(lines[start_line:end_line])
        except Exception:
            pass
        return ""
    
    def _extract_function_variables(self, cursor, local_vars: List[VariableInfo], global_vars: List[VariableInfo], depth: int = 0):
        """提取函数中的变量 - 优化版本"""
        # 递归深度限制
        if depth > MAX_RECURSION_DEPTH:
            return
        
        # 变量数量限制
        max_vars = 100 if self.fast_mode else 200
        
        try:
            for child in cursor.get_children():
                # 检查变量数量限制
                if len(local_vars) + len(global_vars) >= max_vars:
                    break
                    
                if child.kind == CursorKind.VAR_DECL:
                    if len(local_vars) < max_vars:
                        var_info = self._extract_variable_info(child, "local")
                        if var_info:
                            local_vars.append(var_info)
                elif child.kind == CursorKind.PARM_DECL:
                    if len(local_vars) < max_vars:
                        var_info = self._extract_variable_info(child, "parameter")
                        if var_info:
                            local_vars.append(var_info)
                elif child.kind == CursorKind.DECL_REF_EXPR and not self.fast_mode:
                    # 检查是否引用了全局变量（快速模式下跳过）
                    if len(global_vars) < max_vars // 2:
                        try:
                            ref = child.referenced
                            if ref and ref.kind == CursorKind.VAR_DECL and ref.linkage.name == 'EXTERNAL':
                                var_info = self._extract_variable_info(ref, "global")
                                if var_info and var_info not in global_vars:
                                    global_vars.append(var_info)
                        except Exception:
                            pass
                
                # 递归处理子节点（限制深度）
                if depth < MAX_RECURSION_DEPTH // 2:  # 更严格的深度限制
                    self._extract_function_variables(child, local_vars, global_vars, depth + 1)
        except Exception as e:
            if not self.fast_mode:
                print(f"提取函数变量时出错: {e}")
    
    def _extract_function_dependencies(self, cursor, dependencies: List[str], called_functions: List[str], depth: int = 0):
        """提取函数依赖关系 - 优化版本"""
        # 递归深度限制
        if depth > MAX_RECURSION_DEPTH:
            return
        
        # 依赖数量限制
        max_deps = 100 if self.fast_mode else 200
        
        try:
            for child in cursor.get_children():
                # 检查数量限制
                if len(dependencies) >= max_deps:
                    break
                    
                if child.kind == CursorKind.CALL_EXPR:
                    # 函数调用
                    try:
                        called_func = child.referenced
                        if called_func and called_func.spelling and len(called_functions) < max_deps // 2:
                            func_name = called_func.spelling
                            if func_name not in called_functions:
                                called_functions.append(func_name)
                            if func_name not in dependencies:
                                dependencies.append(func_name)
                    except Exception:
                        pass
                elif child.kind == CursorKind.DECL_REF_EXPR and not self.fast_mode:
                    # 变量或函数引用（快速模式下跳过）
                    try:
                        ref = child.referenced
                        if ref and ref.spelling and len(dependencies) < max_deps:
                            dep_name = ref.spelling
                            if dep_name not in dependencies:
                                dependencies.append(dep_name)
                    except Exception:
                        pass
                
                # 递归处理子节点（限制深度）
                if depth < MAX_RECURSION_DEPTH // 3:  # 更严格的深度限制
                    self._extract_function_dependencies(child, dependencies, called_functions, depth + 1)
        except Exception as e:
            if not self.fast_mode:
                print(f"获取依赖关系时出错: {e}")
        
        # 去重（在最后一次调用时执行）
        if depth == 0:
            dependencies[:] = list(dict.fromkeys(dependencies))  # 保持顺序的去重
            called_functions[:] = list(dict.fromkeys(called_functions))
    
    def _has_return_statement(self, cursor, depth: int = 0) -> bool:
        """检查函数是否有return语句 - 优化版本"""
        # 递归深度限制
        if depth > MAX_RECURSION_DEPTH // 4:  # 更严格的深度限制
            return False
            
        try:
            for child in cursor.get_children():
                if child.kind == CursorKind.RETURN_STMT:
                    return True
                # 限制递归深度
                if depth < MAX_RECURSION_DEPTH // 4:
                    if self._has_return_statement(child, depth + 1):
                        return True
        except Exception:
            pass
        return False
    
    def _get_return_value_type(self, cursor) -> Optional[str]:
        """获取返回值类型"""
        try:
            for child in cursor.get_children():
                if child.kind == CursorKind.RETURN_STMT:
                    for return_child in child.get_children():
                        if return_child.type:
                            return return_child.type.spelling
        except Exception:
            pass
        return None
    
    def _get_function_comment(self, cursor, content: str) -> Optional[str]:
        """获取函数注释"""
        try:
            lines = content.split('\n')
            start_line = cursor.extent.start.line - 1
            
            # 向前查找注释
            comments = []
            for i in range(start_line - 1, max(start_line - 10, -1), -1):
                if i >= 0 and i < len(lines):
                    line = lines[i].strip()
                    if line.startswith('//') or line.startswith('/*') or line.endswith('*/'):
                        comments.insert(0, line)
                    elif line == '':
                        continue
                    else:
                        break
            
            return '\n'.join(comments) if comments else None
        except Exception:
            pass
        return None
    
    def _calculate_complexity(self, cursor, depth: int = 0) -> int:
        """计算函数复杂度 - 优化版本"""
        # 快速模式下返回简单复杂度
        if self.fast_mode:
            return 1
            
        # 递归深度限制
        if depth > MAX_RECURSION_DEPTH // 4:
            return 0
            
        complexity = 1 if depth == 0 else 0  # 基础复杂度只在顶层计算
        
        try:
            for child in cursor.get_children():
                # 检查控制结构
                if child.kind in [CursorKind.IF_STMT, CursorKind.WHILE_STMT, 
                                 CursorKind.FOR_STMT, CursorKind.SWITCH_STMT,
                                 CursorKind.CASE_STMT]:
                    complexity += 1
                
                # 限制递归深度和复杂度上限
                if depth < MAX_RECURSION_DEPTH // 4 and complexity < 100:
                    complexity += self._calculate_complexity(child, depth + 1)
                
                # 避免计算过于复杂的函数
                if complexity > 100:
                    break
                    
        except Exception:
            pass
        return min(complexity, 100)  # 限制最大复杂度
    
    def parse_single_file(self, file_path: Path) -> bool:
        """解析单个文件并保存结果"""
        try:
            file_info = self.get_file_info(file_path)
            
            # 转换为字典格式
            result = {
                "file_info": asdict(file_info),
                "functions": [],
                "statistics": {
                    "total_functions": len(file_info.functions),
                    "total_variables": len(file_info.global_variables),
                    "total_lines": file_info.total_lines,
                    "has_errors": len(file_info.parse_errors) > 0
                }
            }
            
            # 处理函数列表
            for func in file_info.functions:
                func_dict = asdict(func)
                # 处理变量列表
                func_dict["local_variables"] = [asdict(var) for var in func.local_variables]
                func_dict["global_variables"] = [asdict(var) for var in func.global_variables]
                result["functions"].append(func_dict)
            
            # 处理全局变量列表
            result["file_info"]["global_variables"] = [asdict(var) for var in file_info.global_variables]
            
            # 保存到对应的JSON文件，避免同名文件覆盖
            # 将文件扩展名转换为安全的后缀名
            safe_suffix = file_path.suffix.replace('.', '_')  # .c -> _c, .h -> _h
            output_file = self.output_dir / f"{file_path.stem}{safe_suffix}_analysis.json"
            with open(output_file, 'w', encoding='utf-8') as f:
                json.dump(result, f, ensure_ascii=False, indent=2)
            
            print(f"✓ 已保存: {output_file}")
            return True
            
        except Exception as e:
            print(f"✗ 处理文件 {file_path} 时出错: {e}")
            return False
    
    def parse_all_files(self) -> Dict[str, Any]:
        """解析所有C文件"""
        print(f"开始解析目录: {self.code_dir}")
        print(f"输出目录: {self.output_dir}")
        
        # 获取所有.c和.h文件
        c_files = list(self.code_dir.glob("*.c")) + list(self.code_dir.glob("*.h"))
        
        print(f"找到 {len(c_files)} 个文件")
        
        # 统计信息
        success_count = 0
        error_count = 0
        total_functions = 0
        
        # 处理每个文件
        for file_path in c_files:
            if self.parse_single_file(file_path):
                success_count += 1
                try:
                    # 简单统计函数数量
                    safe_suffix = file_path.suffix.replace('.', '_')  # .c -> _c, .h -> _h
                    output_file = self.output_dir / f"{file_path.stem}{safe_suffix}_analysis.json"
                    with open(output_file, 'r', encoding='utf-8') as f:
                        data = json.load(f)
                        total_functions += data["statistics"]["total_functions"]
                except Exception:
                    pass
            else:
                error_count += 1
        
        # 生成总结报告
        summary = {
            "parse_time": datetime.now().isoformat(),
            "total_files": len(c_files),
            "success_files": success_count,
            "error_files": error_count,
            "total_functions": total_functions,
            "output_directory": str(self.output_dir),
            "files_processed": [f.name for f in c_files]
        }
        
        # 保存总结报告
        summary_file = self.output_dir / "parse_summary.json"
        with open(summary_file, 'w', encoding='utf-8') as f:
            json.dump(summary, f, ensure_ascii=False, indent=2)
        
        print(f"\n解析完成!")
        print(f"成功处理: {success_count} 个文件")
        print(f"失败文件: {error_count} 个文件")
        print(f"总函数数: {total_functions}")
        print(f"总结报告: {summary_file}")
        
        return summary

def c_parser_flow():
    """主函数 - 优化版本"""
    import argparse
    
    # 命令行参数解析
    parser_args = argparse.ArgumentParser(description='增强版C代码解析器')
    parser_args.add_argument('--timeout', type=int, default=DEFAULT_TIMEOUT, 
                           help=f'超时时间（秒），默认 {DEFAULT_TIMEOUT}')
    parser_args.add_argument('--fast-mode', action='store_true', 
                           help='启用快速模式（跳过详细分析）')
    parser_args.add_argument('--code-dir', type=str, 
                           help='代码目录路径')
    parser_args.add_argument('--output-dir', type=str,
                           help='输出目录路径')
    
    args = parser_args.parse_args()
    
    # 设置路径
    current_dir = Path(__file__).parent
    code_dir = Path(args.code_dir) if args.code_dir else current_dir / "code"
    output_dir = Path(args.output_dir) if args.output_dir else current_dir / "code_info_json"
    
    if not code_dir.exists():
        print(f"错误: 代码目录不存在 {code_dir}")
        return
    
    print(f"C代码解析器 - 优化版本")
    print(f"代码目录: {code_dir}")
    print(f"输出目录: {output_dir}")
    print(f"超时设置: {args.timeout} 秒")
    if args.fast_mode:
        print("使用快速模式")
    print("-" * 50)
    
    # 创建解析器
    parser_obj = EnhancedCParser(code_dir, output_dir, timeout=args.timeout)
    
    # 如果指定了快速模式，强制设置
    if args.fast_mode:
        parser_obj.fast_mode = True
    
    try:
        # 解析所有文件
        summary = parser_obj.parse_all_files()
        
        print(f"\n解析完成!")
        print(f"所有结果已保存到: {output_dir}")
        print(f"详细统计: {output_dir / 'parse_summary.json'}")
        
    except KeyboardInterrupt:
        print("\n用户中断解析过程")
    except Exception as e:
        print(f"\n解析过程中出现错误: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    c_parser_flow() 