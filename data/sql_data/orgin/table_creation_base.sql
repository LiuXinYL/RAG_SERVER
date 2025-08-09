TableName:'角色表';
Comment:'表示一个智能实体，如人员、算法等';
CREATE TABLE `agent` (
  `org_agent_site` varchar(16) NOT NULL,
  `agent_id` bigint(20) NOT NULL DEFAULT '0',
  `agent_db_site` varchar(16) NOT NULL,
  `agent_db_id` bigint(20) NOT NULL DEFAULT '0',
  `agent_type_code` bigint(20) NOT NULL DEFAULT '0',
  `asset_org_site` varchar(16) DEFAULT NULL,
  `asset_id` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`org_agent_site`,`agent_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'角色类型表';
Comment:'如管理者、操作人员、购买者、租佣者等';
CREATE TABLE `agent_role` (
  `org_agent_site` varchar(16) NOT NULL,
  `agent_id` bigint(20) NOT NULL DEFAULT '0',
  `ag_role_db_site` varchar(16) NOT NULL,
  `ag_role_db_id` bigint(20) NOT NULL DEFAULT '0',
  `ag_role_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`org_agent_site`,`agent_id`,`ag_role_db_site`,`ag_role_db_id`,`ag_role_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'角色关系表';
Comment:'用于定义agent与其他agent间的角色关系。如租赁关系、雇主关系、买卖关系等';
CREATE TABLE `agent_role_with_agent` (
  `org_agent_site` varchar(16) NOT NULL,
  `agent_id` bigint(20) NOT NULL DEFAULT '0',
  `ag_role_db_site` varchar(16) NOT NULL,
  `ag_role_db_id` bigint(20) NOT NULL DEFAULT '0',
  `ag_role_type_code` bigint(20) NOT NULL DEFAULT '0',
  `other_org_agent_site` varchar(16) NOT NULL,
  `other_agent_id` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`org_agent_site`,`agent_id`,`ag_role_db_site`,`ag_role_db_id`,`ag_role_type_code`,`other_org_agent_site`,`other_agent_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'智能个体类型表';
Comment:'';
CREATE TABLE `agent_type` (
  `agent_db_site` varchar(16) NOT NULL,
  `agent_db_id` bigint(20) NOT NULL DEFAULT '0',
  `agent_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`agent_db_site`,`agent_db_id`,`agent_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'设备表';
Comment:'系统表和设备表一一对应，查询某个系统下的设备信息时需要先去segemnt_child中找到对应的子系统，然后再查询设备表，输出设备信息';
CREATE TABLE `asset` (
  `asset_org_site` varchar(16) NOT NULL,
  `asset_id` bigint(20) NOT NULL DEFAULT '0',
  `as_db_site` varchar(16) NOT NULL,
  `as_db_id` bigint(20) NOT NULL DEFAULT '0',
  `as_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `long_description` varchar(4000) DEFAULT NULL,
  `criticality` bigint(20) DEFAULT '0',
  `cs_type_db_site` varchar(16) DEFAULT NULL,
  `cs_type_db_id` bigint(20) DEFAULT '0',
  `cs_type_code` bigint(20) DEFAULT '0',
  `mf_db_site` varchar(16) DEFAULT NULL,
  `mf_db_id` bigint(20) DEFAULT '0',
  `manuf_code` bigint(20) DEFAULT '0',
  `model_db_site` varchar(16) DEFAULT NULL,
  `model_db_id` bigint(20) DEFAULT '0',
  `model_id` bigint(20) DEFAULT '0',
  `serial_number` varchar(254) DEFAULT NULL,
  `asr_db_site` varchar(16) DEFAULT NULL,
  `asr_db_id` bigint(20) DEFAULT '0',
  `asr_type_code` bigint(20) DEFAULT '0',
  `segment_site` varchar(16) DEFAULT NULL,
  `segment_id` bigint(20) DEFAULT '0',
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`asset_org_site`,`asset_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'设备二进制数据表';
Comment:'';
CREATE TABLE `asset_blob_data` (
  `db_site` varchar(16) NOT NULL,
  `db_id` bigint(20) NOT NULL DEFAULT '0',
  `asset_org_site` varchar(16) NOT NULL,
  `asset_id` bigint(20) NOT NULL DEFAULT '0',
  `bd_db_site` varchar(16) NOT NULL,
  `bd_db_id` bigint(20) NOT NULL DEFAULT '0',
  `bd_type_code` bigint(20) NOT NULL DEFAULT '0',
  `ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `blct_db_site` varchar(16) NOT NULL,
  `blct_db_id` bigint(20) NOT NULL DEFAULT '0',
  `blc_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `assoc_file_name` varchar(254) DEFAULT NULL,
  `image_data` longblob,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`db_site`,`db_id`,`asset_org_site`,`asset_id`,`bd_db_site`,`bd_db_id`,`bd_type_code`,`ordering_seq`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'子设备表';
Comment:'';
CREATE TABLE `asset_child` (
  `asset_org_site` varchar(16) NOT NULL,
  `asset_id` bigint(20) NOT NULL DEFAULT '0',
  `child_as_site` varchar(16) NOT NULL,
  `child_as_id` bigint(20) NOT NULL DEFAULT '0',
  `ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`asset_org_site`,`asset_id`,`child_as_site`,`child_as_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'设备字符数据表';
Comment:'';
CREATE TABLE `asset_chr_data` (
  `asset_org_site` varchar(16) NOT NULL,
  `asset_id` bigint(20) NOT NULL DEFAULT '0',
  `ac_db_site` varchar(16) NOT NULL,
  `ac_db_id` bigint(20) NOT NULL DEFAULT '0',
  `ac_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`asset_org_site`,`asset_id`,`ac_db_site`,`ac_db_id`,`ac_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'设备数值数据表';
Comment:'';
CREATE TABLE `asset_num_data` (
  `asset_org_site` varchar(16) NOT NULL,
  `asset_id` bigint(20) NOT NULL DEFAULT '0',
  `an_db_site` varchar(16) NOT NULL,
  `an_db_id` bigint(20) NOT NULL DEFAULT '0',
  `an_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` double NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`asset_org_site`,`asset_id`,`an_db_site`,`an_db_id`,`an_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统上安装设备表';
Comment:'用于存储安装在系统上的设备';
CREATE TABLE `asset_on_segment` (
  `asset_org_site` varchar(16) NOT NULL,
  `asset_id` bigint(20) NOT NULL DEFAULT '0',
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `gmt_installed` datetime(3) NOT NULL,
  `gmt_removed` datetime(3) DEFAULT NULL,
  `installed_by_agent_site` varchar(16) DEFAULT NULL,
  `installed_by_agent_id` bigint(20) DEFAULT '0',
  `removed_by_agent_site` varchar(16) DEFAULT NULL,
  `removed_by_agent_id` bigint(20) DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`asset_org_site`,`asset_id`,`segment_site`,`segment_id`,`gmt_installed`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'设备类型表';
Comment:'';
CREATE TABLE `asset_type` (
  `as_db_site` varchar(16) NOT NULL,
  `as_db_id` bigint(20) NOT NULL DEFAULT '0',
  `as_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `default_mnemonic` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`as_db_site`,`as_db_id`,`as_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统二进制数据类型表';
Comment:'';
CREATE TABLE `blob_data_type` (
  `bd_db_site` varchar(16) NOT NULL,
  `bd_db_id` bigint(20) NOT NULL DEFAULT '0',
  `bd_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`bd_db_site`,`bd_db_id`,`bd_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'危害等级表';
Comment:'';
CREATE TABLE `criticality_scale_type` (
  `cs_type_db_site` varchar(16) NOT NULL,
  `cs_type_db_id` bigint(20) NOT NULL DEFAULT '0',
  `cs_type_code` bigint(20) NOT NULL DEFAULT '0',
  `min_value` bigint(20) NOT NULL DEFAULT '0',
  `max_value` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`cs_type_db_site`,`cs_type_db_id`,`cs_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'单位表';
Comment:'';
CREATE TABLE `eng_unit_type` (
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `ru_type_code` bigint(20) NOT NULL DEFAULT '0',
  `mult_fact_to_ref` double NOT NULL,
  `refer_off_to_ref` double NOT NULL,
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`eu_db_site`,`eu_db_id`,`eu_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'组织表';
Comment:'';
CREATE TABLE `enterprise` (
  `enterprise_id` bigint(20) NOT NULL DEFAULT '0',
  `ent_db_site` varchar(16) NOT NULL,
  `ent_db_id` bigint(20) NOT NULL DEFAULT '0',
  `ent_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`enterprise_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'组织类型表';
Comment:'';
CREATE TABLE `enterprise_type` (
  `ent_db_site` varchar(16) NOT NULL,
  `ent_db_id` bigint(20) NOT NULL DEFAULT '0',
  `ent_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`ent_db_site`,`ent_db_id`,`ent_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'健康等级表';
Comment:'';
CREATE TABLE `health_level_type` (
  `health_lev_db_site` varchar(16) NOT NULL,
  `health_lev_db_id` bigint(20) NOT NULL DEFAULT '0',
  `health_lev_type_code` bigint(20) NOT NULL DEFAULT '0',
  `health_scale` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`health_lev_db_site`,`health_lev_db_id`,`health_lev_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'测试点关联表';
Comment:'';
CREATE TABLE `meas_loc_assoc` (
  `meas_loc_site` varchar(16) NOT NULL,
  `meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `related_mloc_site` varchar(16) NOT NULL,
  `related_mloc_id` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`meas_loc_site`,`meas_loc_id`,`related_mloc_site`,`related_mloc_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'测试点类型表';
Comment:'';
CREATE TABLE `meas_loc_type` (
  `ml_db_site` varchar(16) NOT NULL,
  `ml_db_id` bigint(20) NOT NULL DEFAULT '0',
  `ml_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`ml_db_site`,`ml_db_id`,`ml_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'测试点表';
Comment:'';
CREATE TABLE `meas_location` (
  `meas_loc_site` varchar(16) NOT NULL,
  `meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `ml_db_site` varchar(16) NOT NULL,
  `ml_db_id` bigint(20) NOT NULL DEFAULT '0',
  `ml_type_code` bigint(20) NOT NULL DEFAULT '0',
  `segment_or_asset` varchar(1) NOT NULL,
  `segment_site` varchar(16) DEFAULT NULL,
  `segment_id` bigint(20) DEFAULT '0',
  `asset_org_site` varchar(16) DEFAULT NULL,
  `asset_id` bigint(20) DEFAULT '0',
  `ml_eu_db_site` varchar(16) DEFAULT NULL,
  `ml_eu_db_id` bigint(20) DEFAULT '0',
  `ml_eu_type_code` bigint(20) DEFAULT '0',
  `ds_db_site` varchar(16) DEFAULT NULL,
  `ds_db_id` bigint(20) DEFAULT '0',
  `ds_type_code` bigint(20) DEFAULT '0',
  `tr_db_site` varchar(16) DEFAULT NULL,
  `tr_db_id` bigint(20) DEFAULT '0',
  `tr_type_code` bigint(20) DEFAULT '0',
  `ta_orient_deg` bigint(20) DEFAULT '0',
  `ta_db_site` varchar(16) DEFAULT NULL,
  `ta_db_id` bigint(20) DEFAULT '0',
  `ta_type_code` bigint(20) DEFAULT '0',
  `mim_loc_seq` bigint(20) DEFAULT '0',
  `motion_direction` varchar(1) DEFAULT NULL,
  `mim_user_prefix` varchar(254) DEFAULT NULL,
  `mc_db_site` varchar(16) DEFAULT NULL,
  `mc_db_id` bigint(20) DEFAULT '0',
  `mc_type_code` bigint(20) DEFAULT '0',
  `mc_calc_size` bigint(20) DEFAULT '0',
  `update_interval` double DEFAULT NULL,
  `int_eu_db_site` varchar(16) DEFAULT NULL,
  `int_eu_db_id` bigint(20) DEFAULT '0',
  `int_eu_type_code` bigint(20) DEFAULT '0',
  `collect_duration` double DEFAULT NULL,
  `dur_eu_db_site` varchar(16) DEFAULT NULL,
  `dur_eu_db_id` bigint(20) DEFAULT '0',
  `dur_eu_type_code` bigint(20) DEFAULT '0',
  `xml_data_type` varchar(254) DEFAULT NULL,
  `xml_pattern_regex` varchar(254) DEFAULT NULL,
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `barcode` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`meas_loc_site`,`meas_loc_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'实时二进制数据表';
Comment:'包括振动、图片数据，与测试点表关联查询';
CREATE TABLE `mevent_blob_data` (
  `meas_loc_site` varchar(16) NOT NULL,
  `meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `gmt_event` datetime(3) NOT NULL,
  `mebt_db_site` varchar(16) NOT NULL,
  `mebt_db_id` bigint(20) NOT NULL DEFAULT '0',
  `meb_type_code` bigint(20) NOT NULL DEFAULT '0',
  `bd_db_site` varchar(16) NOT NULL,
  `bd_db_id` bigint(20) NOT NULL DEFAULT '0',
  `bd_type_code` bigint(20) NOT NULL DEFAULT '0',
  `name` varchar(254) DEFAULT NULL,
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `assoc_file_name` varchar(254) DEFAULT NULL,
  `image_data` longblob,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`meas_loc_site`,`meas_loc_id`,`gmt_event`,`mebt_db_site`,`mebt_db_id`,`meb_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'实时字符数据表';
Comment:'与测试点类型表关联查询，若为状态类型，查询此表，与测试点表关联查询';
CREATE TABLE `mevent_chr_data` (
  `meas_loc_site` varchar(16) NOT NULL,
  `meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `gmt_event` datetime(3) NOT NULL,
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`meas_loc_site`,`meas_loc_id`,`gmt_event`,`eu_db_site`,`eu_db_id`,`eu_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'数值类数据告警表';
Comment:'';
CREATE TABLE `mevent_num_alarm` (
  `meas_loc_site` varchar(16) NOT NULL,
  `meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `gmt_event` datetime(3) NOT NULL,
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `al_db_site` varchar(16) NOT NULL,
  `al_db_id` bigint(20) NOT NULL DEFAULT '0',
  `al_type_code` bigint(20) NOT NULL DEFAULT '0',
  `gmt_acknowledged` datetime(3) DEFAULT NULL,
  `ack_loc_hr_delta` int(11) DEFAULT '0',
  `ack_loc_min_delta` int(11) DEFAULT '0',
  `org_agent_site` varchar(16) DEFAULT NULL,
  `agent_id` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`meas_loc_site`,`meas_loc_id`,`gmt_event`,`eu_db_site`,`eu_db_id`,`eu_type_code`,`al_db_site`,`al_db_id`,`al_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'实时数值数据表';
Comment:'与测试点类型表关联查询，若为非状态类型，查询此表，与测试点表关联查询';
CREATE TABLE `mevent_num_data` (
  `meas_loc_site` varchar(16) NOT NULL,
  `meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `gmt_event` datetime(3) NOT NULL,
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` double NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`meas_loc_site`,`meas_loc_id`,`gmt_event`,`eu_db_site`,`eu_db_id`,`eu_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'告警事件与关联的告警配置信息表';
Comment:'';
CREATE TABLE `num_al_assoc_reg` (
  `meas_loc_site` varchar(16) NOT NULL,
  `meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `gmt_event` datetime(3) NOT NULL,
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `al_db_site` varchar(16) NOT NULL,
  `al_db_id` bigint(20) NOT NULL DEFAULT '0',
  `al_type_code` bigint(20) NOT NULL DEFAULT '0',
  `alarm_db_site` varchar(16) NOT NULL,
  `alarm_db_id` bigint(20) NOT NULL DEFAULT '0',
  `al_meas_loc_site` varchar(16) NOT NULL,
  `al_meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `al_ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`meas_loc_site`,`meas_loc_id`,`gmt_event`,`eu_db_site`,`eu_db_id`,`eu_type_code`,`al_db_site`,`al_db_id`,`al_type_code`,`alarm_db_site`,`alarm_db_id`,`al_meas_loc_site`,`al_meas_loc_id`,`al_ordering_seq`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'实数型数据告警配置表';
Comment:'实数型数据的告警配置信息。包括上下限、单位、告警类型等信息';
CREATE TABLE `num_alarm_reg` (
  `alarm_db_site` varchar(16) NOT NULL,
  `alarm_db_id` bigint(20) NOT NULL DEFAULT '0',
  `meas_loc_site` varchar(16) NOT NULL,
  `meas_loc_id` bigint(20) NOT NULL DEFAULT '0',
  `ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `ml_db_site` varchar(16) DEFAULT NULL,
  `ml_db_id` bigint(20) DEFAULT '0',
  `ml_type_code` bigint(20) DEFAULT '0',
  `mc_db_site` varchar(16) DEFAULT NULL,
  `mc_db_id` bigint(20) DEFAULT '0',
  `mc_type_code` bigint(20) DEFAULT '0',
  `al_db_site` varchar(16) NOT NULL,
  `al_db_id` bigint(20) NOT NULL DEFAULT '0',
  `al_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `gmt_alarm_start` datetime(3) NOT NULL,
  `st_loc_hr_delta` int(11) DEFAULT '0',
  `st_loc_min_delta` int(11) DEFAULT '0',
  `min_amplitude` double DEFAULT NULL,
  `max_amplitude` double DEFAULT NULL,
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`alarm_db_site`,`alarm_db_id`,`meas_loc_site`,`meas_loc_id`,`ordering_seq`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'优先级表';
Comment:'';
CREATE TABLE `priority_level_type` (
  `priority_lev_db_site` varchar(16) NOT NULL,
  `priority_lev_db_id` bigint(20) NOT NULL DEFAULT '0',
  `priority_lev_type_code` bigint(20) NOT NULL DEFAULT '0',
  `priority_scale` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`priority_lev_db_site`,`priority_lev_db_id`,`priority_lev_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'行数据类型表';
Comment:'';
CREATE TABLE `row_status_type` (
  `rstat_type_cod` int(11) NOT NULL DEFAULT '0',
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`rstat_type_cod`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统表';
Comment:'记录所有系统信息和设备信息';
CREATE TABLE `segment` (
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `sg_db_site` varchar(16) NOT NULL,
  `sg_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sg_type_code` bigint(20) NOT NULL DEFAULT '0',
  `segment_group_yn` varchar(1) NOT NULL,
  `criticality` bigint(20) DEFAULT '0',
  `cs_type_db_site` varchar(16) DEFAULT NULL,
  `cs_type_db_id` bigint(20) DEFAULT '0',
  `cs_type_code` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `long_description` varchar(4000) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`segment_site`,`segment_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统二进制数据表';
Comment:'';
CREATE TABLE `segment_blob_data` (
  `db_site` varchar(16) NOT NULL,
  `db_id` bigint(20) NOT NULL DEFAULT '0',
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `bd_db_site` varchar(16) NOT NULL,
  `bd_db_id` bigint(20) NOT NULL DEFAULT '0',
  `bd_type_code` bigint(20) NOT NULL DEFAULT '0',
  `ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `blct_db_site` varchar(16) NOT NULL,
  `blct_db_id` bigint(20) NOT NULL DEFAULT '0',
  `blc_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `assoc_file_name` varchar(254) DEFAULT NULL,
  `image_data` longblob,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`db_site`,`db_id`,`segment_site`,`segment_id`,`bd_db_site`,`bd_db_id`,`bd_type_code`,`ordering_seq`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统和子系统关系表';
Comment:'记录系统表中的父子关系，子系统信息去系统表中查询';
CREATE TABLE `segment_child` (
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `child_sg_site` varchar(16) NOT NULL,
  `child_sg_id` bigint(20) NOT NULL DEFAULT '0',
  `ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`segment_site`,`segment_id`,`child_sg_site`,`child_sg_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统字符数据表';
Comment:'';
CREATE TABLE `segment_chr_data` (
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `sc_db_site` varchar(16) NOT NULL,
  `sc_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sc_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`segment_site`,`segment_id`,`sc_db_site`,`sc_db_id`,`sc_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'事件表';
Comment:'';
CREATE TABLE `segment_event` (
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `ev_db_site` varchar(16) NOT NULL,
  `ev_db_id` bigint(20) NOT NULL DEFAULT '0',
  `event_type_code` bigint(20) NOT NULL DEFAULT '0',
  `gmt_event_start` datetime(3) NOT NULL,
  `gmt_event_stop` datetime(3) DEFAULT NULL,
  `ev_loc_hr_delta` int(11) DEFAULT '0',
  `ev_loc_min_delta` int(11) DEFAULT '0',
  `gmt_stored` datetime(3) DEFAULT NULL,
  `st_loc_hr_delta` int(11) DEFAULT '0',
  `st_loc_min_delta` int(11) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`segment_site`,`segment_id`,`ev_db_site`,`ev_db_id`,`event_type_code`,`gmt_event_start`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'故障模式功能表';
Comment:'';
CREATE TABLE `segment_function` (
  `db_site` varchar(16) NOT NULL,
  `db_id` bigint(20) NOT NULL DEFAULT '0',
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_created` datetime(3) DEFAULT NULL,
  `cr_loc_hr_delta` int(11) DEFAULT '0',
  `cr_loc_min_delta` int(11) DEFAULT '0',
  `by_org_asite` varchar(16) DEFAULT NULL,
  `by_agent_id` bigint(20) DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`db_site`,`db_id`,`segment_site`,`segment_id`,`ordering_seq`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'健康评估表';
Comment:'';
CREATE TABLE `segment_health` (
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `gmt_assessment` datetime(3) NOT NULL,
  `by_agent_site` varchar(16) NOT NULL,
  `by_agent_id` bigint(20) NOT NULL DEFAULT '0',
  `loc_hr_delta` int(11) DEFAULT '0',
  `loc_min_delta` int(11) DEFAULT '0',
  `health_lev_db_site` varchar(16) NOT NULL,
  `health_lev_db_id` bigint(20) NOT NULL DEFAULT '0',
  `health_lev_type_code` bigint(20) NOT NULL DEFAULT '0',
  `health_scale_precise` double DEFAULT NULL,
  `likelihood_prob` double DEFAULT NULL,
  `gmt_created` datetime(3) DEFAULT NULL,
  `cr_loc_hr_delta` int(11) DEFAULT '0',
  `cr_loc_min_delta` int(11) DEFAULT '0',
  `ch_patt_db_site` varchar(16) DEFAULT NULL,
  `ch_patt_db_id` bigint(20) DEFAULT '0',
  `ch_patt_type_code` bigint(20) DEFAULT '0',
  `gmt_audited` datetime(3) DEFAULT NULL,
  `aud_loc_hr_delta` int(11) DEFAULT '0',
  `aud_loc_min_delta` int(11) DEFAULT '0',
  `aud_quality_code` int(11) DEFAULT '0',
  `aud_by_org_asite` varchar(16) DEFAULT NULL,
  `aud_by_agent_id` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`segment_site`,`segment_id`,`gmt_assessment`,`by_agent_site`,`by_agent_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统数据表';
Comment:'';
CREATE TABLE `segment_num_data` (
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `sn_db_site` varchar(16) NOT NULL,
  `sn_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sn_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` double NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`segment_site`,`segment_id`,`sn_db_site`,`sn_db_id`,`sn_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统类型表';
Comment:'';
CREATE TABLE `segment_type` (
  `sg_db_site` varchar(16) NOT NULL,
  `sg_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sg_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `default_mnemonic` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sg_db_site`,`sg_db_id`,`sg_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'事件类型表';
Comment:'';
CREATE TABLE `sg_as_event_type` (
  `ev_db_site` varchar(16) NOT NULL,
  `ev_db_id` bigint(20) NOT NULL DEFAULT '0',
  `event_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`ev_db_site`,`ev_db_id`,`event_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统字符数据类型表';
Comment:'';
CREATE TABLE `sg_chr_dat_type` (
  `sc_db_site` varchar(16) NOT NULL,
  `sc_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sc_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `default_ru_type` bigint(20) DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sc_db_site`,`sc_db_id`,`sc_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'实时维修维护数据表';
Comment:'';
CREATE TABLE `sg_completed_work` (
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `task_db_site` varchar(16) NOT NULL,
  `task_db_id` bigint(20) NOT NULL DEFAULT '0',
  `task_type_code` bigint(20) NOT NULL DEFAULT '0',
  `gmt_completed` datetime(3) NOT NULL,
  `cp_loc_hr_delta` int(11) DEFAULT '0',
  `cp_loc_min_delta` int(11) DEFAULT '0',
  `gmt_started` datetime(3) DEFAULT NULL,
  `st_loc_hr_delta` int(11) DEFAULT '0',
  `st_loc_min_delta` int(11) DEFAULT '0',
  `by_agent_site` varchar(16) DEFAULT NULL,
  `by_agent_id` bigint(20) DEFAULT '0',
  `from_sy_agent_site` varchar(16) DEFAULT NULL,
  `from_sy_agent_id` bigint(20) DEFAULT '0',
  `priority_lev_db_site` varchar(16) DEFAULT NULL,
  `priority_lev_db_id` bigint(20) DEFAULT '0',
  `priority_lev_type_code` bigint(20) DEFAULT '0',
  `work_order_db_site` varchar(16) DEFAULT NULL,
  `work_order_db_id` bigint(20) DEFAULT '0',
  `work_order_id` bigint(20) DEFAULT '0',
  `work_req_db_site` varchar(16) DEFAULT NULL,
  `work_req_db_id` bigint(20) DEFAULT '0',
  `work_req_id` bigint(20) DEFAULT '0',
  `work_step_db_site` varchar(16) DEFAULT NULL,
  `work_step_db_id` bigint(20) DEFAULT '0',
  `work_step_id` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `long_description` varchar(4000) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  `work_ord_step_seq` int(11) DEFAULT '0',
  PRIMARY KEY (`segment_site`,`segment_id`,`task_db_site`,`task_db_id`,`task_type_code`,`gmt_completed`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'模糊组与故障模式关联表';
Comment:'';
CREATE TABLE `sg_hyp_ev_log_conn` (
  `sg_hyp_amb_set_db_site` varchar(16) NOT NULL,
  `sg_hyp_amb_set_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sg_hyp_amb_set_id` bigint(20) NOT NULL DEFAULT '0',
  `log_conn_id` bigint(20) NOT NULL DEFAULT '0',
  `lc_db_site` varchar(16) NOT NULL,
  `lc_db_id` bigint(20) NOT NULL DEFAULT '0',
  `lc_type_code` bigint(20) NOT NULL DEFAULT '0',
  `sg_hyp_db_site` varchar(16) DEFAULT NULL,
  `sg_hyp_db_id` bigint(20) DEFAULT '0',
  `sg_hyp_event_id` bigint(20) DEFAULT '0',
  `par_log_conn_id` bigint(20) DEFAULT '0',
  `likelihood_prob` double DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sg_hyp_amb_set_db_site`,`sg_hyp_amb_set_db_id`,`sg_hyp_amb_set_id`,`log_conn_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'故障率表';
Comment:'';
CREATE TABLE `sg_hyp_ev_num_data` (
  `sg_hyp_db_site` varchar(16) NOT NULL,
  `sg_hyp_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sg_hyp_event_id` bigint(20) NOT NULL DEFAULT '0',
  `en_db_site` varchar(16) NOT NULL,
  `en_db_id` bigint(20) NOT NULL DEFAULT '0',
  `en_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` double NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sg_hyp_db_site`,`sg_hyp_db_id`,`sg_hyp_event_id`,`en_db_site`,`en_db_id`,`en_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'故障模式与功能关联表';
Comment:'';
CREATE TABLE `sg_hyp_ev_sg_func` (
  `sg_hyp_db_site` varchar(16) NOT NULL,
  `sg_hyp_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sg_hyp_event_id` bigint(20) NOT NULL DEFAULT '0',
  `db_site` varchar(16) NOT NULL,
  `db_id` bigint(20) NOT NULL DEFAULT '0',
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `by_org_asite` varchar(16) DEFAULT NULL,
  `by_agent_id` bigint(20) DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sg_hyp_db_site`,`sg_hyp_db_id`,`sg_hyp_event_id`,`db_site`,`db_id`,`segment_site`,`segment_id`,`ordering_seq`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'故障模式表';
Comment:'存储某个系统或设备所有的故障模式';
CREATE TABLE `sg_hyp_event` (
  `sg_hyp_db_site` varchar(16) NOT NULL,
  `sg_hyp_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sg_hyp_event_id` bigint(20) NOT NULL DEFAULT '0',
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `ev_db_site` varchar(16) NOT NULL,
  `ev_db_id` bigint(20) NOT NULL DEFAULT '0',
  `event_type_code` bigint(20) NOT NULL DEFAULT '0',
  `severity_lev_db_site` varchar(16) NOT NULL,
  `severity_lev_db_id` bigint(20) NOT NULL DEFAULT '0',
  `severity_lev_type_code` bigint(20) NOT NULL DEFAULT '0',
  `gmt_created` datetime(3) DEFAULT NULL,
  `cr_loc_hr_delta` int(11) DEFAULT '0',
  `cr_loc_min_delta` int(11) DEFAULT '0',
  `by_org_asite` varchar(16) DEFAULT NULL,
  `by_agent_id` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `assoc_file_name` varchar(254) DEFAULT NULL,
  `associated_blob` longblob,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sg_hyp_db_site`,`sg_hyp_db_id`,`sg_hyp_event_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'系统数值数据类型表';
Comment:'';
CREATE TABLE `sg_num_dat_type` (
  `sn_db_site` varchar(16) NOT NULL,
  `sn_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sn_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `default_ru_type` bigint(20) DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sn_db_site`,`sn_db_id`,`sn_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'故障表';
Comment:'查询故障系统或设备步骤，关联sg_hyp_ev_amb_set表查找对应的sg_hyp_amb_set_id，关联sg_hyp_ev_log_conn表查找对应的sg_hyp_event_id，关联sg_hyp_event查找对应的segment_site，segment_id，关联segment表查找故障系统或设备';
CREATE TABLE `sg_pr_ev_amb_set_sg_ev` (
  `sg_prop_amb_set_db_site` varchar(16) NOT NULL,
  `sg_prop_amb_set_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sg_prop_amb_set_id` bigint(20) NOT NULL DEFAULT '0',
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `ev_db_site` varchar(16) NOT NULL,
  `ev_db_id` bigint(20) NOT NULL DEFAULT '0',
  `event_type_code` bigint(20) NOT NULL DEFAULT '0',
  `gmt_event_start` datetime(3) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sg_prop_amb_set_db_site`,`sg_prop_amb_set_db_id`,`sg_prop_amb_set_id`,`segment_site`,`segment_id`,`ev_db_site`,`ev_db_id`,`event_type_code`,`gmt_event_start`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维修建议表';
Comment:'';
CREATE TABLE `sg_recommendation` (
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `gmt_recommendation` datetime(3) NOT NULL,
  `by_agent_site` varchar(16) NOT NULL,
  `by_agent_id` bigint(20) NOT NULL DEFAULT '0',
  `loc_hr_delta` int(11) DEFAULT '0',
  `loc_min_delta` int(11) DEFAULT '0',
  `priority_lev_db_site` varchar(16) DEFAULT NULL,
  `priority_lev_db_id` bigint(20) DEFAULT '0',
  `priority_lev_type_code` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`segment_site`,`segment_id`,`gmt_recommendation`,`by_agent_site`,`by_agent_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'工作管理表';
Comment:'系统或设备的维修项或维护项,查找系统或设备的维护信息，有关联segment,查找segment_site和segment_id，关联work_manage_type，查找name为维护保养的wm_type_code,查找sg_req_for_work中对应wm_type_code的所有wm_type_code,关联work_request表，查找name';
CREATE TABLE `sg_req_for_work` (
  `req_db_site` varchar(16) NOT NULL,
  `req_db_id` bigint(20) NOT NULL DEFAULT '0',
  `request_id` bigint(20) NOT NULL DEFAULT '0',
  `segment_site` varchar(16) NOT NULL,
  `segment_id` bigint(20) NOT NULL DEFAULT '0',
  `wm_type_db_site` varchar(16) NOT NULL,
  `wm_type_db_id` bigint(20) NOT NULL DEFAULT '0',
  `wm_type_code` bigint(20) NOT NULL DEFAULT '0',
  `task_db_site` varchar(16) NOT NULL,
  `task_db_id` bigint(20) NOT NULL DEFAULT '0',
  `task_type_code` bigint(20) NOT NULL DEFAULT '0',
  `auto_approve` varchar(1) DEFAULT NULL,
  `start_before_gmt` datetime(3) DEFAULT NULL,
  `end_before_gmt` datetime(3) DEFAULT NULL,
  `start_after_gmt` datetime(3) DEFAULT NULL,
  `end_after_gmt` datetime(3) DEFAULT NULL,
  `repeat_interval` bigint(20) DEFAULT '0',
  `int_eu_db_site` varchar(16) DEFAULT NULL,
  `int_eu_db_id` bigint(20) DEFAULT '0',
  `int_eu_type_code` bigint(20) DEFAULT '0',
  `to_agent_site` varchar(16) DEFAULT NULL,
  `to_agent_id` bigint(20) DEFAULT '0',
  `sol_pack_db_site` varchar(16) DEFAULT NULL,
  `sol_pack_db_id` bigint(20) DEFAULT '0',
  `sol_pack_id` bigint(20) DEFAULT '0',
  `rec_segment_site` varchar(16) DEFAULT NULL,
  `rec_segment_id` bigint(20) DEFAULT '0',
  `rec_gmt_recomm` datetime(3) DEFAULT NULL,
  `rec_by_agent_site` varchar(16) DEFAULT NULL,
  `rec_by_agent_id` bigint(20) DEFAULT '0',
  `work_req_db_site` varchar(16) DEFAULT NULL,
  `work_req_db_id` bigint(20) DEFAULT '0',
  `work_req_id` bigint(20) DEFAULT '0',
  `work_order_db_site` varchar(16) DEFAULT NULL,
  `work_order_db_id` bigint(20) DEFAULT '0',
  `work_order_id` bigint(20) DEFAULT '0',
  `name` varchar(254) DEFAULT NULL,
  `long_description` varchar(4000) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`req_db_site`,`req_db_id`,`request_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'站点表';
Comment:'表示办公楼、飞机、生产基地、车辆、武器装备、坦克、飞艇';
CREATE TABLE `site` (
  `site_code` varchar(16) NOT NULL,
  `enterprise_id` bigint(20) NOT NULL DEFAULT '0',
  `site_id` bigint(20) NOT NULL DEFAULT '0',
  `st_db_site` varchar(16) NOT NULL,
  `st_db_id` bigint(20) NOT NULL DEFAULT '0',
  `st_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `duns_number` bigint(20) DEFAULT '0',
  `template_yn` varchar(1) DEFAULT NULL,
  `segment_site` varchar(16) DEFAULT NULL,
  `segment_id` bigint(20) DEFAULT '0',
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`site_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'站点类型表';
Comment:'';
CREATE TABLE `site_type` (
  `st_db_site` varchar(16) NOT NULL,
  `st_db_id` bigint(20) NOT NULL DEFAULT '0',
  `st_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `mobile_yn` varchar(1) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`st_db_site`,`st_db_id`,`st_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维护项';
Comment:'';
CREATE TABLE `solution_package` (
  `sol_pack_db_site` varchar(16) NOT NULL,
  `sol_pack_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_db_site` varchar(16) NOT NULL,
  `sol_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_type_code` bigint(20) NOT NULL DEFAULT '0',
  `gmt_created` datetime(3) DEFAULT NULL,
  `loc_hr_delta` int(11) DEFAULT '0',
  `loc_min_delta` int(11) DEFAULT '0',
  `priority_lev_db_site` varchar(16) DEFAULT NULL,
  `priority_lev_db_id` bigint(20) DEFAULT '0',
  `priority_lev_type_code` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sol_pack_db_site`,`sol_pack_db_id`,`sol_pack_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维护项二进制数据表';
Comment:'';
CREATE TABLE `solution_package_blob_data` (
  `sol_pack_db_site` varchar(16) NOT NULL,
  `sol_pack_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_id` bigint(20) NOT NULL DEFAULT '0',
  `bd_db_site` varchar(16) NOT NULL,
  `bd_db_id` bigint(20) NOT NULL DEFAULT '0',
  `bd_type_code` bigint(20) NOT NULL DEFAULT '0',
  `bd_ordering_seq` bigint(20) NOT NULL DEFAULT '0',
  `blct_db_site` varchar(16) NOT NULL,
  `blct_db_id` bigint(20) NOT NULL DEFAULT '0',
  `blc_type_code` bigint(20) NOT NULL DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `assoc_file_name` varchar(254) DEFAULT NULL,
  `image_data` longblob,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sol_pack_db_site`,`sol_pack_db_id`,`sol_pack_id`,`bd_db_site`,`bd_db_id`,`bd_type_code`,`bd_ordering_seq`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维护项字符数据表';
Comment:'';
CREATE TABLE `solution_package_chr_data` (
  `sol_pack_db_site` varchar(16) NOT NULL,
  `sol_pack_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_id` bigint(20) NOT NULL DEFAULT '0',
  `wc_db_site` varchar(16) NOT NULL,
  `wc_db_id` bigint(20) NOT NULL DEFAULT '0',
  `wc_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sol_pack_db_site`,`sol_pack_db_id`,`sol_pack_id`,`wc_db_site`,`wc_db_id`,`wc_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维护项数值数据表';
Comment:'';
CREATE TABLE `solution_package_num_data` (
  `sol_pack_db_site` varchar(16) NOT NULL,
  `sol_pack_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_id` bigint(20) NOT NULL DEFAULT '0',
  `wn_db_site` varchar(16) NOT NULL,
  `wn_db_id` bigint(20) NOT NULL DEFAULT '0',
  `wn_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` double NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sol_pack_db_site`,`sol_pack_db_id`,`sol_pack_id`,`wn_db_site`,`wn_db_id`,`wn_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维护步骤';
Comment:'';
CREATE TABLE `solution_package_step` (
  `sol_pack_step_db_site` varchar(16) NOT NULL,
  `sol_pack_step_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_step_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_db_site` varchar(16) NOT NULL,
  `sol_pack_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_id` bigint(20) NOT NULL DEFAULT '0',
  `seq_num` bigint(20) DEFAULT '0',
  `gmt_created` datetime(3) DEFAULT NULL,
  `loc_hr_delta` int(11) DEFAULT '0',
  `loc_min_delta` int(11) DEFAULT '0',
  `priority_lev_db_site` varchar(16) DEFAULT NULL,
  `priority_lev_db_id` bigint(20) DEFAULT '0',
  `priority_lev_type_code` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `long_description` varchar(4000) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sol_pack_step_db_site`,`sol_pack_step_db_id`,`sol_pack_step_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维护步骤字符数据表';
Comment:'';
CREATE TABLE `solution_package_step_chr_data` (
  `sol_pack_step_db_site` varchar(16) NOT NULL,
  `sol_pack_step_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_step_id` bigint(20) NOT NULL DEFAULT '0',
  `wc_db_site` varchar(16) NOT NULL,
  `wc_db_id` bigint(20) NOT NULL DEFAULT '0',
  `wc_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sol_pack_step_db_site`,`sol_pack_step_db_id`,`sol_pack_step_id`,`wc_db_site`,`wc_db_id`,`wc_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维护步骤数值数据表';
Comment:'';
CREATE TABLE `solution_package_step_num_data` (
  `sol_pack_step_db_site` varchar(16) NOT NULL,
  `sol_pack_step_db_id` bigint(20) NOT NULL DEFAULT '0',
  `sol_pack_step_id` bigint(20) NOT NULL DEFAULT '0',
  `wn_db_site` varchar(16) NOT NULL,
  `wn_db_id` bigint(20) NOT NULL DEFAULT '0',
  `wn_type_code` bigint(20) NOT NULL DEFAULT '0',
  `eu_db_site` varchar(16) NOT NULL,
  `eu_db_id` bigint(20) NOT NULL DEFAULT '0',
  `eu_type_code` bigint(20) NOT NULL DEFAULT '0',
  `data_value` double NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`sol_pack_step_db_site`,`sol_pack_step_db_id`,`sol_pack_step_id`,`wn_db_site`,`wn_db_id`,`wn_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'工作管理类型表';
Comment:'';
CREATE TABLE `work_manage_type` (
  `wm_type_db_site` varchar(16) NOT NULL,
  `wm_type_db_id` bigint(20) NOT NULL DEFAULT '0',
  `wm_type_code` bigint(20) NOT NULL DEFAULT '0',
  `work_item_db_site` varchar(16) DEFAULT NULL,
  `work_item_db_id` bigint(20) DEFAULT '0',
  `work_item_type_code` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`wm_type_db_site`,`wm_type_db_id`,`wm_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'';
Comment:'';
CREATE TABLE `work_order` (
  `work_order_db_site` varchar(16) NOT NULL,
  `work_order_db_id` bigint(20) NOT NULL DEFAULT '0',
  `work_order_id` bigint(20) NOT NULL DEFAULT '0',
  `wm_type_db_site` varchar(16) NOT NULL,
  `wm_type_db_id` bigint(20) NOT NULL DEFAULT '0',
  `wm_type_code` bigint(20) NOT NULL DEFAULT '0',
  `task_db_site` varchar(16) DEFAULT NULL,
  `task_db_id` bigint(20) DEFAULT '0',
  `task_type_code` bigint(20) DEFAULT '0',
  `gmt_created` datetime(3) DEFAULT NULL,
  `loc_hr_delta` int(11) DEFAULT '0',
  `loc_min_delta` int(11) DEFAULT '0',
  `by_agent_site` varchar(16) DEFAULT NULL,
  `by_agent_id` bigint(20) DEFAULT '0',
  `start_before_gmt` datetime(3) DEFAULT NULL,
  `end_before_gmt` datetime(3) DEFAULT NULL,
  `start_after_gmt` datetime(3) DEFAULT NULL,
  `end_after_gmt` datetime(3) DEFAULT NULL,
  `repeat_interval` bigint(20) DEFAULT '0',
  `int_eu_db_site` varchar(16) DEFAULT NULL,
  `int_eu_db_id` bigint(20) DEFAULT '0',
  `int_eu_type_code` bigint(20) DEFAULT '0',
  `from_sy_agent_site` varchar(16) DEFAULT NULL,
  `from_sy_agent_id` bigint(20) DEFAULT '0',
  `to_agent_site` varchar(16) DEFAULT NULL,
  `to_agent_id` bigint(20) DEFAULT '0',
  `priority_lev_db_site` varchar(16) DEFAULT NULL,
  `priority_lev_db_id` bigint(20) DEFAULT '0',
  `priority_lev_type_code` bigint(20) DEFAULT '0',
  `eng_study_entry_db_site` varchar(16) DEFAULT NULL,
  `eng_study_entry_db_id` bigint(20) DEFAULT '0',
  `eng_study_entry_id` bigint(20) DEFAULT '0',
  `sol_pack_db_site` varchar(16) DEFAULT NULL,
  `sol_pack_db_id` bigint(20) DEFAULT '0',
  `sol_pack_id` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `long_description` varchar(4000) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`work_order_db_site`,`work_order_db_id`,`work_order_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'维护保养信息表';
Comment:'';
CREATE TABLE `work_request` (
  `work_req_db_site` varchar(16) NOT NULL,
  `work_req_db_id` bigint(20) NOT NULL DEFAULT '0',
  `work_req_id` bigint(20) NOT NULL DEFAULT '0',
  `work_order_id` bigint(20) DEFAULT '0',
  `work_order_db_id` bigint(20) DEFAULT '0',
  `work_order_db_site` varchar(16) DEFAULT NULL,
  `wm_type_db_site` varchar(16) NOT NULL,
  `wm_type_db_id` bigint(20) NOT NULL DEFAULT '0',
  `wm_type_code` bigint(20) NOT NULL DEFAULT '0',
  `task_db_site` varchar(16) DEFAULT NULL,
  `task_db_id` bigint(20) DEFAULT '0',
  `task_type_code` bigint(20) DEFAULT '0',
  `gmt_created` datetime(3) DEFAULT NULL,
  `loc_hr_delta` int(11) DEFAULT '0',
  `loc_min_delta` int(11) DEFAULT '0',
  `by_agent_site` varchar(16) DEFAULT NULL,
  `by_agent_id` bigint(20) DEFAULT '0',
  `start_before_gmt` datetime(3) DEFAULT NULL,
  `end_before_gmt` datetime(3) DEFAULT NULL,
  `start_after_gmt` datetime(3) DEFAULT NULL,
  `end_after_gmt` datetime(3) DEFAULT NULL,
  `repeat_interval` bigint(20) DEFAULT '0',
  `int_eu_db_site` varchar(16) DEFAULT NULL,
  `int_eu_db_id` bigint(20) DEFAULT '0',
  `int_eu_type_code` bigint(20) DEFAULT '0',
  `from_sy_agent_site` varchar(16) DEFAULT NULL,
  `from_sy_agent_id` bigint(20) DEFAULT '0',
  `to_agent_site` varchar(16) DEFAULT NULL,
  `to_agent_id` bigint(20) DEFAULT '0',
  `priority_lev_db_site` varchar(16) DEFAULT NULL,
  `priority_lev_db_id` bigint(20) DEFAULT '0',
  `priority_lev_type_code` bigint(20) DEFAULT '0',
  `eng_study_entry_db_site` varchar(16) DEFAULT NULL,
  `eng_study_entry_db_id` bigint(20) DEFAULT '0',
  `eng_study_entry_id` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) DEFAULT NULL,
  `long_description` varchar(4000) DEFAULT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`work_req_db_site`,`work_req_db_id`,`work_req_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

TableName:'任务类型表';
Comment:'';
CREATE TABLE `work_task_type` (
  `task_db_site` varchar(16) NOT NULL,
  `task_db_id` bigint(20) NOT NULL DEFAULT '0',
  `task_type_code` bigint(20) NOT NULL DEFAULT '0',
  `wm_type_db_site` varchar(16) DEFAULT NULL,
  `wm_type_db_id` bigint(20) DEFAULT '0',
  `wm_type_code` bigint(20) DEFAULT '0',
  `user_tag_ident` varchar(254) DEFAULT NULL,
  `name` varchar(254) NOT NULL,
  `gmt_last_updated` datetime(3) DEFAULT NULL,
  `last_upd_db_site` varchar(16) DEFAULT NULL,
  `last_upd_db_id` bigint(20) DEFAULT '0',
  `rstat_type_code` int(11) DEFAULT '0',
  PRIMARY KEY (`task_db_site`,`task_db_id`,`task_type_code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

