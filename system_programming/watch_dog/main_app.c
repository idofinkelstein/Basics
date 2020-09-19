#include <stdio.h>
#include <unistd.h>

#include "keep_alive.h"

int main(int argc, char **argv)
{
	int i = 0;
	(void)argc;
/*	registration
	.
	.
	.
*/

	MMI(argv);

	for (i = 0; i < 20; ++i)
	sleep(1);
	
	puts("main process terminated properly");

	/*
	code...
	*/

	DNR();

	return 0;

}
