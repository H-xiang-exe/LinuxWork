#include <func.h>

int main(int argc,char *argv[])
{
    int fds[2];
    pipe(fds);
    if(!fork()){
        close(fds[0]);
        write(fds[1],"Hello",5);
        exit(0);
    }else{
        close(fds[1]);
        char buf[100]={0};
        read(fds[0],buf,sizeof(buf));
        puts(buf);
        wait(NULL);
        return 0;
    }
}

