#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"

typedef struct tag_node{//队列结点
    int newFd;
    struct tag_node *pNext;
}Node_t,*pNode_t;

typedef struct{//队列
    pNode_t queHead,queTail;//方便进行头部插入和尾部删除
    int queCapacity;//队列容量
    int queSize;//队列当前元素个数
    pthread_mutex_t queMutex;//线程锁，用于各个不同线程互斥访问队列
}Que_t,*pQue_t;
//队列初始化
int que_init(pQue_t ,int );
//加入新结点到队列中
int que_set(pQue_t ,pNode_t );

int que_get(pQue_t ,pNode_t*);
#endif
