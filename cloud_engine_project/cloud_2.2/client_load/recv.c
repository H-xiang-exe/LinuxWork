#include "process_pool.h"

int recvInfo(int socketFd){
    int flag;
    int ret;
    ret=recv(socketFd,&flag,sizeof(flag),MSG_WAITALL);
    if(ret==0){
        printf("logout success\n");
        return -1;
    }
    if(flag==0){//路径
        ret=recvPath(socketFd);
        if(ret==-1){
            return -1;
        }
    }else if(flag==1){//传输的是文件
        ret=recvDoc(socketFd);
    }else{
        printf("wrong commander!\n");
    }
    return 0;
}

int recvDoc(int socketFd){
    int datalen;
    char buf[1000]={0};
    //先接文件名
    recv(socketFd,&datalen,4,MSG_WAITALL);
    recv(socketFd,buf,datalen,MSG_WAITALL);//拿到文件名
    //接收文件大小
    off_t fileSize,downLoadSize=0,lastLoadSize=0,fileSlice;
    recv(socketFd,&datalen,4,MSG_WAITALL);
    recv(socketFd,&fileSize,datalen,MSG_WAITALL);//拿到文件大小
    fileSlice=fileSize/10000;
    //建立文件
    int ret;
    int i=1;
    int fd;
    char tmp[1000];
    strcpy(tmp,buf);
    struct stat mystat;
    ret=stat(buf,&mystat);
    if(ret==0&&mystat.st_size<fileSize){//文件已存在且小于完整文件的大小，说明需要断点续传
            fd=open(buf,O_WRONLY|O_APPEND);
            downLoadSize=lastLoadSize=mystat.st_size;
    }else{
        while((fd=open(buf,O_WRONLY|O_CREAT|O_EXCL,0666))==-1){//创建文件失败，文件名已存在
            bzero(buf,sizeof(buf));
            sprintf(buf,"%s%d",tmp,i);
            i++;
        }
    }
    while(1){
        ret=recvCycle(socketFd,&datalen,4);
        if(ret==0&&datalen>0){
            bzero(buf,sizeof(buf));
            ret=recvCycle(socketFd,buf,datalen);
            if(ret==-1){
                printf("diconnected!transmitting failed!\n");
                break;
            }
            write(fd,buf,datalen);
            downLoadSize+=datalen;
            if(downLoadSize-lastLoadSize>fileSlice){
                printf("已下载：%5.2f%%\r",(double)downLoadSize/fileSize*100);
                fflush(stdout);
                lastLoadSize=downLoadSize;
            }
        }else{
            if(ret==-1){
                printf("diconnected!transmitting failed!\n");
                break;
            }
            else{
                printf("已下载：100.00%%\n");
            }
            break;
        }
    }
    close(fd);
    return 0;
}

int recvPath(int socketFd){
    int len,ret;
    char buf[100]={0};
    ret=recv(socketFd,&len,sizeof(int),0);
    ret=recv(socketFd,&buf,len,MSG_WAITALL);
    if(ret==0){
        printf("server dicconected!\n");
        return -1;
    }
    printf("%s\n",buf);
    return 0;
}

