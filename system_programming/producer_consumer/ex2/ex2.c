#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "slist.h"


pthread_mutex_t producer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t consumer_mutex = PTHREAD_MUTEX_INITIALIZER;

void *Producer(void *data);
void *Consumer(void *data);

int main()
{
	pthread_t t1, t2, t3, t4;
	slist_t *slist = NULL;

	slist = SListCreate();

	if (NULL == slist)
	{
		return (EXIT_FAILURE);
	}

	pthread_create(&t1, NULL, Producer, slist);
	pthread_create(&t2, NULL, Consumer, slist);
	pthread_create(&t3, NULL, Producer, slist);
	pthread_create(&t4, NULL, Consumer, slist);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);


	return 0;
}

void *Producer(void *data)
{
	slist_t *slist =(slist_t*)data;
	void *item = "item";

	while(1)
	{
		pthread_mutex_lock(&producer_mutex);

		SListInsert(slist, SListEnd(slist), item);
		puts("produced");

		pthread_mutex_unlock(&producer_mutex);
	}

	return (NULL);
}

void *Consumer(void *data)
{
	slist_t *slist =(slist_t*)data;

	while (1)
	{
		/*pthread_mutex_lock(&consumer_mutex);*/

		while(SListIsEmpty(slist));
		
		SListRemove(slist, SListBegin(slist));
		
		puts("consumed");

		/*pthread_mutex_unlock(&consumer_mutex);*/
	}

	return (NULL);
}
