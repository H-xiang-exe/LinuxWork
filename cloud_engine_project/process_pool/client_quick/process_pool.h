#include <func.h>

typedef struct{//子进程的数据结构
    int fd;
    pid_t pid;
    short busy;
}proData_t;

typedef struct {//传输信息的数据结构
    int len;
    char buf[1000];
}train_t;

int tcp_init(int *,char *,char *);

int makechild(proData_t *,int);

int child_handle(int);

int sendFd(int sfd,int fd);

int recvFd(int sfd,int *fd);

int trans_file(int );

int recvCycle(int sfd,void *,off_t);

