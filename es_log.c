#include "es_log_inter.h"
#include "es_log.h"

char global_log_level = ES_LOG_INFO;
char print_syslog = 1;
const char default_log_prefix[] = {
	#ifndef __KERNEL__
	[ES_LOG_ERR]  = ES_LOG_PREFIX_SYSTIME | ES_LOG_PREFIX_BOOTTIME |
			ES_LOG_PREFIX_COREID |
			ES_LOG_PREFIX_TID | ES_LOG_PREFIX_FUNC |
			ES_LOG_PREFIX_LINE,
	[ES_LOG_WARN] = ES_LOG_PREFIX_SYSTIME | ES_LOG_PREFIX_FUNC |
			ES_LOG_PREFIX_LINE,
	[ES_LOG_INFO] = ES_LOG_PREFIX_SYSTIME,
	[ES_LOG_DBG]  = ES_LOG_PREFIX_SYSTIME | ES_LOG_PREFIX_COREID |
			ES_LOG_PREFIX_TID | ES_LOG_PREFIX_FUNC |
			ES_LOG_PREFIX_LINE,
	#else
	[ES_LOG_ERR]  = ES_LOG_PREFIX_COREID |
			ES_LOG_PREFIX_TID | ES_LOG_PREFIX_FUNC |
			ES_LOG_PREFIX_LINE,
	[ES_LOG_WARN] = ES_LOG_PREFIX_FUNC |
			ES_LOG_PREFIX_LINE,
	[ES_LOG_INFO] = 0,
	[ES_LOG_DBG]  = ES_LOG_PREFIX_COREID |
			ES_LOG_PREFIX_TID | ES_LOG_PREFIX_FUNC |
			ES_LOG_PREFIX_LINE,
	#endif
};
#ifndef __KERNEL__
#define __DEFAULT_PREFIX \
{ \
	[es_log_level_emerg]= 0, \
	[es_log_level_alert]= 0, \
	[es_log_level_crit]= 0, \
	[ES_LOG_ERR]  = ES_LOG_PREFIX_SYSTIME | \
			ES_LOG_PREFIX_BOOTTIME | \
			ES_LOG_PREFIX_COREID | \
			ES_LOG_PREFIX_TID | \
			ES_LOG_PREFIX_FUNC | \
			ES_LOG_PREFIX_LINE, \
	[ES_LOG_WARN] = ES_LOG_PREFIX_SYSTIME | \
			ES_LOG_PREFIX_FUNC | \
			ES_LOG_PREFIX_LINE, \
	[es_log_level_notice]= 0, \
	[ES_LOG_INFO] = ES_LOG_PREFIX_SYSTIME, \
	[ES_LOG_DBG]  = ES_LOG_PREFIX_SYSTIME | \
			ES_LOG_PREFIX_COREID | \
			ES_LOG_PREFIX_TID | \
			ES_LOG_PREFIX_FUNC | \
			ES_LOG_PREFIX_LINE, \
}
#else
#define __DEFAULT_PREFIX \
{ \
	[es_log_level_emerg]= 0, \
	[es_log_level_alert]= 0, \
	[es_log_level_crit]= 0, \
	[ES_LOG_ERR]  = \
			ES_LOG_PREFIX_COREID | \
			ES_LOG_PREFIX_TID | \
			ES_LOG_PREFIX_FUNC | \
			ES_LOG_PREFIX_LINE, \
	[ES_LOG_WARN] = \
			ES_LOG_PREFIX_FUNC | \
			ES_LOG_PREFIX_LINE, \
	[es_log_level_notice]= 0, \
	[ES_LOG_INFO] = 0, \
	[ES_LOG_DBG]  = \
			ES_LOG_PREFIX_COREID | \
			ES_LOG_PREFIX_TID | \
			ES_LOG_PREFIX_FUNC | \
			ES_LOG_PREFIX_LINE, \
}
#endif

#define DEFAULT_LOG_CONFIGURE(mod_idx) \
	[mod_idx] = { \
		.level = es_log_level_info, \
		.enable = 1, \
		.prefix = __DEFAULT_PREFIX, \
	}

struct module_log_configure module_log_conf[] = {
	DEFAULT_LOG_CONFIGURE(ES_ID_VB),
	DEFAULT_LOG_CONFIGURE(ES_ID_SYS),
	DEFAULT_LOG_CONFIGURE(ES_ID_VDEC),
	DEFAULT_LOG_CONFIGURE(ES_ID_VPS),
	DEFAULT_LOG_CONFIGURE(ES_ID_VENC),
	DEFAULT_LOG_CONFIGURE(ES_ID_VO),
	DEFAULT_LOG_CONFIGURE(ES_ID_VI),
	DEFAULT_LOG_CONFIGURE(ES_ID_AIO),
	DEFAULT_LOG_CONFIGURE(ES_ID_AI),
	DEFAULT_LOG_CONFIGURE(ES_ID_AO),
	DEFAULT_LOG_CONFIGURE(ES_ID_AENC),
	DEFAULT_LOG_CONFIGURE(ES_ID_ADEC),
	DEFAULT_LOG_CONFIGURE(ES_ID_USER),
	DEFAULT_LOG_CONFIGURE(ES_ID_GDC),
	DEFAULT_LOG_CONFIGURE(ES_ID_NPU),
	DEFAULT_LOG_CONFIGURE(ES_ID_DSP),
	DEFAULT_LOG_CONFIGURE(ES_ID_BMS),
	DEFAULT_LOG_CONFIGURE(ES_ID_NUMA),
	DEFAULT_LOG_CONFIGURE(ES_ID_CIPHER),
	DEFAULT_LOG_CONFIGURE(ES_ID_BUTT),
	DEFAULT_LOG_CONFIGURE(ES_ID_NUM),
};
const char *module_str[] = {
	[ES_ID_VB]	= "VB",
	[ES_ID_SYS]	= "SYS",
	[ES_ID_VDEC]	= "VDEC",
	[ES_ID_VPS]	= "VPS",
	[ES_ID_VENC]	= "VENC",
	[ES_ID_VO]	= "VO",
	[ES_ID_VI]	= "VI",
	[ES_ID_AIO]	= "AIO",
	[ES_ID_AI]	= "AI",
	[ES_ID_AO]	= "AO",
	[ES_ID_AENC]	= "AENC",
	[ES_ID_ADEC]	= "ADEC",
	[ES_ID_USER]	= "USER",
	[ES_ID_GDC]	= "GDC",
	[ES_ID_NPU]	= "NPU",
	[ES_ID_DSP]	= "DSP",
	[ES_ID_BMS]	= "BMS",
	[ES_ID_NUMA]	= "NUMA",
	[ES_ID_CIPHER]	= "CIPHER",
	[ES_ID_BUTT]	= "BUTT",
	[ES_ID_NUM]	= "UNDEF_MOD",
	NULL,
};
char *log_level_str[] = {
	[es_log_level_emerg] = "EMERG",
	[es_log_level_alert] = "ALERT",
	[es_log_level_crit] = "CRIT",
	[es_log_level_err] = "ERR",
	[es_log_level_warn] = "WARN",
	[es_log_level_notice] = "NOTICE",
	[es_log_level_info] = "INFO",
	[es_log_level_debug] = "DBG",
	[es_log_level_num] = "UNDEF_LOG_LEVEL",
};

int es_enable_dbg_modules(enum esMOD_ID_E mod_idx,
				enum module_log_enable_ctrl enable)
{
	if (mod_idx < ES_ID_NUM && enable < module_log_enable_ctrl_num) {
		module_log_conf[mod_idx].enable = enable;
		return 0;
	}
	return -1;
}
int es_set_log_level(enum esMOD_ID_E mod_idx, enum es_log_level log_level)
{
	if (mod_idx < ES_ID_NUM && log_level < es_log_level_num) {
		module_log_conf[mod_idx].level = log_level;
		return 0;
	}
	return -1;
}
int es_set_verbose(enum esMOD_ID_E mod_idx, enum es_log_level log_level,
						unsigned char prefix_set)
{
	if (mod_idx < ES_ID_NUM && log_level < es_log_level_num &&
					prefix_set < ES_LOG_PREFIX_MAX ) {
		module_log_conf[mod_idx].prefix[log_level] = prefix_set;
		return 0;
	} return -1;
}
int es_log_init(enum esMOD_ID_E mod_idx)
{
#ifndef __KERNEL__
	char *enable_syslog = getenv("ES_SYSLOG");

	if (enable_syslog != NULL && (enable_syslog[0] == 'n' ||
					enable_syslog[0] == 'N')) {
		print_syslog = 0;
	} else {
		openlog("", LOG_CONS, 0);
		syslog(LOG_ERR , "start\n");
		print_syslog = 1;
	}
#endif

	return 0;
}
#ifndef __KERNEL__
int main(void)
{
#else
MODULE_LICENSE("GPL");
static void test_exit(void)
{
	printk("%s exit\n", __func__);
}
static int test_init(void);
module_init(test_init);
module_exit(test_exit);

static int test_init(void)
{
#endif
	int a, i;

	es_log_init(ES_ID_NPU);
for (i = 0; i < ES_ID_NUM; i++) {
	es_set_log_level(i, ES_LOG_DBG);
}
for (i = 0; i < ES_ID_NUM; i++) {
	es_enable_dbg_modules(i, module_log_on);
}
for (i = 0; i < ES_ID_NUM; i++) {
	es_set_verbose(i, ES_LOG_DBG, 
#if 1
				ES_LOG_PREFIX_SYSTIME |
				ES_LOG_PREFIX_BOOTTIME |
				ES_LOG_PREFIX_COREID |
				ES_LOG_PREFIX_TID |
				ES_LOG_PREFIX_FUNC |
				ES_LOG_PREFIX_LINE);
#else
				 0);
#endif

	es_set_verbose(i, ES_LOG_INFO,
#if 1
				ES_LOG_PREFIX_SYSTIME |
				ES_LOG_PREFIX_BOOTTIME |
				ES_LOG_PREFIX_COREID |
				ES_LOG_PREFIX_TID |
				ES_LOG_PREFIX_FUNC |
				ES_LOG_PREFIX_LINE);
#else
				 0);
#endif
	es_set_verbose(i, ES_LOG_WARN,
#if 1
				ES_LOG_PREFIX_SYSTIME |
				ES_LOG_PREFIX_BOOTTIME |
				ES_LOG_PREFIX_COREID |
				ES_LOG_PREFIX_TID |
				ES_LOG_PREFIX_FUNC |
				ES_LOG_PREFIX_LINE);
#else
				 0);
#endif

	es_set_verbose(i, ES_LOG_ERR,
#if 1
				ES_LOG_PREFIX_SYSTIME |
				ES_LOG_PREFIX_BOOTTIME |
				ES_LOG_PREFIX_COREID |
				ES_LOG_PREFIX_TID |
				ES_LOG_PREFIX_FUNC |
				ES_LOG_PREFIX_LINE);
#else
				 0);
#endif

}


	es_log_npu_dbg("nothing\n");
	es_log_npu_info("nothing\n");
	es_log_npu_warn("nothing\n");
	es_log_npu_err("nothing %d\n", a);


	es_log_vb_err("nothing %d\n", a);
	es_log_vb_warn("nothing %d\n", a);
	es_log_vb_info("nothing %d\n", a);
	es_log_vb_dbg("nothing %d\n", a);


	es_log_sys_err("nothing %d\n", a);
	es_log_sys_warn("nothing %d\n", a);
	es_log_sys_info("nothing %d\n", a);
	es_log_sys_dbg("nothing %d\n", a);

	es_log_vdec_err("nothing %d\n", a);
	es_log_vdec_warn("nothing %d\n", a);
	es_log_vdec_info("nothing %d\n", a);
	es_log_vdec_dbg("nothing %d\n", a);

	es_log_vps_err("nothing %d\n", a);
	es_log_vps_warn("nothing %d\n", a);
	es_log_vps_info("nothing %d\n", a);
	es_log_vps_dbg("nothing %d\n", a);

	es_log_venc_err("nothing %d\n", a);
	es_log_venc_warn("nothing %d\n", a);
	es_log_venc_info("nothing %d\n", a);
	es_log_venc_dbg("nothing %d\n", a);

	es_log_vo_err("nothing %d\n", a);
	es_log_vo_warn("nothing %d\n", a);
	es_log_vo_info("nothing %d\n", a);
	es_log_vo_dbg("nothing %d\n", a);

	es_log_vi_err("nothing %d\n", a);
	es_log_vi_warn("nothing %d\n", a);
	es_log_vi_info("nothing %d\n", a);
	es_log_vi_dbg("nothing %d\n", a);

	es_log_aio_err("nothing %d\n", a);
	es_log_aio_warn("nothing %d\n", a);
	es_log_aio_info("nothing %d\n", a);
	es_log_aio_dbg("nothing %d\n", a);

	es_log_ai_err("nothing %d\n", a);
	es_log_ai_warn("nothing %d\n", a);
	es_log_ai_info("nothing %d\n", a);
	es_log_ai_dbg("nothing %d\n", a);

	es_log_ao_err("nothing %d\n", a);
	es_log_ao_warn("nothing %d\n", a);
	es_log_ao_info("nothing %d\n", a);
	es_log_ao_dbg("nothing %d\n", a);

	es_log_aenc_err("nothing %d\n", a);
	es_log_aenc_warn("nothing %d\n", a);
	es_log_aenc_info("nothing %d\n", a);
	es_log_aenc_dbg("nothing %d\n", a);

	es_log_adec_err("nothing %d\n", a);
	es_log_adec_warn("nothing %d\n", a);
	es_log_adec_info("nothing %d\n", a);
	es_log_adec_dbg("nothing %d\n", a);

	es_log_user_err("nothing %d\n", a);
	es_log_user_warn("nothing %d\n", a);
	es_log_user_info("nothing %d\n", a);
	es_log_user_dbg("nothing %d\n", a);

	es_log_gdc_err("nothing %d\n", a);
	es_log_gdc_warn("nothing %d\n", a);
	es_log_gdc_info("nothing %d\n", a);
	es_log_gdc_dbg("nothing %d\n", a);

	es_log_npu_err("nothing %d\n", a);
	es_log_npu_warn("nothing %d\n", a);
	es_log_npu_info("nothing %d\n", a);
	es_log_npu_dbg("nothing %d\n", a);

	es_log_dsp_err("nothing %d\n", a);
	es_log_dsp_warn("nothing %d\n", a);
	es_log_dsp_info("nothing %d\n", a);
	es_log_dsp_dbg("nothing %d\n", a);

	es_log_bms_err("nothing %d\n", a);
	es_log_bms_warn("nothing %d\n", a);
	es_log_bms_info("nothing %d\n", a);
	es_log_bms_dbg("nothing %d\n", a);

	es_log_numa_err("nothing %d\n", a);
	es_log_numa_warn("nothing %d\n", a);
	es_log_numa_info("nothing %d\n", a);
	es_log_numa_dbg("nothing %d\n", a);

	es_log_cipher_err("nothing %d\n", a);
	es_log_cipher_warn("nothing %d\n", a);
	es_log_cipher_info("nothing %d\n", a);
	es_log_cipher_dbg("nothing %d\n", a);

	es_log_butt_err("nothing %d\n", a);
	es_log_butt_warn("nothing %d\n", a);
	es_log_butt_info("nothing %d\n", a);
	es_log_butt_dbg("nothing %d\n", a);


	es_log_err("gaga", "nothing %d\n", a);
	es_log_warn("mama", "nothing %d\n", a);
	es_log_info("dada", "nothing %d\n", a);
	es_log_dbg("lala", "nothing %d\n", a);
	return 0;
}
