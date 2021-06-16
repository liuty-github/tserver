#include "tThread.h"
#include "tLog.h"

tThread::tThread()
{
	TTHREAD_INITMUTEX(m_mutex);
	TLOGI("无参数构造函数");

}

tThread::~tThread()
{
	TTHREAD_FINITMUTEX(m_mutex);
}

int tThread::CreatThread()
{
	
	int iret = -1;
#if TPLATFORM == TWIN
	m_hdl = nullptr;
	m_hdl = (TTHREAD_HDL)_beginthreadex(NULL, 0, &tThread::th_function, (void*)this, NULL, 0);
	if(m_hdl != nullptr){iret = 0;}
#else	
	iret = pthread_create(&m_hdl, NULL, tThread::th_function, (void*)this);
#endif
	return iret;
}

int tThread::DestroyThread()
{
	m_Status = DESTROY;
	TTHREAD_JOIN(m_hdl);//线程同步防止析构了还在调用非法的函数
}

void tThread::ThreadStart()
{
	m_Status = BUSY;
}

#if TPLATFORM == TWIN
unsigned __stdcall tThread::th_function(void* pParam)
#else	
void* tThread::th_function(void* pParam)
#endif
{
	tThread* pthis = (tThread*)pParam;
	while (true)
	{
		if (pthis->m_Status == BUSY)
		{
			TTHREAD_MUTEXLOCK(pthis->m_mutex);
			pthis->run();
			TTHREAD_MUTEXUNLOCK(pthis->m_mutex);
			//break;
		}
		if(pthis->m_Status == DESTROY){break;}
	}
	pthis->m_Status = FINISH;
	return 0;
}

TINT64 tThread::Getthreadid()
{
	return (TINT64)m_hdl;
}

int tThread::GetStatus()
{
	return m_Status;
}
