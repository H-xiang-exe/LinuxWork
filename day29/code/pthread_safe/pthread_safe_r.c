#include <func.h>
//子线程在cancel点之前陷入死循环cancel无法取消子线程
void *threadFunc(void *p){
    //ctime不是线程安全借口
    time_t t;
    time(&t);
    char buf[128]={0};
    char *ptime=ctime_r(&t,buf);//此时ptime不再指向数据段的静态局部变量区，而是指向了栈空间的buf空间
    printf("child ptime=%p,ptime=%p\n",ptime,&ptime);
    printf("I am child thread %s\n",ptime);
    sleep(3);
    printf("I am child thread %s\n",ptime);
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    sleep(2);
    time_t t;
    time(&t);
    char *ptime=ctime(&t);
    printf("main ptime=%p,ptime=%p\n",ptime,&ptime);
    printf("I am main thread %s\n",ptime);
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("child exit code=%ld\n",threadRet);
    return 0;
}

