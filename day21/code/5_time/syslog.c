#include <func.h>

int main(int argc,char *argv[])
{
    syslog(LOG_INFO,"I am %d years old,line=%d\n",22,
           __LINE__);
    return 0;
}

