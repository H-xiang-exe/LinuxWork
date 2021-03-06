#include<func.h>

int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    int fdw=open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    printf("I am writer!\n");
    char buf[512]={0};
    int ret=read(STDIN_FILENO,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    ret=write(fdw,buf,strlen(buf)-1);
    ERROR_CHECK(ret,-1,"write");
    return 0;
}
