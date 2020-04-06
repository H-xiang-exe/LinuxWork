#include "process_pool.h"

int main(int argc,char *argv[])
{
    if(argc!=3){
        printf("usuage:./server ip port\n");
        return -1;
    }
    char *ip=argv[1];
    char *port=argv[2];
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_addr.s_addr=inet_addr(ip);
    ser.sin_port=htons(atoi(port));
    ser.sin_family=AF_INET;
    socklen_t addrlen=sizeof(ser);
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&ser,addrlen);
    ERROR_CHECK(ret,-1,"connect");
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.data.fd=socketFd;
    event.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    event.data.fd=STDIN_FILENO;
    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    int readyFdNum;
    char buf[1000];
    do{
        ret=loadRequest(socketFd);
    }while(ret==-1);//密码输入错误需要重新输入信息以重新登录
    while(1){
        readyFdNum=epoll_wait(epfd,evs,2,-1);
        for(int i=0;i<readyFdNum;i++){
            if(evs[i].data.fd==socketFd){
                ret=recvInfo(socketFd);
                if(ret==-1){
                    goto end;
                }
            }
            if(evs[i].data.fd==STDIN_FILENO){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                sendInfo(socketFd,buf);
            }
        }
    }
end:
    close(socketFd);
    return 0;
}

