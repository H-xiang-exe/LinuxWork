#include "process_pool.h"

int sendInfo(int socketFd,char *buf){
    int len=strlen(buf)-1;
    send(socketFd,&len,sizeof(int),0);
    send(socketFd,buf,strlen(buf)-1,0);
    char *result=NULL;
    char cmd[100],postfix[1000];
    result=strtok(buf," ");                                
    strcpy(cmd,result);
    if(strcmp(cmd,"puts")==0){
        result=strtok(NULL," ");
        strcpy(postfix,result);
        result=strtok(NULL," ");
        printf("trans_file\n");
        char filename[1000]={0};
        strncpy(filename,postfix,strlen(postfix)-1);//postfix末尾有回车，作为文件名参数时需要去掉末尾回车
        trans_file(socketFd,filename);
    }
    return 0;
}


