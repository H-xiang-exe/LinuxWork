#include <func.h>
void *threadFunc(void *p){
    pthread_mutex_t *pmutex=(pthread_mutex_t*)p;
    pthread_mutex_unlock(pmutex);
    pthread_mutex_lock(pmutex);
    printf("I am child thread,exit\n");
    return NULL;
}
int main(int argc,char *argv[])
{
    pthread_mutex_t mutex;
    int ret=pthread_mutex_init(&mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    pthread_t pthid;
    ret=pthread_create(&pthid,NULL,threadFunc,&mutex);
    pthread_mutex_lock(&mutex);
    pthread_join(pthid,NULL);
    printf("I am main thread\n");
    return 0;
}

