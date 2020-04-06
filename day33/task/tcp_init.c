#include "process_pool.h"

int tcp_init(int *socketFd,char *ip,char *port){
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sfd,-1,"socket");
    int reuse=1;
    int ret;
    ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_addr.s_addr=inet_addr(ip);
    ser.sin_port=htons(atoi(port));
    ser.sin_family=AF_INET;
    ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
    listen(sfd,10);
    *socketFd=sfd;
    return 0;
}

