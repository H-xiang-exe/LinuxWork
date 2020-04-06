#include <func.h>

int main(int argc,char *argv[])
{
    int sems_id;
    sems_id=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(sems_id,-1,"semget");
    unsigned short arr[2]={10,0};//仓库个数，产品个数
    int ret=semctl(sems_id,0,SETALL,arr);
    ERROR_CHECK(ret,-1,"semctl");
    bzero(arr,sizeof(arr));
    ret=semctl(sems_id,0,GETALL,arr);
    ERROR_CHECK(ret,-1,"semctl");
    printf("space value=%d,product num=%d\n",arr[0],arr[1]);
    //父进程是生产者，子进程是消费者
    struct sembuf sopp,sopv;
    if(!fork()){
        while(1){//子进程
            sopp.sem_num=1;
            sopp.sem_op=-1;
            sopp.sem_flg=SEM_UNDO;
            sopv.sem_num=0;
            sopv.sem_op=1;
            sopv.sem_flg=SEM_UNDO;
            printf("I am customer,space num=%d,product num=%d\n"
                   ,semctl(sems_id,0,GETVAL),semctl(sems_id,1,GETVAL));
            printf("I am customer start cost\n");
            semop(sems_id,&sopp,1);
            semop(sems_id,&sopv,1);
            printf("I am customer,space num=%d,product num=%d\n",semctl(sems_id,0,GETVAL),semctl(sems_id,1,GETVAL));
            printf("------------------------------------------------\n");
            sleep(2);
        }
    }else{//父进程——生产者
        while(1){
            sopp.sem_num=0;
            sopp.sem_op=-1;
            sopp.sem_flg=SEM_UNDO;
            sopv.sem_num=1;
            sopv.sem_op=1;
            sopv.sem_flg=SEM_UNDO;
            printf("I am producer,space num=%d,product num=%d\n"
                   ,semctl(sems_id,0,GETVAL),semctl(sems_id,1,GETVAL));
            printf("I am producer start produce\n");
            semop(sems_id,&sopp,1);
            semop(sems_id,&sopv,1);
            printf("I am producer,space num=%d,product num=%d\n"
                   ,semctl(sems_id,0,GETVAL),semctl(sems_id,1,GETVAL));
            printf("------------------------------------------------\n");
            sleep(1);
        }
    }
    return 0;
}

