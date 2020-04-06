#include "factory.h"

void *threadFunc(void *p){//线程函数
    pFactory_t pFactory=(pFactory_t)p;
    pQue_t pQue=&pFactory->que;
    pNode_t pTask=NULL;//取任务
    while(1){
        pthread_mutex_lock(&pQue->queMutex);
        if(!pQue->queSize){
            pthread_cond_wait(&pFactory->cond,&pQue->queMutex);
        }
        queGet(pQue,&pTask);//取任务
        if(pTask){//如果成功取出任务
            trans_file(pTask->newFd);//传输文件
            close(pTask->newFd);//传输完文件要关闭
            free(pTask);//结点取出来用完之后需要释放
        }
        pthread_mutex_unlock(&pQue->queMutex);
    }
}

int factory_init(pFactory_t pFactory,int threadNum,int capacity)
{
    bzero(pFactory,sizeof(Factory_t));
    //队列初始化
    queInit(&pFactory->que,capacity);
    //为子线程id申请空间
    pFactory->pthid=(pthread_t*)calloc(threadNum,sizeof(pthread_t));
    pFactory->threadNum=threadNum;
    //初始化条件变量
    pthread_cond_init(&pFactory->cond,NULL);
    return 0;
}

int factory_start(pFactory_t pFactory){
    if(pFactory->startFlag==0){
        for(int i=0;i<pFactory->threadNum;i++){
            pthread_create(pFactory->pthid+i,NULL,threadFunc,pFactory);
        }
        pFactory->startFlag=1;
    }
    return 0;
}

