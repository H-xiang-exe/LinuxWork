#include<stdio.h>
int main(int argc,char **argv){
	if(argc!=2){
		printf("error args!\n");
		return -1;
	}
	FILE *fp=fopen(argv[1],"r+");
	if(fp==NULL){
		perror("fopen");
		return -1;
	}
	char ch;
	while((ch=fgetc(fp))!=EOF){
		if(ch<='z'&&ch>='a'){
			ch-=32;
		}
		fseek(fp,-1,SEEK_CUR);
		fputc(ch,fp);
	}
	fclose(fp);
	return 0;
}
