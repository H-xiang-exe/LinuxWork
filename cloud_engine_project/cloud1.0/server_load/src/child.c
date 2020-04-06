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
        communicate(newFd);//通信
        printf("communication is over\n");
        finishFlag='1';
        write(sfd,&finishFlag,1);
        close(newFd);
    }
    exit(0);
}

int communicate(int newFd){
    char buf[1000];
    int ret;
    char cmd[100],postfix[1000];//用于存储分离后的命令和后缀，如cd和..
    char *result=NULL;
    CmdRet_t cmdRet;
    cmdRet.newFd=newFd;
    int len;
    while(1){
        recv(newFd,&len,sizeof(int),MSG_WAITALL);
        bzero(buf,sizeof(buf));
        ret=recv(newFd,buf,len,MSG_WAITALL);
        printf("===================\n");
        if(ret==0){
            break;
        }
        printf("%s\n",buf);
        if(strcmp(buf,"ls")==0){
            do_ls(newFd);
        }else if(strcmp(buf,"pwd")==0){
            do_pwd(newFd);
        }else{
            bzero(cmd,sizeof(cmd));
            bzero(postfix,sizeof(cmd));
            result=strtok(buf," ");
            strcpy(cmd,result);
            result=strtok(NULL," ");
            strcpy(postfix,result);
            result=strtok(NULL," ");
            cmdRet.cmd=cmd;
            cmdRet.postfix=postfix;
            cmdParse(&cmdRet);//解析并执行有两个参数的命令
        }
    }
    return 0;
}
