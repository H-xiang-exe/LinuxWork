#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid=fork();
    if(!pid){
        printf("child:pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
        while(1);
        return 0;
    }else{
        printf("parent:pid=%d,ppid=%d,pgid=%d\n",getpid(),getppid(),getpgid(0));
        wait(NULL);
        return 0;
    }
   return 0;
}

