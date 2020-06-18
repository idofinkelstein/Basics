/*
* Circular buffer is a data structure with limited capacity, allowing re-use of the same memory areas.
*
* Attributes:
* -	Capacity is a user given value
*  
* Main operations on Circular buffer:
* -	Create - create a new buffer according to a given capacity. O(1)
* -	Destroy -destroy a given buffer. O(1)
* -	Read - Read "count" bytes from a given buffer, and writes it to a given dest. O(n)
* -	Write - Write "count" bytes into a given buffer. O(n)
* -	IsEmpty - Check if a given buffer is empty. O(1)
* -	FreeSpace - Check how many free spaces a given buffer has, in bytes. O(1)
* -	Capacity - Get the capacity of a given buffer. O(1)
*
* c_buffer API
* - June 16th 16:40 Ver:  1.0 API team discussion                                     
    June 16th 17:40 Ver:  1.1 API updated comments                                    
    June 16th 18:22 Ver:  1.2 API mentor approval                                     
    June 16th 23:32 Ver:  1.3 Include guard added                                     
    June 17th 09:17 Ver:  1.4 Fixing: CBufferWrite + CBufferread complexity: O(n)
                              Include guard updated to fixed format  
                              Errno under CBufferWrite + CBufferread has been updated
                              size_t + ssize_t libraries have been added              
    June 17th 11:40 Ver:  1.5 CBufferWrite + CBufferread description updated          
*/

#ifndef ILRD_CIRCULAR_BUFFER_H
#define ILRD_CIRCULAR_BUFFER_H

#include <unistd.h> /* ssize_t */
#include <stddef.h> /* size_t  */

typedef struct c_buffer c_buffer_t;

/*---------------------------------------------------------------------------*/

/* CBufferCreate:
*   - Creates a new circular buffer
* Args:
*   - capacity of the new c_buffer, in bytes
*  
* Return Value:
*   Pointer to c_buffer if succeeded
*   Null if failed
*/
c_buffer_t *CBufferCreate(size_t capacity);

/*---------------------------------------------------------------------------*/

/* CBufferDestroy:
*   - Destroys given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
*     
*/
void CBufferDestroy(c_buffer_t *c_buffer);

/*---------------------------------------------------------------------------*/

/* CBufferRead:
*   - Reads data from given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
*   - dest - The buffer to write to (must be large enough to contain the data) 
*   - count - number of bytes to read from buffer
* 
* Return Value:
*   -number of bytes read from buffer
*   -(-1) for error 
*   
* Comments:
*    -in case of an error, errno will be updated with the given case:
*        -(ENODATA)  No data available while trying to read.
*    -in case of an invalid dest - undefined behavior.
*/
ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count);

/*---------------------------------------------------------------------------*/

/* CBufferWrite:
*   - Writes a given number of bytes into the given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
*   - src - source of data to write into buffer
*   - count - number of bytes to write into buffer
*
* Return Value:
*   -number of bytes to write into buffer
*   -(-1) for error
* 
* Comments:
*    -in case of an error, errno will be updated with the given case:
*       -(ENOBUFS) No buffer space available.
*    -in case of an invalid src - undefined behavior.
*/
ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count);

/*---------------------------------------------------------------------------*/

/* CBufferIsEmpty:
*   - checks if the buffer is empty or not
* 
* Args:
*   - c_buffer - pointer to c_buffer given by user
*  
* Return Value:
*   1 - empty (TRUE)
*   0 - not empty (FALSE)       
*/
int CBufferIsEmpty(const c_buffer_t *c_buffer);

/*---------------------------------------------------------------------------*/

/* CBufferFreeSpace:
*   - Returns the amount of free space a given buffer has, in bytes
* 
* Args:
*   - c_buffer - pointer to c_buffer given by user
*  
* Return Value:
*   number of free bytes in the buffer
*/
size_t CBufferFreeSpace(const c_buffer_t *c_buffer);

/*---------------------------------------------------------------------------*/

/* CBufferCapacity:
*   - Returns the capacity of a given buffer in bytes
* 
* Args:
*   - c_buffer - pointer to c_buffer given by user
*  
* Return Value:
*   Number of capacity in a given buffer in bytes
*/
size_t CBufferCapacity(const c_buffer_t *c_buffer);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_CIRCULAR_BUFFER_H */
