#ifndef __FACTORY_H__
#define __FACTOTY_H__
#include "head.h"
#include "work_que.h"

typedef struct{
    Que_t que;
    pthread_cond_t cond;//条件变量，控制同步
    pthread_t *pthid;//所有子线程ID存储的起始地址
    int threadNum;//子线程数目
    int startFlag;//工厂是否启动
}Factory_t,*pFactory_t;


typedef struct{
    int datalen;//每次运送了多少数据
    char buf[1000];//存储要发送的数据
}train_t;

int factory_init(pFactory_t,int,int);

int factory_start(pFactory_t);

int tcp_init(int *,char *,char *);

int trans_file(int newFd);
#endif
