#include"func.h"
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	DIR *pdir=opendir(argv[1]);
	struct dirent *pbuf;
	off_t pos;
	RET_CHECK(pdir,NULL,"opendir");
	while((pbuf=readdir(pdir))!=NULL){
		pos=telldir(pdir);
		printf("name=%s type=%d off=%ld",pbuf->d_name,pbuf->d_type,pbuf->d_off);
		printf("pos=%ld\n",pos);		
	}
	closedir(pdir);
	return 0;
}	
