#include "tEngine/tEngine.h"





#define TENGINE     tEngine::getInstance()
#define TPROCCESS   tEngine::getInstance()->getProccessIns()
#define TMEMRYPOOL  tEngine::getInstance()->getMemoryPoolIns()
#define TTHREADTASK tEngine::getInstance()->getThreadTaskIns()

class usrmission:public tMission
{
public:
    usrmission(int i):m_i(i){};
    ~usrmission(){};
    void proccess()
    {
        for(int i = 0;i < 100;++i)
        {
            TLOGI("%d, proccess",m_i++);
            TSLEEP(10);
        }
    }
    int m_i;
};

int main(int argc, char** argv)
{
    TENGINE->initEngine();
    TPROCCESS->initProccess(argc, argv);
    if(TPROCCESS->usrDamon("tserver-master-proccess") != 0){return 0;}
    for(int i = 0;i < 1;++i)
    {
        char szname[40] = {0};
        sprintf(szname,"tserver-worker-proccess-no%d",i);
        TPROCCESS->usrFork(szname);
    }
    TENGINE->initModule();
    TMEMRYPOOL->initMemoryPool();
    TTHREADTASK->initThreadTask(1, 5, 3);
    TTHREADTASK->addTask(new usrmission(1));
    while(1){sleep(1);}
    getchar();
    return 0;
}