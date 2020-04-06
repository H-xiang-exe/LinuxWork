#include "client.h"

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    //初始化一个socket，有一个缓冲区
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&ser,sizeof(ser));
    ERROR_CHECK(ret,-1,"connect");
    char buf[1000]={0};
    //先接文件名
    int datalen;
    recvCycle(socketFd,&datalen,4);//先接火车头，文件名长度
    recvCycle(socketFd,buf,datalen);//拿车厢，即文件名
    int fd;//新建文件并确定名字，重名则在文件尾加1
    //如若"file"存在，则命名为"file1";"file1"存在则命名为"file2",以此类推
    int i=1;
    char tmp[1000];
    strcpy(tmp,buf);//保存初始名字
    while((fd=open(buf,O_RDWR|O_CREAT|O_EXCL,0666))==-1){//O_EXCL表明当文件已存在时,强制创建失败
        bzero(buf,sizeof(buf)); 
        sprintf(buf,"%s%d",tmp,i);
        i++;
    }
    //接收文件大小
    off_t fileSize;
    //文件总大小，文件已下载大小,文件分成10000片后每片大小,此次之前已下载大小
    recvCycle(socketFd,&datalen,4);//火车头
    recvCycle(socketFd,&fileSize,datalen);//火车厢——文件大小
    //接文件内容
    struct timeval start,end;
    gettimeofday(&start,NULL);
    ftruncate(fd,fileSize);//先做出一个大小为fileSize的文件
    char *pStart=(char*)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ret=recvCycle(socketFd,pStart,fileSize);//接数据
    if(ret==0){
        munmap(pStart,fileSize);
        gettimeofday(&end,NULL);
        printf("100.00%%\n");
        long total_time=(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec;
        printf("using time=%ld\n",total_time);
    }else{
        printf("error load!\n");
    }
    close(socketFd);
    return 0;
}
