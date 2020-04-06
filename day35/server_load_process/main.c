#include"process_pool.h"

int main(int argc,char *argv[])
{
    //ARGS_CHECK(argc,4);//3个参数加上自身执行
    if(argc!=4){
        printf("usage ./process_pool_sever IP PORT PROCESS_NUM\n");
        return -1;
    }
    //为存储子进程信息申请空间
    int processNum=atoi(argv[3]);
    process_data_t *pData=(process_data_t*)calloc(processNum,sizeof(process_data_t)); 
    makechild(pData,processNum);
    int socketFd;
    //实现socket,bind,listen
    tcp_init(&socketFd,argv[1],argv[2]);
    //使用epoll监控socketFd,监控每一个子进程管道对端
    int epfd=epoll_create(1);
    struct epoll_event event,*evs;
    evs=(struct epoll_event*)calloc(processNum+1,sizeof(struct epoll_event));//监控子进程管道对端，监控客户端是否有连接
    event.events=EPOLLIN;
    event.data.fd=socketFd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);//监控socketFd
    for(int i=0;i<processNum;i++){//监控每一个子进程管道对端
        event.data.fd=pData[i].fd;
        epoll_ctl(epfd,EPOLL_CTL_ADD,pData[i].fd,&event);
    }
    //监控各个端口
    int readyFdNum;//监控数目
    struct sockaddr_in client;//用于接收客户端ip和端口号信息
    int newFd;//用于与客户端进行通信
    socklen_t len=sizeof(struct sockaddr);
    int childBusyFlag=0;
    while(1){
        readyFdNum=epoll_wait(epfd,evs,processNum+1,-1);
        for(int i=0;i<readyFdNum;i++){
            if(evs[i].data.fd==socketFd){//监测到客户端欲建立连接
                //接受连接
                bzero(&client,sizeof(client));
                newFd=accept(socketFd,(struct sockaddr*)&client,&len);
                ERROR_CHECK(newFd,-1,"accept");
                printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                //将任务(newFd)分派给空闲的子进程
                for(int j=0;j<processNum;j++){
                    if(pData[j].busy==0){//空闲
                        sendFd(pData[j].fd,newFd);//将newFd的值传给子进程以便子进程能通过newFd与客户端直接通信
                        printf("main process:give %d task to %d\n",newFd,pData[j].pid);
                        pData[j].busy=1;//设置为本子进程忙碌
                        break;
                    }
                }
                close(newFd);//减少对应缓冲区的引用计数
            }
            for(int j=0;j<processNum;j++){//检查子进程管道对端，看是否有消息（子进程不再忙碌）传来
                if(evs[i].data.fd==pData[j].fd){
                    read(pData[j].fd,&childBusyFlag,1);//此处必须要把管道里的内容读出，否则会一直触发epoll_wait
                    //进而导致本循环体的内容重复循环执行
                    //另外，若是写端断开，也会导致读端疯狂读空然后打印
                    pData[j].busy=0;
                    printf("子进程%d不忙碌\n",pData[j].pid);
                    break;//break的原因是每一轮循环只验证一个evs[i]，所以找到了就可以break了
                }
            }//此处也可不用循环，利用哈希将evs[i].data.fd通过hash函数映射出其在epfd对应的缓冲区位置j
        }
    }
    return 0;
}

