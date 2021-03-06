#include <func.h>
#define N 10000000
int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1000,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget sucess %d\n",shmid);
    int *p=(int *)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int *)-1,"shmat");
    p[0]=0;
    int i;
    int sems_id=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(sems_id,-1,"semget");
    int ret;
    ret=semctl(sems_id,0,SETVAL,1);
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf sopp,sopv;
    sopp.sem_num=0;//0号信号量
    sopp.sem_op=-1;//p操作,为-1
    sopp.sem_flg=SEM_UNDO;
    sopv.sem_num=0;
    sopv.sem_op=1;
    sopv.sem_flg=SEM_UNDO;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    if(!fork()){
        for(i=0;i<N;i++){
            semop(sems_id,&sopp,1);
            p[0]=p[0]+1;
            semop(sems_id,&sopv,1);
        }
        exit(0);
    }else{
        for(i=0;i<N;i++){
            semop(sems_id,&sopp,1);
            p[0]=p[0]+1;
            semop(sems_id,&sopv,1);
        }
        wait(NULL);
        gettimeofday(&end,NULL);
        printf("result=%d,using time=%ld\n",p[0],(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    }
    return 0;
}

