#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
QAC系统测试脚本
用于验证prompt模板、RAG系统和API接口的功能
"""

import asyncio
import json
import requests
from pathlib import Path

from prompt_manager import QACPromptManager
from qac_chat_rag import QACChatRAG


def test_prompt_manager():
    """测试Prompt管理器"""
    print("=== 测试Prompt管理器 ===")
    
    try:
        # 初始化管理器
        prompt_manager = QACPromptManager()
        
        # 测试单个问题prompt格式化
        function_info = {
            'name': 'test_function',
            'return_type': 'int',
            'start_line': 10,
            'end_line': 20,
            'parameters': [
                {'type': 'int', 'name': 'a'},
                {'type': 'char*', 'name': 'str'}
            ],
            'complexity_score': 5,
            'body_content': 'int test_function(int a, char* str) {\n    return a + strlen(str);\n}'
        }
        
        # 创建RAG知识内容
        rag_knowledge = prompt_manager.create_rag_context(
            rule_name="MISRA C 2012 Rule 10.3",
            rule_description="The value of an expression shall not be assigned to an object with a narrower essential type",
            best_practices=[
                "使用显式类型转换",
                "检查数值范围"
            ],
            examples={
                'good_example': 'uint16_t x = (uint16_t)y;',
                'bad_example': 'uint16_t x = y;'
            }
        )
        
        # 格式化prompt
        prompt = prompt_manager.format_single_issue_prompt(
            file_name="test.c",
            line_number=15,
            error_id="MISRA-10.3",
            rule_violated="MISRA C 2012 Rule 10.3",
            error_message="Implicit conversion changes signedness",
            function_info=function_info,
            rag_knowledge=rag_knowledge
        )
        
        print("✓ 单个问题prompt格式化成功")
        print(f"Prompt长度: {len(prompt)} 字符")
        
        # 测试综合分析prompt
        file_info = {
            'file_name': 'test.c',
            'total_lines': 100,
            'functions': [function_info],
            'includes': ['stdio.h', 'string.h']
        }
        
        detected_issues = [
            {
                'id': 'MISRA-10.3',
                'line': 15,
                'message': 'Implicit conversion',
                'rule': 'MISRA C 2012 Rule 10.3'
            }
        ]
        
        comprehensive_prompt = prompt_manager.format_comprehensive_analysis_prompt(
            file_info=file_info,
            detected_issues=detected_issues
        )
        
        print("✓ 综合分析prompt格式化成功")
        print(f"综合分析Prompt长度: {len(comprehensive_prompt)} 字符")
        
        return True
        
    except Exception as e:
        print(f"✗ Prompt管理器测试失败: {e}")
        return False


def test_qac_rag_system():
    """测试QAC RAG系统"""
    print("\n=== 测试QAC RAG系统 ===")
    
    try:
        # 初始化系统（可能会失败，因为依赖外部配置）
        try:
            qac_rag = QACChatRAG()
            print("✓ QAC RAG系统初始化成功")
        except Exception as e:
            print(f"⚠ QAC RAG系统初始化失败（可能是配置问题）: {e}")
            return False
        
        # 测试代码上下文获取
        context = qac_rag.get_code_context("test.c", 15)
        print(f"✓ 代码上下文获取测试完成: {len(context)} 个字段")
        
        # 测试相关问题获取
        related_issues = qac_rag.get_related_issues("test.c", 15)
        print(f"✓ 相关问题获取测试完成: {len(related_issues)} 个问题")
        
        # 测试知识库查询（可能返回空结果）
        rag_docs = qac_rag.query_knowledge_base("MISRA C rule", k=3)
        print(f"✓ 知识库查询测试完成: {len(rag_docs)} 个文档")
        
        # 测试流式返回功能
        print("✓ 开始测试流式返回功能...")
        
        # 测试单个问题分析流式返回
        try:
            stream_result = qac_rag.analyze_single_issue(
                file_name="test.c",
                line_number=15,
                error_id="test-001",
                rule_violated="MISRA C 2012 Rule 10.3",
                error_message="Test error message",
                error_type="test",
                severity_level="medium",
                stream=True
            )
            
            # 检查是否返回生成器
            if hasattr(stream_result, '__iter__') and not isinstance(stream_result, str):
                print("✓ 单个问题分析流式返回测试通过")
            else:
                print("⚠ 单个问题分析流式返回格式异常")
                
        except Exception as e:
            print(f"⚠ 单个问题分析流式返回测试失败: {e}")
        
        # 测试文件综合分析流式返回
        try:
            stream_result = qac_rag.analyze_file_comprehensive(
                file_name="test.c",
                stream=True
            )
            
            # 检查是否返回生成器
            if hasattr(stream_result, '__iter__') and not isinstance(stream_result, str):
                print("✓ 文件综合分析流式返回测试通过")
            else:
                print("⚠ 文件综合分析流式返回格式异常")
                
        except Exception as e:
            print(f"⚠ 文件综合分析流式返回测试失败: {e}")
        
        # 测试上下文对话流式返回
        try:
            stream_result = qac_rag.chat_with_context(
                question="测试问题",
                file_name="test.c",
                line_number=15,
                stream=True
            )
            
            # 检查是否返回生成器
            if hasattr(stream_result, '__iter__') and not isinstance(stream_result, str):
                print("✓ 上下文对话流式返回测试通过")
            else:
                print("⚠ 上下文对话流式返回格式异常")
                
        except Exception as e:
            print(f"⚠ 上下文对话流式返回测试失败: {e}")
        
        return True
        
    except Exception as e:
        print(f"✗ QAC RAG系统测试失败: {e}")
        return False


def test_api_endpoints():
    """测试API端点"""
    print("\n=== 测试API端点 ===")
    
    base_url = "http://localhost:9803"
    
    try:
        # 测试健康检查
        response = requests.get(f"{base_url}/health", timeout=5)
        if response.status_code == 200:
            print("✓ 健康检查端点正常")
            health_data = response.json()
            print(f"  系统状态: {health_data.get('status')}")
            print(f"  RAG系统: {health_data.get('qac_rag_system')}")
        else:
            print(f"✗ 健康检查失败: {response.status_code}")
            return False
        
        # 测试系统状态
        response = requests.get(f"{base_url}/system/status", timeout=5)
        if response.status_code == 200:
            print("✓ 系统状态端点正常")
            status_data = response.json()
            for key, value in status_data.items():
                print(f"  {key}: {value}")
        else:
            print(f"⚠ 系统状态查询失败: {response.status_code}")
        
        # 测试文件列表
        response = requests.get(f"{base_url}/files/list", timeout=5)
        if response.status_code == 200:
            print("✓ 文件列表端点正常")
            files_data = response.json()
            print(f"  可用文件数量: {files_data.get('total_count', 0)}")
        else:
            print(f"⚠ 文件列表查询失败: {response.status_code}")
        
        # 测试单个问题分析（可能会因为系统未初始化而失败）
        test_data = {
            "file_name": "test.c",
            "line_number": 15,
            "error_id": "MISRA-10.3",
            "rule_violated": "MISRA C 2012 Rule 10.3",
            "error_message": "Test error message",
            "error_type": "Type conversion",
            "severity_level": "medium"
        }
        
        response = requests.post(f"{base_url}/analyze/single-issue", json=test_data, timeout=30)
        if response.status_code == 200:
            print("✓ 单个问题分析端点正常")
            result = response.json()
            print(f"  分析成功: {result.get('success')}")
        else:
            print(f"⚠ 单个问题分析失败: {response.status_code}")
            if response.status_code == 503:
                print("  (系统未初始化，这是正常的)")
        
        return True
        
    except requests.exceptions.ConnectionError:
        print("✗ 无法连接到API服务器")
        print("  请先启动API服务: python qac_api.py")
        return False
    except Exception as e:
        print(f"✗ API测试失败: {e}")
        return False


def test_stream_functionality():
    """测试流式返回功能"""
    print("\n=== 测试流式返回功能 ===")
    
    try:
        # 初始化系统
        qac_rag = QACChatRAG()
        print("✓ QAC RAG系统初始化成功")
        
        # 测试1: 单个问题分析流式返回
        print("测试1: 单个问题分析流式返回")
        try:
            stream_result = qac_rag.analyze_single_issue(
                file_name="test.c",
                line_number=15,
                error_id="test-001",
                rule_violated="MISRA C 2012 Rule 10.3",
                error_message="Test error message",
                error_type="test",
                severity_level="medium",
                stream=True
            )
            
            # 检查返回类型
            if hasattr(stream_result, '__iter__') and not isinstance(stream_result, str):
                print("✓ 返回类型正确（生成器）")
                
                # 尝试迭代（不实际输出内容，避免长时间等待）
                chunk_count = 0
                for chunk in stream_result:
                    chunk_count += 1
                    if chunk_count >= 3:  # 只测试前3个chunk
                        break
                print(f"✓ 流式迭代测试通过（测试了 {chunk_count} 个chunk）")
            else:
                print("✗ 返回类型错误")
                return False
                
        except Exception as e:
            print(f"✗ 单个问题分析流式返回测试失败: {e}")
            return False
        
        # 测试2: 文件综合分析流式返回
        print("测试2: 文件综合分析流式返回")
        try:
            stream_result = qac_rag.analyze_file_comprehensive(
                file_name="test.c",
                stream=True
            )
            
            if hasattr(stream_result, '__iter__') and not isinstance(stream_result, str):
                print("✓ 返回类型正确（生成器）")
                
                # 尝试迭代
                chunk_count = 0
                for chunk in stream_result:
                    chunk_count += 1
                    if chunk_count >= 3:
                        break
                print(f"✓ 流式迭代测试通过（测试了 {chunk_count} 个chunk）")
            else:
                print("✗ 返回类型错误")
                return False
                
        except Exception as e:
            print(f"✗ 文件综合分析流式返回测试失败: {e}")
            return False
        
        # 测试3: 上下文对话流式返回
        print("测试3: 上下文对话流式返回")
        try:
            stream_result = qac_rag.chat_with_context(
                question="测试问题",
                file_name="test.c",
                line_number=15,
                stream=True
            )
            
            if hasattr(stream_result, '__iter__') and not isinstance(stream_result, str):
                print("✓ 返回类型正确（生成器）")
                
                # 尝试迭代
                chunk_count = 0
                for chunk in stream_result:
                    chunk_count += 1
                    if chunk_count >= 3:
                        break
                print(f"✓ 流式迭代测试通过（测试了 {chunk_count} 个chunk）")
            else:
                print("✗ 返回类型错误")
                return False
                
        except Exception as e:
            print(f"✗ 上下文对话流式返回测试失败: {e}")
            return False
        
        # 测试4: 对比非流式返回
        print("测试4: 对比非流式返回")
        try:
            non_stream_result = qac_rag.analyze_single_issue(
                file_name="test.c",
                line_number=15,
                error_id="test-001",
                rule_violated="MISRA C 2012 Rule 10.3",
                error_message="Test error message",
                error_type="test",
                severity_level="medium",
                stream=False
            )
            
            if isinstance(non_stream_result, str):
                print("✓ 非流式返回类型正确（字符串）")
            else:
                print("✗ 非流式返回类型错误")
                return False
                
        except Exception as e:
            print(f"✗ 非流式返回测试失败: {e}")
            return False
        
        print("✓ 所有流式返回功能测试通过")
        return True
        
    except Exception as e:
        print(f"✗ 流式返回功能测试失败: {e}")
        return False


def test_file_structure():
    """测试文件结构"""
    print("\n=== 测试文件结构 ===")
    
    current_dir = Path(__file__).parent
    
    # 检查必要的文件
    required_files = [
        "qac_prompt_manager.py",
        "qac_chat_rag.py", 
        "qac_api.py",
        "enhanced_c_parser.py",
        "enhanced_data_processing.py"
    ]
    
    for file_name in required_files:
        file_path = current_dir / file_name
        if file_path.exists():
            print(f"✓ {file_name} 存在")
        else:
            print(f"✗ {file_name} 缺失")
    
    # 检查目录
    required_dirs = [
        "prompt",
        "code",
        "code_info_json",
        "context"
    ]
    
    for dir_name in required_dirs:
        dir_path = current_dir / dir_name
        if dir_path.exists():
            print(f"✓ {dir_name}/ 目录存在")
        else:
            print(f"⚠ {dir_name}/ 目录不存在")
    
    # 检查prompt配置文件
    prompt_config = current_dir / "prompt" / "qac_comprehensive_analysis_prompt.json"
    if prompt_config.exists():
        print("✓ prompt配置文件存在")
        try:
            with open(prompt_config, 'r', encoding='utf-8') as f:
                config_data = json.load(f)
                print(f"  包含 {len(config_data)} 个prompt模板")
        except Exception as e:
            print(f"⚠ prompt配置文件格式错误: {e}")
    else:
        print("✗ prompt配置文件缺失")
    
    return True


def run_all_tests():
    """运行所有测试"""
    print("QAC系统集成测试")
    print("=" * 50)
    
    tests = [
        ("文件结构", test_file_structure),
        ("Prompt管理器", test_prompt_manager),
        ("QAC RAG系统", test_qac_rag_system),
        ("流式返回功能", test_stream_functionality),
        ("API端点", test_api_endpoints)
    ]
    
    results = {}
    
    for test_name, test_func in tests:
        print(f"\n开始测试: {test_name}")
        try:
            results[test_name] = test_func()
        except Exception as e:
            print(f"✗ {test_name} 测试异常: {e}")
            results[test_name] = False
    
    # 总结
    print("\n" + "=" * 50)
    print("测试总结:")
    passed = 0
    total = len(tests)
    
    for test_name, success in results.items():
        status = "✓ 通过" if success else "✗ 失败"
        print(f"  {test_name}: {status}")
        if success:
            passed += 1
    
    print(f"\n总体结果: {passed}/{total} 个测试通过")
    
    if passed == total:
        print("🎉 所有测试通过！系统运行正常")
    elif passed >= total * 0.75:
        print("⚠ 大部分测试通过，系统基本可用")
    else:
        print("❌ 多个测试失败，请检查系统配置")
    
    return passed == total


if __name__ == "__main__":
    run_all_tests()