#include <func.h>
int print(){
    printf("I am print");
    _exit(1);//子进程在此终止
}

int main(int argc,char *argv[])
{
    if(!fork()){
        printf("child:%d\n",getpid());
        print();
        printf("I am child after print\n");
        return 0;
    }else{
        printf("I am parent\n");
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("child exit code=%d\n",WEXITSTATUS(status));
        }
        return 0;
    }
    return 0;
}

