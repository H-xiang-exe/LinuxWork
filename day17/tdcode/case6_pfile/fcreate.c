#include<stdio.h>
int main(int argc,char **argv){
	if(argc!=2){
		printf("error args!\n");
		return -1;
	}
	FILE *fp=fopen(argv[1],"w+");
	if(fp==NULL){
		perror("fopen");
		return -1;
	}
	char str[50]={0};
	fscanf(fp,"%s",str);
	puts(str);
	fclose(fp);
	return 0;
}
