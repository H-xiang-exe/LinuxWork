#include "process_pool.h"

int sendFd(int sfd,int fd){
    struct msghdr msg;
    bzero(&msg,sizeof(msg));

    struct iovec iov[1];
    char buf[10]="hello";
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=1;

    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    int *fdptr;
    fdptr=(int *)CMSG_DATA(cmsg);
    *fdptr=fd;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    
    printf("sendFd:sfd=%d\n",sfd);
    int ret=sendmsg(sfd,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}

int recvFd(int sfd,int *fd){
    struct msghdr msg;
    bzero(&msg,sizeof(msg));

    struct iovec iov[1];
    char buf[10]={0};
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=1;

    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;

    int ret=recvmsg(sfd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    int *fdptr;
    fdptr=(int *)CMSG_DATA(cmsg);
    *fd=*fdptr;
    return 0;

}

