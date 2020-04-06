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
    int ret;
    while(1){
        recvFd(sfd,&newFd);
        do{
            ret=loadCheck(newFd);
        }while(ret==-1);
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
    bzero(&cmdRet,sizeof(cmdRet));
    cmdRet.newFd=newFd;
    int len;
    time_t timep;
    int flag;
    char log[100],wrong[100]="wrong command";//log用来存储日志，wrong用来存储"wrong command"
    int logfd=open("cloudlog",O_RDWR|O_APPEND);
    ERROR_CHECK(logfd,-1,"open");
    while(1){
        recv(newFd,&len,sizeof(int),MSG_WAITALL);
        bzero(&buf,sizeof(buf));
        ret=recv(newFd,buf,len,MSG_WAITALL);
        if(ret==0){
            break;
        }
        //记录日志
        time(&timep);
        char *dt=ctime(&timep);
        dt[strlen(dt)-1]=0;//去掉末尾的换行符
        bzero(log,sizeof(log));
        sprintf(log,"%s command:%s\n",dt,buf);
        write(logfd,log,strlen(log));

        if(strcmp(buf,"logout")==0){
            break;
        }else if(strcmp(buf,"ls")==0){
            do_ls(newFd);
        }else if(strcmp(buf,"pwd")==0){
            do_pwd(newFd);
        }else{
            bzero(cmd,sizeof(cmd));
            bzero(postfix,sizeof(cmd));
            result=strtok(buf," ");
            strcpy(cmd,result);
            result=strtok(NULL," ");
            if(result==NULL){
                flag=0;
                send(newFd,&flag,sizeof(int),0);
                len=strlen(wrong);
                send(newFd,&len,sizeof(len),0);
                send(newFd,wrong,len,0);
                continue;
            }
            strcpy(postfix,result);
            cmdRet.cmd=cmd;
            cmdRet.postfix=postfix;
            result=strtok(NULL," ");
            if(result!=NULL){//说明有三段,客户端要下载文件
               cmdRet.fileSize=atoi(result);
            }
            cmdParse(&cmdRet);//解析并执行有多个参数的命令
        }
    }
    close(logfd);
    return 0;
}
