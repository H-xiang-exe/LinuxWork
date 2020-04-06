#include"func.h"
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	DIR *pdir=opendir(argv[1]);
	struct dirent *pbuf;
	while((pbuf=readdir(pdir))!=NULL){
		printf("%s %d\n",pbuf->d_name,pbuf->d_type);		
	}
	RET_CHECK(pdir,NULL,"opendir");
	closedir(pdir);
	return 0;
}	
