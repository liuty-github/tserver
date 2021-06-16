#include "tEngine.h"


static tEngine*        g_pIns = nullptr;
static tThreadTask*    g_pThreadTaskIns = nullptr;
static tProccess*      g_pProccessIns = nullptr;
tEngine::tEngine()
{
}

tEngine::~tEngine()
{
}

void tEngine::initEngine()
{
    tConfig::getInstance()->initConfig("tserver.conf");
    tLog::getInstance()->ngx_log_init();
    g_pProccessIns = g_pProccessIns == nullptr ? new tProccess() : g_pProccessIns;

}

void tEngine::initModule()
{
    g_pThreadTaskIns = tThreadTask::getInstance();
}

tEngine* tEngine::getInstance()
{
    if(g_pIns == nullptr)
    {
        if(g_pIns == nullptr)
        {
            g_pIns = new tEngine();
        } 
    }
    return g_pIns;
}

tProccess* tEngine::getProccessIns()
{
    return g_pProccessIns;
}

tThreadTask* tEngine::getThreadTaskIns()
{
    return g_pThreadTaskIns;
}

