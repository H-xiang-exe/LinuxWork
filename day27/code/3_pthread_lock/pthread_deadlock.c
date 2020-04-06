#include <func.h>
int main(int argc,char *argv[])
{
    pthread_mutex_t mutex;
    int ret=pthread_mutex_init(&mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    pthread_mutex_lock(&mutex);
    pthread_mutex_lock(&mutex);
    return 0;
}

