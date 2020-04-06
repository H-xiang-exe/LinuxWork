#include <func.h>
int change_nonblock(int fd){
    int status;
    status=fcntl(fd,F_GETFL);
    status=status|O_NONBLOCK;
    status=fcntl(fd,F_SETFL,status);
    ERROR_CHECK(status,-1,"fcntl");
    return 0;
}
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);

    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    change_nonblock(sfd);
    struct sockaddr_in ser;
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_family=AF_INET;

    int ret;
    ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.data.fd=sfd;
    event.events=EPOLLIN;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    
    int readyFdNum;
    char buf[10];
    while(1){
        readyFdNum=epoll_wait(epfd,evs,2,-1);
        if(readyFdNum>0){
            for(int i=0;i<readyFdNum;i++){
                if(evs[i].data.fd==sfd){
                    while(1){
                        bzero(&buf,sizeof(buf));
                        ret=recv(sfd,buf,sizeof(buf)-1,0);
                        if(!ret){//断开
                            printf("connect is over!\n");
                            goto end;
                        }else if(ret==-1){//读空
                            printf("\n");
                            break;
                        }else{
                            printf("%s",buf);
                        }
                    }
                }
                if(evs[i].data.fd==STDIN_FILENO){
                    bzero(&buf,sizeof(buf));
                    ret=read(STDIN_FILENO,buf,sizeof(buf));
                    if(ret==0){
                        break;
                    }
                    send(sfd,buf,strlen(buf)-1,0);
                }
            }
        }
    }
end:
    close(sfd);
    return 0;
}

