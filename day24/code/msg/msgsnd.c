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
    msg.mtype=1;
    strcpy(msg.mtext,"I am strong");
    ret=msgsnd(msgid,&msg,strlen(msg.mtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");
}
