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
    fd_set rdset,tmpset;
    FD_ZERO(&tmpset);
    FD_SET(socketfd,&tmpset);
    FD_SET(STDIN_FILENO,&tmpset);
    int msg_fd;
    char buf[128]={0};
    while(1){
        FD_ZERO(&rdset);
        memcpy(&rdset,&tmpset,sizeof(fd_set));
        int readyNum=select(10,&rdset,NULL,NULL,NULL);
        if(readyNum>0){
            if(FD_ISSET(socketfd,&rdset)){
                bzero(&client_msg,sizeof(client_msg));
                socklen_t len=sizeof(client_msg);
                msg_fd=accept(socketfd,(struct sockaddr *)&client_msg,&len);
                ERROR_CHECK(msg_fd,-1,"accept");
                printf("client ip=%s,client msg port=%d\n",inet_ntoa(client_msg.sin_addr),ntohs(client_msg.sin_port));
                FD_SET(msg_fd,&tmpset);
            }
            if(FD_ISSET(msg_fd,&rdset)){
                bzero(buf,sizeof(buf));
                ret=recv(msg_fd,buf,sizeof(buf),0);
                if(!ret){
                    printf("connect is over\n");
                    FD_CLR(msg_fd,&tmpset);
                    close(msg_fd);
                    continue;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(ret==0){
                    break;
                }
                send(msg_fd,buf,strlen(buf)-1,0);
            }
        }
    }
    close(msg_fd);
    close(socketfd);
    return 0;
}

