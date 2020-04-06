#include "process_pool.h"

int main(int argc,char *argv[])
{
    if(argc!=3){
        printf("usuage:./server ip port\n");
        return -1;
    }
    char *ip=argv[1];
    char *port=argv[2];
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_addr.s_addr=inet_addr(ip);
    ser.sin_port=htons(atoi(port));
    ser.sin_family=AF_INET;
    socklen_t addrlen=sizeof(ser);
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&ser,addrlen);
    ERROR_CHECK(ret,-1,"connect");
    int datalen;
    char buf[1000]={0};
    //先接文件名
    recv(socketFd,&datalen,4,MSG_WAITALL);
    recv(socketFd,buf,datalen,MSG_WAITALL);//拿到文件名
    //建立文件
    int i=1;
    int fd;
    char tmp[1000];
    strcpy(tmp,buf);
    while((fd=open(buf,O_RDWR|O_CREAT|O_EXCL,0666))==-1){//创建文件失败，文件名已存在
        bzero(buf,sizeof(buf));
        sprintf(buf,"%s%d",tmp,i);
        i++;
    }
    //接收文件大小
    off_t fileSize;
    recv(socketFd,&datalen,4,MSG_WAITALL);
    recv(socketFd,&fileSize,datalen,MSG_WAITALL);//拿到文件名
    ftruncate(fd,fileSize);
    char *pStart=(char *)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(pStart,(char*)-1,"mmap");
    ret=recvCycle(socketFd,pStart,fileSize);
    if(ret==0){
        munmap(pStart,fileSize);//解除内存映射
        printf("已下载：100.00%%\n");
    }else{
        printf("loading error!\n");
    }
    close(fd);
    close(socketFd);
    return 0;
}

