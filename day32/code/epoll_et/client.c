#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);//ip地址+端口号
    int socketFd;//初始化一个socket->缓冲区
    //初始值等于3，类似于文件描述符
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    //绑定一个缓冲区
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    //主机端口字节序转网络字节序，字符串转换为整型数
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    //点分十进制ip地址转换为网络字节序
    int ret;
    ret=connect(socketFd,(struct sockaddr *)&ser,sizeof(ser));
    //connect不阻塞，无人监听则connect失败，所以要先启动服务器端
    ERROR_CHECK(ret,-1,"connect");
    char buf[1000]={0};
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
                ret=recv(socketFd,buf,sizeof(buf),0);
                if(!ret){
                    printf("byebye\n");
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                send(socketFd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(socketFd);
    return 0;
}

