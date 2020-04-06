#include "process_pool.h"
#include <shadow.h>
#include <errno.h>
#include <crypt.h>

void getsalt(char *salt,char *passwd){
    int i,j;
    for(i=0,j=0;passwd[i]&&j!=3;i++){
        if(passwd[i]=='$'){
            j++;
        }
    }
    strncpy(salt,passwd,i-1);//第三个'$'前的字符串即盐值
}

int loadCheck(int newFd){
    UsrLoad_t usr;
    bzero(&usr,sizeof(usr));
    int len;
    //收到账户名
    recvCycle(newFd,&len,sizeof(int));
    recvCycle(newFd,usr.name,len);
    struct spwd *sp;
    char salt[512]={0};
    char nameFlag='1';
    sp=getspnam(usr.name);
    if(sp==NULL){
        perror("getspnam");
        nameFlag='0';//服务端没有此用户名，向客户端通报，让其重新输入
        send(newFd,&nameFlag,1,0);
        return -1;
    }
    send(newFd,&nameFlag,1,0);
    getsalt(salt,sp->sp_pwdp);//获取盐值
    //发送盐值
    len=strlen(salt);
    send(newFd,&len,sizeof(int),0);
    send(newFd,salt,len,0);
    //接收客户端发来的密文
    char cpwd[500];
    recvCycle(newFd,&len,sizeof(int));
    recvCycle(newFd,cpwd,len);
    //将客户端发来的密文与服务端存储的密文进行对比
    int flag;
    if(!strncmp(sp->sp_pwdp,cpwd,len)){
        flag=1;
        send(newFd,&flag,sizeof(flag),0);
        return 0;
    }else{
        flag=0;
        send(newFd,&flag,sizeof(flag),0);
        return -1;
    }
}

