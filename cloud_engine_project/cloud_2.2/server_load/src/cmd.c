#include "process_pool.h"

int cmdParse(pCmdRet_t pCmdRet)
{
    if(strcmp(pCmdRet->cmd,"cd")==0){
        do_cd(pCmdRet);
    }else if(strcmp(pCmdRet->cmd,"puts")==0){
        do_puts(pCmdRet);
    }else if(strcmp(pCmdRet->cmd,"gets")==0){
        do_gets(pCmdRet);
    }else if(strcmp(pCmdRet->cmd,"remove")==0){
        do_remove(pCmdRet);
    }else{
        int flag=0;
        char wrong[100]="wrong command";
        send(pCmdRet->newFd,&flag,sizeof(int),0);
        int len=strlen(wrong);
        send(pCmdRet->newFd,&len,sizeof(len),0);
        send(pCmdRet->newFd,wrong,len,0);
    }
    return 0;
}

static char *fileType(mode_t md){
    if(S_ISREG(md))
    {
        return "-"; 

    }else if(S_ISDIR(md))
    {
        return "d";

    }else if(S_ISFIFO(md))
    {
        return "p";

    }else 
    {
        return "o" ;

    }
}

int do_cd(pCmdRet_t p){
    int flag=0;
    char dir[128]={0};
    if(p->postfix!=NULL){
        chdir(p->postfix);
        getcwd(dir,sizeof(dir));
        //需要把当前目录传给客户端，因此需要newFd;
        send(p->newFd,&flag,sizeof(flag),0);//发送传输文件路径的标志
        int len=strlen(dir);
        send(p->newFd,&len,sizeof(int),0);
        send(p->newFd,dir,len,0);
    }
    return 0;
}

int do_puts(pCmdRet_t p){
    printf("do_puts\n");
    recvDoc(p->newFd);
    printf("do_puts_finish\n");
    int flag=0;
    char buf[100]="upload finished!";
    int len=strlen(buf)-1;
    send(p->newFd,&flag,sizeof(flag),0);
    send(p->newFd,&len,sizeof(int),0);
    send(p->newFd,buf,len,0);
    return 0;
}

int do_gets(pCmdRet_t p){
    int flag=1;//传输文件
    send(p->newFd,&flag,sizeof(int),0);
    trans_file(p);
    return 0;
}

int do_remove(pCmdRet_t p){
    char cmd[1000]={0};
    char buf[1000]={0};
    sprintf(cmd,"rm -rf %s",p->postfix);
    system(cmd);//执行删除命令
    sprintf(buf,"%s removed!\n",p->postfix);
    int flag=0;//不是文件
    int len=strlen(buf)-1;
    send(p->newFd,&flag,sizeof(flag),0);
    send(p->newFd,&len,sizeof(int),0);
    send(p->newFd,buf,len,0);
    while(1);
    return 0;
}

int do_pwd(int newFd){
    int flag=0;
    char dir[128]={0};
    getcwd(dir,sizeof(dir));
    printf("%s\n",dir);
    send(newFd,&flag,sizeof(flag),0);//发送传输文件路径的标志
    int len=strlen(dir);
    printf("len=%d\n",len);
    send(newFd,&len,sizeof(int),0);
    send(newFd,dir,len,0);
    return 0;
}

int do_ls(int newFd){
    int flag;
    char buf[1000];
    DIR *pdir=opendir("./");
    if(pdir==NULL){
        flag=-1;
        send(newFd,&flag,sizeof(flag),0);
    }else{
        struct dirent *mydir;
        while((mydir=readdir(pdir))!=NULL){
            if(strncmp(mydir->d_name,".",1)==0||strncmp(mydir->d_name,"..",2)==0){
                continue;
            }
            struct stat mystat;
            bzero(&mystat,sizeof(mystat));
            stat(mydir->d_name,&mystat);
            bzero(buf,sizeof(buf));
            sprintf(buf,"%-2s%ld %s %s %-10s %10ldB %s",fileType(mystat.st_mode)
                    ,mystat.st_nlink,getpwuid(mystat.st_uid)->pw_name
                    ,getgrgid(mystat.st_gid)->gr_name,mydir->d_name,mystat.st_size
                    ,ctime(&mystat.st_mtime));
            flag=0;
            send(newFd,&flag,sizeof(flag),0);
            int len=strlen(buf);
            send(newFd,&len,sizeof(int),0);
            send(newFd,buf,len,0);
        }
    }
    return 0;
}

