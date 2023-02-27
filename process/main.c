#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void func(int signum)
{
    printf("Im in func() \n");
    wait(NULL);
}

int main(int argc, char const *argv[])   
{
    pid_t child_pid;
    child_pid = fork();         
    if (child_pid >= 0) {
        if (0 == child_pid) {       /* Process con */
           printf("I am Child, mypid: %d\n",getpid());
           while(1);
        } else {                    /* Process cha */
           signal(SIGCHLD, func);
           printf("\nIm the parent process");
           while(1);
        }
    } else {
        printf("fork() unsuccessfully\n");      // fork() return -1 nếu lỗi.
    }
    return 0;
}
