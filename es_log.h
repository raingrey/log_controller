#ifndef __ES_LOG__
#define __ES_LOG__

#if 0
#include "es_common.h"
#else
#include "tmp_code.h"
#endif

#include "es_log_inter.h"

/* err/warn/info/dbg used only */
#define ES_LOG_ERR	(es_log_level_err)
#define ES_LOG_WARN	(es_log_level_warn)
#define ES_LOG_INFO	(es_log_level_info)
#define ES_LOG_DBG	(es_log_level_debug)


/* Prefix setup */
#define ES_LOG_PREFIX_SYSTIME	(1)
#define ES_LOG_PREFIX_BOOTTIME	(ES_LOG_PREFIX_SYSTIME << 1)
#define ES_LOG_PREFIX_COREID	(ES_LOG_PREFIX_BOOTTIME << 1)
#define ES_LOG_PREFIX_TID	(ES_LOG_PREFIX_COREID << 1)
#define ES_LOG_PREFIX_FUNC	(ES_LOG_PREFIX_TID << 1)
#define ES_LOG_PREFIX_LINE	(ES_LOG_PREFIX_FUNC << 1)
#define ES_LOG_PREFIX_MAX (ES_LOG_PREFIX_LINE << 1)
int es_set_verbose(enum esMOD_ID_E mod_idx, enum es_log_level log_level,
						unsigned char prefix_set);

enum module_log_enable_ctrl {
	module_log_off,
	module_log_on,
	module_log_enable_ctrl_num
};
int es_enable_dbg_modules(enum esMOD_ID_E mod_idx,
				enum module_log_enable_ctrl enable);

int es_set_log_level(enum esMOD_ID_E mod_idx, enum es_log_level log_level);


#define es_log_err(module_name, fmt, __args...) \
	es_print_unname_module(module_name, ES_LOG_ERR, fmt, ##__args);

#define es_log_warn(module_name, fmt, __args...) \
	es_print_unname_module(module_name, ES_LOG_WARN, fmt, ##__args);

#define es_log_info(module_name, fmt, __args...) \
	es_print_unname_module(module_name, ES_LOG_INFO, fmt, ##__args);

#define es_log_dbg(module_name, fmt, __args...) \
	es_print_unname_module(module_name, ES_LOG_DBG, fmt, ##__args);


#define es_log_vb_err(fmt, __args...) \
	es_print(ES_ID_VB, ES_LOG_ERR, fmt, ##__args);

#define es_log_vb_warn(fmt, __args...) \
	es_print(ES_ID_VB, ES_LOG_WARN, fmt, ##__args);

#define es_log_vb_info(fmt, __args...) \
	es_print(ES_ID_VB, ES_LOG_INFO, fmt, ##__args);

#define es_log_vb_dbg(fmt, __args...) \
	es_print(ES_ID_VB, ES_LOG_DBG, fmt, ##__args);


#define es_log_sys_err(fmt, __args...) \
	es_print(ES_ID_SYS, ES_LOG_ERR, fmt, ##__args);

#define es_log_sys_warn(fmt, __args...) \
	es_print(ES_ID_SYS, ES_LOG_WARN, fmt, ##__args);

#define es_log_sys_info(fmt, __args...) \
	es_print(ES_ID_SYS, ES_LOG_INFO, fmt, ##__args);

#define es_log_sys_dbg(fmt, __args...) \
	es_print(ES_ID_SYS, ES_LOG_DBG, fmt, ##__args);


#define es_log_vdec_err(fmt, __args...) \
	es_print(ES_ID_VDEC, ES_LOG_ERR, fmt, ##__args);

#define es_log_vdec_warn(fmt, __args...) \
	es_print(ES_ID_VDEC, ES_LOG_WARN, fmt, ##__args);

#define es_log_vdec_info(fmt, __args...) \
	es_print(ES_ID_VDEC, ES_LOG_INFO, fmt, ##__args);

#define es_log_vdec_dbg(fmt, __args...) \
	es_print(ES_ID_VDEC, ES_LOG_DBG, fmt, ##__args);


#define es_log_vps_err(fmt, __args...) \
	es_print(ES_ID_VPS, ES_LOG_ERR, fmt, ##__args);

#define es_log_vps_warn(fmt, __args...) \
	es_print(ES_ID_VPS, ES_LOG_WARN, fmt, ##__args);

#define es_log_vps_info(fmt, __args...) \
	es_print(ES_ID_VPS, ES_LOG_INFO, fmt, ##__args);

#define es_log_vps_dbg(fmt, __args...) \
	es_print(ES_ID_VPS, ES_LOG_DBG, fmt, ##__args);


#define es_log_venc_err(fmt, __args...) \
	es_print(ES_ID_VENC, ES_LOG_ERR, fmt, ##__args);

#define es_log_venc_warn(fmt, __args...) \
	es_print(ES_ID_VENC, ES_LOG_WARN, fmt, ##__args);

#define es_log_venc_info(fmt, __args...) \
	es_print(ES_ID_VENC, ES_LOG_INFO, fmt, ##__args);

#define es_log_venc_dbg(fmt, __args...) \
	es_print(ES_ID_VENC, ES_LOG_DBG, fmt, ##__args);


#define es_log_vo_err(fmt, __args...) \
	es_print(ES_ID_VO, ES_LOG_ERR, fmt, ##__args);

#define es_log_vo_warn(fmt, __args...) \
	es_print(ES_ID_VO, ES_LOG_WARN, fmt, ##__args);

#define es_log_vo_info(fmt, __args...) \
	es_print(ES_ID_VO, ES_LOG_INFO, fmt, ##__args);

#define es_log_vo_dbg(fmt, __args...) \
	es_print(ES_ID_VO, ES_LOG_DBG, fmt, ##__args);


#define es_log_vi_err(fmt, __args...) \
	es_print(ES_ID_VI, ES_LOG_ERR, fmt, ##__args);

#define es_log_vi_warn(fmt, __args...) \
	es_print(ES_ID_VI, ES_LOG_WARN, fmt, ##__args);

#define es_log_vi_info(fmt, __args...) \
	es_print(ES_ID_VI, ES_LOG_INFO, fmt, ##__args);

#define es_log_vi_dbg(fmt, __args...) \
	es_print(ES_ID_VI, ES_LOG_DBG, fmt, ##__args);


#define es_log_aio_err(fmt, __args...) \
	es_print(ES_ID_AIO, ES_LOG_ERR, fmt, ##__args);

#define es_log_aio_warn(fmt, __args...) \
	es_print(ES_ID_AIO, ES_LOG_WARN, fmt, ##__args);

#define es_log_aio_info(fmt, __args...) \
	es_print(ES_ID_AIO, ES_LOG_INFO, fmt, ##__args);

#define es_log_aio_dbg(fmt, __args...) \
	es_print(ES_ID_AIO, ES_LOG_DBG, fmt, ##__args);


#define es_log_ai_err(fmt, __args...) \
	es_print(ES_ID_AI, ES_LOG_ERR, fmt, ##__args);

#define es_log_ai_warn(fmt, __args...) \
	es_print(ES_ID_AI, ES_LOG_WARN, fmt, ##__args);

#define es_log_ai_info(fmt, __args...) \
	es_print(ES_ID_AI, ES_LOG_INFO, fmt, ##__args);

#define es_log_ai_dbg(fmt, __args...) \
	es_print(ES_ID_AI, ES_LOG_DBG, fmt, ##__args);


#define es_log_ao_err(fmt, __args...) \
	es_print(ES_ID_AO, ES_LOG_ERR, fmt, ##__args);

#define es_log_ao_warn(fmt, __args...) \
	es_print(ES_ID_AO, ES_LOG_WARN, fmt, ##__args);

#define es_log_ao_info(fmt, __args...) \
	es_print(ES_ID_AO, ES_LOG_INFO, fmt, ##__args);

#define es_log_ao_dbg(fmt, __args...) \
	es_print(ES_ID_AO, ES_LOG_DBG, fmt, ##__args);


#define es_log_aenc_err(fmt, __args...) \
	es_print(ES_ID_AENC, ES_LOG_ERR, fmt, ##__args);

#define es_log_aenc_warn(fmt, __args...) \
	es_print(ES_ID_AENC, ES_LOG_WARN, fmt, ##__args);

#define es_log_aenc_info(fmt, __args...) \
	es_print(ES_ID_AENC, ES_LOG_INFO, fmt, ##__args);

#define es_log_aenc_dbg(fmt, __args...) \
	es_print(ES_ID_AENC, ES_LOG_DBG, fmt, ##__args);


#define es_log_adec_err(fmt, __args...) \
	es_print(ES_ID_ADEC, ES_LOG_ERR, fmt, ##__args);

#define es_log_adec_warn(fmt, __args...) \
	es_print(ES_ID_ADEC, ES_LOG_WARN, fmt, ##__args);

#define es_log_adec_info(fmt, __args...) \
	es_print(ES_ID_ADEC, ES_LOG_INFO, fmt, ##__args);

#define es_log_adec_dbg(fmt, __args...) \
	es_print(ES_ID_ADEC, ES_LOG_DBG, fmt, ##__args);


#define es_log_user_err(fmt, __args...) \
	es_print(ES_ID_USER, ES_LOG_ERR, fmt, ##__args);

#define es_log_user_warn(fmt, __args...) \
	es_print(ES_ID_USER, ES_LOG_WARN, fmt, ##__args);

#define es_log_user_info(fmt, __args...) \
	es_print(ES_ID_USER, ES_LOG_INFO, fmt, ##__args);

#define es_log_user_dbg(fmt, __args...) \
	es_print(ES_ID_USER, ES_LOG_DBG, fmt, ##__args);


#define es_log_gdc_err(fmt, __args...) \
	es_print(ES_ID_GDC, ES_LOG_ERR, fmt, ##__args);

#define es_log_gdc_warn(fmt, __args...) \
	es_print(ES_ID_GDC, ES_LOG_WARN, fmt, ##__args);

#define es_log_gdc_info(fmt, __args...) \
	es_print(ES_ID_GDC, ES_LOG_INFO, fmt, ##__args);

#define es_log_gdc_dbg(fmt, __args...) \
	es_print(ES_ID_GDC, ES_LOG_DBG, fmt, ##__args);


#define es_log_npu_err(fmt, __args...) \
	es_print(ES_ID_NPU, ES_LOG_ERR, fmt, ##__args);

#define es_log_npu_warn(fmt, __args...) \
	es_print(ES_ID_NPU, ES_LOG_WARN, fmt, ##__args);

#define es_log_npu_info(fmt, __args...) \
	es_print(ES_ID_NPU, ES_LOG_INFO, fmt, ##__args);

#define es_log_npu_dbg(fmt, __args...) \
	es_print(ES_ID_NPU, ES_LOG_DBG, fmt, ##__args);


#define es_log_dsp_err(fmt, __args...) \
	es_print(ES_ID_DSP, ES_LOG_ERR, fmt, ##__args);

#define es_log_dsp_warn(fmt, __args...) \
	es_print(ES_ID_DSP, ES_LOG_WARN, fmt, ##__args);

#define es_log_dsp_info(fmt, __args...) \
	es_print(ES_ID_DSP, ES_LOG_INFO, fmt, ##__args);

#define es_log_dsp_dbg(fmt, __args...) \
	es_print(ES_ID_DSP, ES_LOG_DBG, fmt, ##__args);


#define es_log_bms_err(fmt, __args...) \
	es_print(ES_ID_BMS, ES_LOG_ERR, fmt, ##__args);

#define es_log_bms_warn(fmt, __args...) \
	es_print(ES_ID_BMS, ES_LOG_WARN, fmt, ##__args);

#define es_log_bms_info(fmt, __args...) \
	es_print(ES_ID_BMS, ES_LOG_INFO, fmt, ##__args);

#define es_log_bms_dbg(fmt, __args...) \
	es_print(ES_ID_BMS, ES_LOG_DBG, fmt, ##__args);


#define es_log_numa_err(fmt, __args...) \
	es_print(ES_ID_NUMA, ES_LOG_ERR, fmt, ##__args);

#define es_log_numa_warn(fmt, __args...) \
	es_print(ES_ID_NUMA, ES_LOG_WARN, fmt, ##__args);

#define es_log_numa_info(fmt, __args...) \
	es_print(ES_ID_NUMA, ES_LOG_INFO, fmt, ##__args);

#define es_log_numa_dbg(fmt, __args...) \
	es_print(ES_ID_NUMA, ES_LOG_DBG, fmt, ##__args);


#define es_log_cipher_err(fmt, __args...) \
	es_print(ES_ID_CIPHER, ES_LOG_ERR, fmt, ##__args);

#define es_log_cipher_warn(fmt, __args...) \
	es_print(ES_ID_CIPHER, ES_LOG_WARN, fmt, ##__args);

#define es_log_cipher_info(fmt, __args...) \
	es_print(ES_ID_CIPHER, ES_LOG_INFO, fmt, ##__args);

#define es_log_cipher_dbg(fmt, __args...) \
	es_print(ES_ID_CIPHER, ES_LOG_DBG, fmt, ##__args);


#define es_log_butt_err(fmt, __args...) \
	es_print(ES_ID_BUTT, ES_LOG_ERR, fmt, ##__args);

#define es_log_butt_warn(fmt, __args...) \
	es_print(ES_ID_BUTT, ES_LOG_WARN, fmt, ##__args);

#define es_log_butt_info(fmt, __args...) \
	es_print(ES_ID_BUTT, ES_LOG_INFO, fmt, ##__args);

#define es_log_butt_dbg(fmt, __args...) \
	es_print(ES_ID_BUTT, ES_LOG_DBG, fmt, ##__args);




#endif
