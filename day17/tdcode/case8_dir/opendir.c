#include"func.h"
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	DIR *pdir=opendir(argv[1]);
	RET_CHECK(pdir,NULL,"opendir");
	closedir(pdir);
	return 0;
}	
