#include<func.h>
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	int fd;
	char buf[10]="abc";
	fd=open(argv[1],O_RDWR|O_APPEND);
	if(fd==-1){
		perror("open");
		return  -1;
	}
	int ret=write(fd,buf,3);
	ERROR_CHECK(ret,-1,"write");
	printf("fd=%d\n",fd);
	close(fd);
	return 0;
}
