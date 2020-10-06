#include <stdio.h>

void EnableEcho(void)
{
	
}

void DisableEcho(void)
{
	size_t where_is_sp = 1;
	size_t *sp = &where_is_sp;
	int i = -5;
		
	printf("initial address = %p\n", (void*)sp);
	printf("initial address = %p\n", (void*)&where_is_sp);

	while (i < 6)
	{
		printf("address = %p\n", (void*)sp[i]);
		++i;
	}

	sp[4] = 0x4008df;

	
}
