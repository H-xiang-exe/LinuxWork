#include<func.h>

typedef struct{
    pid_t pid;//进程id,因为主进程需要了解是哪个子进程完成了任务
    int fd;//子进程管道对端,因为主进程需要能够与子进程通信
    short busy;//子进程的状态,因为主进程分配任务时需要了解子进程的状态
}process_data_t;

int makeChildProcess(process_data_t *pData,int childProcessNum);

int child_handle(int fd);

int tcp_init(int *socketFd,char *ip,char *port);

int sendFd(int sfd,int fd);

int recvFd(int sfd,int *fd);
