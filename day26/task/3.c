#include <func.h>
#define N 50000000
void *threadFunc(void *p){
    long *add=(long*)p;
    for(int i=0;i<N;i++){
        (*add)++;
    }
    return NULL;
}
int main(int argc,char *argv[])
{
    long sum=0;
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,(void*)&sum);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    for(int i=0;i<N;i++){
        sum++;
    }
    pthread_join(pthid,NULL);
    printf("main thread sum=%ld\n",sum);
    return 0;
}

