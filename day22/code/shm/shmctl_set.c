#include <func.h>

int main(int argc,char *argv[])
{
    int shmid;
    shmid=shmget(1001,4096,IPC_CREAT|0600);//4096相当于一个物理页,IP_CREAT判断是否存在
    //共享内存段
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmget sucess %d\n",shmid);
    struct shmid_ds buf;
   
    int ret=shmctl(shmid,IPC_STAT,&buf);
    ERROR_CHECK(ret,-1,"shmctl");
    printf("cuid=%d,mode=%o,size=%ld,nattch=%ld\n",
           buf.shm_perm.cuid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    
    buf.shm_perm.mode=0666;
    ret=shmctl(shmid,IPC_SET,&buf);
    ERROR_CHECK(ret,-1,"shmctl");

    bzero(&buf,sizeof(buf));
    ret=shmctl(shmid,IPC_STAT,&buf);
    ERROR_CHECK(ret,-1,"shmctl");
    printf("cuid=%d,mode=%o,size=%ld,nattch=%ld\n",
           buf.shm_perm.cuid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    
    ret=shmctl(shmid,IPC_RMID,NULL);
    ERROR_CHECK(ret,-1,"shmctl");

    return 0;
}

