#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

volatile int flag = 0;

void *Producer(void *queue);
void *Consumer(void *queue);

int main()
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, Producer, NULL);
	pthread_create(&t2, NULL, Consumer, NULL);

	while (1)
	{
		printf("flag = %d\n", flag);
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);


	return 0;
}

void *Producer(void *data)
{
	(void)data;

	while(1)
	{
		while(flag == 1);

		 __atomic_store_n(&flag, 1, __ATOMIC_SEQ_CST);
		puts("produced");
	}

	return (NULL);
}

void *Consumer(void *data)
{
	(void)data;

	while (1)
	{
		while(flag == 0);
		
		 __atomic_store_n(&flag, 0, __ATOMIC_SEQ_CST);
		puts("consumed");
	}

	return (NULL);
}
