#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);//4096相当于一个物理页,IP_CREAT判断是否存在
    //共享内存段
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget sucess %d\n",shmid);
    char *p=(char *)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    strcpy(p,"I am handsome");
    int ret;
    p++;
    ret=shmdt(p);
    printf("ret=%d,errno=%d\n",ret,errno);
    while(1);
    return 0;
}

