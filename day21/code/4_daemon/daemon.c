#include <func.h>

int main(int argc,char *argv[])
{
    if(fork()){
        exit(0);//父进程退出
    }else{
        setsid();//成立新会话
        chdir("/");//改变当前目录为根目录
        umask(0);
        for(int i=0;i<3;i++){
            close(i);
        }
        while(1);
        return 0;
    }
}

