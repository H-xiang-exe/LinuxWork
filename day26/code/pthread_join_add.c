#include <func.h>
const int N=1000000;
int global_val=0;

void *threadFunc(void *p){
    for(int i=0;i<N;i++){
        global_val+=1;
    }
    printf("I am child thread,global_val=%d\n",global_val);
    return NULL;
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    for(int i=0;i<N;++i){
        global_val+=1;
    }
    pthread_join(pthid,NULL);
    printf("I am main thread,global_val=%d\n",global_val);
    return 0;
}

