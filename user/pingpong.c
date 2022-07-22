#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RD 0
#define WD 1

int f2s[2];
int s2f[2];
int state;
char *buf;

int main(int argc, char *argv[])
{
    pipe(f2s);
    pipe(s2f);

    int pid = fork();

    if (pid < 0)
    {

    }    
    if (pid == 0)
    {
        close(f2s[0]);
        read(f2s[1], buf, 1);
        close(f2s[1]);

        close(s2f[1]);
        printf("%d: received ping\n", pid);
        write(s2f[0], "1", 1);
        close(s2f[0]);
    }
    else
    {
        close(f2s[1]);
        write(f2s[0], "1", 1);
        close(f2s[0]);

        close(s2f[0]);
        read(s2f[1], buf, 1);
        close(s2f[1]);
        wait(&state);
        printf("%d: received pong\n", pid);
    }

    exit(0);
}