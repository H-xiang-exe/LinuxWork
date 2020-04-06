#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork()){
        printf("I am child,mypid=%d\n",getpid());
        return 0;
    }else{
        printf("I am parent,mypid=%d\n",getpid());
        int ret=wait(NULL);
        printf("child pid=%d\n",ret);
    }
    return 0;
}

