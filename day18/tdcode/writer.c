#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fdw=open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open_2");
    char buf[128]="HelloWorld";
    int ret=write(fdw,buf,strlen(buf));
    ERROR_CHECK(ret,-1,"write");
    printf("%s\n",buf);
    return 0;
}

