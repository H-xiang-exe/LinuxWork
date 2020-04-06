#include <func.h>

int main(int argc,char *argv[])
{
    if(fork()){
        exit(0);
    }else{
        setsid();
        chdir("/");
        umask(0);
        for(int i=0;i<3;i++){
            close(i);
        }
        while(1){
            syslog(LOG_INFO,"xianghaoishandsome");
            sleep(60);
        }
    }
    return 0;
}

