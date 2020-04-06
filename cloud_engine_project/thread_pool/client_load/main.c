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
    while((fd=open(buf,O_WRONLY|O_CREAT|O_EXCL,0666))==-1){//创建文件失败，文件名已存在
        bzero(buf,sizeof(buf));
        sprintf(buf,"%s%d",tmp,i);
        i++;
    }
    //接收文件大小
    off_t fileSize,downLoadSize=0,lastLoadSize=0,fileSlice;
    recv(socketFd,&datalen,4,MSG_WAITALL);
    recv(socketFd,&fileSize,datalen,MSG_WAITALL);//拿到文件名
    fileSlice=fileSize/10000;
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
    close(socketFd);
    return 0;
}

