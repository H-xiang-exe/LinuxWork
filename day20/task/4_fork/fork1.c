#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid,ppid;
    int ret=fork();
    if(ret==0){//子进程
        printf("mypid=%d,myparentpid=%d\n",getpid(),getppid());
        while(1);
    }else{//父进程
        printf("mypid=%d,mychildpid=%d\n",getpid(),ret);
        while(1);
    }
    return 0;
}

