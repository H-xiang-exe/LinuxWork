#include<stdio.h>
int main(){
#ifdef main
	printf("main is defined!\n");
#else
	printf("main is not defined!\n");
#endif
	printf("main exit!\n");
	return 0;
}

