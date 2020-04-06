#include "process_pool.h"

int recvCycle(int sfd,void *pStart,int len)
{
    char *buf=(char *)pStart; 
    int total=0;
    int ret;
    while(total<len){
        ret=recv(sfd,buf+total,len-total,0);
        if(ret==0){
            printf("The transmitting terminal is disconnected!\n");
            return -1;
        }
        total+=ret;
    }
    return 0;
}

