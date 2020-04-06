#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    char buf[10]="Hello";
    int ret=write(fd,buf,strlen(buf));
    ERROR_CHECK(ret,-1,"write");
    close(fd);
    return 0;
}

