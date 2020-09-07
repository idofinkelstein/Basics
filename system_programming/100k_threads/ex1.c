
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


int arr_g[10000] = {0};
	
void *WriteIToArr(void *i)
{
	long index = (long)i;


	arr_g[index] = index;


	return (NULL);
}

int main()
{
	pthread_t threads[10000];
	long i = 0;
	long size = sizeof(threads) / sizeof(pthread_t);
	
	
	printf("%ld\n", size);
	for (i = 0; i < size; ++i)
	{
		pthread_create(&threads[i], NULL, WriteIToArr, (void*)i);
	}
	sleep(10);

	for (i = 0; i < size; ++i)
	{
		pthread_join(threads[i], NULL);
		
	}

	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr_g[i]);
	}
	
	puts("");

	return 0;
}
