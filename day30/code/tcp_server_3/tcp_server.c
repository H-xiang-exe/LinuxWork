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
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);//端口激活：监听
    int new_fd;//用来保存新建连接
    struct sockaddr_in client;//从内核拿出对方的socket信息
    char buf[1000]={0};
    fd_set rdset;//多路转接模型 用于监控多个文件描述符
    int readyFdNum;
    FD_ZERO(&rdset);
    while(1){
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        printf("%d\n",__LINE__ );
        readyFdNum=select(10,&rdset,NULL,NULL,NULL);
        printf("%d\n",__LINE__ );
        if(readyFdNum>0){
            if(FD_ISSET(socketFd,&rdset)){
                printf("%d\n",__LINE__ );
                bzero(&client,sizeof(client));
                socklen_t len=sizeof(client);
                new_fd=accept(socketFd,(struct sockaddr *)&client,&len);
                ERROR_CHECK(new_fd,-1,"accept");
                printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                FD_SET(new_fd,&rdset);
            }
            printf("yyyyyyyyy\n");
            if(FD_ISSET(new_fd,&rdset)){
                printf("%d\n",__LINE__ );
                bzero(buf,sizeof(buf));
                ret=recv(new_fd,buf,sizeof(buf),0);
                printf("%d\n",ret);
                if(!ret){
                    printf("byebye\n");
                    FD_CLR(new_fd,&rdset);
                    close(new_fd);
                    continue;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                printf("%d\n",__LINE__ );
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(ret==0){
                    printf("server is over\n");
                    break;
                }
                send(new_fd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(new_fd);
    close(socketFd);
    return 0;
}

