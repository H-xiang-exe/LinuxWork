#include <func.h>
typedef struct{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}thread_data_t;
void *threadFunc(void *p){
    thread_data_t *pdata=(thread_data_t*)p;
    printf("I am child thread\n");
    pthread_mutex_lock(&pdata->mutex);
    pthread_cond_wait(&pdata->cond,&pdata->mutex);
    pthread_mutex_unlock(&pdata->mutex);
    printf("wait over\n");
}
int main(int argc,char *argv[])
{
    thread_data_t t;
    int ret;
    ret=pthread_cond_init(&t.cond,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_cond_init");
    ret=pthread_mutex_init(&t.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,&t);
    sleep(1);//等待线程wait之后再发signal
    ret=pthread_cond_signal(&t.cond);
    THREAD_ERROR_CHECK(ret,pthread_cond_signal);
    pthread_join(pthid,NULL);
    printf("I am main thread,join success\n");
    return 0;
}

