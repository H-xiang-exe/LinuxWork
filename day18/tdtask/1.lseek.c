#include <func.h>
typedef struct student{
    int no;
    char name[10];
    float score;
}student;
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    student st[3]={
        {1001,"xiang",98.5},
        {1002,"zhao",99},
        {1003,"li",98}
    };
    int fd=open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    char buf[128]={0};
    for(int i=0;i<3;i++){
        sprintf(buf,"%d %s %f\n",st[i].no,st[i].name,st[i].score);//结构体写入文件需要转换为字符串
        write(fd,buf,strlen(buf));
        memset(buf,0,sizeof(buf));
    }
    memset(buf,0,sizeof(buf));
    int ret=lseek(fd,0,SEEK_SET);
    ERROR_CHECK(ret,-1,"lseek");
    read(fd,buf,sizeof(buf));
    printf("%s\n",buf);
    close(fd);
    return 0;
}

