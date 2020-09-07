#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <time.h> /* time */
#include <unistd.h> /* sleep */
/*----------------------------------------------------------------------------*/
#define THREADS 32000

/*----------------------------------------------------------------------------*/
typedef struct thread_info_data thread_info_data_t;
struct thread_info_data
{
	size_t index;
	size_t range;
	size_t number;
};
/*----------------------------------------------------------------------------*/
void *InitIndex(void *data);
void PrintArray(int *arr, size_t arr_size);
void *SumDivisors(void * data);
/*----------------------------------------------------------------------------*/

int main()
{
	size_t i = 0;
	pthread_t *threads = NULL;
	size_t number = 1000604152;
	size_t range = number / THREADS; 
	size_t reminder = number % THREADS;
	size_t first_range = range + reminder;
	size_t sum_of_divisors = 0;
	void *temp_container_ptr = NULL;
	thread_info_data_t data_structs[THREADS] = {0};
	int status = 0;

	threads = (pthread_t*)malloc(THREADS * sizeof(threads));
	
	if (NULL == threads)
	{
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < THREADS && !status; ++i)
	{
		data_structs[i].index = i;
		data_structs[i].range = first_range;
		data_structs[i].number = number;

		status = pthread_create(threads + i, NULL, SumDivisors, &data_structs[i]);

		first_range = range;
	}

	if (status) /* at least one thread creation failed */
	{
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < THREADS; ++i)
	{
		pthread_join(threads[i], &temp_container_ptr);
		sum_of_divisors += (size_t)temp_container_ptr;
	}

	printf("sum_of_divisors = %lu\n", sum_of_divisors);

	free(threads);
	return (0);
}
/*----------------------------------------------------------------------------*/

void PrintArray(int *arr, size_t arr_size)
{
	size_t i = 0;
	for (i = 0; i < arr_size; ++i)
	{
		printf("arr[%lu] = %d; ", i, arr[i]);
	}
}
/*----------------------------------------------------------------------------*/
void *SumDivisors(void *ptr)
{
	thread_info_data_t *data = (thread_info_data_t *)ptr;
	size_t index = data->index;
	size_t range = data->range;
	size_t number = data->number;

	size_t start = index * range + 1;
	size_t end = start + range - 1;
	size_t sum_of_divisors = 0;

	for(; start <= end; ++start)
	{
		if(0 == number % start)
		{
			sum_of_divisors += start;
		}
	}

	return((void *)sum_of_divisors);
}
