#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sigint_handler (int signo)
{
	/*
	* Technically, you shouldn't use printf() in a
	* signal handler, but it isn't the end of the
	* world. I'll discuss why in the section
	* "Reentrancy."
	*/

	
	printf("Caught SIGINT!\nDO NOTHING!\n");
	signal(signo, SIG_IGN);

}

int main()
{

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		fprintf (stderr, "Cannot handle SIGINT!\n");
		exit(EXIT_FAILURE);
	}

	sleep(5);

	return 0;
}




