#ifndef ILRD_FSQ_H
#define ILRD_FSQ_H

#include <unistd.h> /* ssize_t */
#include <stddef.h> /* size_t  */

typedef struct fsq fsq_t;

/*---------------------------------------------------------------------------*/

/* FSQCreate:
*   - Creates a new circular buffer
* Args:
*   - capacity of the new c_buffer, in bytes
*  
* Return Value:
*   Pointer to c_buffer if succeeded
*   Null if failed
*/
fsq_t *FSQCreate(size_t capacity);

/*---------------------------------------------------------------------------*/

/* FSQDestroy:
*   - Destroys given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
*     
*/
void FSQDestroy(fsq_t *fsq);

/*---------------------------------------------------------------------------*/

/* CBufferRead:
*   - Reads data from given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
* 
* Return Value:
*   -int read
*   
* Comments:
*    -in case of an error, errno will be updated with the given case:
*        -(ENODATA)  No data available while trying to read.
*/
int FSQRead(fsq_t *fsq);

/*---------------------------------------------------------------------------*/

/* CBufferWrite:
*   - Writes a given int into the given buffer
* 
* Args:
*   - c_buffer - pointer to buffer given by user
*   - num - int to write
*
* Return Value:
*   -0 for success, (-1) for error
* 
*/
int FSQWrite(fsq_t *fsq, int num);

/*---------------------------------------------------------------------------*/


#endif /* ILRD_CIRCULAR_BUFFER_H */
