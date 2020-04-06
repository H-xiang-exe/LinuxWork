#include <func.h>
struct msgbuf{
    long mtype;
    char mtext[128];
};
int main(int argc,char *argv[])
{
    int msgid=msgget(1000,IPC_CREAT|0600);
    struct msgbuf msg;
    int ret;
    if(!fork()){
        msg.mtype=1;
        strcpy(msg.mtext,"I am strong");
        ret=msgsnd(msgid,&msg,strlen(msg.mtext),0);
        ERROR_CHECK(ret,-1,"msgsnd");
    }else{
        bzero(&msg,sizeof(msg));
        ret=msgrcv(msgid,&msg,sizeof(msg.mtext),0,0);
        printf("ret=%d,type=%ld,%s\n",ret,msg.mtype,msg.mtext);
        wait(NULL);
    }
    return 0;
}

