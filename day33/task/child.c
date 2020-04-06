#include"process_pool.h"

int makeChildProcess(process_data_t *pData,int childProcessNum)
{
    int sockfds[2];
    for(int i=0;i<childProcessNum;i++){
        socketpair(AF_LOCAL,SOCK_STREAM,0,sockfds);
        pid_t pid=fork();
        if(!pid){
            close(sockfds[0]);
            child_handle(sockfds[1]);
        }else{
            close(sockfds[1]);
            pData[i].pid=pid;
            pData[i].fd=sockfds[0];//为了让主函数能够知道和子进程通信的管道对端
            pData[i].busy=0;//初始化子进程时子进程是不忙碌的
        }
    }
    return 0;
}

int child_handle(int fd){
    int newFd;
    char finishFlag=0;
    while(1){
        //接受来自父进程的任务
        recvFd(fd,&newFd); 
        printf("I am child,I get task %d\n",newFd);
        //完成任务
        int ret=send(newFd,"hello,client",15,0);
        if(ret==-1){//此处不能用ERROR_CHECK，否则会返回到makeChildProcess函数，导致产生无穷多子进程
            perror("send");
            break;
        }
        //通告父进程任务已完成
        finishFlag=1;
        write(fd,&finishFlag,1);
        printf("finish task\n");
        close(newFd);
    }
    exit(0);
}

