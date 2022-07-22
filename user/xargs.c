#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
 
int main(int argc, char *argv[])
{
    char *new_argv[MAXARG];
    for (int i = 1; i < argc; i ++ )
        new_argv[i - 1] = argv[i];

    char buf[128];
    char* cur_buf = buf;
    new_argv[argc - 1] = buf;
    int cur_argv = argc;
    char p;

    while (read(0, &p, sizeof p) == sizeof p)
    {
        if (p == '\n')
        {
            *cur_buf = '\0';
            new_argv[cur_argv] = 0;
            int status;
            int pid = fork();
            if (pid == 0)
            {
                exec(new_argv[0], new_argv);
                exit(0);
            }
            else 
            {
                wait(&status);
                cur_buf = buf;
                cur_argv = argc;
            }
        }   
        else 
        {
            if (p == ' ')
            {
                *cur_buf = '\0';
                cur_buf ++ ;
                new_argv[cur_argv] = cur_buf;
                cur_argv ++ ;
            }
            else 
            {
                *cur_buf = p;
                cur_buf ++ ;
            }
        } 
    }
    exit(0);
}