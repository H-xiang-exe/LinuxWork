#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid=fork();
    if(!pid){
        printf("child:pid=%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
        return 0;
    }else{
        printf("parent:pid=%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),getppid(),getpgid(0),getsid(0));
        wait(NULL);
        return 0;
    }
   return 0;
}

