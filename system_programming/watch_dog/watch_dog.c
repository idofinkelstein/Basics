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

	for (i = 0; i < 10000000; ++i)
	sleep(1);

	puts("watch dog process terminated properly");

	DNR();


	return 0;
}
