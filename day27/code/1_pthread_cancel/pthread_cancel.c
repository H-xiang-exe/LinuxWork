#include <func.h>
void *threadFunc(void *p){
    printf("I am child thread\n");
    sleep(3);
    printf("I am child thread I wake\n");
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    //线程被cancel以后，返回值为-1
    printf("child exit code=%ld\n",threadRet);
    return 0;
}

