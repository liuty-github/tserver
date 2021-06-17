#include "tDefine.h"
#ifndef	__THREAD_H__
#define __THREAD_H__
/***********************************TThread****************************************
说明					线程类
TThread()				无参数构造函数

TThread(void* pfun)		有参数构造函数
入参：
pfun					希望托管给线程的函数指针类型为void* (*threadfunc)()

CreatThread()			创建线程
DestroyThread()			销毁线程（暂未实现）
GetStatus()				获取线程状态。SLEEP线程未运行。BUSY线程运行中。FINISH线程执行
						完毕。
Getthreadid()			获取线程ID（实际返回线程指针的地址）
th_function()			thread类执行函数。当时用无参数构造函数定义类对象时，该函数将
						执行run()函数；若使用有参数构造函数定义类对象时（传入了函数指
						针），则执行构造传入的函数
run()					线程函数。若使用无参数构造函数定义类对象，则需继承该函数，重
						写需要执行的内容
**********************************************************************************/
class tThread
{
	typedef void (*threadfunc)();
public:
	enum TTStatus
	{
		SLEEP = 0,
		BUSY,
		DESTROY,
		FINISH,
	};
	tThread();			//继承线程类时使用，使用默认构造函数，派生类通过重写run函数实现任务函数
	~tThread();

	TEXPORTS int		CreatThread();
	TEXPORTS int		DestroyThread();
	TEXPORTS int        GetStatus();
	TEXPORTS void		ThreadStart();
	TEXPORTS TINT64		Getthreadid();
private:
	#if TPLATFORM == TWIN
		static unsigned __stdcall th_function(void *pParam);
	#else	
		static void* 	th_function(void* pParam);
	#endif
	virtual void		run() = 0;
private:
	threadfunc			m_pfun	  = nullptr;
	TTHREAD_HDL			m_hdl;
	TTHREAD_MUTEX   	m_mutex;
	TTStatus        	m_Status  = SLEEP;
};

#endif