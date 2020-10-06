#include "bts_queue.h"



void* I_am_a_producer(void* data)
{
    btsq_t* btsq = (btsq_t*)data;

    while (1)    
    {
        sleep(3);

        // void* info = ReadDataFromSensor();

        BTSQ_Enqueue(btsq, info);
    }
}

void* I_am_a_consumer(void* data)
{
    btsq_t* btsq = (btsq_t*)data;

    while (1)    
    {
        void* info = BTSQ_Dequeue(btsq);

        // process data
    }
}


int main()
{
    btsq_t* btsq = BTSQ_Create();

    pthread_create(&thid1, NULL, I_am_a_producer, btsq);
    pthread_create(&thid2, NULL, I_am_a_consumer, btsq);

    // ...


    return 0;
}

typedef struct bts_queue
{
	void **arr;
	pthread_mutex_t mutex;
	sem_t sem_full;
	sem_t sem_empty;
	size_t capacity;
	size_t size;
	size_t write;
	size_t read;

}bts_queue_t;

bts_queue_t *BTSQueue(size_t capacity)
{
	bts_queue_t *queue = NULL;

	queue = (bts_queue_t*)malloc(sizeof(bts_queue_t));

	if (queue == NULL)
	{
		return (NULL);
	}

	queue->arr = (void**)malloc(capacity * sizeof(void*));
	
	if (queue->arr == NULL)
	{
		free(queue);
		return (NULL;
	}


	if (0 != pthread_mutex_init(&queue->mutex))
	{
		free(queue->arr);
		free(queue);
		return (NULL;
	}

	
	if (0 != sem_init(&queue->sem_empty, 0, fsq_capacity))
	{
		pthread_mutex_destroy(&queue->mutex);
		free(queue->arr);
		free(queue);
		return (NULL;
	}	

	
	if (0 != sem_init(&queue->sem_full, 0, 0))
	{
		sem_destroy(&queue->sem_empty);
		pthread_mutex_destroy(&queue->mutex);
		free(queue->arr);
		free(queue);
		return (NULL);
	}

	queue->size = 0;
	queue->capacity = capacity;
	queue->write = queue->read = 0;

	return (queue);
}

int BSTEnqueue(bts_queue_t *queue, void *item)
{
	sem_wait(&thread_info->sem_empty);	
	pthread_mutex_lock(&queue->mutex);

	if (size == capacity)
	{
		return 1;
	}

	*queue->(arr + queue->write) = item;
	queue->write = (queue->write + 1) % queue->capacity;
	++queue->size;

	sem_post(&queue->sem_full);

	pthread_mutex_unlock(&thread_info->mutex);

	return 0;	
}

void *BSTDequeue(bts_queue_t *queue)
{
	void *item = NULL;

	sem_wait(&thread_info->sem_full);
	pthread_mutex_lock(&thread_info->mutex);

	if (size == 0)
	{
		return (NULL);
	}

	item = *queue->(arr + queue->read);
	queue->read = (queue->read + 1) % queue->capacity;
	--queue->size;

	sem_post(&queue->sem_empty);
	pthread_mutex_unlock(&thread_info->mutex);

	return (item);	
}
