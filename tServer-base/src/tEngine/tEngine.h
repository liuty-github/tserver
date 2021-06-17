#ifndef  __TENGINE_H__
#define  __TENGINE_H__
#include "tDefine.h"
#include "tMemoryPool.h"
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
    TEXPORTS static tEngine* getInstance();
    TEXPORTS void            initEngine();
    TEXPORTS void            initModule();
    TEXPORTS tProccess*      getProccessIns();
    TEXPORTS tMemoryPool*    getMemoryPoolIns();
    TEXPORTS tThreadTask*    getThreadTaskIns();
};




#endif