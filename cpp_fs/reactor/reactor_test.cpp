#include <cstdio> 		/* perror, printf */
#include <cstdlib> 		/* malloc, free */
#include <cstring>
#include <sys/ioctl.h>  /* ioctl */
#include <unistd.h> 	/* read */

#include "reactor.hpp"
#include "tcp.hpp"

using namespace ilrd::rd90;

void ReadSTDIN(int fd);


int main()
{
#if 0
    Reactor<Select> reactor(new Select);
#else
    Reactor<Epoll> reactor(new Epoll(5));
#endif
    TCPServer server(&reactor, "9998");


	reactor.Add(0, Bind(ReadSTDIN, 0));

    server.Start();
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
        throw("ioctl");
    }

	buff = new char[buff_size];

    read_bytes = read(fd, buff, buff_size);
    if (-1 == read_bytes)
    {
        throw("read");
    }

    buff[read_bytes - 1] = '\0';

    printf("Message received on STDIN!\n message: %s\n", buff);
 
	if (!strcmp(buff, "exit"))
	{
		throw("strcmp");
	}

	delete[] buff; 


}
