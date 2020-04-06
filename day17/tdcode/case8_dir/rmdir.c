#include"func.h"
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	int ret=rmdir(argv[1]);
	//if(ret==-1){
	//	perror("mkdir");
	//	return -1;
	//}
	RET_CHECK(ret,-1,"rmdir");
	return 0;
}	
