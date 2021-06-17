#include "tLog.h"
#include "tConfig.h"
//全局量---------------------
//错误等级，和ngx_macro.h里定义的日志等级宏是一一对应关系

extern pid_t           g_curpid;

static u_char err_levels[][20]  = 
{
    {"stderr"},    //0：控制台错误
    {"emerg"},     //1：紧急
    {"alert"},     //2：警戒
    {"crit"},      //3：严重
    {"error"},     //4：错误
    {"warn"},      //5：警告
    {"notice"},    //6：注意
    {"info"},      //7：信息
    {"debug"}      //8：调试
};




void tLog::ngx_log_stderr(int err, const char *fmt, ...)
{    
    va_list args;                        //创建一个va_list类型变量
    u_char  errstr[NGX_MAX_ERROR_STR+1]; //2048  -- ************  +1是我自己填的，感谢官方写法有点小瑕疵，所以动手调整一下
    u_char  *p,*last;

    memset(errstr,0,sizeof(errstr));     //我个人加的，这块有必要加，至少在va_end处理之前有必要，否则字符串没有结束标记不行的；***************************

    last = errstr + NGX_MAX_ERROR_STR;        //last指向整个buffer最后去了【指向最后一个有效位置的后面也就是非有效位】，作为一个标记，防止输出内容超过这么长,
                                                    //其实我认为这有问题，所以我才在上边errstr[NGX_MAX_ERROR_STR+1]; 给加了1
                                              //比如你定义 char tmp[2]; 你如果last = tmp+2，那么last实际指向了tmp[2]，而tmp[2]在使用中是无效的
                                                
    p = ngx_cpymem(errstr, "nginx: ", 7);     //p指向"nginx: "之后    
    
    va_start(args, fmt); //使args指向起始的参数
    p = ngx_vslprintf(p,last,fmt,args); //组合出这个字符串保存在errstr里
    va_end(args);        //释放args

    if (err)  //如果错误代码不是0，表示有错误发生
    {
        //错误代码和错误信息也要显示出来
        p = ngx_log_errno(p, last, err);
    }
    
    //若位置不够，那换行也要硬插入到末尾，哪怕覆盖到其他内容    
    if (p >= (last - 1))
    {
        p = (last - 1) - 1; //把尾部空格留出来，这里感觉nginx处理的似乎就不对 
                             //我觉得，last-1，才是最后 一个而有效的内存，而这个位置要保存\0，所以我认为再减1，这个位置，才适合保存\n
    }
    *p++ = '\n'; //增加个换行符    
    
    //往标准错误【一般是屏幕】输出信息    
    write(STDERR_FILENO,errstr,p - errstr); //三章七节讲过，这个叫标准错误，一般指屏幕

    if(ngx_log.fd > STDERR_FILENO) //如果这是个有效的日志文件，本条件肯定成立，此时也才有意义将这个信息写到日志文件
    {
        //因为上边已经把err信息显示出来了，所以这里就不要显示了，否则显示重复了
        err = 0;    //不要再次把错误信息弄到字符串里，否则字符串里重复了
        p--;*p = 0; //把原来末尾的\n干掉，因为到ngx_log_err_core中还会加这个\n 
        ngx_log_error_core(NGX_LOG_STDERR,err,__FILE__,__FUNCTION__,__LINE__,(const char *)errstr); 
    }    
    return;
}

//----------------------------------------------------------------------------------------------------------------------
//描述：给一段内存，一个错误编号，我要组合出一个字符串，形如：   (错误编号: 错误原因)，放到给的这段内存中去
//     这个函数我改造的比较多，和原始的nginx代码多有不同
//buf：是个内存，要往这里保存数据
//last：放的数据不要超过这里
//err：错误编号，我们是要取得这个错误编号对应的错误字符串，保存到buffer中
u_char * tLog::ngx_log_errno(u_char *buf, u_char *last, int err)
{
    //以下代码是我自己改造，感觉作者的代码有些瑕疵
    char *perrorinfo = strerror(err); //根据资料不会返回NULL;
    size_t len = strlen(perrorinfo);

    //然后我还要插入一些字符串： (%d:)  
    char leftstr[10] = {0}; 
    sprintf(leftstr," (%d: ",err);
    size_t leftlen = strlen(leftstr);

    char rightstr[] = ") "; 
    size_t rightlen = strlen(rightstr);
    
    size_t extralen = leftlen + rightlen; //左右的额外宽度
    if ((buf + len + extralen) < last)
    {
        //保证整个我装得下，我就装，否则我全部抛弃 ,nginx的做法是 如果位置不够，就硬留出50个位置【哪怕覆盖掉以往的有效内容】，也要硬往后边塞，这样当然也可以；
        buf = ngx_cpymem(buf, leftstr, leftlen);
        buf = ngx_cpymem(buf, perrorinfo, len);
        buf = ngx_cpymem(buf, rightstr, rightlen);
    }
    return buf;
}

//----------------------------------------------------------------------------------------------------------------------
//往日志文件中写日志，代码中有自动加换行符，所以调用时字符串不用刻意加\n；
//    日过定向为标准错误，则直接往屏幕上写日志【比如日志文件打不开，则会直接定位到标准错误，此时日志就打印到屏幕上，参考ngx_log_init()】
//level:一个等级数字，我们把日志分成一些等级，以方便管理、显示、过滤等等，如果这个等级数字比配置文件中的等级数字"LogLevel"大，那么该条信息不被写到日志文件中
//err：是个错误代码，如果不是0，就应该转换成显示对应的错误信息,一起写到日志文件中，
//ngx_log_error_core(5,8,"这个XXX工作的有问题,显示的结果是=%s","YYYY");
void tLog::ngx_log_error_core(int level,  int err, const char* filename, const char* function, unsigned int codeline, const char *fmt, ...)
{
    u_char  *last;
    u_char  errstr[NGX_MAX_ERROR_STR+1];   //这个+1也是我放入进来的，本函数可以参考ngx_log_stderr()函数的写法；

    memset(errstr,0,sizeof(errstr));  
    last = errstr + NGX_MAX_ERROR_STR;   
    
    struct timeval   tv;
    struct tm        tm;
    time_t           sec;   //秒
    u_char           *p;    //指向当前要拷贝数据到其中的内存位置
    va_list          args;

    memset(&tv,0,sizeof(struct timeval));    
    memset(&tm,0,sizeof(struct tm));

    gettimeofday(&tv, NULL);     //获取当前时间，返回自1970-01-01 00:00:00到现在经历的秒数【第二个参数是时区，一般不关心】        

    sec = tv.tv_sec;             //秒
    localtime_r(&sec, &tm);      //把参数1的time_t转换为本地时间，保存到参数2中去，带_r的是线程安全的版本，尽量使用
    tm.tm_mon++;                 //月份要调整下正常
    tm.tm_year += 1900;          //年份要调整下才正常
    
    u_char strcurrtime[40]={0};  //先组合出一个当前时间字符串，格式形如：2019/01/08 19:57:11
    ngx_slprintf(strcurrtime,  
                    (u_char *)-1,                       //若用一个u_char *接一个 (u_char *)-1,则 得到的结果是 0xffffffff....，这个值足够大
                    "%4d/%02d/%02d %02d:%02d:%02d",     //格式是 年/月/日 时:分:秒
                    tm.tm_year, tm.tm_mon,
                    tm.tm_mday, tm.tm_hour,
                    tm.tm_min, tm.tm_sec);
    p = ngx_cpymem(errstr,strcurrtime,strlen((const char *)strcurrtime));  //日期增加进来，得到形如：     2019/01/08 20:26:07
    p = ngx_slprintf(p, last, " [%s] [PID %d] [%s+%d %s] ", err_levels[level], g_curpid, filename, codeline, function);                //日志级别增加进来，得到形如：  2019/01/08 20:26:07 [crit] 
    //p = ngx_slprintf(p, last, "%P: ",ngx_pid);                             //支持%P格式，进程id增加进来，得到形如：   2019/01/08 20:50:15 [crit] 2037:

    va_start(args, fmt);                     //使args指向起始的参数
    p = ngx_vslprintf(p, last, fmt, args);   //把fmt和args参数弄进去，组合出来这个字符串
    va_end(args);                            //释放args 

    if (err)  //如果错误代码不是0，表示有错误发生
    {
        //错误代码和错误信息也要显示出来
        p = ngx_log_errno(p, last, err);
    }
    //若位置不够，那换行也要硬插入到末尾，哪怕覆盖到其他内容
    if (p >= (last - 1))
    {
        p = (last - 1) - 1; //把尾部空格留出来，这里感觉nginx处理的似乎就不对 
                             //我觉得，last-1，才是最后 一个而有效的内存，而这个位置要保存\0，所以我认为再减1，这个位置，才适合保存\n
    }
    *p++ = '\n'; //增加个换行符       

    //这么写代码是图方便：随时可以把流程弄到while后边去；大家可以借鉴一下这种写法
    ssize_t   n;
    while(1) 
    {        
        if (level > ngx_log.log_level) 
        {
            //要打印的这个日志的等级太落后（等级数字太大，比配置文件中的数字大)
            //这种日志就不打印了
            break;
        }
        //磁盘是否满了的判断，先算了吧，还是由管理员保证这个事情吧； 

        //写日志文件        
        n = write(ngx_log.fd,errstr,p - errstr);  //文件写入成功后，如果中途
        if (n == -1) 
        {
            //写失败有问题
            if(errno == ENOSPC) //写失败，且原因是磁盘没空间了
            {
                //磁盘没空间了
                //没空间还写个毛线啊
                //先do nothing吧；
            }
            else
            {
                //这是有其他错误，那么我考虑把这个错误显示到标准错误设备吧；
                if(ngx_log.fd != STDERR_FILENO) //当前是定位到文件的，则条件成立
                {
                    n = write(STDERR_FILENO,errstr,p - errstr);
                }
            }
        }
        break;
    } //end while    
    return;
}
static tLog* 	 g_logIns = nullptr;
tLog* tLog::getInstance()
{
    if(g_logIns == nullptr)
    {
        if(g_logIns == nullptr)
        {
            g_logIns = new tLog();
        }
    }
    return g_logIns;
}
//----------------------------------------------------------------------------------------------------------------------
//描述：日志初始化，就是把日志文件打开 ，注意这里边涉及到释放的问题，如何解决？
void tLog::ngx_log_init()
{
    u_char *plogname = NULL;
    size_t nlen;

    //从配置文件中读取和日志相关的配置信息
    tConfig *p_config = tConfig::getInstance();
    plogname = (u_char *)p_config->getString("Log");
    if(plogname == NULL)
    {
        //没读到，就要给个缺省的路径文件名了
        plogname = (u_char *) NGX_ERROR_LOG_PATH; //"logs/error.log" ,logs目录需要提前建立出来
    }
    ngx_log.log_level = p_config->getIntDefault("LogLevel",NGX_LOG_NOTICE);//缺省日志等级为6【注意】 ，如果读失败，就给缺省日志等级
    //nlen = strlen((const char *)plogname);

    //只写打开|追加到末尾|文件不存在则创建【这个需要跟第三参数指定文件访问权限】
    //mode = 0644：文件访问权限， 6: 110    , 4: 100：     【用户：读写， 用户所在组：读，其他：读】 老师在第三章第一节介绍过
    //ngx_log.fd = open((const char *)plogname,O_WRONLY|O_APPEND|O_CREAT|O_DIRECT,0644);   //绕过内和缓冲区，write()成功则写磁盘必然成功，但效率可能会比较低；
    ngx_log.fd = open((const char *)plogname,O_WRONLY|O_APPEND|O_CREAT,0644);  
    if (ngx_log.fd == -1)  //如果有错误，则直接定位到 标准错误上去 
    {
        ngx_log_stderr(errno,"[alert] could not open error log file: open() \"%s\" failed", plogname);
        ngx_log.fd = STDERR_FILENO; //直接定位到标准错误去了        
    } 
    return;
}

//----------------------------------------------------------------------------------------------------------------------
//和上边的ngx_snprintf非常类似
u_char * tLog::ngx_snprintf(u_char *buf, size_t max, const char *fmt, ...)   //类printf()格式化函数，比较安全，max指明了缓冲区结束位置
{
    u_char   *p;
    va_list   args;

    va_start(args, fmt);
    p = ngx_vslprintf(buf, buf + max, fmt, args);
    va_end(args);
    return p;
}

//----------------------------------------------------------------------------------------------------------------------
//对于 nginx 自定义的数据结构进行标准格式化输出,就像 printf,vprintf 一样，我们顺道学习写这类函数到底内部是怎么实现的
//例如，给进来一个 "abc = %d",13   ,最终buf里得到的应该是   abc=13 这种结果
//buf：往这里放数据
//last：放的数据不要超过这里
//fmt：以这个为首的一系列可变参数
//支持的格式： %d【%Xd/%xd】:数字,    %s:字符串      %f：浮点,  %P：pid_t
    //对于：ngx_log_stderr(0, "invalid option: \"%s\",%d", "testinfo",123);
       //fmt = "invalid option: \"%s\",%d"
       //args = "testinfo",123
u_char *tLog::ngx_vslprintf(u_char *buf, u_char *last,const char *fmt,va_list args)
{
    //比如说你要调用ngx_log_stderr(0, "invalid option: \"%s\"", argv[i]);，那么这里的fmt就应该是:   invalid option: "%s"
    //printf("fmt = %s\n",fmt);
    
    u_char     zero;

    /*
    #ifdef _WIN64
        typedef unsigned __int64  uintptr_t;
    #else
        typedef unsigned int uintptr_t;
    #endif
    */
    uintptr_t  width,sign,hex,frac_width,scale,n;  //临时用到的一些变量

    int64_t    i64;   //保存%d对应的可变参
    uint64_t   ui64;  //保存%ud对应的可变参，临时作为%f可变参的整数部分也是可以的 
    u_char     *p;    //保存%s对应的可变参
    double     f;     //保存%f对应的可变参
    uint64_t   frac;  //%f可变参数,根据%.2f等，取得小数部分的2位后的内容；
    

    while (*fmt && buf < last) //每次处理一个字符，处理的是  "invalid option: \"%s\",%d" 中的字符
    {
        if (*fmt == '%')  //%开头的一般都是需要被可变参数 取代的 
        {
            //-----------------变量初始化工作开始-----------------
            //++fmt是先加后用，也就是fmt先往后走一个字节位置，然后再判断该位置的内容
            zero  = (u_char) ((*++fmt == '0') ? '0' : ' ');  //判断%后边接的是否是个'0',如果是zero = '0'，否则zero = ' '，一般比如你想显示10位，而实际数字7位，前头填充三个字符，就是这里的zero用于填充
                                                                //ngx_log_stderr(0, "数字是%010d", 12); 
                                                                
            width = 0;                                       //格式字符% 后边如果是个数字，这个数字最终会弄到width里边来 ,这东西目前只对数字格式有效，比如%d,%f这种
            sign  = 1;                                       //显示的是否是有符号数，这里给1，表示是有符号数，除非你 用%u，这个u表示无符号数 
            hex   = 0;                                       //是否以16进制形式显示(比如显示一些地址)，0：不是，1：是，并以小写字母显示a-f，2：是，并以大写字母显示A-F
            frac_width = 0;                                  //小数点后位数字，一般需要和%.10f配合使用，这里10就是frac_width；
            i64 = 0;                                         //一般用%d对应的可变参中的实际数字，会保存在这里
            ui64 = 0;                                        //一般用%ud对应的可变参中的实际数字，会保存在这里    
            
            //-----------------变量初始化工作结束-----------------

            //这个while就是判断%后边是否是个数字，如果是个数字，就把这个数字取出来，比如%16，最终这个循环就能够把16取出来弄到width里边去
            //%16d 这里最终width = 16;
            while (*fmt >= '0' && *fmt <= '9')  //如果%后边接的字符是 '0' --'9'之间的内容   ，比如  %16这种；   
            {
                //第一次 ：width = 1;  第二次 width = 16，所以整个width = 16；
                width = width * 10 + (*fmt++ - '0');
            }

            for ( ;; ) //一些特殊的格式，我们做一些特殊的标记【给一些变量特殊值等等】
            {
                switch (*fmt)  //处理一些%之后的特殊字符
                {
                case 'u':       //%u，这个u表示无符号
                    sign = 0;   //标记这是个无符号数
                    fmt++;      //往后走一个字符
                    continue;   //回到for继续判断

                case 'X':       //%X，X表示十六进制，并且十六进制中的A-F以大写字母显示，不要单独使用，一般是%Xd
                    hex = 2;    //标记以大写字母显示十六进制中的A-F
                    sign = 0;
                    fmt++;
                    continue;
                case 'x':       //%x，x表示十六进制，并且十六进制中的a-f以小写字母显示，不要单独使用，一般是%xd
                    hex = 1;    //标记以小写字母显示十六进制中的a-f
                    sign = 0;
                    fmt++;
                    continue;

                case '.':       //其后边必须跟个数字，必须与%f配合使用，形如 %.10f：表示转换浮点数时小数部分的位数，比如%.10f表示转换浮点数时，小数点后必须保证10位数字，不足10位则用0来填补；
                    fmt++;      //往后走一个字符，后边这个字符肯定是0-9之间，因为%.要求接个数字先 
                    while(*fmt >= '0' && *fmt <= '9')  //如果是数字，一直循环，这个循环最终就能把诸如%.10f中的10提取出来
                    {
                        frac_width = frac_width * 10 + (*fmt++ - '0'); 
                    } //end while(*fmt >= '0' && *fmt <= '9') 
                    break;

                default:
                    break;                
                } //end switch (*fmt) 
                break;
            } //end for ( ;; )

            switch (*fmt) 
            {
            case '%': //只有%%时才会遇到这个情形，本意是打印一个%，所以
                *buf++ = '%';
                fmt++;
                continue;
        
            case 'd': //显示整型数据，如果和u配合使用，也就是%ud,则是显示无符号整型数据
                if (sign)  //如果是有符号数
                {
                    i64 = (int64_t) va_arg(args, int);  //va_arg():遍历可变参数，var_arg的第二个参数表示遍历的这个可变的参数的类型
                }
                else //如何是和 %ud配合使用，则本条件就成立
                {
                    ui64 = (uint64_t) va_arg(args, u_int);    
                }
                break;  //这break掉，直接跳道switch后边的代码去执行,这种凡是break的，都不做fmt++;  *********************【switch后仍旧需要进一步处理】

             case 'i': //转换ngx_int_t型数据，如果用%ui，则转换的数据类型是ngx_uint_t  
                if (sign) 
                {
                    i64 = (int64_t) va_arg(args, intptr_t);
                } 
                else 
                {
                    ui64 = (uint64_t) va_arg(args, uintptr_t);
                }

                //if (max_width) 
                //{
                //    width = NGX_INT_T_LEN;
                //}

                break;    

            case 'L':  //转换int64j型数据，如果用%uL，则转换的数据类型是uint64 t
                if (sign)
                {
                    i64 = va_arg(args, int64_t);
                } 
                else 
                {
                    ui64 = va_arg(args, uint64_t);
                }
                break;

            case 'p':  
                ui64 = (uintptr_t) va_arg(args, void *); 
                hex = 2;    //标记以大写字母显示十六进制中的A-F
                sign = 0;   //标记这是个无符号数
                zero = '0'; //前边0填充
                width = 2 * sizeof(void *);
                break;

            case 's': //一般用于显示字符串
                p = va_arg(args, u_char *); //va_arg():遍历可变参数，var_arg的第二个参数表示遍历的这个可变的参数的类型

                while (*p && buf < last)  //没遇到字符串结束标记，并且buf值够装得下这个参数
                {
                    *buf++ = *p++;  //那就装，比如  "%s"    ，   "abcdefg"，那abcdefg都被装进来
                }
                
                fmt++;
                continue; //重新从while开始执行 

            case 'P':  //转换一个pid_t类型
                i64 = (int64_t) va_arg(args, pid_t);
                sign = 1;
                break;

            case 'f': //一般 用于显示double类型数据，如果要显示小数部分，则要形如 %.5f  
                f = va_arg(args, double);  //va_arg():遍历可变参数，var_arg的第二个参数表示遍历的这个可变的参数的类型
                if (f < 0)  //负数的处理
                {
                    *buf++ = '-'; //单独搞个负号出来
                    f = -f; //那这里f应该是正数了!
                }
                //走到这里保证f肯定 >= 0【不为负数】
                ui64 = (int64_t) f; //正整数部分给到ui64里
                frac = 0;

                //如果要求小数点后显示多少位小数
                if (frac_width) //如果是%d.2f，那么frac_width就会是这里的2
                {
                    scale = 1;  //缩放从1开始
                    for (n = frac_width; n; n--) 
                    {
                        scale *= 10; //这可能溢出哦
                    }

                    //把小数部分取出来 ，比如如果是格式    %.2f   ，对应的参数是12.537
                    // (uint64_t) ((12.537 - (double) 12) * 100 + 0.5);  
                                //= (uint64_t) (0.537 * 100 + 0.5)  = (uint64_t) (53.7 + 0.5) = (uint64_t) (54.2) = 54
                    frac = (uint64_t) ((f - (double) ui64) * scale + 0.5);   //取得保留的那些小数位数，【比如  %.2f   ，对应的参数是12.537，取得的就是小数点后的2位四舍五入，也就是54】
                                                                             //如果是"%.6f", 21.378，那么这里frac = 378000

                    if (frac == scale)   //进位，比如    %.2f ，对应的参数是12.999，那么  = (uint64_t) (0.999 * 100 + 0.5)  = (uint64_t) (99.9 + 0.5) = (uint64_t) (100.4) = 100
                                          //而此时scale == 100，两者正好相等
                    {
                        ui64++;    //正整数部分进位
                        frac = 0;  //小数部分归0
                    }
                } //end if (frac_width)

                //正整数部分，先显示出来
                buf = ngx_sprintf_num(buf, last, ui64, zero, 0, width); //把一个数字 比如“1234567”弄到buffer中显示

                if (frac_width) //指定了显示多少位小数
                {
                    if (buf < last) 
                    {
                        *buf++ = '.'; //因为指定显示多少位小数，先把小数点增加进来
                    }
                    buf = ngx_sprintf_num(buf, last, frac, '0', 0, frac_width); //frac这里是小数部分，显示出来，不够的，前边填充'0'字符
                }
                fmt++;
                continue;  //重新从while开始执行

            //..................................
            //................其他格式符，逐步完善
            //..................................

            default:
                *buf++ = *fmt++; //往下移动一个字符
                continue; //注意这里不break，而是continue;而这个continue其实是continue到外层的while去了，也就是流程重新从while开头开始执行;
            } //end switch (*fmt) 
            
            //显示%d的，会走下来，其他走下来的格式日后逐步完善......

            //统一把显示的数字都保存到 ui64 里去；
            if (sign) //显示的是有符号数
            {
                if (i64 < 0)  //这可能是和%d格式对应的要显示的数字
                {
                    *buf++ = '-';  //小于0，自然要把负号先显示出来
                    ui64 = (uint64_t) -i64; //变成无符号数（正数）
                }
                else //显示正数
                {
                    ui64 = (uint64_t) i64;
                }
            } //end if (sign) 

            //把一个数字 比如“1234567”弄到buffer中显示，如果是要求10位，则前边会填充3个空格比如“   1234567”
            //注意第5个参数hex，是否以16进制显示，比如如果你是想以16进制显示一个数字则可以%Xd或者%xd，此时hex = 2或者1
            buf = ngx_sprintf_num(buf, last, ui64, zero, hex, width); 
            fmt++;
        }
        else  //当成正常字符，源【fmt】拷贝到目标【buf】里
        {
            //用fmt当前指向的字符赋给buf当前指向的位置，然后buf往前走一个字符位置，fmt当前走一个字符位置
            *buf++ = *fmt++;   //*和++优先级相同，结合性从右到左，所以先求的是buf++以及fmt++，但++是先用后加；
        } //end if (*fmt == '%') 
    }  //end while (*fmt && buf < last) 
    
    return buf;
}

//----------------------------------------------------------------------------------------------------------------------
//对于 nginx 自定义的数据结构进行标准格式化输出,就像 printf,vprintf 一样，我们顺道学习写这类函数到底内部是怎么实现的
//该函数只不过相当于针对ngx_vslprintf()函数包装了一下，所以，直接研究ngx_vslprintf()即可
u_char *tLog::ngx_slprintf(u_char *buf, u_char *last, const char *fmt, ...) 
{
    va_list   args;
    u_char   *p;

    va_start(args, fmt); //使args指向起始的参数
    p = ngx_vslprintf(buf, last, fmt, args);
    va_end(args);        //释放args   
    return p;
}

u_char * tLog::ngx_sprintf_num(u_char *buf, u_char *last, uint64_t ui64, u_char zero, uintptr_t hexadecimal, uintptr_t width)
{
    //temp[21]
    u_char      *p, temp[NGX_INT64_LEN + 1];   //#define NGX_INT64_LEN   (sizeof("-9223372036854775808") - 1)     = 20   ，注意这里是sizeof是包括末尾的\0，不是strlen；             
    size_t      len;
    uint32_t    ui32;

    static u_char   hex[] = "0123456789abcdef";  //跟把一个10进制数显示成16进制有关，换句话说和  %xd格式符有关，显示的16进制数中a-f小写
    static u_char   HEX[] = "0123456789ABCDEF";  //跟把一个10进制数显示成16进制有关，换句话说和  %Xd格式符有关，显示的16进制数中A-F大写

    p = temp + NGX_INT64_LEN; //NGX_INT64_LEN = 20,所以 p指向的是temp[20]那个位置，也就是数组最后一个元素位置

    if (hexadecimal == 0)  
    {
        if (ui64 <= (uint64_t) NGX_MAX_UINT32_VALUE)   //NGX_MAX_UINT32_VALUE :最大的32位无符号数：十进制是‭4294967295‬
        {
            ui32 = (uint32_t) ui64; //能保存下
            do  //这个循环能够把诸如 7654321这个数字保存成：temp[13]=7,temp[14]=6,temp[15]=5,temp[16]=4,temp[17]=3,temp[18]=2,temp[19]=1
                  //而且的包括temp[0..12]以及temp[20]都是不确定的值
            {
                *--p = (u_char) (ui32 % 10 + '0');  //把屁股后边这个数字拿出来往数组里装，并且是倒着装：屁股后的也往数组下标大的位置装；
            }
            while (ui32 /= 10); //每次缩小10倍等于去掉屁股后边这个数字
        }
        else
        {
            do 
            {
                *--p = (u_char) (ui64 % 10 + '0');
            } while (ui64 /= 10); //每次缩小10倍等于去掉屁股后边这个数字
        }
    }
    else if (hexadecimal == 1)  //如果显示一个十六进制数字，格式符为：%xd，则这个条件成立，要以16进制数字形式显示出来这个十进制数,a-f小写
    {
        //比如我显示一个1,234,567【十进制数】，他对应的二进制数实际是 12 D687 ，那怎么显示出这个12D687来呢？
        do 
        {            
            //0xf就是二进制的1111,大家都学习过位运算，ui64 & 0xf，就等于把 一个数的最末尾的4个二进制位拿出来；
            //ui64 & 0xf  其实就能分别得到 这个16进制数也就是 7,8,6,D,2,1这个数字，转成 (uint32_t) ，然后以这个为hex的下标，找到这几个数字的对应的能够显示的字符；
            *--p = hex[(uint32_t) (ui64 & 0xf)];    
        } while (ui64 >>= 4);    //ui64 >>= 4     --->   ui64 = ui64 >> 4 ,而ui64 >> 4是啥，实际上就是右移4位，就是除以16,因为右移4位就等于移动了1111；
                                 //相当于把该16进制数的最末尾一位干掉，原来是 12 D687, >> 4后是 12 D68，如此反复，最终肯定有=0时导致while不成立退出循环
                                  //比如 1234567 / 16 = 77160(0x12D68) 
                                  // 77160 / 16 = 4822(0x12D6)
    } 
    else // hexadecimal == 2    //如果显示一个十六进制数字，格式符为：%Xd，则这个条件成立，要以16进制数字形式显示出来这个十进制数,A-F大写
    { 
        //参考else if (hexadecimal == 1)，非常类似
        do 
        { 
            *--p = HEX[(uint32_t) (ui64 & 0xf)];
        } while (ui64 >>= 4);
    }

    len = (temp + NGX_INT64_LEN) - p;  //得到这个数字的宽度，比如 “7654321”这个数字 ,len = 7

    while (len++ < width && buf < last)  //如果你希望显示的宽度是10个宽度【%12f】，而实际想显示的是7654321，只有7个宽度，那么这里要填充5个0进去到末尾，凑够要求的宽度
    {
        *buf++ = zero;  //填充0进去到buffer中（往末尾增加），比如你用格式  
                                          //ngx_log_stderr(0, "invalid option: %10d\n", 21); 
                                          //显示的结果是：nginx: invalid option:         21  ---21前面有8个空格，这8个弄个，就是在这里添加进去的；
    }
    
    len = (temp + NGX_INT64_LEN) - p; //还原这个len，也就是要显示的数字的实际宽度【因为上边这个while循环改变了len的值】
    //现在还没把实际的数字比如“7654321”往buf里拷贝呢，要准备拷贝

    //如下这个等号是我加的【我认为应该加等号】，nginx源码里并没有加;***********************************************
    if((buf + len) >= last)   //发现如果往buf里拷贝“7654321”后，会导致buf不够长【剩余的空间不够拷贝整个数字】
    {
        len = last - buf; //剩余的buf有多少我就拷贝多少
    }

    return ngx_cpymem(buf, p, len); //把最新buf返回去；
}