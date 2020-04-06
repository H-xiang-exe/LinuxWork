#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fdr=open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open_1");
    char buf[128]={0};
    int ret=read(fdr,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"read");
    printf("%s\n",buf);
    return 0;
}

