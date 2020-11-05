#define _GNU_SOURCE 

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>              

#define LEN 5

int main()
{
    char *fifo_name = "FIFO";
    size_t i = 0, count = 6;
    char buf[LEN];
    int fd;
    char *ping = "ping\n";
    char *pong = "pong\n";

    mkfifo(fifo_name, S_IWUSR | S_IRUSR);

     while(1)
    {
        fd = open(fifo_name, O_WRONLY);
        write(fd, pong, strlen(pong));

        close(fd);

        fd = open(fifo_name, O_RDONLY);
        read(fd, &buf, LEN);
        write(STDOUT_FILENO, &buf, LEN);

        close(fd);
    }
    unlink(fifo_name);

    return 0;
}