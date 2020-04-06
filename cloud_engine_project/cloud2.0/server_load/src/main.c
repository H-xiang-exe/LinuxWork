#include "process_pool.h"

int main(int argc,char *argv[])
{
    if(argc!=4){
        printf("usuage:./server ip port processNum\n");
        return -1;
    }
    int processNum=atoi(argv[3]);
    int socketFd;
    tcp_init(&socketFd,argv[1],argv[2]);
    proData_t data[processNum];
    makechild(data,processNum);
    int epfd=epoll_create(1);
    struct epoll_event event,*evs;
    evs=(struct epoll_event*)calloc(processNum+1,sizeof(struct epoll_event));
    event.data.fd=socketFd;
    event.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    for(int i=0;i<processNum;i++){
        event.data.fd=data[i].fd;
        epoll_ctl(epfd,EPOLL_CTL_ADD,data[i].fd,&event);
    }
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t len=sizeof(client);
    int newFd;
    int ret,readyFdNum;
    char finishFlag;
    int logfd=open("cloudlog",O_RDWR|O_APPEND);
    ERROR_CHECK(logfd,-1,"open");
    char log[100];//记录日志
    time_t timep;
    while(1){
        readyFdNum=epoll_wait(epfd,evs,processNum+1,-1);
        if(readyFdNum>0){
            for(int i=0;i<processNum+1;i++){
                if(evs[i].data.fd==socketFd){
                    bzero(&client,sizeof(client));
                    newFd=accept(socketFd,(struct sockaddr*)&client,&len);
                    ERROR_CHECK(newFd,-1,"accept");
                    time(&timep);
                    char *dt=ctime(&timep);
                    dt[strlen(dt)-1]=0;//去掉末尾的换行符
                    bzero(log,sizeof(log));
                    sprintf(log,"%s login:%s %d\n",dt,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                    printf("%s\n",log);
                    write(logfd,log,strlen(log));
                    close(logfd);
                    for(int j=0;j<processNum;j++){
                        if(data[j].busy==0){
                            sendFd(data[j].fd,newFd);
                            data[j].busy=1;
                            break;
                        }
                    }
                    close(newFd);
                }
                for(int j=0;j<processNum;j++){
                    if(evs[i].data.fd==data[j].fd){
                        ret=read(data[j].fd,&finishFlag,1);
                        ERROR_CHECK(ret,-1,"read");
                        data[j].busy=0;
                        printf("process %d is not busy\n",data[j].pid);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

