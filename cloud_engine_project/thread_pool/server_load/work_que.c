#include "work_que.h"

int queInit(pQue_t pQue,int capacity)
{
    bzero(pQue,sizeof(Que_t));
    pQue->queCapacity=capacity;
    pthread_mutex_init(&pQue->queMutex,NULL);
    return 0;
}

int queGet(pQue_t pQue,pNode_t *ppTask){
    if(pQue->queSize){
        *ppTask=pQue->queHead;
        pQue->queHead=pQue->queHead->pNext;
        if(pQue->queHead==NULL){//只有一个结点的情况
            pQue->queTail=NULL;
        }
        pQue->queSize--;
    }
    return 0;
}

int queSet(pQue_t pQue,pNode_t pNode){
    if(pQue->queHead==NULL){
        pQue->queHead=pQue->queTail=pNode;
    }else{
        pQue->queTail->pNext=pNode;
        pQue->queTail=pNode;
    }
    pQue->queSize++;
    return 0;
}
