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
    ret=bind(socketfd,(struct sockaddr*)&server,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(socketfd,10);
    struct sockaddr_in client_msg;
    bzero(&client_msg,sizeof(client_msg));
    socklen_t len=sizeof(client_msg);
    int msg_fd=accept(socketfd,(struct sockaddr *)&client_msg,&len);
    ERROR_CHECK(msg_fd,-1,"accept");
    printf("client ip=%s,client msg port=%d\n",inet_ntoa(client_msg.sin_addr),ntohs(client_msg.sin_port));
    fd_set rdset;
    char buf[128]={0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(msg_fd,&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        int readyNum=select(msg_fd+1,&rdset,NULL,NULL,NULL);
        if(readyNum>0){
            if(FD_ISSET(msg_fd,&rdset)){
                bzero(buf,sizeof(buf));
                ret=recv(msg_fd,buf,sizeof(buf),0);
                if(!ret){
                    printf("connect is over\n");
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(buf,sizeof(buf));
                read(STDIN_FILENO,buf,sizeof(buf));
                send(msg_fd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(msg_fd);
    close(socketfd);
    return 0;
}

