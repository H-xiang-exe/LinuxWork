#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    pid=fork();
    if(pid==0){
        printf("I am child,mypid=%d,myppid=%d\n",getpid(),getppid());
        int *p=NULL;
        *p=10;
        printf("you cannot see me!\n");
    }
    else{
        printf("I am parent,childpid=%d,mypid=%d\n",pid,getpid());
        while(1);
        sleep(1);
    }
    return 0;
}

