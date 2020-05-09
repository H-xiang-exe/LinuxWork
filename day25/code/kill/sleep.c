#include <func.h>
void sigFunc(int signum){
    printf("SIGALRM is here\n");
}
int main(int argc,char *argv[])
{
    signal(SIGALRM,sigFunc);
    alarm(3);
    pause();
    return 0;
}

