#include "client.h"

int recvCycle(int newFd,void *pStart,int len)//循环接收
{
    char *p=(char*)pStart;//传送的数据放在哪儿
    int total=0,ret;//目前累积接收字节数和返回值
    while(total<len){
        ret=recv(newFd,p+total,len-total,0);
        if(ret==0){//为了避免客户端突然端掉，recv一直读,ret=0,陷入死循环
            printf("byebye!\n");
            return -1;
        }
        total+=ret;
    }
    return 0;
}

