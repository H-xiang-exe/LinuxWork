#include <func.h>

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
    recv(socketFd,&datalen,4,0);//先接火车头，文件名长度
    recv(socketFd,buf,datalen,0);//拿车厢，即文件名
    int fd;//新建文件并确定名字，重名则在文件尾加1
    //如若"file"存在，则命名为"file1";"file1"存在则命名为"file2",以此类推
    int i=1;
    char tmp[1000];
    strcpy(tmp,buf);//保存初始名字
    while((fd=open(buf,O_WRONLY|O_CREAT|O_EXCL,0666))==-1){//O_EXCL表明当文件已存在时,强制创建失败
        bzero(buf,sizeof(buf)); 
        sprintf(buf,"%s%d",tmp,i);
        i++;
    }
    //接文件内容
    while(1){
        recv(socketFd,&datalen,4,0);//先接火车头
        if(datalen>0){
            recv(socketFd,buf,datalen,0);//拿车厢，即文件内容
            write(fd,buf,datalen);//把内容写进文件里
        }else{
            break;
        }
    }
    close(socketFd);
    return 0;
}
