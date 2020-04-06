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
    ret=bind(socketFd,(struct sockaddr *)&server,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    int new_fd;
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t len=sizeof(client);
    new_fd=accept(socketFd,(struct sockaddr*)&client,&len);
    ERROR_CHECK(new_fd,-1,"accept");
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[128]={0};
    recv(new_fd,buf,sizeof(buf),0);
    printf("I am server gets:%s\n",buf);
    char info[20]="I am fine.Thank you";
    send(new_fd,info,strlen(info),0);
    printf("%s\n",info);
    return 0;
}

