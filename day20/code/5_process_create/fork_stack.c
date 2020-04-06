#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    int i=10;
    pid=fork();
    if(pid==0){
        printf("child:i=%d\n",i);
        return 0;
    }
    else{
        i=5;
        printf("parent:i=%d\n",i);
        sleep(1);
        return 0;
    }
}

