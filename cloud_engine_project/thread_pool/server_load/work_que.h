#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"
typedef struct node{
    int newFd;
    struct node *pNext;
}Node_t,*pNode_t;//队列中的元素结点，每一个元素代表一个任务

typedef struct que{
    pNode_t queHead,queTail;
    int queCapacity;//队列容量
    int queSize;//队列大小
    pthread_mutex_t queMutex;//队列锁
}Que_t,*pQue_t;

int queInit(pQue_t ,int );//队列初始化

int queSet(pQue_t ,pNode_t);//向队列中添加任务

int queGet(pQue_t,pNode_t* );//从队列中取任务

#endif
