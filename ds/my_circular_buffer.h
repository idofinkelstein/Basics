/*
CIRCULAR BUFFER - A data structure that uses a single, fixed-size buffer
				  as if it were connected end-to-end.

POLICY - A FIFO structure.


*/
#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */
#include <errno.h> /* int errno */

extern int errno;

struct circular_buffer
{
...
int err; /* = errno */
void *buf /* or buf[] */
};

typedef circular_buffer circular_buffer_t;

/*

*/
circular_buffer_t *BufferCreate(size_t capacity);

/*

*/
void BufferDestroy(circular_buffer_t);

/*

*/
ssize_t BufferRead(int fd, void *buf, size_t cnt);

/*

*/
ssize_t BufferWrite(int fd, const void *buf, size_t cnt)

/*

*/
int BufferIsEmpty(const circular_buffer_t buf);

/*

*/
size_t BufferFreeSpace(const circular_buffer_t buf);

/*

*/
size_t BufferCapcity(const circular_buffer_t buf);

#endif /* __CIRCULAR_BUFFER__ */
