#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1){
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    sigset_t pending;
    sigemptyset(&pending);
    sigpending(&pending);
    if(sigismember(&pending,SIGQUIT)){
        printf("signal 3 is pending\n");
    }else{
        printf("signal 3 is not pending\n");
    }
    printf("after sleep %d is coming\n",signum);
}
int main(int argc,char *argv[])
{
    struct sigaction act;
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO;
    sigaddset(&act.sa_mask,SIGQUIT);
    int ret=sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

