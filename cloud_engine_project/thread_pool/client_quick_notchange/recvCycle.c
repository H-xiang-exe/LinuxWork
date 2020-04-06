#include "process_pool.h"

int recvCycle(int sfd,void *pStart,off_t fileSize)
{
    char *buf=(char *)pStart; 
    int total=0,ret;
    //off_t fileSlice=fileSize/10000;
    while(total<fileSize){
        ret=recv(sfd,buf+total,fileSize-total,0);
        if(ret==0){
            printf("The transmitting terminal is disconnected!\n");
            return -1;
        }
        total+=ret;
        printf("已下载：%5.2f%%\r",(double)total/fileSize*100);
    }
    return 0;
}

