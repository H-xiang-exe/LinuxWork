#include <func.h>

int main(int argc,char *argv[])
{//服务端一直写，客户端不接受，查看服务端最大能向缓冲区写多少
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_family=AF_INET;
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&ser,sizeof(ser));
    ERROR_CHECK(ret,-1,"connect");
    while(1);
    return 0;
}

