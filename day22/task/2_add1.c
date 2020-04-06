#include <func.h>
#define N 10000000
int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1001,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p=(int *)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int *)-1,"shmat");
    p[0]=0;
    int i;
    if(!fork()){
        for(i=0;i<N;i++){
            p[0]++;
        }
        exit(0);
    }else{
        for(i=0;i<N;i++){
            p[0]++;
        }
        wait(NULL);
        printf("result=%d\n",p[0]);
    }
    return 0;
}

