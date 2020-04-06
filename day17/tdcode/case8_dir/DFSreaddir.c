#include"func.h"
void printDir(char *path,int width){
	DIR *pdir=opendir(path);
	struct dirent *pbuf;
	char newPath[1024]={0};
	while((pbuf=readdir(pdir))!=NULL){
		if(strcmp(pbuf->d_name,".")==0||strcmp(pbuf->d_name,"..")==0){
			continue;
		}
		printf("%*s%s\n",width," ",pbuf->d_name);
		sprintf(newPath,"%s%s%s",path,"/",pbuf->d_name);
		if(pbuf->d_type==4){
			printDir(newPath,width+4);
		}
	}
	closedir(pdir);
}
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	printDir(argv[1],0);
	return 0;
}	
