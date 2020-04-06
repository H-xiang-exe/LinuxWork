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
    const char *p="I am shuaige";
    send(socketFd,p,strlen(p),0);
    return 0;
}

