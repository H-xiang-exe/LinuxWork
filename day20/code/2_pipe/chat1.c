#include<func.h>

int main(int argc,char *argv[]){
    ARGS_CHECK(argc,3);
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open_1");//以读的方式打开第一条管道
    int fdw=open(argv[2],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open_2");
    printf("I am female\n");
    char buf[512]={0};
    int ret;
    while(1){
        ret=read(fdr,buf,sizeof(buf));  
        ERROR_CHECK(ret,-1,"read");
        printf("%s\n",buf);
        memset(buf,0,sizeof(buf));
        ret=read(STDIN_FILENO,buf,sizeof(buf));
        ERROR_CHECK(ret,-1,"read");
        ret=write(fdw,buf,strlen(buf)-1);
        memset(buf,0,sizeof(buf));
    }
    close(fdr);
    close(fdw);
    return 0;
}
