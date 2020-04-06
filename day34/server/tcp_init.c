#include"process_pool.h"

int tcp_init(int *socketFd,char *ip,char *port){
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_addr.s_addr=inet_addr(ip);
    ser.sin_port=htons(atoi(port));
    ser.sin_family=AF_INET;
    int ret;
    int reuse=1;
    ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sfd,10);
    *socketFd=sfd;
    return 0;
}


