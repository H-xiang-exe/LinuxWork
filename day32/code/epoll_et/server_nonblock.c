#include <func.h>
int change_nonblock(int fd)//传描述符即可
{
    int status;
    status=fcntl(fd,F_GETFL);
    status=status|O_NONBLOCK;
    int ret=fcntl(fd,F_SETFL,status);
    ERROR_CHECK(ret,-1,"fcntl");
    return 0;
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);//ip地址+端口号
    int socketFd;//初始化一个socket->缓冲区 //初始值等于3，类似于文件描述符
    socketFd=socket(AF_INET,SOCK_STREAM,0);//绑定一个缓冲区
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));//主机端口字节序转网络字节序，字符串转换为整型数
    ser.sin_addr.s_addr=inet_addr(argv[1]);//点分十进制ip地址转换为网络字节序
    int ret;
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));//强制类型转换是为了向前兼容
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);//端口激活：监听
    int new_fd;//用来保存新建连接
    struct sockaddr_in client;//从内核拿出对方的socket信息
    char buf[10]={0};
    int readyFdNum;
    int epfd=epoll_create(1);
    struct epoll_event event,evs[3];
    event.data.fd=STDIN_FILENO;
    event.events=EPOLLIN;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    while(1){
        readyFdNum=epoll_wait(epfd,evs,3,-1);
        for(int i=0;i<readyFdNum;i++){
            if(evs[i].data.fd==socketFd){
                //有人连接
                bzero(&client,sizeof(client));
                socklen_t len=sizeof(client);
                new_fd=accept(socketFd,(struct sockaddr *)&client,&len);
                ERROR_CHECK(new_fd,-1,"accept");
                printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                change_nonblock(new_fd);
                event.data.fd=new_fd;
                event.events=EPOLLIN|EPOLLET;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
            }
            if(evs[i].data.fd==new_fd){
                while(1){
                    bzero(buf,sizeof(buf));
                    ret=recv(new_fd,buf,sizeof(buf)-1,0);//不读结尾的\0，读确定大小的数据，防止有时候消息结尾没有\0
                    if(!ret){
                        printf("byebye\n");
                        epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
                        close(new_fd);
                        break;
                    }else if(ret==-1&&errno==EAGAIN){//读空
                        printf("\n");
                        break;//读空了
                    }else{
                        printf("%s",buf);
                        //将换行符换到读空的时候再打印，实现一次消息
                        //一行打印的效果
                    }
                }
            }
            if(evs[i].data.fd==STDIN_FILENO){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                send(new_fd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(new_fd);
    close(socketFd);
    return 0;
}

