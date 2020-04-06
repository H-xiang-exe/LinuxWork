#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    int i=10;
    char *p=(char *)malloc(20);
    strcpy(p,"hello");
    pid=fork();
    if(pid==0){
        printf("child:&i=%p,i=%s\n",&i,p);
        return 0;
    }
    else{
        printf("parent:&i=%p,i=%s\n",&i,p);
        i=5;
        strcpy(p,"world");
        printf("parent:&i=%p,i=%s\n",&i,p);
        sleep(1);
        return 0;
    }
}

