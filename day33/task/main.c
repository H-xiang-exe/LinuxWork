#include"process_pool.h"

int main(int argc,char *argv[])
{
    //获取参数 ip port childProcessNum
    ARGS_CHECK(argc,4);
    int childProcessNum=atoi(argv[3]);
    process_data_t *pData=(process_data_t*)calloc(childProcessNum,sizeof(process_data_t));
    //开辟子进程,并完成主进程与子进程的管道的建立
    makeChildProcess(pData,childProcessNum);
    //监听客户端的连接请求并连接
    int socketFd;
    tcp_init(&socketFd,argv[1],argv[2]);//完成socket,bind,listen
    int epfd=epoll_create(1);
    struct epoll_event event,*evs;
    evs=(struct epoll_event*)calloc(childProcessNum+1,sizeof(struct epoll_event));
    event.data.fd=socketFd;
    event.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    for(int i=0;i<childProcessNum;i++){
        event.data.fd=pData[i].fd;
        epoll_ctl(epfd,EPOLL_CTL_ADD,pData[i].fd,&event);
    }
    int readyFdNum;
    int newFd;
    struct sockaddr_in client;
    socklen_t len=sizeof(struct sockaddr);
    char processBusy=0;
    while(1){
        readyFdNum=epoll_wait(epfd,evs,childProcessNum+1,-1);
        for(int i=0;i<readyFdNum;i++){
            if(evs[i].data.fd==socketFd){//有新的客户端连接
                bzero(&client,sizeof(client));
                newFd=accept(socketFd,(struct sockaddr*)&client,&len);//与客户端进程建立传递消息的连接
                ERROR_CHECK(newFd,-1,"accept");
                printf("client ip=%s,port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                for(int j=0;j<childProcessNum;j++){//将任务交予子进程
                    if(pData[j].busy==0){
                        sendFd(pData[j].fd,newFd);
                        pData[j].busy=1;
                        printf("I am parent,now give a task %d to child process %d\n",newFd,pData[j].pid);
                        break;
                    }
                }
                close(newFd);
            }
            for(int j=0;j<childProcessNum;j++){//子进程通知父进程，任务完成
                if(evs[i].data.fd==pData[i].fd){
                    read(pData[i].fd,&processBusy,1);//子进程通知任务完成
                    pData[i].busy=0;
                    printf("child process %d is not busy\n",pData[i].pid);
                    break;
                }
            }
        }
    }
    return 0;
}

