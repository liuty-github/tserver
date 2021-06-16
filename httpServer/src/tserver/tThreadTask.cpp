#include "tThreadTask.h"
#include "tLog.h"


static tThreadTask* g_pInstance = nullptr;
void tMissionThread::run()
{
	TTHREAD_MUTEXLOCK(m_missionMutex);
	if(m_qDoingQueue.empty())
	{
		TTHREAD_MUTEXUNLOCK(m_missionMutex);
		TSLEEP(10);
		return;
	}
	m_pCurMission = m_qDoingQueue.front();
	m_qDoingQueue.pop();
	TTHREAD_MUTEXUNLOCK(m_missionMutex);
	m_bBusy = true;
	m_pCurMission->proccess();
	//delete m_pCurMission;
	m_pCurMission = nullptr;
	m_bBusy = false;
}


tThreadTask::tThreadTask()
{
	TTHREAD_INITMUTEX(m_taskMutex);
	TTHREAD_INITMUTEX(m_doingMissionMutex);
	CreatThread();
	ThreadStart();
}


tThreadTask::~tThreadTask()
{
	DestroyThread();
	TTHREAD_FINITMUTEX(m_doingMissionMutex);
	TTHREAD_FINITMUTEX(m_taskMutex);
}

tThreadTask* tThreadTask::getInstance()
{
	if (g_pInstance == nullptr)
	{
		if (g_pInstance == nullptr)
		{
			g_pInstance = new tThreadTask();
		}
	}
	return g_pInstance;
}

bool tThreadTask::initThreadTask(int minSize, int maxSize, int incSize)
{
	m_iMinSize = minSize;
	m_iMaxSize = maxSize;
	m_iIncSize = incSize;
	createTaskThread(m_iMinSize);
}

void tThreadTask::createTaskThread(int size)
{
	for(int i = 0;i < size;++i)
	{
		m_vThreadTask.push_back(new tMissionThread(m_doingMissionMutex, m_qDoingQueue) );
	}
}

void tThreadTask::addTask(tMission* pMission)
{
	TTHREAD_MUTEXLOCK(m_taskMutex);
	m_qMissionQueue.push(pMission);
	TTHREAD_MUTEXUNLOCK(m_taskMutex);
}


void tThreadTask::run()
{
	TTHREAD_MUTEXLOCK(m_taskMutex);
	if(m_qMissionQueue.empty() == false)
	{
		TTHREAD_MUTEXLOCK(m_doingMissionMutex);
		while(m_qMissionQueue.empty() == false)
		{
			m_qDoingQueue.push(m_qMissionQueue.front());
			m_qMissionQueue.pop();
		}
		TTHREAD_MUTEXUNLOCK(m_doingMissionMutex);
	}
	TTHREAD_MUTEXUNLOCK(m_taskMutex);

	//缩减线程池
	int freeNum = 0;
	auto iter = m_vThreadTask.begin();
	for (; iter != m_vThreadTask.end(); ++iter)
	{
		if (!(*iter)->isBusy())
		{
			if ((*iter)->isDisused())
			{
				TSAFE_DELETE(*iter);
				m_vThreadTask.erase(iter);
				return;
			}
			else
			{
				if (freeNum > m_iMinSize)
				{
					(*iter)->isDisused(true);
				}
				else
				{
					freeNum++;
				}
			}
		}
	}
	//扩充线程池
	int ic = m_iMaxSize - (int)(m_vThreadTask.size());
	if ((!freeNum) && (ic > 0))
	{
		if (ic >= m_iIncSize)
		{
			TLOGW("create pool thread size: %d.", m_iIncSize);
			createTaskThread(m_iIncSize);
		}
		else
		{
			TLOGW("create pool thread size: %d.", ic);
			createTaskThread(ic);
		}
	}
	else if (!ic)
	{
		TLOGW("thread pool full: %d.", m_iMaxSize);
	}
	TSLEEP(50);
}
