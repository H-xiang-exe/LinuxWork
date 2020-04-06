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
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        ret=select(fdr+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret==0){
                printf("chat is broken!\n");
                break;
            }
            ERROR_CHECK(ret,-1,"read");
            ret=write(fdw,buf,strlen(buf)-1);
        }
        if(FD_ISSET(fdr,&rdset)){
            memset(buf,0,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));  
            if(ret==0){
                printf("chat is broken!\n");
                break;
            }
            ERROR_CHECK(ret,-1,"read");
            printf("%s\n",buf);
        }
    }
    close(fdr);
    close(fdw);
    return 0;
}
