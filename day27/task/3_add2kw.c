#include <func.h>
#define N 20000000
typedef struct{
    pthread_mutex_t mutex;
    long sum;
}Data;
void *threadFunc(void *p){
    Data *pdata=(Data*)p;
    for(int i=0;i<N;i++){
        pthread_mutex_lock(&pdata->mutex);
        (pdata->sum)++;
        pthread_mutex_unlock(&pdata->mutex);
    }
}
int main(int argc,char *argv[])
{
    Data data;
    data.sum=0;
    int ret=pthread_mutex_init(&data.mutex,NULL);//初始化
    struct timeval beg,end;//定义计时变量
    gettimeofday(&beg,NULL);//开始计时
    pthread_t pthid;
    ret=pthread_create(&pthid,NULL,threadFunc,&data);
    THREAD_ERROR_CHECK(ret,"pthread_create");//创造子线程并检查是否成功
    for(int i=0;i<N;i++){
        pthread_mutex_lock(&data.mutex);
        data.sum++;
        pthread_mutex_unlock(&data.mutex);
    }
    pthread_join(pthid,NULL);
    gettimeofday(&end,NULL);
    printf("main thread sum=%ld,using time=%ld\n",data.sum,(end.tv_sec-beg.tv_sec)*1000000+end.tv_usec-beg.tv_usec);
    return 0;
}

