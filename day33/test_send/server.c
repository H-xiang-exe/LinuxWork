#include <func.h>

int main(int argc,char *argv[])
{
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
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(socketFd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t len=sizeof(struct sockaddr);
    int newFd=accept(socketFd,(struct sockaddr*)&client,&len);
    ERROR_CHECK(newFd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[1000]={0};
    int total=0;//记录发送的字节数
    while(1){
        ret=send(newFd,buf,sizeof(buf),0);
        ERROR_CHECK(ret,-1,"send");
        total+=ret;
        printf("total Byte=%d\n",total);
    }
    close(socketFd);
    return 0;
}

