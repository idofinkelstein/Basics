#include <stdio.h>
#include <stdlib.h>

int main()
{
	void *ptr = (size_t*)malloc(sizeof(size_t) * 2);

	*(size_t*)ptr = 10;

	++(size_t*)ptr;

	free (ptr);

	return 0;
}
