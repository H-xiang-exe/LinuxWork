#include "work_que.h"

int que_init(pQue_t pQue,int Capacity)
{
    bzero(pQue,sizeof(Que_t));
    pQue->queCapacity=Capacity;//队列容量
    pthread_mutex_init(&pQue->queMutex,NULL);//初始化队列锁
    return 0;
}
//加入新结点到队列中
int que_set(pQue_t pQue,pNode_t pNew){
    if(pQue->queSize==pQue->queCapacity){
        printf("sorry,Too many tasks to accept!\n");
        return -1;
    }else if(!pQue->queSize){//没有任务
        pQue->queHead=pNew;
        pQue->queTail=pNew;
    }else{
        pQue->queTail->pNext=pNew;
        pQue->queTail=pNew;
    }
    pQue->queSize++;
    return 0;
}

int que_get(pQue_t pQue,pNode_t *ppTask){
    if(pQue->queSize){//此处必须判空，难点！！！见笔记
        *ppTask=pQue->queHead;
        pQue->queHead=pQue->queHead->pNext;
        pQue->queSize--;
        if(pQue->queHead==NULL){
            pQue->queTail=pQue->queHead;
        }
    }
    return 0;
}


