#include "factory.h"

int main(int argc,char *argv[])
{
    if(argc!=5){
        printf("usage:./server IP PORT threadNum queCapacity\n");
    }
    Factory_t facData;//线程池数据结构
    int threadNum=atoi(argv[3]);
    int queCapacity=atoi(argv[4]);
    //工厂(线程池)初始化
    factory_init(&facData,threadNum,queCapacity);
    //启动线程池
    factory_start(&facData);
    //初始化socket bind listen
    int socketFd;
    tcp_init(&socketFd,argv[1],argv[2]);
    //while循环接任务 分发任务
    int newFd;
    pNode_t pNewRequest;//用于存储新接收的客户端请求
    pQue_t pQueue=&facData.que;//拿到队列的结构体地址
    while(1){
        newFd=accept(socketFd,NULL,NULL);
        ERROR_CHECK(newFd,-1,"accept");
        pNewRequest=(pNode_t)calloc(1,sizeof(pNode_t));
        pNewRequest->newFd=newFd;
        //加锁放入队列
        pthread_mutex_lock(&pQueue->queMutex);//加锁
        que_set(pQueue,pNewRequest);//放入队列
        pthread_mutex_unlock(&pQueue->queMutex);//解锁
        //唤醒一个子线程
        pthread_cond_signal(&facData.cond);
    }
    return 0;
}

