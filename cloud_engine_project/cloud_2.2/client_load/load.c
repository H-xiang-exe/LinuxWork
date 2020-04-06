#include "process_pool.h"
#include <shadow.h>                                                
#include <errno.h>
#include <crypt.h>

int loadRequest(int socketFd){
    int len;                             
    char name[1000];        
    bzero(name,sizeof(name));
    //发送账户名
    printf("请输入ID：");                
    fflush(stdout);                      
    read(STDIN_FILENO,name,sizeof(name));
    len=strlen(name)-1;                  
    send(socketFd,&len,sizeof(int),0);   
    send(socketFd,name,len,0);
    //判断服务端是否有此用户名
    char nameFlag;
    recv(socketFd,&nameFlag,1,0);
    if(nameFlag=='0'){
        printf("用户名错误，请重新输入\n");
        return -1;
    }
    //输入密码
    char *pwd=getpass("请输入密码：");   
    //接收盐值
    char salt[500]={0};
    recvCycle(socketFd,&len,sizeof(int));
    recvCycle(socketFd,salt,len);
    //获取本地输入的密码对应的密文并发送给服务端
    char *cpwd=crypt(pwd,salt);
    len=strlen(cpwd);
    send(socketFd,&len,sizeof(int),0);   
    send(socketFd,cpwd,len,0);           
    //接收登录服务端成功或失败的消息
    int flag;
    recvCycle(socketFd,&flag,sizeof(int));
    if(flag==1){
        printf("登录成功\n");
        return 0;
    }else{
        printf("登录失败\n");
        return -1;
    }
}
