#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open_1");
    int fdw=open(argv[2],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open_2");
    fd_set rdset;
    int ret;
    char buf[256]={0};
    printf("I am Li\n");
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        ret=select(fdr+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret==0){
                printf("I want end this dialog!\n");
                break;
            }
            ERROR_CHECK(ret,-1,"read");
            ret=write(fdw,buf,strlen(buf)-1);
            ERROR_CHECK(ret,-1,"write");
        }
        if(FD_ISSET(fdr,&rdset)){
            memset(buf,0,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));
            if(ret==0){
                printf("dialog is over!\n");
                break;
            }
            ERROR_CHECK(ret,-1,"read");
            printf("%s\n",buf);
        }
    }
    return 0;
}

