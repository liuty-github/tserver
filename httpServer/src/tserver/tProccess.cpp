#include "tProccess.h"
#include "tLog.h"
//和设置标题有关的全局量
size_t  g_argvneedmem=0;        //保存下这些argv参数所需要的内存大小
size_t  g_envneedmem=0;         //环境变量所占内存大小
int     g_os_argc;              //参数个数 
char    **g_os_argv;            //原始命令行参数数组,在main中会被赋值
char    *gp_envmem=NULL;        //指向自己分配的env环境变量的内存，在ngx_init_setproctitle()函数中会被分配内存
int     g_daemonized=0;         //守护进程标记，标记是否启用了守护进程模式，0：未启用，1：启用了
pid_t   g_curpid;

tProccess::tProccess()
{
    g_curpid = getpid();
}

tProccess::~tProccess()
{

}

void tProccess::initProccess(int argc, char** argv)
{
   //统计argv所占的内存
    g_argvneedmem = 0;
    int i = 0;
    for(i = 0; i < argc; i++)  //argv =  ./nginx -a -b -c asdfas
    {
        g_argvneedmem += strlen(argv[i]) + 1; //+1是给\0留空间。
    } 
    //统计环境变量所占的内存。注意判断方法是environ[i]是否为空作为环境变量结束标记
    for(i = 0; environ[i]; i++) 
    {
        g_envneedmem += strlen(environ[i]) + 1; //+1是因为末尾有\0,是占实际内存位置的，要算进来
    } //end for

    g_os_argc = argc;           //保存参数个数
    g_os_argv = (char **) argv; //保存参数指针

    //这里无需判断penvmen == NULL,有些编译器new会返回NULL，有些会报异常，但不管怎样，如果在重要的地方new失败了，你无法收场，让程序失控崩溃，助你发现问题为好； 
    gp_envmem = new char[g_envneedmem]; 
    memset(gp_envmem,0,g_envneedmem);  //内存要清空防止出现问题

    char *ptmp = gp_envmem;
    //把原来的内存内容搬到新地方来
    for (int i = 0; environ[i]; i++) 
    {
        size_t size = strlen(environ[i])+1 ; //不要拉下+1，否则内存全乱套了，因为strlen是不包括字符串末尾的\0的
        strcpy(ptmp,environ[i]);      //把原环境变量内容拷贝到新地方【新内存】
        environ[i] = ptmp;            //然后还要让新环境变量指向这段新内存
        ptmp += size;
    }
    return;
    
}

bool tProccess::setMasterTitle(const char* name)
{
    if(strlen(name) <= 1){return false;}
    size_t size;
    int    i;
    size = sizeof(name);  //注意我这里用的是sizeof，所以字符串末尾的\0是被计算进来了的
    size += g_argvneedmem;          //argv参数长度加进来    
    if(size < 1000) //长度小于这个，我才设置标题
    {
        char title[1000] = {0};
        strcpy(title,name); //"master process"
        strcat(title," ");  //跟一个空格分开一些，清晰    //"master process "
        for (i = 0; i < g_os_argc; i++)         //"master process ./nginx"
        {
            strcat(title,g_os_argv[i]);
        }//end for
        setTitleName(title); //设置标题
    }    
}

bool tProccess::setTitleName(const char* title)
{
    
    //判断title长度合法性
    size_t ititlelen = strlen(title); 
    if(ititlelen <= 1){return false;}
    //(2)计算总的原始的argv那块内存的总长度【包括各种参数】    
    size_t esy = g_argvneedmem + g_envneedmem; //argv和environ内存总和
    if( esy <= ititlelen)
    {
        //你标题多长啊，我argv和environ总和都存不下？注意字符串末尾多了个 \0，所以这块判断是 <=【也就是=都算存不下】
        return false;
    }

    //空间够保存标题的，够长，存得下，继续走下来    

    //(3)设置后续的命令行参数为空，表示只有argv[]中只有一个元素了，这是好习惯；防止后续argv被滥用，因为很多判断是用argv[] == NULL来做结束标记判断的;
    g_os_argv[1] = NULL;  

    //(4)把标题弄进来，注意原来的命令行参数都会被覆盖掉，不要再使用这些命令行参数,而且g_os_argv[1]已经被设置为NULL了
    char *ptmp = g_os_argv[0]; //让ptmp指向g_os_argv所指向的内存
    strcpy(ptmp,title);
    ptmp += ititlelen; //跳过标题

    //(5)把剩余的原argv以及environ所占的内存全部清0，否则会出现在ps的cmd列可能还会残余一些没有被覆盖的内容；
    size_t cha = esy - ititlelen;  //内存总和减去标题字符串长度(不含字符串末尾的\0)，剩余的大小，就是要memset的；
    memset(ptmp,0,cha);
    return true ;
    
}
    
pid_t tProccess::usrDamon(const char* pProccessName)
{
    pid_t result = fork();
    switch (result)
    {
    case -1:
        printf("usrDamon()中fork()失败!");
        return result;
    case 0:
        //子进程，走到这里设置进程名字，然后break向下执行;
        g_curpid = getpid();
        TLOGI("usrDamon success, proccess name = %s, pid = %d", pProccessName, g_curpid);
        setMasterTitle(pProccessName);
        break;
    default:
        //父进程以往 直接退出exit(0);现在希望回到主流程去释放一些资源
        printf("守护进程设置成功原进程退出~\n");
        freeresource();
        exit(0);
        return result;  //父进程直接返回result,应该为0；
    } 
    
    //脱离终端，终端关闭，将跟此子进程无关
    if (setsid() == -1)  
    {
        printf("usrDamon()中setsid()失败!");
        return -1;
    }

    //设置为0，不要让它来限制文件权限，以免引起混乱
    umask(0); 

    //打开黑洞设备，以读写方式打开
    int fd = open("/dev/null", O_RDWR);
    if (fd == -1) 
    {
        printf("usrDamon()中open(\"/dev/null\")失败!");        
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1) //先关闭STDIN_FILENO[这是规矩，已经打开的描述符，动他之前，先close]，类似于指针指向null，让/dev/null成为标准输入；
    {
        printf("usrDamon()中dup2(STDIN)失败!");        
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) //再关闭STDIN_FILENO，类似于指针指向null，让/dev/null成为标准输出；
    {
        printf("usrDamon()中dup2(STDOUT)失败!");
        return -1;
    }
    if (fd > STDERR_FILENO)  //fd应该是3，这个应该成立
     {
        if (close(fd) == -1)  //释放资源这样这个文件描述符就可以被复用；不然这个数字【文件描述符】会被一直占着；
        {
            printf("usrDamon()中close(fd)失败!");
            return -1;
        }
    }
    return result; //子进程返回pid
}

pid_t tProccess::usrFork(const char* pProccessName)
{
    pid_t pid = fork();
    if(pid == 0){
        setTitleName(pProccessName);
        g_curpid = getpid();
        TLOGI("usrFork success, proccess name = %s, pid = %d", pProccessName, g_curpid);
    }
    else if(pid == -1){
        TLOGE("usrFork failed");
    }
    return pid;
}

void tProccess::freeresource()
{
    //(1)对于因为设置可执行程序标题导致的环境变量分配的内存，我们应该释放
    if(gp_envmem)
    {
        delete []gp_envmem;
        gp_envmem = NULL;
    }

    //(2)关闭日志文件
    if(tLog::getInstance()->ngx_log.fd != STDERR_FILENO && tLog::getInstance()->ngx_log.fd != -1)  
    {        
        close(tLog::getInstance()->ngx_log.fd); //不用判断结果了
        tLog::getInstance()->ngx_log.fd = -1; //标记下，防止被再次close吧        
    }
}