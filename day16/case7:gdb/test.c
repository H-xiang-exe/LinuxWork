#include<stdio.h>
int main(int argc,char **argv){
	if(argc!=2){
		printf("args error!\n");
	}
	FILE *fp=fopen(argv[1],"r+");
	if(fp==NULL){
		perror("fopen");
	}
	char str[50]={0};
	fscanf(fp,"%s",str);
	puts(str);
	return 0;
}
