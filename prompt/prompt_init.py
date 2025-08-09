import json
import os

from config import SYSTEM_PROMPT_PATH, XML_PROMPT_PATH, NEO4J_PROMPT_PATH

# 系统提示词配置
SYSTEM_PROMPT = """你是一个专业的助手。
请基于以下参考信息回答用户问题。如果无法从参考信息中得到答案，请如实告知。
请用简洁专业的语气回答。

参考信息:
{}
"""

# xml提示词配置
XML_PROMPT = '''你是一个生成xml文件格式生成助手。你需要根据参考信息，生成格式正确的层级嵌套xml格式。
节点（node_type）的层级关系（层级关系为硬性规则）依次为：PROJECT->ENTERPRIS->SITE->SEGMENT->ASSET->MEASLOC。
其节点从左到右互为父-子节点，通常为“父子嵌套”，子节点嵌套父节点内的其他节点后，与父节点的其他节点互为同级节点。
嵌套时必须要考虑上述层级关系，可根据参考信息中的节点类型（node_type）和节点关系（user_tag_ident）作为嵌套关系的大致思路。
步骤一：根据节点层级关系以及参考信息中的节点类型（node_type）、节点关系（user_tag_ident），将xml值（node_xml）正确的嵌套。
步骤二：将提取好的user_name值，替换步骤一中xml文件对应的ProjectName、NodeName、name和user_tag_ident等,并返回。
正确案例如下：（
案例一：
参考信息一：[{'user_name': '你是真天真哈哈哈哈', 'user_type': 'PROJECT'}, {'user_name': '788', 'user_type': 'ENTERPRISE'}, {'user_name': 'sdd', 'user_type': 'SITE'}];
参考信息二：[{'node_labels': '弹箱1（站点）', 'node_type': 'SITE', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<SITE _byVersion="1" Expand="1" NodeCode="11" NodeType="3" NodeName="弹箱1（站点）">
<siteTYPE _byVersion="2" name="弹箱1（站点）" user_tag_ident="一院一部（组织）:弹箱1（站点）" st_type_code="4" duns_number="0" site_id="1" gmt_last_updated="2025.03.25 15:13:53" site_code="11" enterprise_id="1" segment_site="11" segment_id="1" st_db_site="" st_db_id="0" template_yn="1" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" />
<FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
<WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
<HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
</SITE>'}, {'node_labels': '一院一部（组织）', 'node_type': 'ENTERPRISE', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<ENTERPRISE _byVersion="1" Expand="1" NodeCode="1" NodeType="2" NodeName="一院一部（组织）">
<enterpriseTYPE _byVersion="3" name="一院一部（组织）" user_tag_ident="一院一部（组织）" ent_type_code="5" enterprise_id="1" gmt_last_updated="2025.03.25 15:10:42" ent_db_site="" ent_db_id="0" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" enterprise_child_count="0" />
</ENTERPRISE>'}, {'node_labels': '一院一部弹箱健康管理系统（工程-项目名称）', 'node_type': 'PROJECT', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<PROJECT ProjectByVersion="1" ProjectName="一院一部弹箱健康管理系统（工程-项目名称）" ProjectId="1" ProjectGmtLastUpdatedField="2022.03.07 14:55:33" _byVersion="1" Expand="1" NodeCode="1" NodeType="1" NodeName="一院一部弹箱健康管理系统（工程-项目名称）">
</PROJECT>'}];
正确输出：
<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<PROJECT ProjectByVersion="1" ProjectName="你是真天真哈哈哈哈" ProjectId="1" ProjectGmtLastUpdatedField="2022.03.07 14:55:33" _byVersion="1" Expand="1" NodeCode="1" NodeType="1" NodeName="你是真天真哈哈哈哈">
    <ENTERPRISE _byVersion="1" Expand="1" NodeCode="1" NodeType="2" NodeName="788">
    <enterpriseTYPE _byVersion="3" name="788" user_tag_ident="788" ent_type_code="5" enterprise_id="1" gmt_last_updated="2025.03.25 15:10:42" ent_db_site="" ent_db_id="0" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" enterprise_child_count="0" />
        <SITE _byVersion="1" Expand="1" NodeCode="11" NodeType="3" NodeName="sdd">
            <siteTYPE _byVersion="2" name="sdd" user_tag_ident="788:sdd" st_type_code="4" duns_number="0" site_id="1" gmt_last_updated="2025.03.25 15:13:53" site_code="11" enterprise_id="1" segment_site="11" segment_id="1" st_db_site="" st_db_id="0" template_yn="1" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" />
            <FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
            <WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
            <HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
        </SITE>
    </ENTERPRISE>
</PROJECT>；
案例二：
参考信息一：[{'user_name': '组织架构调整', 'user_type': 'PROJECT'}, {'user_name': '软件研发', 'user_type': 'ENTERPRISE'}, {'user_name': '算法开发小组', 'user_type': 'SITE'}];
参考信息二：[{'node_labels': '弹箱1（站点）', 'node_type': 'SITE', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<SITE _byVersion="1" Expand="1" NodeCode="11" NodeType="3" NodeName="弹箱1（站点）">
<siteTYPE _byVersion="2" name="弹箱1（站点）" user_tag_ident="一院一部（组织）:弹箱1（站点）" st_type_code="4" duns_number="0" site_id="1" gmt_last_updated="2025.03.25 15:13:53" site_code="11" enterprise_id="1" segment_site="11" segment_id="1" st_db_site="" st_db_id="0" template_yn="1" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" />
<FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
<WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
<HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
</SITE>'}, {'node_labels': '一院一部（组织）', 'node_type': 'ENTERPRISE', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<ENTERPRISE _byVersion="1" Expand="1" NodeCode="1" NodeType="2" NodeName="一院一部（组织）">
<enterpriseTYPE _byVersion="3" name="一院一部（组织）" user_tag_ident="一院一部（组织）" ent_type_code="5" enterprise_id="1" gmt_last_updated="2025.03.25 15:10:42" ent_db_site="" ent_db_id="0" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" enterprise_child_count="0" />
</ENTERPRISE>'}, {'node_labels': '一院一部弹箱健康管理系统（工程-项目名称）', 'node_type': 'PROJECT', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<PROJECT ProjectByVersion="1" ProjectName="一院一部弹箱健康管理系统（工程-项目名称）" ProjectId="1" ProjectGmtLastUpdatedField="2022.03.07 14:55:33" _byVersion="1" Expand="1" NodeCode="1" NodeType="1" NodeName="一院一部弹箱健康管理系统（工程-项目名称）">
</PROJECT>
'}];
正确输出：
<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<PROJECT ProjectByVersion="1" ProjectName="组织架构调整" ProjectId="1" ProjectGmtLastUpdatedField="2022.03.07 14:55:33" _byVersion="1" Expand="1" NodeCode="1" NodeType="1" NodeName="组织架构调整">
    <ENTERPRISE _byVersion="1" Expand="1" NodeCode="1" NodeType="2" NodeName="软件研发">
    <enterpriseTYPE _byVersion="3" name="软件研发" user_tag_ident="软件研发" ent_type_code="5" enterprise_id="1" gmt_last_updated="2025.03.25 15:10:42" ent_db_site="" ent_db_id="0" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" enterprise_child_count="0" />
        <SITE _byVersion="1" Expand="1" NodeCode="11" NodeType="3" NodeName="算法开发小组">
            <siteTYPE _byVersion="2" name="算法开发小组" user_tag_ident="软件研发:算法开发小组" st_type_code="4" duns_number="0" site_id="1" gmt_last_updated="2025.03.25 15:13:53" site_code="11" enterprise_id="1" segment_site="11" segment_id="1" st_db_site="" st_db_id="0" template_yn="1" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" />
            <FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
            <WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
            <HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
        </SITE>
    </ENTERPRISE>
</PROJECT>；
案例三：
参考信息一：[{'user_name': 'test', 'user_type': 'PROJECT'}, {'user_name': '哈哈哈哈', 'user_type': 'ENTERPRISE'}, {'user_name': '真的可以134', 'user_type': 'SITE'}, {'user_name': '你好', 'user_type': 'ASSET'},{'user_name': '子系统', 'user_type': 'SEGMENT'}, {'user_name': '微信测试点', 'user_type': 'MEASLOC'},];
参考信息二：[{'node_labels': '温度传感器_测试点', 'node_type': 'MEASLOC', 'node_xml': <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<MEASLOC _byVersion="1" Expand="1" NodeCode="35034f" NodeType="8" NodeName="温度传感器_测试点">
<meas_locationTYPE _byVersion="2" name="温度传感器_测试点" user_tag_ident="通信数据,ICD" barcode=" meas_loc_id="15" ml_type_code="15" gmt_last_updated="2025.04.16 10:35:17" meas_loc_site="350" segment_or_asset="1" segment_site="350" segment_id="52" asset_org_site=" asset_id="0" ml_eu_type_code="0" xml_data_type="二院二部（组织）:弹箱2_站点:环控子系统_子系统:温度传感器_测试点">
<meas_loc_num_data />
<meas_loc_chr_data />
<meas_loc_blob_data />
</meas_locationTYPE>
</MEASLOC>}, {'node_labels': '温湿度传感器_设备', 'node_type': 'ASSET', 'node_xml': <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<ASSET _byVersion="1" Expand="1" NodeCode="350ea60" NodeType="5" NodeName="温湿度传感器_设备">
<assetTYPE _byVersion="1" asset_org_site="350" asset_id="60000" as_type_code="0" user_tag_ident="二院二部（组织）:弹箱2_站点:温湿度传感器_设备" name="温湿度传感器_设备" long_description=" criticality="0" model_id="0" serial_number=" segment_site="350" segment_id="51" gmt_last_updated="2025.04.16 10:33:04">
<asset_num_data />
<asset_chr_data />
<asset_blob_data />
<childNode />
</assetTYPE>
<FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
<WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
<HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
</ASSET>}, {'node_labels': '环控子系统_子系统', 'node_type': 'SEGMENT', 'node_xml': <?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<SEGMENT _byVersion="1" Expand="1" NodeCode="35034" NodeType="4" NodeName="环控子系统_子系统">
<segmentTYPE _byVersion="1" name="环控子系统_子系统" user_tag_ident="二院二部（组织）:弹箱2_站点:环控子系统_子系统" long_description=" sg_type_code="0" criticality="1" segment_id="52" gmt_last_updated="2025.04.16 10:35:32" segment_site="350">
<segment_num_data />
<segment_chr_data />
<segment_blob_data /><childNode />
</segmentTYPE><FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
<WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
<HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
</SEGMENT>}, {'node_labels': '弹箱1（站点）', 'node_type': 'SITE', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<SITE _byVersion="1" Expand="1" NodeCode="11" NodeType="3" NodeName="弹箱1（站点）">
<siteTYPE _byVersion="2" name="弹箱1（站点）" user_tag_ident="一院一部（组织）:弹箱1（站点）" st_type_code="4" duns_number="0" site_id="1" gmt_last_updated="2025.03.25 15:13:53" site_code="11" enterprise_id="1" segment_site="11" segment_id="1" st_db_site="" st_db_id="0" template_yn="1" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" />
<FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
<WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
<HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
</SITE>'}, {'node_labels': '一院一部（组织）', 'node_type': 'ENTERPRISE', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<ENTERPRISE _byVersion="1" Expand="1" NodeCode="1" NodeType="2" NodeName="一院一部（组织）">
<enterpriseTYPE _byVersion="3" name="一院一部（组织）" user_tag_ident="一院一部（组织）" ent_type_code="5" enterprise_id="1" gmt_last_updated="2025.03.25 15:10:42" ent_db_site="" ent_db_id="0" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" enterprise_child_count="0" />
</ENTERPRISE>'}, {'node_labels': '一院一部弹箱健康管理系统（工程-项目名称）', 'node_type': 'PROJECT', 'node_xml': '<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<PROJECT ProjectByVersion="1" ProjectName="一院一部弹箱健康管理系统（工程-项目名称）" ProjectId="1" ProjectGmtLastUpdatedField="2022.03.07 14:55:33" _byVersion="1" Expand="1" NodeCode="1" NodeType="1" NodeName="一院一部弹箱健康管理系统（工程-项目名称）">
</PROJECT>'} ];
正确输出：
<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<PROJECT ProjectByVersion="1" ProjectName="test" ProjectId="1" ProjectGmtLastUpdatedField="2022.03.07 14:55:33" _byVersion="1" Expand="1" NodeCode="1" NodeType="1" NodeName="test">
    <ENTERPRISE _byVersion="1" Expand="1" NodeCode="1" NodeType="2" NodeName="哈哈哈哈">
        <enterpriseTYPE _byVersion="3" name="哈哈哈哈" user_tag_ident="哈哈哈哈" ent_type_code="5" enterprise_id="1" gmt_last_updated="2025.03.25 15:10:42" ent_db_site="" ent_db_id="0" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0" enterprise_child_count="0" />
        <SITE _byVersion="1" Expand="1" NodeCode="11" NodeType="3" NodeName="真的可以134">
            <siteTYPE _byVersion="2" name="真的可以134" user_tag_ident="哈哈哈哈:真的可以134" st_type_code="4" duns_number="0" site_id="1" gmt_last_updated="2025.03.25 15:13:53" site_code="11" enterprise_id="1" segment_site="11" segment_id="1" st_db_site="" st_db_id="0" template_yn="1" last_upd_db_site="" last_upd_db_id="0" rstat_type_code="0">
            </siteTYPE>
            <FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
            <WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
            <HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
            <SEGMENT _byVersion="1" Expand="1" NodeCode="115" NodeType="4" NodeName="子系统">
                <segmentTYPE _byVersion="1" name="子系统" user_tag_ident="哈哈哈哈:真的可以134:子系统" long_description="" sg_type_code="1" criticality="0" segment_id="5" gmt_last_updated="2025.03.25 15:13:06" segment_site="11">
                <segment_num_data />
                <segment_chr_data />
                <segment_blob_data />
                <childNode>
                <segment _byVersion="1" segment_site="11" segment_id="5" child_sg_site="11" child_sg_id="23" gmt_last_updated="2022.03.07 15:03:47" />
                <segment _byVersion="1" segment_site="11" segment_id="5" child_sg_site="11" child_sg_id="24" gmt_last_updated="2022.03.07 15:04:04" />
                <segment _byVersion="1" segment_site="11" segment_id="5" child_sg_site="11" child_sg_id="25" gmt_last_updated="2022.03.07 15:04:20" />
                </childNode>
                </segmentTYPE>
                <FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
                <WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
                <HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
                <ASSET _byVersion="1" Expand="1" NodeCode="115171a" NodeType="5" NodeName="你好">
                    <assetTYPE _byVersion="1" asset_org_site="11" asset_id="26" as_type_code="3" user_tag_ident="哈哈哈哈:真的可以134:子系统:你好" name="你好" long_description="" criticality="0" model_id="0" serial_number="" segment_site="11" segment_id="26" gmt_last_updated="2025.03.25 15:23:14">
                    <asset_num_data />
                    <asset_chr_data />
                    <asset_blob_data />
                    <childNode />
                    </assetTYPE>
                    <FMECA ByVersion="1" AttributeName="FMECA" AttributeType="2" />
                    <WorkManager ByVersion="1" AttributeName="工作管理" AttributeType="3" />
                    <HealthAssess ByVersion="1" AttributeName="健康评估指标" AttributeType="4" />
                    <MEASLOC _byVersion="1" Expand="1" NodeCode="115171a5" NodeType="8" NodeName="微信测试点">
                        <meas_locationTYPE _byVersion="2" name="微信测试点" user_tag_ident="通信数据,ICD" barcode="" meas_loc_id="5" ml_type_code="15" gmt_last_updated="2025.03.25 15:23:50" meas_loc_site="11" segment_or_asset="0" segment_site="11" segment_id="26" asset_org_site="11" asset_id="26" ml_eu_type_code="2" xml_data_type="哈哈哈哈:真的可以134:子系统:你好:微信测试点">
                        <meas_loc_num_data />
                        <meas_loc_chr_data />
                        <meas_loc_blob_data />
                        </meas_locationTYPE>
                    </MEASLOC>
                </ASSET>
            </SEGMENT>
        </SITE>
    </ENTERPRISE>
</PROJECT>）；
请结合以下参考信息给出我想要的输出。参考信息一：{$user_info}；参考信息二：{$neo4j_info}；
'''

# neo4j提示词配置
NEO4J_PROMPT = '''你是一个节点解析助手，你需要根据用户的自然语言描述，解析出我需要的节点的'node_name'和'node_type', 并返回json结果 。
我有以下节点映射关系：{工程:PROJECT、组织:ENTERPRISE、站点:SITE、子系统:SEGMENT、设备:ASSET、测试点-MEASLOC}。
正确的解析案例如下：(
案例一:
用户：帮我创建一个名为电控子系统的子系统。
答案：[{"user_name": "电控子系统", "user_type": "SEGMENT"}]；
案例二:
用户：帮我创建一个名为火控系统的测试点。
答案：[{"user_name": "火控系统", "user_type": "MEASLOC"}]；
案例三：
用户：帮我创建一个叫测试的工程。
答案：[{"user_name": "测试", "user_type": "PROJECT"}]；
案例四：
用户：帮我创建一个名为坦克项目测试的工程，其下有四部坦克的组织，组织下有叫坦克集群的站点，站点下有名为火控系统的子系统，子系统下有叫火控测试点的测试点。
答案：[{"user_name": "坦克项目测试", "user_type": "PROJECT"},{"user_name": "四部坦克", "user_type": "ENTERPRISE"},
{"user_name": "坦克集群", "user_type": "SITE"},{"user_name": "火控系统", "user_type": "SEGMENT"}, 
{"user_name": "火控测试点", "user_type": "MEASLOC"}]；
案例五：
用户：帮我创建一个叫一院一部弹箱健康管理系统的工程，有一院一部组织，有弹箱1站点，站点下有环控系统的子系统，子系统下有环控主控单元的设备，
设备下有环控单元1控制指令回令测试点。
答案：[{"user_name": "一院一部弹箱健康管理系统", "user_type": "PROJECT"},{"user_name": "一院一部", "user_type": "ENTERPRISE"},
{"user_name": "弹箱1", "user_type": "SITE"},{"user_name": "环控系统", "user_type": "SEGMENT"},
{"user_name": "环控主控单元", "user_type": "ASSET"},{"user_name": "环控单元1控制指令回令", "user_type": "MEASLOC"}]；);
请参考节点映射关系和正确案例，正确生成json格式的输出，只返回json语句。如果无法从参考信息中得到答案请如实告知。
'''


def show_prompt(save_path):

    # 读取 JSON 文件
    with open(save_path, "r") as f:
        loaded_data = json.load(f)

    # print(loaded_data)
    # print(type(loaded_data))  # 输出: <class 'dict'>
    # print('====================================')

    return loaded_data

def write_json(save_path, data):

    print('save_path', save_path)
    with open(save_path, "w") as f:
        json.dump(data, f, indent=4)  # indent=4 让输出的 JSON 格式更美观

    show_prompt(save_path)

if __name__ == '__main__':

    # 写入 JSON 文件

    # data1 = SYSTEM_PROMPT
    # data2 = XML_PROMPT
    # data3 = NEO4J_PROMPT
    #
    # write_json(system_prompt_path, data1)
    # write_json(xml_prompt_path, data2)
    # write_json(neo4j_prompt_path, data3)

    show_prompt(xml_prompt_path)
