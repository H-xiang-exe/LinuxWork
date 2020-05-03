#include <func.h>

int main(int argc,char *argv[])
{
    int sems_id;
    sems_id=semget(1001,2,IPC_CREAT|0600);
    ERROR_CHECK(sems_id,-1,"semget");
    unsigned short arr[2]={2,5};
    int ret=semctl(sems_id,0,SETALL,arr);
    ERROR_CHECK(ret,-1,"semctl");
    bzero(arr,sizeof(arr));//清空数组
    semctl(sems_id,0,GETALL,arr);//获取信号量的值到arr
    printf("arr[0]=%d,arr[1]=%d\n",arr[0],arr[1]);//
    return 0;
}

