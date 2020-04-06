#include <func.h>

void *threadFunc(void *p){
    time_t t;
    time(&t);
    char buf[128]={0};
    char *ptime=ctime_r(&t,buf);
    printf("I am child thread:%s\n",ptime);
    pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    sleep(3);
    time_t t;
    time(&t);
    char buf[128]={0};
    char *ptime=ctime_r(&t,buf);
    printf("I am main thread:%s\n",ptime);
    return 0;
}

