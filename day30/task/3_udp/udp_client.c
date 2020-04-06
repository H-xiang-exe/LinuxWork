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
    char buf[128]={0};
    sendto(socketfd,"Are you hungry",15,0,(struct sockaddr*)&server,sizeof(struct sockaddr));
    recvfrom(socketfd,buf,sizeof(buf),0,NULL,NULL);
    printf("%s\n",buf);
    close(socketfd);
    return 0;
}

