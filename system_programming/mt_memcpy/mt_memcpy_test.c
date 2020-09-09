#include <stdio.h>	 /* printf		 */
#include <stdlib.h>	 /* malloc, free */
#include <time.h>    /* time		 */

#include "ws9.h"

static const unsigned buf_size = 100000000; /* 100MB */

int MemCpyTest(void);
int MT_MemCpyTest(void);

int main()
{
#ifdef MT
	puts("MT_MemCpy running...");
	MT_MemCpyTest();
#else	
	puts("MemCpy running...");	
	MemCpyTest();
#endif

	return 0;
}

int MemCpyTest(void)
{
	int *src = NULL;
	int *dest = NULL;

	src = (int*)malloc(buf_size);

	if (NULL == src)
	{
		return(EXIT_FAILURE);
	}

	dest = (int*)malloc(buf_size);
	
	if (NULL == dest)
	{
		free(src);
		return(EXIT_FAILURE);
	}

	MemCpy(dest, src, buf_size);
	
	free(src);
	free(dest);

	return 0;
}

int MT_MemCpyTest(void)
{
	int *src = NULL;
	int *dest = NULL;

	src = (int*)malloc(buf_size);

	if (NULL == src)
	{
		return(EXIT_FAILURE);
	}

	dest = (int*)malloc(buf_size);
	
	if (NULL == dest)
	{
		free(src);
		return(EXIT_FAILURE);
	}

	MT_MemCpy(dest, src, buf_size);

	free(src);
	free(dest);

	return 0;
}
