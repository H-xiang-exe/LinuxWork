#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1){
    printf("%d is coming,ok\n",signum);
}
int main(int argc,char *argv[])
{
    int ret;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_sigaction=sigFunc;
    act.sa_flags=SA_SIGINFO|SA_RESTART;
    ret=sigaction(SIGINT,&act,NULL);//内核调用我们设置的信号处理行为函数
    char buf[128]={0};
    read(0,buf,sizeof(buf));
    return 0;
}

