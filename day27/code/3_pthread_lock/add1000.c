#include <func.h>
int global_k=0;
#define N 10000000
void * threadFunc(void *p)
{
    pthread_mutex_t *pmutex=(pthread_mutex_t*)p;
    int i;
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(pmutex);
        global_k+=1;
        pthread_mutex_unlock(pmutex);
    }
    return NULL;

}
int main()
{
    int ret,i;
    pthread_mutex_t mutex;
    ret=pthread_mutex_init(&mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    struct timeval start,end;
    gettimeofday(&start,NULL);//获取当前秒数和微秒数
    pthread_t pthid;//线程ID
    ret=pthread_create(&pthid,NULL,threadFunc,&mutex);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&mutex);
        global_k+=1;//不是原子操作
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(pthid,NULL);
    gettimeofday(&end,NULL);
    printf("I am main thread total=%d,using time=%ld\n",global_k,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    return 0;
}
