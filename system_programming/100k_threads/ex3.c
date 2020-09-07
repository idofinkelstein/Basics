#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


int arr_g[50000] = {0};
	
void *WriteIToArr(void *i)
{
	long index = (long)i;


	arr_g[index] = index;

	pthread_exit(NULL);
	return (NULL);
}

int main()
{
	pthread_t threads[50000];
	long i = 0;
	long size = sizeof(threads) / sizeof(pthread_t);
	int status = 0;
	
	printf("%ld\n", size);
	for (i = 0; i < size; ++i)
	{
		status = pthread_create(&threads[i], NULL, WriteIToArr, (void*)i);
		pthread_detach(threads[i]);
		while (status)
		{
			status = pthread_create(&threads[i], NULL, WriteIToArr, (void*)i);
		}
		
	}

	/*sleep(10);*/

	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr_g[i]);
	}
	
	puts("");
	pthread_exit(NULL);
	return 0;
}
