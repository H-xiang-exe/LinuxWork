#include <func.h>

int main(int argc,char *argv[])
{
    char *const envp[]={"PATH=/usr/bin",NULL};
    int ret=execle("./test_path",argv[0],NULL,envp);    
    ERROR_CHECK(ret,-1,"execle");
    return 0;
}

