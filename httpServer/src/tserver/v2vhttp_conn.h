#include "tDefine.h"
#include "tThreadTask.h"
#include "tLog.h"
#ifndef __V2VHTTP_CONN_H__
#define __V2VHTTP_CONN_H__
#define READ_BUFFER_SIZE 2048
#define WRITE_BUFFER_SIZE 2048
#define FILENAME_LEN    300

class v2vhttp_conn:public tMission
{
public:
    /*
    状态机
    HTTP请求方法
    */
    enum METHOD {GET = 0, POST, HEAD, PUT, DELETE, TRACE, OPTIONS, CONNECT};
    /*
    解析客户端请求时，主状态机的状态
    CHECK_STATE_REQUESTLINE：当前正在分析请求行
    CHECK_STATE_HEADER：当前正在分析头部字段
    CHECK_STATE_CONTENT：当前正在解析请求体
    */
    enum CHECK_STATE {CHECK_STATE_REQUESTLINE = 0, CHECK_STATE_HEADER, CHECK_STATE_CONTENT};
    /*
    从状态机的三种可能状态，即行的读取状态，分别标识：
    1.读取到一个完整的行 2.行出错 3.行数据尚且不完整
    */
    enum LINE_STATUS {LINE_OK = 0, LINE_BAD, LINE_OPEN};
    /*
    服务器处理HTTP请求的可能结果，报文解析的结果
    NO_REQUEST              ：请求不完整，需要继续读取客户数据
    GET_REQUEST             ：标识获得了一个完整的客户请求
    BAD_REQUEST             ：标识客户请求语法错误
    NO_RESOURCE             ：标识服务器没有资源
    _FORBIDDEN_REQUEST      ：标识客户对资源没有足够的访问权限
    FILE_REQUEST            ：文件请求，获取文件成功
    INTERNAL_ERROR          ：标识服务器内部错误
    CLOSED_CONNECTION       ：标识客户端已经关闭连接了
    */
    enum HTTP_CODE {NO_REQUEST, GET_REQUEST, BAD_REQUEST, NO_RESOURCE, FORBIDDEN_REQUEST, FILE_REQUEST, INTERNAL_ERROR, CLOSED_CONNECTION};
public:
    v2vhttp_conn(){};
    ~v2vhttp_conn(){};

    void proccess();//处理客户端请求
    void init(int sockfd, const sockaddr_in& addr);
    void close_conn();//关闭连接
    bool read();//非阻塞读
    bool write();//非阻塞写

public:
    static int m_epollfd;  //对所有连接共享epoll对象
    static std::atomic<int> m_user_count;//用户连接数

private:
    void init();//初始化连接其余的信息
    bool proccess_write(HTTP_CODE ret);//根据HTTP请求，生成响应内容发送给客户端
    HTTP_CODE proccess_read();//解析HTTP请求
    HTTP_CODE parse_request_line(char* text);//解析请求首行
    HTTP_CODE parse_headers(char* text);//解析请求头
    HTTP_CODE parse_content(char* text);//解析请求体

    LINE_STATUS parse_line();
    inline char* get_line(){return m_readbuf + m_start_line;};
    HTTP_CODE do_request();

    bool add_response(const char* format, ...);
    bool add_status_line(int status, const char* title);
    bool add_headers(int content_len);
    bool add_content_length(int content_len);
    bool add_content_type();
    bool add_linger();
    bool add_blank_line();
    bool add_content(const char* content);
    bool add_setutf8();

    void unmap();

private:
    int         m_sockfd;   //该http连接的socket
    sockaddr_in m_address; //通信socket地址
    char        m_readbuf[READ_BUFFER_SIZE];//读缓冲区
    int         m_readindex;//读缓冲区中读入数据的最后一个位置
    char        m_write_buf[WRITE_BUFFER_SIZE];//写缓冲区
    int         m_write_idx;//写缓冲区写入位置

    int m_checked_index;//当前正在分析的自服在读缓冲区的位置
    int m_start_line;//当前正在解析的行的起始位置
    char* m_url;//请求目标文件的文件名
    char* m_version;//协议版本，只支持http1.1
    METHOD m_method;//请求方法
    char* m_host;//主机名
    bool m_linger;//HTTP请求是否要保持连接
    int m_content_length;
    char        m_real_file[FILENAME_LEN];
    struct stat m_file_stat;
    char*       m_file_address;
    struct iovec m_iv[2];//采用writec来执行

    CHECK_STATE m_check_state;//主状态机当前所处的状态
};
//epoll
//添加文件描述符到epoll
void addfd(int epollfd, int fd, bool one_shot, bool et_flag = true);
//从epoll删除文件描述符
void removefd(int epollfd, int fd);
//修改文件描述
void modfd(int epollfd, int fd, int ev);
//设置文件描述符非阻塞
void setnonblocking(int fd);
#endif