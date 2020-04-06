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
	long off;
	while((ch=fgetc(fp))!=EOF){
		off=ftell(fp);
		printf("off=%ld\n",off);
	}
	fclose(fp);
	return 0;
}
