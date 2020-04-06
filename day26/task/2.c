#include <func.h>
void *threadFunc(void *p){
   char *pStr=(char*)malloc(10);
   strcpy(pStr,"hello");
   printf("I am child thread %s\n",pStr);
   pthread_exit(pStr);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    void *p;
    pthread_join(pthid,&p);
    printf("main thread=%s\n",(char*)p);
    free(p);
    return 0;
}

