#include<func.h>
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR|O_CREAT,0664);
	if(fd==-1){
		perror("fopen");
		return  -1;
	}
	printf("fd=%d\n",fd);
	return 0;
}
