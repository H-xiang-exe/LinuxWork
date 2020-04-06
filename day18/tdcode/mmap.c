#include<func.h>
int main(int argc,char **argv){
    ARGS_CHECK(argc,2);
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char *p;
    struct stat buf;
    fstat(fd,&buf);
    p=(char *)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,NULL,"mmap");
    p[0]='H';
    munmap(p,buf.st_size);
    close(fd);
    return 0;
}
