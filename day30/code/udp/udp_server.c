#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);//ip地址+端口号
    int socketFd;//初始化一个socket->缓冲区
    socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    printf("socketFd=%d\n",socketFd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
    //主机端口字节序转网络字节序，字符串转换为整型数
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    //点分十进制ip地址转换为网络字节序
    int ret;
    ret=bind(socketFd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
    //强制类型转换是为了向前兼容
    //udp在bind时就激活了
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    //一定要先recvfrom
    char buf[128]={0};
    socklen_t addrlen=sizeof(struct sockaddr);
    recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr *)&client,&addrlen);
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    printf("%s\n",buf);
    sendto(socketFd,"I am hungry",11,0,(struct sockaddr *)&client,sizeof(client));
    close(socketFd);
}
