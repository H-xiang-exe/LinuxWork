#include <func.h>//清理函数
void cleanup(void *p)
{
    printf("I am cleanup,%ld\n",(long)p);
}

void * threadFunc(void *p)
{
    pthread_cleanup_push(cleanup,(void*)1);
    pthread_cleanup_push(cleanup,(void*)2);
    printf("I am child thread\n");
    sleep(3);//被cancel,弹出清理函数栈的所有函数并执行
    printf("I am child thread I am wake\n");
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}
int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    //线程被cancel以后，接收到的返回值是-1
    printf("child exit code=%ld\n",threadRet);
    return 0;
}
