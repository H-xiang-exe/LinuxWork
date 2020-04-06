#include <func.h>
int change_nonblock(int fd){
    int status;//获取属性a
    status=fcntl(fd,F_GETFL);
    status=status|O_NONBLOCK;
    int ret=fcntl(fd,F_SETFL,status);
    ERROR_CHECK(ret,-1,"fcntl");
    return 0;
}
int change_block(int fd){
    int status;//获取属性a
    status=fcntl(fd,F_GETFL);
    status=status&~O_NONBLOCK;
    int ret=fcntl(fd,F_SETFL,status);
    ERROR_CHECK(ret,-1,"fcntl");
    return 0;
}
int main(int argc,char *argv[])
{
    char buf[128]={0};
    sleep(5);
    change_nonblock(STDIN_FILENO);
    int ret=read(0,buf,sizeof(buf));
    printf("ret=%d,buf=%s,errno=%d\n",ret,buf,errno);
    return 0;
}

