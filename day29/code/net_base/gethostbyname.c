#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    struct hostent *p;
    p=gethostbyname(argv[1]);
    if(NULL==p){
        printf("gethostbyname failed\n");
        return -1;
    }
    printf("%s\n",p->h_name);//主机名
    int i;
    for(int i=0;p->h_aliases[i]!=NULL;i++){
        printf("%s\n",p->h_aliases[i]);//打印主机别名
    }
    printf("%d\n",p->h_addrtype);//IP地址类型
    printf("%d\n",p->h_length);//IP地址长度
    char ip[100]={0};
    for(i=0;p->h_addr_list[i]!=NULL;i++){
        printf("%s\n",inet_ntop(p->h_addrtype,p->h_addr_list[i],ip,sizeof(ip)));
    }
    return 0;
}

