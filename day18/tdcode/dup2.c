#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    printf("\n");
    int fd1=dup2(fd,STDOUT_FILENO);
    printf("fd1=%d\n",fd1);
    close(fd);
    printf("the out of stdout");
    return 0;
}

