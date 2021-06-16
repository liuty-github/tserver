#ifndef  __TDEFINE_H__
#define  __TDEFINE_H__

/***************************************|确认平台**********************************************/
#define		TWIN		0																	////
#define		TUNIX		1																	////
#define		TOSX		2																	////
#define		TANDROID	3																	////
																							////
#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )							////
#  define TPLATFORM			TWIN															////
#  define TPLATFORM_NAME	"win"															////
#elif defined( __APPLE_CC__ )																////
#  define TPLATFORM			TOSX															////
#  define TPLATFORM_NAME	"osx"															////
#elif defined( __ANDROID__ )																////
#  define TPLATFORM			TANDROID														////
#  define TPLATFORM_NAME	"android"														////
#else																						////
#  define TPLATFORM			TUNIX															////
#  define TPLATFORM_NAME	"unix"															////
#endif																						////
/***********************************************************************************************/

/**************************************|Include*************************************************/
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <string.h>
#include <map>
#include <vector>
#include <queue>
#include <assert.h>
#include <fstream>
#include <atomic> 

#if TPLATFORM == TWIN																		////
#pragma warning(disable:4996)																////
#pragma warning(disable:4819)																////
#pragma warning(disable:4005)																////
#define WIN32_LEAN_AND_MEAN																	////																
#include <winsock2.h>
#include <windows.h> 
#include <process.h>
#include <mutex>	
#include <algorithm>																		////
#elif 	TPLATFORM == TUNIX																	////
#include <pthread.h> 																		////
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>     //errno
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/mman.h>

#endif	

/***********************************************************************************************/
/**************************************Ttype****************************************************/
#if TPLATFORM == TWIN
typedef unsigned short				TUSHORT;
typedef signed __int64				TINT64;
typedef signed __int32				TINT32;
typedef signed __int16				TINT16;
typedef signed __int8				TINT8;
typedef unsigned __int64			TUINT64;
typedef unsigned __int32			TUINT32;
typedef unsigned __int16			TUINT16;
typedef unsigned __int8				TUINT8;
#else
typedef unsigned short				TUSHORT;
typedef int64_t						TINT64;
typedef int32_t						TINT32;
typedef int16_t						TINT16;
typedef int8_t						TINT8;
typedef uint64_t					TUINT64;
typedef uint32_t					TUINT32;
typedef uint16_t					TUINT16;
typedef uint8_t						TUINT8;
#endif

#define TSAFE_DELETE(x)				if (x){delete x; x = nullptr;}			
#define TSAFE_FREE(x)   			if (x){free(x); x = nullptr;}
#if defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )//Win
#ifdef __TEXPORTS__
#define TEXPORTS __declspec(dllexport)
#else
#define TEXPORTS __declspec(dllimport)
#endif
#else//Linux
#define  TEXPORTS
#endif
/**************************************|线程相关************************************************/
//#define  TTHREAD_MUTEXAutoLock(x)			std::mutex x;std::lock_guard<std::mutex> instcance(x);
#if TPLATFORM == TWIN																		////
#define  TTHREAD_MUTEX						CRITICAL_SECTION								////
#define  TTHREAD_INITMUTEX(x)				InitializeCriticalSection(&x);					////
#define  TTHREAD_FINITMUTEX(x)				DeleteCriticalSection(&x);						////
#define  TTHREAD_MUTEXLOCK(x)				EnterCriticalSection(&x);						////
#define  TTHREAD_MUTEXUNLOCK(x)				LeaveCriticalSection(&x);						////								
#define  TTHREAD_HDL						HANDLE											////
#define  TSLEEP(ms)							::Sleep(ms)

inline void winThreadJoin(ZTHREAD_HDL m_hdl_)
{
	DWORD exitCode;
	while (1)
	{
		if (GetExitCodeThread(m_hdl_, &exitCode) != 0)
		{
			if (exitCode != STILL_ACTIVE)
			{
				break;
			}
			else
			{
				//wait之前， 需要唤起线程， 防止线程处于挂起状态导致死等
				ResumeThread(m_hdl_);
				WaitForSingleObject(m_hdl_, INFINITE);
			}
		}
		else
		{
			break;
		}
	}

	CloseHandle(m_hdl_);
}
#defien  TTHREAD_JOIN(x)					threadJoin(x)
#else																						////
#define TTHREAD_MUTEX						pthread_mutex_t									////
#define TTHREAD_INITMUTEX(x)				pthread_mutex_init (&x, NULL)					////
#define TTHREAD_FINITMUTEX(x)				pthread_mutex_destroy(&x)						////
#define TTHREAD_MUTEXLOCK(x)				pthread_mutex_lock(&x)							////
#define TTHREAD_MUTEXUNLOCK(x)				pthread_mutex_unlock(&x)						////
#define TTHREAD_HDL							pthread_t										////
#define TTHREAD_JOIN(x)						pthread_join(x, NULL)
#define TSLEEP(ms)							struct timeval tval;\
											tval.tv_sec = ms / 1000;\
											tval.tv_usec = (ms * 1000) % 1000000;\
											select(0, NULL, NULL, NULL, &tval);
#endif																						////
/***********************************************************************************************/

#define STATIC_TCHECK(expr) { char strBuf[(expr) ? 1 : 0]; strBuf[0] = 0; };
#endif