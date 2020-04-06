#include"process_pool.h"

int sendFd(int sfd,int fd){
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    //用户态要给什么样的信息说明 
    struct iovec iov[1];//一些附加信息
    char buf[10]="hello";
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=1;
    //要传递什么样的内核控制信息
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    int *fdptr=(int *)CMSG_DATA(cmsg);
    *fdptr=fd;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;

    int ret;
    ret=sendmsg(sfd,&msg,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}


int recvFd(int sfd,int *fd){
    struct msghdr msg;
    bzero(&msg,sizeof(msg));
    //用户态要接什么样的信息说明 
    struct iovec iov[1];//一些附加信息
    char buf[10]={0};
    iov[0].iov_base=buf;
    iov[0].iov_len=5;
    msg.msg_iov=iov;
    msg.msg_iovlen=1;//表示有1个iovec大小
    //要传递什么样的内核控制信息
    struct cmsghdr *cmsg;
    int len=CMSG_LEN(sizeof(int));
    cmsg=(struct cmsghdr*)calloc(1,len);
    cmsg->cmsg_len=len;
    cmsg->cmsg_level=SOL_SOCKET;
    cmsg->cmsg_type=SCM_RIGHTS;
    msg.msg_control=cmsg;
    msg.msg_controllen=len;
    int ret;
    ret=recvmsg(sfd,&msg,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    *fd=*(int *)CMSG_DATA(cmsg);
    return 0;
}
