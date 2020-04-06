#include<func.h>

typedef struct {
    pid_t pid;//子进程pid
    int fd;//子进程的管道对端
    short busy;//子进程的状态：是否忙碌
}process_data_t;

typedef struct{
    int datalen;//每次运送了多少数据
    char buf[1000];//存储要发送的数据
}train_t;

int makechild(process_data_t*,int);

int child_handle(int);

int tcp_init(int *socketFd,char *ip,char *port);

int sendFd(int sfd,int fd);

int recvFd(int sfd,int *fd);

int trans_file(int);
