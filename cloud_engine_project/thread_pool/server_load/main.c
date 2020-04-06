#include "factory.h"

int main(int argc,char *argv[])
{
    if(argc!=5){
        printf("usuage:./server ip port threadNum capacity\n");
        return -1;
    }
    char *ip=argv[1];
    char *port=argv[2];
    int threadNum=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    Factory_t facData;
    //初始化线程池
    factory_init(&facData,threadNum,capacity);
    //启动线程池,运行线程函数
    factory_start(&facData);
    //sock,bind,listen
    int socketFd;
    tcp_init(&socketFd,ip,port);
    //while接收任务
    int newFd;
    pQue_t pQue=&facData.que;
    while(1){
        newFd=accept(socketFd,NULL,NULL);
        pNode_t pNewRequest=(pNode_t)calloc(1,sizeof(Node_t));
        pNewRequest->newFd=newFd;
        pNewRequest->pNext=NULL;
        //加锁放入任务队列
        pthread_mutex_lock(&pQue->queMutex);
        queSet(pQue,pNewRequest);
        pthread_mutex_unlock(&pQue->queMutex);
        pthread_cond_signal(&facData.cond);
    }
    return 0;
}

