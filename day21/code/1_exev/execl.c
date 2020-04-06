#include <func.h>

int main(int argc,char *argv[])
{
    execl("./add","add","3","4",NULL);    
    return 0;
}

