#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "ws9.h"

/* 4 threads in Intel® Core™ i5-5200U Processor architecture */
#define NUM_OF_TRHEADS 4
static const unsigned num_of_threads = NUM_OF_TRHEADS;

typedef struct mem_info mem_info_t;

struct mem_info
{
	void *dest;
	const void *src;
	size_t bytes_in_thread;
};

static void *MemWraper(void *info);

void *MT_MemCpy(void *dest, const void *src, size_t n)
{
	/* this version is suitable for Intel® Core™ i5-5200U Processor */

	mem_info_t *info_arr = NULL;
	pthread_t t[NUM_OF_TRHEADS]; 
	size_t bytes_in_thread = n / num_of_threads;
	size_t reminder = n % num_of_threads;
	size_t bytes_in_thread_correction = bytes_in_thread + reminder;
	size_t i = 0;
	char *temp_dest = (char*)dest;
	char *temp_src = (char*)src;
	int status = 0;
	
	info_arr = (mem_info_t*)malloc(sizeof(mem_info_t) * num_of_threads);

	if (NULL == info_arr)
	{
		return (NULL);
	}

	/* initiates info stuct, first struct gets the addition of the reminder */
	for (i = 0; i < num_of_threads && !status; ++i)
	{
		(info_arr + i)->bytes_in_thread = bytes_in_thread_correction;
		(info_arr + i)->dest = temp_dest;
		(info_arr + i)->src = temp_src;

		temp_dest += bytes_in_thread_correction;
		temp_src += bytes_in_thread_correction;

		bytes_in_thread_correction = bytes_in_thread; 

		status = pthread_create(&t[i], NULL, MemWraper, info_arr + i);
	}

	if (status)
	{
		free(info_arr);
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < num_of_threads; ++i)
	{
		pthread_join(t[i], (void**)dest);
	}

	free(info_arr);
	return (dest);
}

static void *MemWraper(void *info)
{
	mem_info_t *data_package = (mem_info_t*)info;
	
	return (MemCpy(data_package->dest, 
				   data_package->src, 
				   data_package->bytes_in_thread));	
}
