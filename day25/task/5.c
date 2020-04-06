#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *q){
}
int main(int argc,char *argv[])
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,SIGINT);
    int ret=sigprocmask(SIG_BLOCK,&sigset,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    printf("before sleep\n");
    sleep(5);
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    if(sigismember(&pending,SIGINT)){
        printf("signal 2 is pending\n");
    }else{
        printf("signal 2 is not pending\n");
    }
    printf("after sleep\n");
    ret=sigprocmask(SIG_UNBLOCK,&sigset,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    printf("programme is over\n");
    return 0;
}

