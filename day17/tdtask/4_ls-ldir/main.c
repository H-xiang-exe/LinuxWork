#include"func.h"
int main(int argc,char **argv){
	ARGS_CHECK(argc,2);
	DIR *pdir=opendir(argv[1]);
	RET_CHECK(pdir,NULL,"opendir");
	struct dirent *pbuf;
	char Path[1024]={0};
	int ret;
	struct stat buf;
	while((pbuf=readdir(pdir))!=NULL){
		sprintf(Path,"%s%s%s",argv[1],"/",pbuf->d_name);
		ret=stat(Path,&buf);
		RET_CHECK(ret,-1,"stat");
		printf("%x %ld %s %s %ld %s %s\n",buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,ctime(&buf.st_mtime),pbuf->d_name);		
	}
	closedir(pdir);
	return 0;
}
