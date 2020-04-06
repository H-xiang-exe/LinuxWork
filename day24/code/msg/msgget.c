#include <func.h>

int main(int argc,char *argv[])
{
    int msgid=msgget(1000,IPC_CREAT|0600);
    return 0;
}

