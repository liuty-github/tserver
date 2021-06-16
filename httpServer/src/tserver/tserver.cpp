#include "tEngine.h"
#include "v2vhttp_conn.h"

#define MAX_FD 65535
#define MAX_EVENT_NUMBER 10000


extern void addfd(int epollfd, int fd, bool one_shot);
//从epoll删除文件描述符
extern void removefd(int epollfd, int fd);
//修改文件描述
extern void modfd(int epollfd, int fd, int ev);
//设置文件描述符非阻塞
extern void setnonblocking(int fd);
#define TENGINE     tEngine::getInstance()
#define TPROCCESS   tEngine::getInstance()->getProccessIns()
#define TTHREADTASK tEngine::getInstance()->getThreadTaskIns()


int main(int argc, char** argv)
{
    TENGINE->initEngine();
    TPROCCESS->initProccess(argc, argv);
    //if(TPROCCESS->usrDamon("tserver-master-proccess") != 0){return 0;}
    TENGINE->initModule();
    TTHREADTASK->initThreadTask(1, 5, 3);
    v2vhttp_conn* users = new v2vhttp_conn[200];


    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    //端口复用
    int reuse = -1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    //绑定
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    int port = 57777;
    address.sin_port = htons(port);
    bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    //监听
    listen(listenfd, 5);
    //epoll
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    addfd(epollfd, listenfd, false, false);
    v2vhttp_conn::m_epollfd = epollfd;
    while (true)
    {
        int num = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if(num < 0 && errno != EINTR){
            TLOGE("epoll failure\n");
            break;
        }
        for(int i = 0;i < num;++i){
            int sockfd = events[i].data.fd;
            if(sockfd == listenfd){
                //有客户端连接进来
                struct sockaddr_in client_address;
                socklen_t client_addrlen = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlen);
                if(v2vhttp_conn::m_user_count >= MAX_FD){
                    TLOGE("connect pull is full");
                    close(connfd);
                    continue;
                }
                //把新的客户端连接放到数组
                users[connfd].init(connfd, client_address);
            }
            else if(events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)){
                //对端断开
                TLOGE("对端断开或遇到错误");
                users[sockfd].close_conn();
            }
            else if(events[i].events & EPOLLIN){
                if(users[sockfd].read()){
                    //一次性读完所有数据放到线程池里执行
                    TTHREADTASK->addTask(&users[sockfd]);
                }
                else{
                    users[sockfd].close_conn();
                }
            }
            else if(events[i].events & EPOLLOUT){
                if(!users[sockfd].write()){
                    users[sockfd].close_conn();
                }
            }
        }
    }

    close(epollfd);
    close(listenfd);
    delete[] users;    

    return 0;
}