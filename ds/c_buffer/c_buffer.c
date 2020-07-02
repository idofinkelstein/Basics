/***********************
File name: c_buffer.c
Author: Ido Finkelstein
Reviewer: Rita Lempert
Date: 17/6/2020
************************/

#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h>
#include <errno.h> 

#include "c_buffer.h"

#define OFFSET_OF(TYPE, FIELD) ((size_t)(&((TYPE*)0)->FIELD))
#define GAP 1
#define ERROR -1

struct c_buffer 
{
    char *read;
    char *write;
    size_t capacity;
    char buffer[1];
};

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *buffer = (c_buffer_t*)malloc(OFFSET_OF(struct c_buffer, buffer)
						  + sizeof(buffer->buffer[0]) * capacity + GAP);

	if (NULL == buffer)
	{
		return (NULL);
	}

	buffer->read = &buffer->buffer[0];
	buffer->write = &buffer->buffer[0];

	buffer->capacity = capacity;

	return (buffer);
}

void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(c_buffer);

	free(c_buffer);

	c_buffer = NULL;
}

ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	size_t bytes_read = count;

	assert(c_buffer);

	if (CBufferIsEmpty(c_buffer))
	{
		errno = ENODATA;
		return ERROR;
	}
	
	errno = 0;

	while (!CBufferIsEmpty(c_buffer) && count)
	{
		*(char*)dest = *(char*)c_buffer->read; 

		dest = (char*)dest + 1;

		--count;
		
		/* if read pointer reaches end of buffer, moves it the the start */
		if (c_buffer->read == &c_buffer->buffer[c_buffer->capacity])
		{
			c_buffer->read = &c_buffer->buffer[0];
		}
		else
		{
			++c_buffer->read;
		}
	}

	return (bytes_read - count);
}

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	size_t bytes_writen = count;

	assert(c_buffer);

	if (!CBufferFreeSpace(c_buffer))
	{
		errno = ENOBUFS;
		return (ERROR);
	}

	errno = 0;

	while (CBufferFreeSpace(c_buffer) && count)
	{
		*(char*)c_buffer->write = *(char*)src;

		src = (char*)src + 1;

		--count;

		/* if write pointer reaches end of buffer, moves it the the start */
		if (c_buffer->write == &c_buffer->buffer[c_buffer->capacity])
		{
			c_buffer->write = &c_buffer->buffer[0];
		}
		else
		{
			++c_buffer->write;
		}
	}

	return (bytes_writen - count);
}

int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(c_buffer);

	return (c_buffer->read == c_buffer->write);
}

size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(c_buffer);

	/* if read is behind write, size = read + capacity - write */
	return((c_buffer->read > c_buffer->write) ? 
		   (c_buffer->read - c_buffer->write - 1) :
		   (c_buffer->read + c_buffer->capacity) - c_buffer->write);	
}

size_t CBufferCapacity(const c_buffer_t *c_buffer)
{
	assert(c_buffer);

	return(c_buffer->capacity);
}
