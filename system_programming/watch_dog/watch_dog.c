#include <stdio.h>

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

	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);
	for (i = 0; i < 10000000; ++i);

	puts("watch dog process terminated properly");

	DNR();


	return 0;
}
