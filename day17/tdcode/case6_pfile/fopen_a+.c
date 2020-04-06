#include<stdio.h>
#include<string.h>
int main(int argc,char **argv){
	if(argc!=2){
		printf("error args!\n");
		return -1;
	}
	FILE *fp=fopen(argv[1],"a+");
	if(fp==NULL){
		perror("fopen");
		return -1;
	}
	char str2[50]={0};//用于放置从文件中读取的内容
	fscanf(fp,"%s",str2);
	puts(str2);
	
	char str1[50]="howareyou";
	fprintf(fp,"%s",str1);

	memset(str2,0,sizeof(str2));	
	fscanf(fp,"%s",str2);
	puts(str2);
	fclose(fp);
	return 0;
}
