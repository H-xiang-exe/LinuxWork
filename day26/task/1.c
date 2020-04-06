#include <func.h>
void * threadFunc(void *p){
    long pNum=(long)p;
    printf("child thread %ld\n",pNum);
    p=(void*)2;
    pthread_exit(p);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    long i=1;
    int ret=pthread_create(&pthid,NULL,threadFunc,(void*)i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    long RetVal;
    ret=pthread_join(pthid,(void **)&RetVal);//传一个地址过去，所以要用
    //取地址符，该地址内装的是一级指针，所以地址为二级指针类型，需要强制
    //类型转换
    printf("child thread exit %ld\n",RetVal);
    return 0;
}

