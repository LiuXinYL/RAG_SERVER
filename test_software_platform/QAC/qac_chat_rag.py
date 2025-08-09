#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
QAC代码分析聊天RAG系统
整合代码信息、错误报告、知识库，提供智能代码分析服务
"""

import os
import sys
import json
import pandas as pd
from typing import Dict, List, Optional, Any, Tuple
from pathlib import Path

# 添加项目根目录到路径
project_root = Path(__file__).parent.parent
sys.path.append(str(project_root))

from config import LLM_CONFIG, VECTOR_SAVE_PATH
from qac_prompt_manager import QACPromptManager
from llm_init import LLM_INIT
from _faiss.custom_faiss import FAISSCUSTOM
from langchain.schema import Document
from langchain_core.messages import HumanMessage, SystemMessage


class QACChatRAG:
    """QAC代码分析聊天RAG系统"""
    
    def __init__(self, 
                 vector_store_name: str = "qac",
                 enhanced_data_path: str = None,
                 code_info_json_dir: str = None,
                 max_tokens: int = LLM_CONFIG["max_tokens"],
                 temperature: float = LLM_CONFIG["temperature"]):
        """
        初始化QAC聊天RAG系统
        
        Args:
            vector_store_name: 向量存储名称
            enhanced_data_path: 增强数据文件路径
            code_info_json_dir: 代码信息JSON目录
            max_tokens: 最大token数
            temperature: 温度参数
        """
        self.prompt_manager = QACPromptManager()
        self.vector_store_name = vector_store_name
        
        # 使用 LLM_INIT 初始化模型
        self.llm_init = LLM_INIT(max_tokens=max_tokens, temperature=temperature)
        self.llm = self.llm_init.create_chat_client()
        self.embeddings_model = self.llm_init.create_embeddings_client()
        self.rerank_model = self.llm_init.create_rerank_client()
        
        # 使用 FAISSCUSTOM 初始化向量存储
        self.faiss_custom = FAISSCUSTOM(
            max_tokens=max_tokens,
            temperature=temperature,
            embedding_client=self.embeddings_model,
            rerank_client=self.rerank_model,
            knowledge_name=vector_store_name
        )
        
        # 设置向量存储路径并加载
        self.vector_store_path = Path(VECTOR_SAVE_PATH) / vector_store_name
        self._load_vector_store()
        
        # 数据路径
        current_dir = Path(__file__).parent
        self.enhanced_data_path = enhanced_data_path or (current_dir / "context" / "enhanced_analysis_result.csv")
        self.code_info_json_dir = code_info_json_dir or (current_dir / "code_info_json")
        
        # 加载增强数据
        self.enhanced_data = self._load_enhanced_data()
        
        print(f"QAC聊天RAG系统初始化完成")
        print(f"- 向量存储路径: {self.vector_store_path}")
        print(f"- 向量存储状态: {'已加载' if self.faiss_custom.vector_store else '未找到'}")
        print(f"- 增强数据: {len(self.enhanced_data) if self.enhanced_data is not None else 0} 条记录")
    
    def _load_vector_store(self) -> bool:
        """加载向量存储"""
        try:
            if self.vector_store_path.exists():
                success = self.faiss_custom.load(str(self.vector_store_path), allow_dangerous=True)
                if success:
                    print(f"向量存储加载成功: {self.vector_store_path}")
                    return True
                else:
                    print(f"向量存储加载失败: {self.vector_store_path}")
                    return False
            else:
                print(f"向量存储不存在: {self.vector_store_path}")
                print("提示：可以使用 create_vector_store() 方法创建新的向量存储")
                return False
        except Exception as e:
            print(f"加载向量存储时出错: {e}")
            return False
    
    def create_vector_store(self, data_dir: str, split_type: str = 'simple') -> bool:
        """
        创建向量存储
        
        Args:
            data_dir: 数据目录路径
            split_type: 分割类型 ('simple' 或 'parent_child')
            
        Returns:
            bool: 是否成功创建
        """
        try:
            print(f"开始创建向量存储，数据路径: {data_dir}")
            self.faiss_custom.init_data(data_dir, split_type=split_type)
            print(f"向量存储创建成功，保存路径: {self.vector_store_path}")
            return True
        except Exception as e:
            print(f"创建向量存储失败: {e}")
            return False
    
    def add_documents_to_vector_store(self, documents: List[Document]) -> bool:
        """
        向现有向量存储添加文档
        
        Args:
            documents: 要添加的文档列表
            
        Returns:
            bool: 是否成功添加
        """
        try:
            if self.faiss_custom.vector_store is None:
                print("错误: 向量存储尚未创建或加载")
                return False
            
            success = self.faiss_custom.add_documents(documents)
            if success:
                # 保存更新后的向量存储
                self.faiss_custom.save(str(self.vector_store_path))
                print(f"成功添加 {len(documents)} 个文档到向量存储")
            return success
        except Exception as e:
            print(f"添加文档到向量存储失败: {e}")
            return False
    
    def _load_enhanced_data(self) -> Optional[pd.DataFrame]:
        """加载增强分析数据"""
        try:
            if Path(self.enhanced_data_path).exists():
                return pd.read_csv(self.enhanced_data_path)
            else:
                print(f"增强数据文件不存在: {self.enhanced_data_path}")
                return None
        except Exception as e:
            print(f"加载增强数据失败: {e}")
            return None

        
    def _format_rag_knowledge(self, docs: List[Document], rule: str = "") -> str:
        """格式化RAG知识内容"""
        if not docs:
            return "暂无相关知识库信息"
        
        formatted_knowledge = []
        
        for i, doc in enumerate(docs, 1):
            content = doc.page_content[:500]  # 限制长度
            metadata = doc.metadata
            
            knowledge_section = f"**知识条目 {i}**:\n{content}"
            
            if metadata:
                knowledge_section += f"\n*来源: {metadata.get('source', 'unknown')}*"
            
            formatted_knowledge.append(knowledge_section)
        
        return "\n\n".join(formatted_knowledge)


    def query_knowledge_base(self, query: str, k: int = 5, use_rerank: bool = True) -> List[Document]:
        """查询知识库"""
        if self.faiss_custom.vector_store is None:
            return []
        
        try:
            # 使用 FAISSCUSTOM 的相似度搜索
            docs = self.faiss_custom.similarity_search(query, k=k*2)  # 先获取更多结果
            
            # 如果启用重排且有足够的结果
            if use_rerank and len(docs) > 1 and self.faiss_custom.rerank_model:
                try:
                    id_str, index, relevance_scores, reranked_docs = self.faiss_custom.enhanced_similarity_search(
                        query, docs, k=min(k, len(docs))
                    )
                    return reranked_docs
                except Exception as rerank_error:
                    print(f"重排失败，使用原始结果: {rerank_error}")
                    return docs[:k]
            else:
                return docs[:k]
                
        except Exception as e:
            print(f"查询知识库失败: {e}")
            return []
    
    def get_code_context(self, file_name: str, line_number: int, context_lines: int = 10) -> Dict[str, Any]:
        """获取代码上下文信息"""
        context_info = {
            'function_info': None,
            'code_context': '',
            'file_info': None
        }
        
        try:
            # 构造JSON文件路径
            if '.' in file_name:
                name_part, ext_part = file_name.rsplit('.', 1)
                json_file_name = f"{name_part}_{ext_part}_analysis.json"
            else:
                json_file_name = f"{file_name}_analysis.json"
            
            json_file_path = self.code_info_json_dir / json_file_name
            
            if json_file_path.exists():
                with open(json_file_path, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                
                context_info['file_info'] = data.get('file_info', {})
                
                # 查找包含该行的函数
                for func in data.get('functions', []):
                    start_line = func.get('start_line', 0)
                    end_line = func.get('end_line', 0)
                    
                    if start_line <= line_number <= end_line:
                        context_info['function_info'] = func
                        context_info['code_context'] = func.get('body_content', '')
                        break
                
                # 如果没找到函数，尝试提供文件级别的上下文
                if not context_info['function_info']:
                    # 这里可以添加基于行号的上下文提取逻辑
                    pass
            
        except Exception as e:
            print(f"获取代码上下文失败: {e}")
        
        return context_info
    
    def get_related_issues(self, file_name: str, line_number: int, rule: str = None) -> List[Dict]:
        """获取相关问题"""
        if self.enhanced_data is None:
            return []
        
        try:
            # 筛选相同文件的问题
            file_issues = self.enhanced_data[self.enhanced_data['File'] == file_name]
            
            # 如果指定了规则，进一步筛选
            if rule:
                file_issues = file_issues[file_issues['Rule'] == rule]
            
            # 按行号距离排序，返回最相关的问题
            file_issues['line_distance'] = abs(file_issues['Line'].astype(int) - line_number)
            related_issues = file_issues.nsmallest(5, 'line_distance')
            
            return related_issues.to_dict('records')
        
        except Exception as e:
            print(f"获取相关问题失败: {e}")
            return []
    
    def analyze_single_issue(self, 
                           file_name: str,
                           line_number: int,
                           error_id: str,
                           rule_violated: str,
                           error_message: str,
                           error_type: str = "unknown",
                           severity_level: str = "medium",
                           stream: bool = False):
        """
        分析单个代码问题
        
        Args:
            file_name: 文件名
            line_number: 错误行号
            error_id: 错误ID
            rule_violated: 违反的规则
            error_message: 错误消息
            error_type: 错误类型
            severity_level: 严重级别
            stream: 是否启用流式返回
            
        Returns:
            如果stream=False，返回分析结果字符串
            如果stream=True，返回生成器，逐步产出分析结果
        """
        try:
            # 1. 获取代码上下文
            code_context = self.get_code_context(file_name, line_number)
            
            # 2. 查询RAG知识库
            query = f"{rule_violated} {error_message}"
            rag_docs = self.query_knowledge_base(query, k=3)
            
            # 3. 构建RAG知识内容
            rag_knowledge = self._format_rag_knowledge(rag_docs, rule_violated)
            
            # 4. 获取相关问题
            related_issues = self.get_related_issues(file_name, line_number, rule_violated)
            
            # 5. 构建prompt
            prompt = self.prompt_manager.format_single_issue_prompt(
                file_name=file_name,
                line_number=line_number,
                error_id=error_id,
                rule_violated=rule_violated,
                error_message=error_message,
                error_type=error_type,
                severity_level=severity_level,
                function_info=code_context.get('function_info'),
                code_context=code_context.get('code_context', ''),
                rag_knowledge=rag_knowledge
            )
            
            # 6. 调用LLM分析
            if stream:
                # 流式返回
                return self._call_llm_stream(prompt)
            else:
                # 非流式返回
                response = self._call_llm(prompt)
                return response
            
        except Exception as e:
            error_msg = f"分析过程中出现错误: {e}"
            if stream:
                # 流式模式下，返回错误生成器
                def error_generator():
                    yield error_msg
                return error_generator()
            else:
                return error_msg
    
    def analyze_file_comprehensive(self, file_name: str, stream: bool = False):
        """
        对文件进行综合分析
        
        Args:
            file_name: 文件名
            stream: 是否启用流式返回
            
        Returns:
            如果stream=False，返回综合分析结果字符串
            如果stream=True，返回生成器，逐步产出分析结果
        """
        try:
            # 1. 获取文件信息
            code_context = self.get_code_context(file_name, 1)  # 获取文件级别信息
            file_info = code_context.get('file_info', {})
            
            # 2. 获取该文件的所有问题
            if self.enhanced_data is not None:
                file_issues = self.enhanced_data[self.enhanced_data['File'] == file_name]
                detected_issues = file_issues.to_dict('records')
            else:
                detected_issues = []
            
            # 3. 查询相关知识
            query = f"code quality analysis {file_name}"
            rag_docs = self.query_knowledge_base(query, k=5)
            
            # 4. 构建综合分析prompt
            prompt = self.prompt_manager.format_comprehensive_analysis_prompt(
                file_info=file_info,
                detected_issues=detected_issues,
                function_dependencies=None  # 可以从code_context中提取
            )
            
            # 5. 调用LLM分析
            if stream:
                # 流式返回
                return self._call_llm_stream(prompt)
            else:
                # 非流式返回
                response = self._call_llm(prompt)
                return response
            
        except Exception as e:
            error_msg = f"综合分析过程中出现错误: {e}"
            if stream:
                # 流式模式下，返回错误生成器
                def error_generator():
                    yield error_msg
                return error_generator()
            else:
                return error_msg

    def _call_llm(self, prompt: str) -> str:
        """
        统一的LLM调用方法，兼容Xinference接口
        
        Args:
            prompt: 输入的prompt字符串
            
        Returns:
            LLM的响应内容
        """
        try:
            # 对于Xinference，直接传入字符串
            if hasattr(self.llm, 'invoke'):
                response = self.llm.invoke(prompt)
                # 检查响应类型
                if hasattr(response, 'content'):
                    return response.content
                else:
                    return str(response)
            else:
                # 如果没有invoke方法，尝试直接调用
                response = self.llm(prompt)
                return str(response)
                
        except Exception as e:
            print(f"LLM调用失败: {e}")
            return f"LLM调用失败: {e}"
    
    def _call_llm_stream(self, prompt: str):
        """
        流式调用LLM方法，参考chat_rag.py的实现
        
        Args:
            prompt: 输入的prompt字符串
            
        Yields:
            LLM的响应内容片段
        """
        try:
            # 转换为消息格式（与chat_rag.py保持一致）
            if isinstance(prompt, str):
                from langchain_core.messages import HumanMessage
                messages = [HumanMessage(content=prompt)]
            else:
                messages = prompt
            
            # 检查是否支持流式调用
            if hasattr(self.llm, 'stream'):
                # 使用与chat_rag.py相同的调用方式
                response = self.llm.stream(messages, generate_config={"max_tokens": 1024, "stream": True})
                
                for chunk in response:
                    if hasattr(chunk, 'content') and chunk.content:
                        yield chunk.content
                    else:
                        chunk_str = str(chunk)
                        if chunk_str.strip():
                            yield chunk_str
            else:
                # 降级为非流式调用
                response = self._call_llm(prompt)
                # 模拟流式返回
                chunk_size = 50
                for i in range(0, len(response), chunk_size):
                    yield response[i:i + chunk_size]
                    import time
                    time.sleep(0.01)
                
        except Exception as e:
            print(f"流式LLM调用失败: {e}")
            # 降级为非流式调用
            try:
                response = self._call_llm(prompt)
                yield response
            except Exception as fallback_error:
                yield f"LLM调用失败: {fallback_error}"
    
    def chat_with_context(self, 
                         question: str, 
                         file_name: str = None, 
                         line_number: int = None,
                         stream: bool = False):
        """
        基于上下文的聊天功能
        
        Args:
            question: 用户问题
            file_name: 相关文件名（可选）
            line_number: 相关行号（可选）
            stream: 是否启用流式返回
            
        Returns:
            如果stream=False，返回回答内容字符串
            如果stream=True，返回生成器，逐步产出回答内容
        """
        try:
            # 构建查询上下文
            context_parts = [question]
            
            if file_name:
                context_parts.append(f"文件: {file_name}")
                
                # 获取代码上下文
                if line_number:
                    code_context = self.get_code_context(file_name, line_number)
                    if code_context.get('function_info'):
                        func_name = code_context['function_info'].get('name', 'unknown')
                        context_parts.append(f"函数: {func_name}")
            
            # 查询知识库
            query = " ".join(context_parts)
            rag_docs = self.query_knowledge_base(query, k=3)
            rag_knowledge = self._format_rag_knowledge(rag_docs)
            
            # 构建对话prompt
            system_prompt = self.prompt_manager.get_system_prompt()
            user_prompt = f"""
                    用户问题: {question}

                    相关上下文:
                    - 文件: {file_name or '未指定'}
                    - 行号: {line_number or '未指定'}

                    相关知识:
                    {rag_knowledge}

                    请基于以上信息回答用户问题。
                """
            
            full_prompt = f"{system_prompt}\n\n{user_prompt}"
            
            # 调用LLM
            if stream:
                return self._call_llm_stream(full_prompt)
            else:
                response = self._call_llm(full_prompt)
                return response
            
        except Exception as e:
            error_msg = f"对话处理过程中出现错误: {e}"
            if stream:
                def error_generator():
                    yield error_msg
                return error_generator()
            else:
                return error_msg
    
    def batch_analyze_issues(self, 
                           output_csv_path: str = None,
                           max_issues: int = None,
                           filter_conditions: Dict[str, Any] = None) -> bool:
        """
        批量分析所有问题并保存结果到CSV
        
        Args:
            output_csv_path: 输出CSV文件路径，如果为None则自动生成
            max_issues: 最大分析问题数量，None表示分析所有问题
            filter_conditions: 过滤条件，例如 {'File': 'specific_file.c', 'Rule': 'MISRA-10.3'}
            
        Returns:
            bool: 是否成功完成批量分析
        """
        if self.enhanced_data is None or self.enhanced_data.empty:
            print("错误: 没有找到增强数据，无法进行批量分析")
            return False
        
        try:
            # 应用过滤条件
            data_to_analyze = self.enhanced_data.copy()
            if filter_conditions:
                for column, value in filter_conditions.items():
                    if column in data_to_analyze.columns:
                        data_to_analyze = data_to_analyze[data_to_analyze[column] == value]
                        print(f"应用过滤条件: {column} = {value}")
            
            # 限制分析数量
            if max_issues and len(data_to_analyze) > max_issues:
                data_to_analyze = data_to_analyze.head(max_issues)
                print(f"限制分析数量为: {max_issues}")
            
            total_issues = len(data_to_analyze)
            print(f"开始批量分析 {total_issues} 个问题...")
            
            # 准备结果列表
            results = []
            
            # 逐个分析问题
            for index, row in data_to_analyze.iterrows():
                try:
                    print(f"正在分析第 {len(results) + 1}/{total_issues} 个问题...")
                    
                    # 提取必要字段，设置默认值
                    file_name = str(row.get('File', 'unknown_file'))
                    line_number = int(row.get('Line', 0))
                    error_id = str(row.get('Error_ID', row.get('ID', f"ERR_{index}")))
                    rule_violated = str(row.get('Rule', 'unknown_rule'))
                    error_message = str(row.get('Message', row.get('Description', 'No message provided')))
                    error_type = str(row.get('Type', row.get('Category', 'unknown')))
                    severity_level = str(row.get('Severity', row.get('Level', 'medium')))
                    
                    # 调用单个问题分析
                    analysis_result = self.analyze_single_issue(
                        file_name=file_name,
                        line_number=line_number,
                        error_id=error_id,
                        rule_violated=rule_violated,
                        error_message=error_message,
                        error_type=error_type,
                        severity_level=severity_level
                    )
                    
                    # 构建结果记录
                    result_record = {
                        'Index': index,
                        'File': file_name,
                        'Line': line_number,
                        'Error_ID': error_id,
                        'Rule': rule_violated,
                        'Error_Message': error_message,
                        'Error_Type': error_type,
                        'Severity_Level': severity_level,
                        'Knowledge_Name': self.vector_store_name,
                        'Analysis_Result': analysis_result,
                        'Analysis_Length': len(analysis_result),
                        'Status': 'Success'
                    }
                    
                    results.append(result_record)
                    
                except Exception as e:
                    print(f"分析第 {index} 行问题时出错: {e}")
                    # 添加错误记录
                    error_record = {
                        'Index': index,
                        'File': str(row.get('File', 'unknown_file')),
                        'Line': row.get('Line', 0),
                        'Error_ID': str(row.get('Error_ID', row.get('ID', f"ERR_{index}"))),
                        'Rule': str(row.get('Rule', 'unknown_rule')),
                        'Error_Message': str(row.get('Message', row.get('Description', 'No message provided'))),
                        'Error_Type': str(row.get('Type', row.get('Category', 'unknown'))),
                        'Severity_Level': str(row.get('Severity', row.get('Level', 'medium'))),
                        'Knowledge_Name': self.vector_store_name,
                        'Analysis_Result': f"分析失败: {e}",
                        'Analysis_Length': 0,
                        'Status': 'Failed'
                    }
                    results.append(error_record)
            
            # todo:转换格式为报告，不为df
            # 转换为DataFrame
            results_df = pd.DataFrame(results)
            
            # 设置输出路径到QAC/report文件夹
            if output_csv_path is None:
                from datetime import datetime
                timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
                # 确保report目录存在
                report_dir = Path(__file__).parent / "report"
                report_dir.mkdir(exist_ok=True)
                output_csv_path = report_dir / f"QAC_batch_analysis_{self.vector_store_name}_{timestamp}.csv"
            else:
                # 如果用户指定了路径，确保在report目录下
                if not str(output_csv_path).startswith(str(Path(__file__).parent / "report")):
                    report_dir = Path(__file__).parent / "report"
                    report_dir.mkdir(exist_ok=True)
                    output_csv_path = report_dir / Path(output_csv_path).name
            
            # 保存到CSV
            results_df.to_csv(output_csv_path, index=False, encoding='utf-8-sig')
            
            # 统计信息
            success_count = len(results_df[results_df['Status'] == 'Success'])
            failed_count = len(results_df[results_df['Status'] == 'Failed'])
            
            print(f"\n批量分析完成!")
            print(f"- 总计分析: {total_issues} 个问题")
            print(f"- 成功分析: {success_count} 个")
            print(f"- 失败分析: {failed_count} 个")
            print(f"- 结果保存至: {output_csv_path}")
            print(f"- 知识库名称: {self.vector_store_name}")
            
            return True
            
        except Exception as e:
            print(f"批量分析过程中出现错误: {e}")
            return False
    
    def get_batch_analysis_summary(self, csv_path: str) -> Dict[str, Any]:
        """
        获取批量分析结果的统计摘要
        
        Args:
            csv_path: 批量分析结果CSV文件路径
            
        Returns:
            Dict: 统计摘要信息
        """
        try:
            results_df = pd.read_csv(csv_path)
            
            summary = {
                'total_issues': len(results_df),
                'success_count': len(results_df[results_df['Status'] == 'Success']),
                'failed_count': len(results_df[results_df['Status'] == 'Failed']),
                'success_rate': len(results_df[results_df['Status'] == 'Success']) / len(results_df) * 100,
                'file_distribution': results_df['File'].value_counts().to_dict(),
                'rule_distribution': results_df['Rule'].value_counts().to_dict(),
                'severity_distribution': results_df['Severity_Level'].value_counts().to_dict(),
                'avg_analysis_length': results_df[results_df['Status'] == 'Success']['Analysis_Length'].mean(),
                'knowledge_name': results_df['Knowledge_Name'].iloc[0] if len(results_df) > 0 else None
            }
            
            return summary
            
        except Exception as e:
            print(f"获取批量分析摘要时出错: {e}")
            return {}


# 使用示例
def example_usage():
    """使用示例"""
    # 初始化系统 (使用自定义参数)
    qac_rag = QACChatRAG(
        vector_store_name="dataflow",
        max_tokens=4096,
        temperature=0.1
    )
    
    # # 如果向量存储不存在，可以创建新的
    # qac_rag.create_vector_store("path/to/qac/data", split_type='parent_child')
    
    # 示例1: 分析单个问题 (非流式)
    print("=== 单个问题分析 (非流式) ===")
    result1 = qac_rag.analyze_single_issue(
        file_name="MC25CM_amain.c",
        line_number=18,
        error_id="2986",
        rule_violated="MISRA C 2025 Rule 2.2",
        error_message="This operation is redundant. The value of the result is always that of the right-hand operand.",
        error_type="",
        severity_level=""
    )
    print(result1)
    
    print("\n" + "="*50 + "\n")
    
    # 示例1.1: 分析单个问题 (流式)
    print("=== 单个问题分析 (流式) ===")
    print("流式输出:")
    for chunk in qac_rag.analyze_single_issue(
        file_name="MC25CM_amain.c",
        line_number=18,
        error_id="2986",
        rule_violated="MISRA C 2025 Rule 2.2",
        error_message="This operation is redundant. The value of the result is always that of the right-hand operand.",
        error_type="",
        severity_level="",
        stream=True
    ):
        print(chunk, end='', flush=True)
    print("\n")
    
    print("\n" + "="*50 + "\n")
    
    # 示例2: 批量分析所有问题
    print("=== 批量分析所有问题 ===")
    success = qac_rag.batch_analyze_issues(
        output_csv_path="qac_batch_analysis_all.csv",  # 自动保存到QAC/report/目录
        max_issues=30  # 限制最多分析10个问题用于演示
    )
    if success:
        print("批量分析成功完成！结果保存在QAC/report/目录")
    
    print("\n" + "="*50 + "\n")
    
    # # 示例3: 有条件的批量分析
    # print("=== 有条件的批量分析 ===")
    # success = qac_rag.batch_analyze_issues(
    #     output_csv_path="qac_batch_analysis_filtered.csv",  # 自动保存到QAC/report/目录
    #     filter_conditions={
    #         'File': 'MC25CM_amain.c',  # 只分析特定文件
    #         # 'Rule': 'MISRA-10.3'     # 可以添加更多过滤条件
    #     },
    #     max_issues=5
    # )
    # if success:
    #     print("有条件批量分析成功完成！")
        
    #     # 获取分析摘要（从report目录）
    #     report_path = Path(__file__).parent / "report" / "qac_batch_analysis_filtered.csv"
    #     summary = qac_rag.get_batch_analysis_summary(str(report_path))
    #     print(f"分析摘要: {summary}")
    
    # print("\n" + "="*50 + "\n")
    
    # # 示例2: 文件综合分析 (非流式)
    # print("=== 文件综合分析 (非流式) ===")
    # result2 = qac_rag.analyze_file_comprehensive("MC25CM_amain.c")
    # print(result2)
    
    # print("\n" + "="*50 + "\n")
    
    # # 示例2.1: 文件综合分析 (流式)
    # print("=== 文件综合分析 (流式) ===")
    # print("流式输出:")
    # for chunk in qac_rag.analyze_file_comprehensive("MC25CM_amain.c", stream=True):
    #     print(chunk, end='', flush=True)
    # print("\n")
    
    # print("\n" + "="*50 + "\n")
    
    # # 示例3: 基于上下文的对话 (非流式)
    # print("=== 上下文对话 (非流式) ===")
    # result3 = qac_rag.chat_with_context(
    #     question="这个函数的复杂度为什么这么高？如何优化？",
    #     file_name="MC25CM_amain.c",
    #     line_number=20
    # )
    # print(result3)
    
    # print("\n" + "="*50 + "\n")
    
    # # 示例3.1: 基于上下文的对话 (流式)
    # print("=== 上下文对话 (流式) ===")
    # print("流式输出:")
    # for chunk in qac_rag.chat_with_context(
    #     question="这个函数的复杂度为什么这么高？如何优化？",
    #     file_name="MC25CM_amain.c",
    #     line_number=20,
    #     stream=True
    # ):
    #     print(chunk, end='', flush=True)
    # print("\n")
    
    # print("\n" + "="*50 + "\n")
    
    # # 示例4: 查询知识库 (支持重排)
    # print("=== 知识库查询 ===")
    # docs = qac_rag.query_knowledge_base(
    #     query="MISRA C 规则违规处理",
    #     k=3,
    #     use_rerank=True
    # )
    # for i, doc in enumerate(docs, 1):
    #     print(f"文档 {i}: {doc.page_content[:200]}...")
    #     print(f"来源: {doc.metadata.get('source', 'unknown')}")
    #     print("-" * 30)


if __name__ == "__main__":
    example_usage()
