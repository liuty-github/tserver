#ifndef  __TLOG_H__
#define  __TLOG_H__

#include "tDefine.h"



//和运行日志相关 
typedef struct
{
	int    log_level;   //日志级别 或者日志类型，ngx_macro.h里分0-8共9个级别
	int    fd;          //日志文件描述符

}ngx_log_t;

#define NGX_MAX_ERROR_STR   2048   //显示的错误信息最大数组长度
#define NGX_ERROR_LOG_PATH       "error.log"   //定义日志存放的路径和文件名
#define ngx_cpymem(dst, src, n)   (((u_char *) memcpy(dst, src, n)) + (n))  //注意#define写法，n这里用()包着，防止出现什么错误
#define ngx_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))              //比较大小，返回小值，注意，参数都用()包着
//数字相关--------------------
#define NGX_MAX_UINT32_VALUE   (uint32_t) 0xffffffff              //最大的32位无符号数：十进制是‭4294967295‬
#define NGX_INT64_LEN          (sizeof("-9223372036854775808") - 1)  

#define NGX_LOG_STDERR            0    //控制台错误【stderr】：最高级别日志，日志的内容写入log参数指定的文件，同时也尝试直接将日志输出到标准错误设备比如控制台屏幕
#define NGX_LOG_EMERG             1    //紧急 【emerg】
#define NGX_LOG_ALERT             2    //警戒 【alert】
#define NGX_LOG_CRIT              3    //严重 【crit】
#define NGX_LOG_ERR               4    //错误 【error】：属于常用级别
#define NGX_LOG_WARN              5    //警告 【warn】：属于常用级别
#define NGX_LOG_NOTICE            6    //注意 【notice】
#define NGX_LOG_INFO              7    //信息 【info】
#define NGX_LOG_DEBUG             8    //调试 【debug】：最低级别

#if TPLATFORM == TWIN
#define REMOVEPATH(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#else
#define REMOVEPATH(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#endif

#define TLOGD(...)				  tLog::getInstance()->ngx_log_error_core(NGX_LOG_DEBUG, errno, REMOVEPATH(__FILE__),  __FUNCTION__, __LINE__, __VA_ARGS__)
#define TLOGI(...)				  tLog::getInstance()->ngx_log_error_core(NGX_LOG_INFO, errno, REMOVEPATH(__FILE__),  __FUNCTION__, __LINE__, __VA_ARGS__)
#define TLOGW(...)				  tLog::getInstance()->ngx_log_error_core(NGX_LOG_WARN, errno, REMOVEPATH(__FILE__),  __FUNCTION__, __LINE__, __VA_ARGS__)
#define TLOGE(...)				  tLog::getInstance()->ngx_log_error_core(NGX_LOG_ERR, errno, REMOVEPATH(__FILE__),  __FUNCTION__, __LINE__, __VA_ARGS__)

class tLog
{
private:
	tLog(){};
public:
	TEXPORTS static tLog* getInstance();
	~tLog(){};
	//和日志，打印输出有关
	void    ngx_log_init();
	void    ngx_log_stderr(int err, const char *fmt, ...);
	void    ngx_log_error_core(int level,  int err, const char* filename, const char* function, unsigned int codeline, const char *fmt, ...);
	u_char* ngx_log_errno(u_char *buf, u_char *last, int err);
	u_char *		 ngx_snprintf(u_char *buf, size_t max, const char *fmt, ...);
	u_char *		 ngx_slprintf(u_char *buf, u_char *last, const char *fmt, ...);
	u_char *		 ngx_vslprintf(u_char *buf, u_char *last,const char *fmt,va_list args);
	u_char *		 ngx_sprintf_num(u_char *buf, u_char *last, uint64_t ui64,u_char zero, uintptr_t hexadecimal, uintptr_t width);

	ngx_log_t   	 ngx_log;
};




#endif	
