#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketfd;
    socketfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketfd,-1,"socket");
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_addr.s_addr=inet_addr(argv[1]);
    server.sin_port=htons(atoi(argv[2]));
    server.sin_family=AF_INET;
    int ret;
    ret=connect(socketfd,(struct sockaddr *)&server,sizeof(server));
    ERROR_CHECK(ret,-1,"connect");
    fd_set rdset;
    char buf[128]={0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(socketfd,&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        int readyNum=select(socketfd+1,&rdset,NULL,NULL,NULL);
        if(readyNum>0){
            if(FD_ISSET(socketfd,&rdset)){
                bzero(buf,sizeof(buf));
                ret=recv(socketfd,buf,sizeof(buf),0);
                if(!ret){
                    printf("connect is over\n");
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                send(socketfd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(socketfd);
    return 0;
}

