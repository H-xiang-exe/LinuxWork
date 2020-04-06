#include "process_pool.h"
#define FILENAME "file"
int trans_file(int newFd)
{
    //开始发送文件名
    train_t dataTrain;
    dataTrain.datalen=strlen(FILENAME);
    strcpy(dataTrain.buf,FILENAME);
    send(newFd,&dataTrain,4+dataTrain.datalen,0);
    //开始发送文件内容
    int fd=open(FILENAME,O_RDONLY);
    while((dataTrain.datalen=read(fd,dataTrain.buf,sizeof(dataTrain.buf)))){
        send(newFd,&dataTrain,4+dataTrain.datalen,0);
    }
    //发送文件结束标志
    dataTrain.datalen=0;
    send(newFd,&dataTrain,4,0);
    //关闭打开的文件
    close(fd);
    return 0;
}

