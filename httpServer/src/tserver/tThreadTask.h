#include "tThread.h"
#ifndef __THREADTASK_H__
#define __THREADTASK_H__



class tMission//使用线程池委托的任务必须继承该类，实现proccess函数
{
public:
	tMission(){};
	virtual ~tMission(){};
	virtual void proccess() = 0;
};

typedef std::queue<tMission*>	MISSIONQUEUE;

class tMissionThread:public tThread
{
public:
	tMissionThread(TTHREAD_MUTEX& taskMutex, MISSIONQUEUE&mqueue):m_missionMutex(taskMutex),m_qDoingQueue(mqueue),m_bBusy(false),m_bDisused(false)
	{
		CreatThread();
		ThreadStart();
	}
	~tMissionThread(){DestroyThread();}
	void run();
	bool isBusy(){return m_bBusy;}
	bool isDisused(){return m_bDisused;}
	void isDisused(bool bFlag){m_bDisused = bFlag;}
	MISSIONQUEUE&	m_qDoingQueue;
	TTHREAD_MUTEX&	m_missionMutex;
	tMission*		m_pCurMission;
	bool			m_bBusy;
	bool			m_bDisused;
};
/***********************************tThreadTask************************************
说明					线程池类（单例类）
tThreadTask()			无参数构造函数
GetInstance()			返回该类的静态对象
addTask(void* pfunc)	添加任务至m_qMissionQueue任务队列中
入参：
pfunc					需要交给线程池执行的函数指针
返回值：				返回交给线程池后创建线程的ID

Remove(__int64 iID)		移除指定ID的线程（暂未实现）
run()					重载run。将任务从m_qMissionQueue取出并加入到m_vThreadPool开始
						执行，当执行完毕线程的状态为FINISH时，将任务移出线程池
**********************************************************************************/


class tThreadTask:public tThread
{
private:
	tThreadTask();
public:
	~tThreadTask();
	static tThreadTask* getInstance();
	bool	 			 initThreadTask(int minSize, int maxSize, int incSize);
	void			 			 createTaskThread(int size);
	void    			 addTask(tMission* pMission);
private:
	void    		 			 run();
	MISSIONQUEUE    			 m_qDoingQueue;
	MISSIONQUEUE	 			 m_qMissionQueue;
	std::vector<tMissionThread*> m_vThreadTask;
	TTHREAD_MUTEX    			 m_taskMutex;
	TTHREAD_MUTEX	 			 m_doingMissionMutex;
	int							 m_iMinSize;
	int							 m_iMaxSize;
	int							 m_iIncSize;
	
	
};

#endif