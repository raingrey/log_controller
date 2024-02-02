#ifndef __ES_LOG_INTER__
#define __ES_LOG_INTER__
#define _GNU_SOURCE
#define SYSTIME_MAX_LEN (29)
#define BOOTTIME_MAX_LEN (18)
#define COREID_MAX_LEN (9)
#define TID_MAX_LEN (16)
#define FUNC_MAX_LEN (32)
#define LINE_MAX_LEN (12)

/* Log index consistent with syslog and linux kernel */
enum es_log_level {
	es_log_level_emerg = 0,
	es_log_level_alert,
	es_log_level_crit,
	es_log_level_err,
	es_log_level_warn,
	es_log_level_notice,
	es_log_level_info,
	es_log_level_debug,
	es_log_level_num,
};

#ifndef __KERNEL__
#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <time.h>
#include <string.h>
#include <sched.h>
#include <unistd.h>

static inline void get_systime_str(char *str_time)
{
	time_t now = time(NULL);
	struct tm localtm;

	str_time[0] = '[';
	localtime_r(&now, &localtm);
	strftime(str_time + 1, SYSTIME_MAX_LEN, "%m-%d %H:%M:%S", &localtm);
	str_time[strlen(str_time) - 1] = ']';
}
static inline void get_boottime_str(char *str_time)
{
	struct timespec times = {0, 0};
	int time;
	char ntime;

	clock_gettime(CLOCK_MONOTONIC, &times);
	time = (unsigned int)times.tv_sec;
	ntime = times.tv_nsec / 10000000;
	snprintf(str_time, BOOTTIME_MAX_LEN, "[%d.%-2d]", time,
						ntime);
}
static inline void get_coreid_str(char *str_coreid)
{
	snprintf(str_coreid, COREID_MAX_LEN, "[%d]", sched_getcpu());
}
static inline void get_tid_str(char *str_tid)
{
	snprintf(str_tid, TID_MAX_LEN, "[%d]", (unsigned int)getpid());
}
static inline void get_func_str(char *str_func, const char *func)
{
	snprintf(str_func, FUNC_MAX_LEN, "[%s]", func);
}
static inline void get_line_str(char *str_line, int line)
{
	snprintf(str_line, LINE_MAX_LEN, "[%d]", line);
}
#else
#include <linux/kernel.h>
#include <linux/smp.h>
#include <linux/module.h>
#include <linux/sched.h>
/* kernel mode do not support systime print */
static inline void get_systime_str(char *str_time)
{
	str_time[0] = 0;
}
/* linux kernel print boottime */
static inline void get_boottime_str(char *str_time)
{
	str_time[0] = 0;
}
static inline void get_coreid_str(char *str_coreid)
{
	snprintf(str_coreid, COREID_MAX_LEN, "[%d]", smp_processor_id());
}
static inline void get_tid_str(char *str_tid)
{
	snprintf(str_tid, TID_MAX_LEN, "[%d]", (unsigned int)(current->pid));
}
static inline void get_func_str(char *str_func, const char *func)
{
	snprintf(str_func, FUNC_MAX_LEN, "[%s]", func);
}
static inline void get_line_str(char *str_line, int line)
{
	snprintf(str_line, LINE_MAX_LEN, "[%d]", line);
}

#endif

struct module_log_configure {
	unsigned char level : 3;
	unsigned char enable : 1;
	unsigned char prefix[es_log_level_num];
};
extern char print_syslog;
extern char global_log_level;
extern const char default_log_prefix[];
extern struct module_log_configure module_log_conf[];
extern const char *module_str[];
extern char *log_level_str[];

#ifndef __KERNEL__ 
#define __DO_PRINT(mod_name, log_level, level_name, prefix_coreid, prefix_tid, \
			prefix_func, prefix_line, fmt, __args...) \
({ \
	char prefix_systime[SYSTIME_MAX_LEN]; \
	char prefix_boottime[BOOTTIME_MAX_LEN]; \
\
	prefix_systime[0] = 0; \
	if (prefix_bitmap & ES_LOG_PREFIX_SYSTIME) { \
		get_systime_str(prefix_systime); \
	} \
	prefix_boottime[0] = 0; \
	if (prefix_bitmap & ES_LOG_PREFIX_BOOTTIME) { \
		get_boottime_str(prefix_boottime); \
	} \
	if (print_syslog == 1) { \
		syslog((int)log_level, "%s[%s][%s]%s%s%s%s:" fmt, \
			prefix_boottime, \
			level_name, \
			mod_name, \
			prefix_coreid, \
			prefix_tid, \
			prefix_func, \
			prefix_line, \
			##__args); \
	} else { \
		printf("%s%s[%s][%s]%s%s%s%s:" fmt, \
			prefix_systime, \
			prefix_boottime, \
			level_name, \
			mod_name, \
			prefix_coreid, \
			prefix_tid, \
			prefix_func, \
			prefix_line, \
			##__args); \
	} \
})
#else
#define __DO_PRINT(mod_name, log_level, level_name, prefix_coreid, prefix_tid, \
			prefix_func, prefix_line, fmt, __args...) \
({ \
	printk("[%s][%s]%s%s%s%s:" fmt, \
			level_name, \
			mod_name, \
			prefix_coreid, \
			prefix_tid, \
			prefix_func, \
			prefix_line, \
			##__args); \
})
#endif

#define do_print(mod_name, log_level, level_name, prefix_bitmap, \
							fmt, __args...) \
({ \
	char prefix_coreid[COREID_MAX_LEN]; \
	char prefix_tid[TID_MAX_LEN]; \
	char prefix_func[FUNC_MAX_LEN]; \
	char prefix_line[LINE_MAX_LEN]; \
\
	prefix_coreid[0] = 0; \
	if (prefix_bitmap & ES_LOG_PREFIX_COREID) { \
		get_coreid_str(prefix_coreid); \
	} \
	prefix_tid[0] = 0; \
	if (prefix_bitmap & ES_LOG_PREFIX_TID) { \
		get_tid_str(prefix_tid); \
	} \
	prefix_func[0] = 0; \
	if (prefix_bitmap & ES_LOG_PREFIX_FUNC) { \
		get_func_str(prefix_func, __func__); \
	} \
	prefix_line[0] = 0; \
	if (prefix_bitmap & ES_LOG_PREFIX_LINE) { \
		get_line_str(prefix_line, __LINE__); \
	} \
	__DO_PRINT(mod_name, log_level, level_name, prefix_coreid, prefix_tid, \
			prefix_func, prefix_line, fmt, ##__args); \
})


#define es_print_unname_module(mod_name, log_level, fmt, __args...) \
({ \
 	char *level_name; \
	char prefix_bitmap; \
\
	if (log_level - global_log_level < 1) { \
		level_name = log_level_str[log_level]; \
		prefix_bitmap = default_log_prefix[log_level]; \
		do_print(mod_name, log_level, level_name, prefix_bitmap, fmt, \
							##__args); \
	} \
})

#define es_print(mod_idx, log_level, fmt, __args...) \
({ \
	char *mod_name; \
	char *level_name; \
	char prefix_bitmap; \
\
	if (mod_idx < ES_ID_NUM) { \
		if ((log_level - module_log_conf[mod_idx].level < 1)&& \
			module_log_conf[mod_idx].enable == module_log_on) { \
			mod_name = (char *)module_str[mod_idx]; \
			level_name = log_level_str[log_level]; \
			prefix_bitmap = \
				module_log_conf[mod_idx].prefix[log_level]; \
			do_print(mod_name, log_level, level_name, \
				prefix_bitmap, fmt, ##__args); \
		} \
	} else { \
		/* undefined module */ \
		if (log_level - global_log_level < 1) { \
			mod_name = (char *)module_str[ES_ID_NUM]; \
			level_name = log_level_str[log_level]; \
			prefix_bitmap = default_log_prefix[log_level]; \
			do_print(mod_name, log_level, level_name, \
				prefix_bitmap, fmt, ##__args); \
		} \
	} \
})


#endif
