#include "process_pool.h"

int makechild(proData_t *pData,int processNum){
    int socketfd[2];
    int ret;
    pid_t pid;
    for(int i=0;i<processNum;i++){
        ret=socketpair(AF_LOCAL,SOCK_STREAM,0,socketfd);
        ERROR_CHECK(ret,-1,"socketpair");
        pid=fork();
        if(pid==0){
            close(socketfd[0]);
            child_handle(socketfd[1]);
        }else{
            close(socketfd[1]);
            pData[i].fd=socketfd[0];
            pData[i].pid=pid;
            pData[i].busy=0;
        }
    }
    return 0;
}

int child_handle(int sfd){
    int newFd;
    char finishFlag=0;
    while(1){
        recvFd(sfd,&newFd);
        printf("receive a task %d\n",newFd);
        trans_file(newFd);
        write(sfd,&finishFlag,1);
        printf("child:finish task!\n");
        close(newFd);
    }
    exit(0);
}
