#include <func.h>

int main(int argc,char *argv[])
{
    char *const args[]={"add","3","4",NULL};
    execv("./add",args);    
    return 0;
}

