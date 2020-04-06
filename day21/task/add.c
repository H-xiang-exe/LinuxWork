#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int i,j;
    i=atoi(argv[1]);
    j=atoi(argv[2]);
    printf("sum=%d\n",i+j);
    return 0;
}

