#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);//ip地址+端口号
    int socketFd;//初始化一个socket->缓冲区
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);//端口激活：监听
    int new_fd;//用来保存新建连接
    struct sockaddr_in client;//从内核拿出对方的socket信息
    bzero(&client,sizeof(client));
    socklen_t len=sizeof(client);
    new_fd=accept(socketFd,(struct sockaddr *)&client,&len);
    ERROR_CHECK(new_fd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[1000]={0};
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.data.fd=STDIN_FILENO;
    event.events=EPOLLIN;//监控标准输入是否可读
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=new_fd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdNum;
    while(1){
        readyFdNum=epoll_wait(epfd,evs,2,-1);
        for(int i=0;i<readyFdNum;i++){
            if(evs[i].data.fd==new_fd){
                bzero(buf,sizeof(buf));
                ret=recv(new_fd,buf,sizeof(buf),0);
                if(!ret){
                    printf("byebye\n");
                    goto end;
                }
                printf("%s\n",buf);
            }
            if(evs[i].data.fd==STDIN_FILENO){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                send(new_fd,buf,strlen(buf)-1,0);
            }
        }
    }
end:
    close(new_fd);
    close(socketFd);
    return 0;
}

