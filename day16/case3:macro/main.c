#include<stdio.h>
int main(){
#ifdef DEBUG
	printf("there is a DEBUG!\n");
#endif
	return 0;
}
