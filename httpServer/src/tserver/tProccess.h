#ifndef  __tProccess_H__
#define  __tProccess_H__
#include "tDefine.h"


class tProccess
{
public:
    tProccess();
    
    ~tProccess();
    //了缓存环境变量和进程入参
    void   initProccess(int argc, char** argv);
    //设置父进程标题
    bool   setMasterTitle(const char* name);
    //设置子进程标题
    bool   setTitleName(const char* title);
    //设置守护进程,父进程返回0，子进程返回pid，失败返回-1
    pid_t  usrDamon(const char* pProccessName = nullptr);
    //fork一个子进程并设置进程名字为pname
    pid_t  usrFork(const char* pProccessName = nullptr);

    void   freeresource();

private:
    
};


#endif