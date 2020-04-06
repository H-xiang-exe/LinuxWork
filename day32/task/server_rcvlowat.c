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
    struct sockaddr_in ser;
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_family=AF_INET;
   
    int ret;
    int reuse=1;
    ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
   
    ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
  
    listen(sfd,10);
   
    int epfd=epoll_create(1);
    struct epoll_event event,evs[3];
    event.data.fd=sfd;
    event.events=EPOLLIN;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
   
    int readyFdNum;
    int msg_fd;
    char buf[10];
   
    struct sockaddr_in client;
    bzero(&client,sizeof(struct sockaddr));
    socklen_t addrlen=sizeof(client);
    
    while(1){
        readyFdNum=epoll_wait(epfd,evs,3,-1);
        if(readyFdNum>0){
            for(int i=0;i<readyFdNum;i++){
                if(evs[i].data.fd==sfd){
                    msg_fd=accept(sfd,(struct sockaddr*)&client,&addrlen);
                    ERROR_CHECK(msg_fd,-1,"accept");
                    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                    change_nonblock(msg_fd);
                    int least=5;
                    ret=setsockopt(msg_fd,SOL_SOCKET,SO_RCVLOWAT,&least,sizeof(int));
                    event.data.fd=msg_fd;
                    event.events=EPOLLIN|EPOLLET;//边缘触发
                    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,msg_fd,&event);//加入到监视队列
                    ERROR_CHECK(ret,-1,"epoll_ctl");
                }
                if(evs[i].data.fd==msg_fd){
                    while(1){
                        bzero(&buf,sizeof(buf));
                        ret=recv(msg_fd,buf,sizeof(buf)-1,0);
                        if(!ret){//断开
                            printf("connect is over!\n");
                            event.data.fd=msg_fd;
                            epoll_ctl(epfd,EPOLL_CTL_DEL,msg_fd,&event);
                            close(msg_fd);
                            break;
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
                    send(msg_fd,buf,strlen(buf)-1,0);
                }
            }
        }
    }
    close(msg_fd);
    close(sfd);
    return 0;
}

