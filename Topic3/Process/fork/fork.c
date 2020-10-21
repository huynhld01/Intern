#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#define FILE_PATH1 "data1.txt"
#define FILE_PATH2 "data2.txt"
int main()
{
    int fd = -1;
    pid_t pid = -1;
    char buffer[1000];
    int byte_read;
    int status;
    pid = fork();
    
    if (-1 == pid)
    {
        perror("cannot create child process");
        return -1;
    }

    if (pid >= 0)
    {
        if (0 == pid)
        {
            printf("this is child process\n");
            status = system("ls -la > data1.txt");
                                   
            fd = open(FILE_PATH1, O_RDONLY);
            if (-1 == fd)
                return -1;
            byte_read = read(fd, buffer, sizeof(buffer));
            if (byte_read > 0)
                printf("%s\n", buffer);
            close(fd);
            while(1);
            return 0;
        }
        else
        {
            int child_status = -1;
            printf("this is the parent process\n");
            wait(&child_status);
            if (0 == child_status)
            {
                status = system("ls -la > data2.txt");
                fd = open(FILE_PATH2, O_RDONLY);
                if (-1 == fd)
                    return -1;
                byte_read = read(fd, buffer, sizeof(buffer));
                if (byte_read > 0)
                    printf("%s\n", buffer);
                close(fd); 
                while(1);
            }
        }
    }
}
