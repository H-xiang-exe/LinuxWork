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

typedef struct {//传输命令的结果给客户端
    int newFd;
    char *cmd;
    char *postfix;
}CmdRet_t,*pCmdRet_t;

int tcp_init(int *,char *,char *);

int makechild(proData_t *,int );

int child_handle(int );

int sendFd(int ,int );

int recvFd(int ,int *);

int recvCycle(int ,void *,int );

int recvInfo(int );

int recvDoc(int );

int recvPath(int );

int trans_file(int ,char *);

int communicate(int );

int cmdParse(pCmdRet_t );

int do_cd(pCmdRet_t );

int do_puts(pCmdRet_t );

int do_gets(pCmdRet_t );

int do_remove(pCmdRet_t );

int do_ls(int );

int do_pwd(int );

//以下为第二期头文件
typedef struct {
    char name[1000];
    char pwd[10];
}UsrLoad_t;

int loadCheck(int );
