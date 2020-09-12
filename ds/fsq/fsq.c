#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h>
#include <errno.h> 

#include "fsq.h"

#define ERROR -1

struct fsq 
{
    size_t read_i;
    size_t write_i;
    size_t capacity;
	size_t size;
    int *array;
};
/*---------------------------------------------------------------------------*/
fsq_t *FSQCreate(size_t capacity)
{
	fsq_t *fsq = NULL;

	fsq = (fsq_t*)calloc(1, sizeof(fsq_t));
	if(!fsq)
	{
		return NULL;
	}
	fsq->array = (int*)calloc(capacity, sizeof(int));
	if(!fsq->array)
	{
		free(fsq);
		return NULL;
	}
	fsq->capacity = capacity;
	fsq->size = 0;
	fsq->write_i = 0;
	fsq->read_i = 0;

	return (fsq);
}
/*---------------------------------------------------------------------------*/
void FSQDestroy(fsq_t *fsq)
{
	free(fsq->array);
	free(fsq);
}
/*---------------------------------------------------------------------------*/
int FSQRead(fsq_t *fsq)
{
	int temp = 0;

	if (fsq->size == 0)
	{
		errno = ENODATA;
		return (ERROR);
	}
	temp = *(fsq->array + fsq->read_i);

	fsq->read_i = (fsq->read_i + 1) % fsq->capacity;
	--(fsq->size);

	return (temp);
}
/*---------------------------------------------------------------------------*/
int FSQWrite(fsq_t *fsq, int num)
{
	if (fsq->size == fsq->capacity)
	{
		errno = ENOBUFS;
		return (ERROR);
	}

	*(fsq->array + fsq->write_i) = num;

	fsq->write_i = (fsq->write_i + 1) % fsq->capacity;
	++(fsq->size);

	return (0);
}
/*---------------------------------------------------------------------------*/


