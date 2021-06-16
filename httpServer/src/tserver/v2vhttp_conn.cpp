#include "v2vhttp_conn.h"

int v2vhttp_conn::m_epollfd = 0;  //对所有连接共享epoll对象
std::atomic<int> v2vhttp_conn::m_user_count;//用户连接数

const char* doc_root = "/mnt/hgfs/E/SVN/picPassthrough/tuchuan/TServer/build";
const char* ok_200_title = "OK";
const char* error_400_title = "Bad Request";
const char* error_400_form = "Your request has bad syntax or is inherently impossible.\n";
const char* error_403_title = "Forbidden";
const char* error_403_form = "You do not have permission to get file from this server.\n";
const char* error_404_title = "Not Found";
const char* error_404_form = "The requested file was not found on this server .\n";
const char* error_500_title = "Internal Error";
const char* error_500_form = "There wa an unusual problem serving the requested file.\n";

//设置文件描述符非阻塞
void setnonblocking(int fd){
    int old_flag = fcntl(fd, F_GETFL);
    int new_flag = old_flag | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_flag);
}
//添加文件描述符到epoll
void addfd(int epollfd, int fd, bool one_shot, bool et_flag){
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLRDHUP;
    if(et_flag == true){
        event.events | EPOLLET;//设置边沿触发
    }
    if(one_shot){
        event.events | EPOLLONESHOT;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    //设置文件描述符为非阻塞
    setnonblocking(fd);
}
//从epoll删除文件描述符
void removefd(int epollfd, int fd){
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}
//修改文件描述
void modfd(int epollfd, int fd, int ev){
    epoll_event event;
    event.data.fd = fd;
    event.events = ev | EPOLLONESHOT |EPOLLRDHUP;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}


void v2vhttp_conn::init(int sockfd, const sockaddr_in& addr){
    m_sockfd = sockfd;
    m_address = addr;
    //端口复用
    int reuse = -1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    //添加到epoll对象中
    addfd(m_epollfd, sockfd, true);

    init();

    // 取得ip和端口号
    char infoip[20] = {0};
    sprintf(infoip, inet_ntoa(addr.sin_addr));
    TLOGI("receive a new connect,ip = %s, fd = %d",infoip, sockfd);
    m_user_count++;
}

void v2vhttp_conn::init(){
    m_checked_index = 0;
    m_start_line = 0;
    m_check_state = CHECK_STATE_REQUESTLINE;
    m_readindex = 0;
    m_write_idx = 0;
    m_url = 0;
    m_version = 0;
    m_method = GET;
    m_linger = false;
    m_host = 0;
    m_content_length = 0;
    m_file_address = 0;


    bzero(m_readbuf, READ_BUFFER_SIZE);
    bzero(m_write_buf, WRITE_BUFFER_SIZE);
    bzero(m_real_file, FILENAME_LEN);
    memset(&m_file_stat, 0, sizeof(m_file_stat));
}

//关闭连接
void v2vhttp_conn::close_conn(){
    if(m_sockfd != -1){
        removefd(m_epollfd, m_sockfd);
        m_sockfd = -1;
        m_user_count--;
    }
}
//非阻塞读
bool v2vhttp_conn::read(){
    if(m_readindex >= READ_BUFFER_SIZE){
        return false;
    }
    int bytes_read = 0;
    while (true)
    {
        bytes_read = recv(m_sockfd, m_readbuf + m_readindex, READ_BUFFER_SIZE - m_readindex, 0);
        if(bytes_read == -1){
            if(errno == EAGAIN || errno == EWOULDBLOCK){
                //没有数据
                break; 
            }
            return false;
        }
        else if(bytes_read == 0){
            //对方关闭连接
            return false;
        }
        m_readindex += bytes_read;
    }
    //TLOGD("读取到数据%s", m_readbuf);
    return true;
}
//非阻塞写
bool v2vhttp_conn::write(){
    int temp = 0;
    int bytes_have_send = 0;//已发送字节数
    int bytes_to_send = m_write_idx;//将要发送的字节

    if(bytes_to_send == 0){
        //将要发送的字节为0，这一次响应结束
        modfd(m_epollfd, m_sockfd, EPOLLIN);
        init();
        return true;
    }

    while(1){
        //分散写
        temp = writev(m_sockfd, m_iv, 2);
        if(temp <= -1){
            //如果tcp写缓冲区没有空间，则等待下一轮EPOLLOUT事件后再继续写
            if(errno == EAGAIN){
                modfd(m_epollfd, m_sockfd, EPOLLOUT);
                return true;
            }
            unmap();
            return false;
        }
    
        bytes_to_send -= temp;
        bytes_have_send += temp;
        if(bytes_to_send <= bytes_have_send){
            //发送的HTTP响应成功，根据HTTP请求中的Connection字段决定是否
            unmap();
            if(m_linger){
                init();
                modfd(m_epollfd, m_sockfd, EPOLLIN);
                return true;
            }
            else{
                modfd(m_epollfd, m_sockfd, EPOLLIN);
                return false;
            }
        }
    }
}

void v2vhttp_conn::proccess(){
    //解析http请求
    TLOGI("收到请求");
    HTTP_CODE read_ret =  proccess_read();
    if(read_ret == NO_REQUEST){
        modfd(m_epollfd, m_sockfd, EPOLLIN);
        return;
    }

    //生成响应
    bool write_ret = proccess_write( read_ret );
    if(!write_ret){
        close_conn();
    }
    modfd(m_epollfd, m_sockfd, EPOLLOUT);
}

bool v2vhttp_conn::proccess_write(HTTP_CODE ret){
    switch (ret)
    {
    case INTERNAL_ERROR:
    {
        add_status_line(500, error_500_title);
        add_headers( strlen(error_500_form) );
        if( !add_content(error_500_form) ){
            return false;
        }
    }
    break;
    case BAD_REQUEST:
    {
        add_status_line(500, error_400_title);
        add_headers( strlen(error_400_form) );
        if( !add_content(error_400_form) ){
            return false;
        }
    }
    break;
    case NO_RESOURCE:
    {
        add_status_line(500, error_404_title);
        add_headers( strlen(error_404_form) );
        if( !add_content(error_404_form) ){
            return false;
        }
    }
    break;
    case FORBIDDEN_REQUEST:
    {
        add_status_line(500, error_403_title);
        add_headers( strlen(error_403_form) );
        if( !add_content(error_403_form) ){
            return false;
        }
    }
    break;
    case FILE_REQUEST:
    {
        add_status_line(200, ok_200_title);
        add_headers(m_file_stat.st_size);
        m_iv[0].iov_base = m_write_buf;
        m_iv[0].iov_len = m_write_idx;
        m_iv[1].iov_base = m_file_address;
        m_iv[1].iov_len = m_file_stat.st_size;
        TLOGD("待发送数据:%s",m_write_buf);
        TLOGD("待发送文件:%s",m_file_address);
        return true;
    }
    break;
    default:
        return false;
    break;
    }
}

//解析HTTP请求，主状态机
v2vhttp_conn::HTTP_CODE v2vhttp_conn::proccess_read(){
    LINE_STATUS line_status = LINE_OK;
    HTTP_CODE ret = NO_REQUEST;
    char * text = nullptr;
    while( ((m_check_state == CHECK_STATE_CONTENT) && (line_status == LINE_OK))
        ||  (line_status = parse_line()) == LINE_OK ){
        text = get_line();
        m_start_line = m_checked_index;
        TLOGD("got 1 http line:%s", text);
        switch(m_check_state)
        {
            case CHECK_STATE_REQUESTLINE:
            {
                ret = parse_request_line(text);
                if(ret == BAD_REQUEST){
                    return ret;
                }
            }
            break;
            case CHECK_STATE_HEADER:
            {
                ret = parse_headers(text);
                if(ret == BAD_REQUEST){
                    return ret;
                }
                else if(ret == GET_REQUEST){
                    return do_request();
                }
                line_status = LINE_OPEN;
            }
            break;
            case CHECK_STATE_CONTENT:
            {
                ret = parse_content(text);
                if(ret == BAD_REQUEST){
                    return ret;
                }
                line_status = LINE_OPEN;
            }
            break;
            default:
            {
                return INTERNAL_ERROR;
            }
            break;
        }
    }
    return NO_REQUEST;
}

v2vhttp_conn::HTTP_CODE v2vhttp_conn::do_request(){
    strcpy(m_real_file, doc_root);
    int len = strlen(doc_root);
    strncpy(m_real_file + len, m_url, FILENAME_LEN - len - 1);
    if(stat(m_real_file, &m_file_stat) < 0){
        return NO_REQUEST;
    }
    if(!(m_file_stat.st_mode & S_IROTH)){
        return FORBIDDEN_REQUEST;
    }
    
    if( S_ISDIR(m_file_stat.st_mode) ){
        return BAD_REQUEST;
    }

    int fd = open(m_real_file, O_RDONLY);
    m_file_address = (char*)mmap(0, m_file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return FILE_REQUEST;
}

void v2vhttp_conn::unmap(){
    if(m_file_address){
        munmap(m_file_address, m_file_stat.st_size);
        m_file_address = 0;
    }
}

//解析请求,获取请求方法，目标URL，HTTP版本
v2vhttp_conn::HTTP_CODE v2vhttp_conn::parse_request_line(char* text){
    m_url = strpbrk(text, " \t");
    *m_url++ = '\0';
    char* method = text;
    if(strcasecmp(method, "GET") == 0 ){
        m_method = GET;
    }
    else{
        return BAD_REQUEST;
    }

    m_version = strpbrk(m_url, " \t");
    if(!m_version){
        return BAD_REQUEST;
    }
    *m_version++ = '\0';
    if(strcasecmp(m_version, "HTTP/1.1") != 0 ){
        return BAD_REQUEST;
    }

    if(strncasecmp(m_url, "http://", 7) == 0){
        m_url += 7;
        m_url = strchr(m_url, '/');
    }

    if(!m_url || m_url[0] != '/'){
        return BAD_REQUEST;
    }

    m_check_state = CHECK_STATE_HEADER;
    return NO_REQUEST;
}
//解析请求头
v2vhttp_conn::HTTP_CODE v2vhttp_conn::parse_headers(char* text){
    if(text[0] == '\0'){
        if(m_content_length != 0){
            m_check_state = CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }
        return GET_REQUEST;
    }
    else if(strncasecmp(text, "Connection:", 11) == 0){
        text += 11;
        text += strspn(text, " \t");
        if(strcasecmp(text, "keep-alive") == 0){
            m_linger = true;
        }
    }
    else if(strncasecmp(text, "Host:", 5) == 0){
        text += 5;
        text += strspn(text, " \t");
        m_host = text;
    }
    else{
        //TLOGE("unknow header %s", text);
    }
    return NO_REQUEST;
}
//解析请求体,m_content_length是后加的
v2vhttp_conn::HTTP_CODE v2vhttp_conn::parse_content(char* text){
    if(m_readindex >= (m_content_length + m_checked_index)){
        text[m_content_length] = '\0';
        return GET_REQUEST;
    }
    return NO_REQUEST;
}
//解析一行，判断依据\r\n
v2vhttp_conn::LINE_STATUS v2vhttp_conn::parse_line(){
    char temp;
    for(;m_checked_index < m_readindex;++m_checked_index){
        temp = m_readbuf[m_checked_index];
        if(temp == '\r'){
            if( (m_checked_index + 1) == m_readindex ){
                return LINE_OPEN;
            }
            else if( m_readbuf[m_checked_index + 1] == '\n' ){
                m_readbuf[m_checked_index++] = '\0';
                m_readbuf[m_checked_index++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
        else if(temp == '\n'){
            if( (m_checked_index > 1) && (m_readbuf[m_checked_index - 1] == '\r') ){
                m_readbuf[m_checked_index - 1] = '\0';
                m_readbuf[m_checked_index++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
        //return LINE_OPEN;
    }
    return LINE_OK;
}

bool v2vhttp_conn::add_response(const char* format, ...){
    if(!m_write_idx >= WRITE_BUFFER_SIZE){
        return false;
    }
    va_list arg_list;
    va_start(arg_list, format);
    int len = vsnprintf(m_write_buf + m_write_idx, WRITE_BUFFER_SIZE - 1 - m_write_idx, format, arg_list);
    if(len >= (WRITE_BUFFER_SIZE - 1 - m_write_idx)){
        return false;
    }
    m_write_idx += len;
    va_end(arg_list);
    return true;
}

bool v2vhttp_conn::add_status_line(int status, const char* title){
    return add_response("%s %d %s\r\n", "HTTP/1.1", status, title);
}
bool v2vhttp_conn::add_headers(int content_len){
    add_content_length(content_len);
    add_content_type();
    add_linger();
    add_blank_line();
}

bool v2vhttp_conn::add_content_length(int content_len){
    return add_response("Content-Length: %d\n\r", content_len);
}

bool v2vhttp_conn::add_content_type(){
    //需要完善其它类型
    return add_response("Content-Type:%s\r\n", "text/html");
}

bool v2vhttp_conn::add_linger(){
    return add_response("Connection: %s\r\n", (m_linger == true) ? "keep-alive" : "close");
}

bool v2vhttp_conn::add_blank_line(){
    return add_response("%s", "\r\n");
}

bool v2vhttp_conn::add_content(const char* content){
    return add_response("%s\r\n", content);
}

bool v2vhttp_conn::add_setutf8(){
    return add_response("%s\r\n", "charset=UTF-8");
}