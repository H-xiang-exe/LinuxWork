#include "process_pool.h"
#define FILENAME "115.day36-线程池1.mp4"
void sigFunc(int sigNum){
    printf("%d is coming!\nclient is disconnected or its receiving speed is too slow!\n",sigNum);
}
int trans_file(int newFd)
{
    signal(SIGPIPE,sigFunc);
    //传输文件名
    train_t data;
    data.len=strlen(FILENAME);
    strcpy(data.buf,FILENAME);
    send(newFd,&data,4+data.len,0);
    //传输文件大小
    struct stat fileInfo;
    stat(FILENAME,&fileInfo);
    data.len=sizeof(fileInfo.st_size);
    memcpy(data.buf,&fileInfo.st_size,data.len);
    send(newFd,&data,4+data.len,0);
    //传输文件内容
    int fd=open(FILENAME,O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char *pStart=(char *)mmap(NULL,fileInfo.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(pStart,(char*)-1,"mmap");
    send(newFd,pStart,fileInfo.st_size,0);
    return 0;
}

