#include"process_pool.h"

int makechild(process_data_t *pData,int processNum){
    int sockFds[2];
    pid_t pid;
    int ret;
    for(int i=0;i<processNum;i++){
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,sockFds);//与每一个子进程之间创建全双工管道
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(pid==0){//子进程
            close(sockFds[0]);
            child_handle(sockFds[1]);
        }//子进程将不会执行到if大括号外面
        //只有父进程在走for循环
        close(sockFds[1]);
        pData[i].pid=pid;
        pData[i].busy=0;
        pData[i].fd=sockFds[0];
    }
    return 0;
}

int child_handle(int fds){
    int new_fd;
    int finishflag=0;//传输文件是否完成
    while(1){
        //接受父进程给的任务
        recvFd(fds,&new_fd);//拿到父进程分配的任务
        printf("I am child process,get new_fd=%d\n",new_fd);
        //发送文件
        int ret=send(new_fd,"sendfile",8,0);
        if(ret==-1){
            perror("send");
            break;
        }
        //完成任务，关闭缓冲区
        close(new_fd);
        //通知父进程完成任务
        printf("finish task\n");
        write(fds,&finishflag,1);//通知父进程完成任务了
    }
    exit(0);
}


