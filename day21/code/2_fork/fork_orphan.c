#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork()){
        printf("I am a child\n");
        while(1);
    }else{
        printf("I am parent\n");
        return 0;
    } 
    return 0;
}

