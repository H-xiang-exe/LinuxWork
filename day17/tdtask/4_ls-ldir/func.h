#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#define ARGS_CHECK(argc,num) {if(argc!=num){printf("error args!\n");return -1;}}
#define RET_CHECK(ret,num,func) {if(ret==num){perror(func);return -1;}}
