#include"func.h"
int main(int argc,char **argv){
	ARGS_CHECK(argc,3);
	DIR *pdir=opendir(argv[1]);
	RET_CHECK(pdir,NULL,"opendir");
	struct dirent *pbuf;
	char Path[1024];
	while((pbuf=readdir(pdir))!=NULL){
		if(strcmp(pbuf->d_name,argv[2])==0){
			chdir(argv[1]);
			getcwd(Path,sizeof(Path));
			printf("Path:%s\n",Path);
			closedir(pdir);
			return 0;
		}
	}
	if(pbuf==NULL){
		printf("No this file!\n");
	}
	closedir(pdir);
	return 0;
}
