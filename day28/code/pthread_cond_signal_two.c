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
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    thread_data_t t;
    pthread_cond_init(&t.cond,NULL);
    pthread_mutex_init(&t.mutex,NULL);
    pthread_t pthid[2];
    for(int i=0;i<2;i++){
        pthread_create(pthid+i,NULL,threadFunc,&t);
    }
    sleep(3);
    int ret=pthread_cond_signal(&t.cond);
    THREAD_ERROR_CHECK(ret,"pthread_cond_signal");
    for(int i=0;i<2;i++){
        pthread_join(pthid[i],NULL);
    }
    printf("I am main thread\n");
    return 0;
}

