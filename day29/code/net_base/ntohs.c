#include <func.h>

int main(int argc,char *argv[])
{
    unsigned short port=0x1234;
    printf("port=%x\n",port);
    unsigned short nport=htons(port);
    printf("nport=%x\n",nport);
    port=0;
    port=ntohs(nport);
    printf("port=%x\n",port);
    return 0;
}

