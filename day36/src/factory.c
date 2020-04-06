#include "factory.h"

int factory_init(pFactory_t pFactory,int threadNum,int queCapacity)
{
    bzero(pFactory,sizeof(Factory_t));//初始化为0
    //队列初始化
    que_init(&pFactory->que,queCapacity);
    //条件变量初始化
    pthread_cond_init(&pFactory->cond,NULL);//条件变量初始化
    //子线程初始化
    pFactory->threadNum=threadNum;
    pFactory->pthid=(pthread_t *)calloc(threadNum,sizeof(pthread_t));
    return 0;
}
//子线程函数
void *threadFunc(void *p){
    pFactory_t pFactory=(pFactory_t)p;
    pQue_t pQue=&pFactory->que;
    pNode_t pTask=NULL;
    while(1){
        pthread_mutex_lock(&pQue->queMutex);
        if(!pQue->queSize){
            pthread_cond_wait(&pFactory->cond,&pQue->queMutex);
        }
        que_get(pQue,&pTask);//从队列中拿任务
        pthread_mutex_unlock(&pQue->queMutex);
        if(pTask){
            trans_file(pTask->newFd);//发送文件给客户端
        }
        close(pTask->newFd);
        free(pTask);
    }
}
//创建子线程，并把主要数据结构传给每一个子线程
int factory_start(pFactory_t pFactory){
    int i;
    if(!pFactory->startFlag){//判断线程池是否启动
        for(i=0;i<pFactory->threadNum;i++){
            pthread_create(pFactory->pthid+i,NULL,threadFunc,pFactory);
        }
        pFactory->startFlag=1;//避免下一次重复启动线程
    }
    return 0;
}
