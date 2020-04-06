#include <func.h>
void sig_func(int signum){
    printf("%d is coming\n",signum);
    puts("");
}
int main(int argc,char *argv[])
{
    signal(SIGINT,sig_func);
    while(1);
    return 0;
}

