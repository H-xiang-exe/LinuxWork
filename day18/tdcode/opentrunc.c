#include<func.h>
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR|O_TRUNC);
	if(fd==-1){
		perror("open");
		return  -1;
	}
	printf("fd=%d\n",fd);
	return 0;
}
