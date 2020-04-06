#include "process_pool.h"
void sigFunc(int sigNum){
    while(waitpid(-1,0,WNOHANG)>0);
}
int trans_file(pCmdRet_t p)
{
    signal(SIGPIPE,sigFunc);
    //传输文件名
    train_t data;
    data.len=strlen(p->postfix);
    strcpy(data.buf,p->postfix);
    send(p->newFd,&data,4+data.len,0);
    //传输文件大小
    struct stat fileInfo;
    stat(p->postfix,&fileInfo);
    data.len=sizeof(fileInfo.st_size);
    memcpy(data.buf,&fileInfo.st_size,data.len);
    send(p->newFd,&data,4+data.len,0);
    //传输文件内容
    int fd=open(p->postfix,O_RDWR);
    lseek(fd,p->fileSize,SEEK_SET);
    while((data.len=read(fd,data.buf,sizeof(data.buf)))){
        send(p->newFd,&data,4+data.len,0);
    }
    //传输文件结束标志
    data.len=0;
    send(p->newFd,&data,4,0);
    return 0;
}

