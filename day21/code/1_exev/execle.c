#include <func.h>

int main(int argc,char *argv[])
{
    char *const envp[]={"PATH=/usr/bin",NULL};
    int ret=execle("./test_path",argv[0],NULL,envp);    
    //指定执行该程序test_path的环境
    ERROR_CHECK(ret,-1,"execle");
    return 0;
}

