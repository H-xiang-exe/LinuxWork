#include<stdio.h>
void func(int i){
	func(i);
}
int main(){
	func(1);
	return 0;
}
