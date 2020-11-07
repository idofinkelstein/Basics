#define _GNU_SOURCE  

#define READ_END 0
#define WRITE_END 1
#define LEN 5
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>              

int main()
{
    int pipefd1[2] = {0};
    int pipefd2[2] = {0};
    size_t i = 0, count = 6;
    pid_t cpid = 0; /* child pid */
    char buf[LEN];
    char *ping = "ping\n";
    char *pong = "pong\n";

    /*
    1 - writing
    0 - reading
    */

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) /* In child process */
    {    
        close(pipefd2[WRITE_END]);          /* Close unused write end */
        close(pipefd1[READ_END]);

        for (i = 0; i < count; i++)
        {
            read(pipefd2[READ_END], &buf, LEN);    
            write(STDOUT_FILENO, &buf, LEN);            
            write(pipefd1[WRITE_END], pong, strlen(pong));
        }

        /* end of read and write session */
        close(pipefd2[READ_END]);
        close(pipefd1[WRITE_END]);

        _exit(EXIT_SUCCESS);

    } 
    else 
    {            
        close(pipefd2[READ_END]);   /* Close unused read end */
        close(pipefd1[WRITE_END]);  /* Close unused write end */
            
        for (i = 0; i < count; i++)
        {
            write(pipefd2[WRITE_END], ping, strlen(ping));    
            read(pipefd1[READ_END], &buf, LEN);        
            write(STDOUT_FILENO, &buf, LEN);
        }
        
        /* end of read and write session */
        close(pipefd1[READ_END]);
        close(pipefd2[WRITE_END]);
        

        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}

