#include"func.h"
int main(int argc,char **argv){
	ARGS_CHECK(argc,1);	
	//char buf[256]={0};
	//getcwd(buf,sizeof(buf));
	//puts(buf);
	puts(getcwd(NULL,0));
	return 0;
}
