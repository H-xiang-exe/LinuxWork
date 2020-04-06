#include<func.h>
int main(int argc,char **argv){
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    int ret=ftruncate(fd,5);
    ERROR_CHECK(ret,-1,"ftrunncate");
    char *p;
    p=(char *)mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    strcpy(p,"world");
    munmap(p,5);
    close(fd);
    return 0;
}
