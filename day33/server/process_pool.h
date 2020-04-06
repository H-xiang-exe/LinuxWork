#include<func.h>

typedef struct {
    pid_t pid;//子进程pid
    int fd;//子进程的管道对端
    short busy;//子进程的状态：是否忙碌
}process_data_t;

int makechild(process_data_t*,int);

int child_handle(int);

int tcp_init(int *socketFd,char *ip,char *port);

int sendFd(int sfd,int fd);

int recvFd(int sfd,int *fd);
