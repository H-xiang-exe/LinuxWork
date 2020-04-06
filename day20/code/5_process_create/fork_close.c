#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid;
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    pid=fork();
    char buf[128]={0};
    if(pid==0){
        read(fd,buf,5);
        printf("child:%s\n",buf);
        return 0;
    }
    else{
        read(fd,buf,5);
        printf("parent:%s\n",buf);
        close(fd);
        printf("I am parent close\n");
        sleep(1);
        return 0;
    }
}

