#include<func.h>
void change(int fd){
	ftruncate(fd,10);
}
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	int fd=open(argv[1],O_RDWR);
	if(fd==-1){
		perror("open");
		return -1;
	}
	change(fd);
	close(fd);
	return 0;
}
