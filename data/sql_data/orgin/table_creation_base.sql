TableName:'��ɫ��';
Comment:'��ʾһ������ʵ�壬����Ա���㷨��';
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

TableName:'��ɫ���ͱ�';
Comment:'������ߡ�������Ա�������ߡ���Ӷ�ߵ�';
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

TableName:'��ɫ��ϵ��';
Comment:'���ڶ���agent������agent��Ľ�ɫ��ϵ�������޹�ϵ��������ϵ��������ϵ��';
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

TableName:'���ܸ������ͱ�';
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

TableName:'�豸��';
Comment:'ϵͳ����豸��һһ��Ӧ����ѯĳ��ϵͳ�µ��豸��Ϣʱ��Ҫ��ȥsegemnt_child���ҵ���Ӧ����ϵͳ��Ȼ���ٲ�ѯ�豸������豸��Ϣ';
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

TableName:'�豸���������ݱ�';
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

TableName:'���豸��';
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

TableName:'�豸�ַ����ݱ�';
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

TableName:'�豸��ֵ���ݱ�';
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

TableName:'ϵͳ�ϰ�װ�豸��';
Comment:'���ڴ洢��װ��ϵͳ�ϵ��豸';
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

TableName:'�豸���ͱ�';
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

TableName:'ϵͳ�������������ͱ�';
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

TableName:'Σ���ȼ���';
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

TableName:'��λ��';
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

TableName:'��֯��';
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

TableName:'��֯���ͱ�';
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

TableName:'�����ȼ���';
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

TableName:'���Ե������';
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

TableName:'���Ե����ͱ�';
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

TableName:'���Ե��';
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

TableName:'ʵʱ���������ݱ�';
Comment:'�����񶯡�ͼƬ���ݣ�����Ե�������ѯ';
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

TableName:'ʵʱ�ַ����ݱ�';
Comment:'����Ե����ͱ������ѯ����Ϊ״̬���ͣ���ѯ�˱�����Ե�������ѯ';
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

TableName:'��ֵ�����ݸ澯��';
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

TableName:'ʵʱ��ֵ���ݱ�';
Comment:'����Ե����ͱ������ѯ����Ϊ��״̬���ͣ���ѯ�˱�����Ե�������ѯ';
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

TableName:'�澯�¼�������ĸ澯������Ϣ��';
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

TableName:'ʵ�������ݸ澯���ñ�';
Comment:'ʵ�������ݵĸ澯������Ϣ�����������ޡ���λ���澯���͵���Ϣ';
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

TableName:'���ȼ���';
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

TableName:'���������ͱ�';
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

TableName:'ϵͳ��';
Comment:'��¼����ϵͳ��Ϣ���豸��Ϣ';
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

TableName:'ϵͳ���������ݱ�';
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

TableName:'ϵͳ����ϵͳ��ϵ��';
Comment:'��¼ϵͳ���еĸ��ӹ�ϵ����ϵͳ��Ϣȥϵͳ���в�ѯ';
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

TableName:'ϵͳ�ַ����ݱ�';
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

TableName:'�¼���';
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

TableName:'����ģʽ���ܱ�';
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

TableName:'����������';
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

TableName:'ϵͳ���ݱ�';
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

TableName:'ϵͳ���ͱ�';
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

TableName:'�¼����ͱ�';
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

TableName:'ϵͳ�ַ��������ͱ�';
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

TableName:'ʵʱά��ά�����ݱ�';
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

TableName:'ģ���������ģʽ������';
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

TableName:'�����ʱ�';
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

TableName:'����ģʽ�빦�ܹ�����';
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

TableName:'����ģʽ��';
Comment:'�洢ĳ��ϵͳ���豸���еĹ���ģʽ';
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

TableName:'ϵͳ��ֵ�������ͱ�';
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

TableName:'���ϱ�';
Comment:'��ѯ����ϵͳ���豸���裬����sg_hyp_ev_amb_set����Ҷ�Ӧ��sg_hyp_amb_set_id������sg_hyp_ev_log_conn����Ҷ�Ӧ��sg_hyp_event_id������sg_hyp_event���Ҷ�Ӧ��segment_site��segment_id������segment����ҹ���ϵͳ���豸';
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

TableName:'ά�޽����';
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

TableName:'���������';
Comment:'ϵͳ���豸��ά�����ά����,����ϵͳ���豸��ά����Ϣ���й���segment,����segment_site��segment_id������work_manage_type������nameΪά��������wm_type_code,����sg_req_for_work�ж�Ӧwm_type_code������wm_type_code,����work_request������name';
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

TableName:'վ���';
Comment:'��ʾ�칫¥���ɻ����������ء�����������װ����̹�ˡ���ͧ';
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

TableName:'վ�����ͱ�';
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

TableName:'ά����';
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

TableName:'ά������������ݱ�';
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

TableName:'ά�����ַ����ݱ�';
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

TableName:'ά������ֵ���ݱ�';
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

TableName:'ά������';
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

TableName:'ά�������ַ����ݱ�';
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

TableName:'ά��������ֵ���ݱ�';
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

TableName:'�����������ͱ�';
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

TableName:'ά��������Ϣ��';
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

TableName:'�������ͱ�';
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

