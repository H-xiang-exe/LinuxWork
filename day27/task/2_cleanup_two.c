#include <func.h>
void cleanup(void *p){
    printf("I am cleanup,%ld\n",(long)p);
}
void *threadFunc(void *p){
    pthread_cleanup_push(cleanup,(void*)1);
    pthread_cleanup_push(cleanup,(void*)2);
    printf("I am child thread\n");
    sleep(3);
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long Retval;
    ret=pthread_join(pthid,(void**)&Retval);
    printf("child exit code=%ld\n",Retval);
    return 0;
}

