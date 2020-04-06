#include "factory.h"
#define FILENAME "115.day36-线程池1.mp4"
void sigFunc(int signum){
    printf("%d is coming\n",signum);
}
int trans_file(int newFd)
{
    signal(SIGPIPE,sigFunc);
    //发送文件名
    train_t dataTrain;
    dataTrain.datalen=strlen(FILENAME);//规范是要转换大小端
    strcpy(dataTrain.buf,FILENAME);
    send(newFd,&dataTrain,4+dataTrain.datalen,0);
    //发送文件大小给客户端
    struct stat buf;
    stat(FILENAME,&buf);
    dataTrain.datalen=sizeof(buf.st_size);
    memcpy(dataTrain.buf,&buf.st_size,dataTrain.datalen);
    send(newFd,&dataTrain,4+dataTrain.datalen,0);
    //发送文件内容
    int fd=open(FILENAME,O_RDWR);//打开文件，读取文件内容
    ERROR_CHECK(fd,-1,"open");
    char *pStart=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(pStart,(char*)-1,"mmap");
    send(newFd,pStart,buf.st_size,0);//仅发送文件内容
    //mmap大火车不需要发结束标志
    return 0;
}

