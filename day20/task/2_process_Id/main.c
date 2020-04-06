#include <func.h>

int main(int argc,char *argv[])
{
    pid_t pid,ppid;
    pid_t uid,gid;
    pid_t euid,egid;
    printf("pid=%d,ppid=%d\nuid=%d,gid=%d\neuid=%d,egid=%d\n",
           getpid(),getppid(),getuid(),getgid(),geteuid(),getegid());
    return 0;
}

