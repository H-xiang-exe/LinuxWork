#include <func.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    fp=popen("wc -w","w");
    ERROR_CHECK(fp,NULL,"popen");
    char buf[128]="aaa bbb ccc ddd eeee";
    fwrite(buf,sizeof(char),strlen(buf),fp);
    fclose(fp);
    return 0;
}

