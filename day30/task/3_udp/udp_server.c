#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketfd;
    socketfd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketfd,-1,"socket");
    printf("socketfd=%d\n",socketfd);
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_port=htons(atoi(argv[2]));
    server.sin_family=AF_INET;
    int ret;
    ret=bind(socketfd,(struct sockaddr*)&server,sizeof(server));
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    char buf[128]={0};
    socklen_t addrlen=sizeof(struct sockaddr);
    recvfrom(socketfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&addrlen);
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    printf("%s\n",buf);
    sendto(socketfd,"I am hungry",11,0,(struct sockaddr*)&client,sizeof(struct sockaddr));
    close(socketfd);
    return 0;
}

