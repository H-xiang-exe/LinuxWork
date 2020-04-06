#include "process_pool.h"
void sigFunc(int sigNum){
    printf("%d is coming!\nclient is disconnected or its receiving speed is too slow!\n",sigNum);
}
int trans_file(int newFd,char *filename)
{
    signal(SIGPIPE,sigFunc);
    //传输文件名
    train_t data;
    data.len=strlen(filename);
    strcpy(data.buf,filename);
    send(newFd,&data,4+data.len,0);
    //传输文件大小
    struct stat fileInfo;
    stat(filename,&fileInfo);
    data.len=sizeof(fileInfo.st_size);
    memcpy(data.buf,&fileInfo.st_size,data.len);
    send(newFd,&data,4+data.len,0);
    //传输文件内容
    int fd=open(filename,O_RDWR);
    while((data.len=read(fd,data.buf,sizeof(data.buf)))){
        send(newFd,&data,4+data.len,0);
    }
    //传输文件结束标志
    data.len=0;
    send(newFd,&data,4,0);
    return 0;
}

