#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_port=htons(atoi(argv[2]));
    server.sin_family=AF_INET;
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&server,sizeof(server));
    ERROR_CHECK(ret,-1,"accept");
    char info[20]="How are you";
    send(socketFd,info,strlen(info),0);
    printf("%s\n",info);
    char buf[128]={0};
    recv(socketFd,buf,sizeof(buf),0);
    printf("I am client gets:%s\n",buf);
    return 0;
}

