#include<stdio.h>
#include<sys/stat.h>
int main(int argc,char **argv){
	if(argc!=2){
		printf("error args!\n");
		return -1;
	}
	chmod(argv[1],0754);
	return 0;
}
