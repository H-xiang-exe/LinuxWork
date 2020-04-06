#include<func.h>
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	FILE *fp=fopen(argv[1],"rb+");
	if(fp==NULL){
		perror("open");
		return -1;
	}
	int fd=fileno(fp);
	int arr[3]={1,2,3};
	write(fd,arr,sizeof(arr));
	return 0;
}
