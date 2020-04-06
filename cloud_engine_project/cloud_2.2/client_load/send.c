#include "process_pool.h"

int sendInfo(int socketFd,char *buf){
    buf[strlen(buf)-1]=0;
    char tmp[1000];
    strcpy(tmp,buf);
    char *result=NULL;
    char cmd[100],postfix[1000];
    result=strtok(buf," ");                                
    strcpy(cmd,result);
    char info[1000];
    if(strcmp(cmd,"gets")==0){
        result=strtok(NULL," ");
        if(result==NULL){//后面是空的，则命令有问题
            printf("wrong command\n");
            return 0;
        }
        strcpy(postfix,result);
        struct stat mystat;
        int ret=stat(postfix,&mystat);
        if(ret==0){//说明文件已存在,那么连同文件大小发送过去
            sprintf(info,"%s %ld",tmp,mystat.st_size);
        }else{
            strcpy(info,tmp);
        }
    }else if(strcmp(cmd,"puts")==0){//上传文件
        result=strtok(NULL," ");
        strcpy(postfix,result);
        result=strtok(NULL," ");
        char filename[1000]={0};
        strncpy(filename,postfix,strlen(postfix)-1);//postfix末尾有回车，作为文件名参数时需要去掉末尾回车
        trans_file(socketFd,filename);
    }else{
        strcpy(info,tmp);
    }
    int len=strlen(info);
    send(socketFd,&len,sizeof(int),0);
    send(socketFd,info,len,0);//发送命令
    return 0;
}


