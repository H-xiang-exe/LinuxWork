#include<func.h>
int main(int argc,char **argv){
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    close(STDOUT_FILENO);
    int fd1=dup(fd);
    close(fd);
    printf("the out of stdout\n");
    return 0;
}
