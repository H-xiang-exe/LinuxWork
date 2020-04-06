#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork()){
        while(1);
    }else{
        return 0;
    }
    return 0;
}

