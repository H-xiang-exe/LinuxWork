#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork()){
        printf("I am a child:%d\n",getpid());
    }else{
        printf("I am parent\n");
        pid_t pid=wait(NULL);
        printf("wait success=%d\n",pid);
        return 0;
    } 
    return 0;
}

