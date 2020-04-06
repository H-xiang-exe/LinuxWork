#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int fd1=open(argv[1],O_RDWR);
    ERROR_CHECK(fd1,-1,"open_1");
    int fd2=open(argv[2],O_RDWR);
    ERROR_CHECK(fd2,-1,"open_2");
    dup2(fd1,STDOUT_FILENO);
    dup2(fd2,STDERR_FILENO);
    close(fd1);
    close(fd2);
    fprintf(stdout,"%s","hello");
    fprintf(stderr,"%s","world");
    return 0;
}

