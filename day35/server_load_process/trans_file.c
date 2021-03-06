#include "process_pool.h"
#define FILENAME "file_zero"
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
    int fd=open(FILENAME,O_RDONLY);//打开文件，读取文件内容
    ERROR_CHECK(fd,-1,"open");
    while((dataTrain.datalen=read(fd,dataTrain.buf,sizeof(dataTrain.buf)))){
        send(newFd,&dataTrain,4+dataTrain.datalen,0);//仅发送文件内容
    }
    //发结束标志
    dataTrain.datalen=0;
    send(newFd,&dataTrain,4,0);
    return 0;
}

