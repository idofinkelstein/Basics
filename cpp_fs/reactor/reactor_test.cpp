#include <stdio.h> 		/* perror, printf */
#include <cstdlib> 		/* malloc, free */
#include <sys/ioctl.h>  /* ioctl */
#include <unistd.h> 	/* read */

#include "reactor.hpp"

using namespace ilrd::rd90;

void ReadSTDIN(int fd);

class STDIN
{
	
};

int main()
{
    Reactor<Select> reactor(new Select);

	reactor.Add(0, Bind(ReadSTDIN));

	reactor.Run();

    return 0;
}


void ReadSTDIN(int fd)
{
    char *buff = NULL;
    size_t buff_size = 0;

    int read_bytes = 0;

    if (-1 == ioctl(fd, FIONREAD, &buff_size))
    {
        perror("udp ictl");
        return;
    }

	buff = new char[buff_size + 1];

    read_bytes = read(fd, buff, buff_size);
    if (-1 == read_bytes)
    {
        perror("stdin read");

        delete[] buff;
        return;
    }

    buff[read_bytes] = '\0';

    printf("Message received on STDIN!\n message: %s\n", buff);
 
	delete[] buff; 

}
