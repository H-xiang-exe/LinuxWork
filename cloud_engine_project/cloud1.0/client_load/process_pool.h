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

int trans_file(int ,char *);

int recvCycle(int sfd,void *,int);

int recvInfo(int );//接收服务端传来的信息，区分是文件还是路径

int recvDoc(int );//接收文件

int recvPath(int );//接收路径

int sendInfo(int ,char* );
