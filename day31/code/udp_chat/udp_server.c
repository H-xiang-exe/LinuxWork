#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);//ip地址+端口号
    int socketFd;//初始化一个socket->缓冲区
    socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
    //udp在bind时就激活了
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    //一定要先recvfrom
    char buf[128]={0};
    socklen_t addrlen=sizeof(struct sockaddr);
    recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr *)&client,&addrlen);
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    fd_set rdset;//多路转接模型 用于监控多个文件描述符
    int readyFdNum;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        readyFdNum=select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(readyFdNum>0){
            if(FD_ISSET(socketFd,&rdset)){
                bzero(buf,sizeof(buf));
                ret=recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&client,&addrlen);
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                sendto(socketFd,buf,strlen(buf)-1,0,(struct sockaddr*)&client,sizeof(client));
            }
        }
    }
    close(socketFd);
}
