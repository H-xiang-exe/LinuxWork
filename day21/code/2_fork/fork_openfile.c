#include <func.h>
//先fork后open
int main(int argc,char *argv[])
{
    pid_t pid;
    ARGS_CHECK(argc,2);
    int fd;
    pid=fork();
    char buf[128]={0};
    if(pid==0){
        fd=open(argv[1],O_RDWR);
        read(fd,buf,5);
        printf("child:%s\n",buf);
        return 0;
    }
    else{
        fd=open(argv[1],O_RDWR);
        read(fd,buf,5);
        printf("parent:%s\n",buf);
        sleep(1);
        return 0;
    }
}

