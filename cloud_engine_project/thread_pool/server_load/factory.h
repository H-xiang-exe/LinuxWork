#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef struct {
    Que_t que;
    pthread_t *pthid;//子线程的起始地址
    int threadNum;//子线程数目
    int startFlag;//线程池启动标志
    pthread_cond_t cond;//子线程同步条件变量
}Factory_t,*pFactory_t;

typedef struct {//传输信息的数据结构
    int len;
    char buf[1000];
}train_t;

int tcp_init(int *,char *,char *);

int sendFd(int sfd,int fd);

int recvFd(int sfd,int *fd);

int trans_file(int );

int factory_init(pFactory_t ,int ,int );

int factory_start(pFactory_t );

#endif
