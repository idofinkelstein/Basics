#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <time.h> /* time */
#include <unistd.h> /* sleep */
/*----------------------------------------------------------------------------*/
#define THREADS 32700

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


int main()
{
	pthread_t thread = 0;
	thread_info_data_t data_struct = {0};
	size_t number = 1000604152;
	size_t sum_of_divisors = 0;
	void *temp_container_ptr = NULL;

	data_struct.index = 0;
	data_struct.range = number;
	data_struct.number = number;

	pthread_create(&thread, NULL, SumDivisors, &data_struct);

	pthread_join(thread, &temp_container_ptr);
	sum_of_divisors += (size_t)temp_container_ptr;

	printf("sum_of_divisors = %lu\n", sum_of_divisors);
	return (0);
}

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
