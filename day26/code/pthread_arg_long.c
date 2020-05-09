#include <func.h>

void *threadFunc(void *p){
    long pNum=(long)p;
    printf("I am child thread ,this time i=%ld\n",pNum);
    return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t pthid,pthid1;
    int i=5;
    int ret=pthread_create(&pthid,NULL,threadFunc,(void*)i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    usleep(1000);
    i=10;
    ret=pthread_create(&pthid1,NULL,threadFunc,(void*)i);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread\n");
    pthread_join(pthid,NULL);
    pthread_join(pthid1,NULL);
    return 0;
}

