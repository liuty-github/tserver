#ifndef  __TENGINE_H__
#define  __TENGINE_H__
#include "tDefine.h"
#include "tThreadTask.h"
#include "tProccess.h"
#include "tConfig.h"
#include "tLog.h"



class tEngine
{
private:
    tEngine(/* args */);
    ~tEngine();
public:
    static tEngine* getInstance();
    void            initEngine();
    void            initModule();
    tProccess*      getProccessIns();
    tThreadTask*    getThreadTaskIns();
};




#endif