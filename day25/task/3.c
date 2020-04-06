#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1){
    printf("before sleep %d is coming\n",signum);
    sleep(3);
    printf("after sleep %d is coming\n",signum);
}
int main(int argc,char *argv[])
{
    struct sigaction act;
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO|SA_NODEFER;
    int ret=sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);
    while(1);
    return 0;
}

