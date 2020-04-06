#include <func.h>
void cleanup(void *p){//清理函数
    free(p);
    p=NULL;
    printf("I am cleanup\n");
}
void *threadFunc(void *p){
    char *pStr=(char *)malloc(20);
    pthread_cleanup_push(cleanup,pStr);
    strcpy(pStr,"hello");
    printf("I am child thread\n");
    sleep(3);//被cancel，没有free，内存泄漏
    printf("I am child thread I wake\n");
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
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

