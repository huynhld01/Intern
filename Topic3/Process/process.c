#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid = -1;
    int num = 0;
    
    pid = fork();
    if (-1 == pid)
    {
        perror("Cannot create child process.");
        return -1;
    }
    
    if (pid >= 0)
    {
        if (0 == pid)
        {
            num += 5;
            sleep(2);
            printf("Child process - num = %d\n", num);
            while(1);
        }
        else
        {
            int child_status;
            wait(&child_status);
            num += 50;
            sleep(2);
            printf("Parent process: PID %d & num = %d\n", getpid(), num);
        }
    }
    return 0;
}

