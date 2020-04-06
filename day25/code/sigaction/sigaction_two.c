#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1){
    printf("before sleep %d is coming,ok\n",signum);
    sleep(3);
    printf("after sleep %d is coming,ok\n",signum);
}//2号和3号信号都要捕捉
int main(int argc,char *argv[])
{
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO;
    ret=sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

