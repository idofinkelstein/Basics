/***********************************/
/* File Name     c_buffer_test.c   */ 
/* Developer     Guy Barazany      */
/* Reviewer      Ido Finkelstein   */
/* Review Date   19/06/2020        */
/***********************************/

#include <stdio.h> /* printf */
#include <errno.h> /* ENOBUFS */

#include "c_buffer.h" /* Header file */

struct c_buffer 
{
    char *read;
    char *write;
    size_t capacity;
    char buffer[1];
};

enum status
{
	ERROR = -1,
	SUCCESS = 0,
	FAILED = 1
};

/*-------------------------Test Functions Declaration------------------------*/
int TestApiCBufferCreate(void);
int TestApiCBufferDestroy(void);
int TestApiCBufferCapacity(void);
int TestApiCBufferIsEmpty(void);
int TestApiCBufferWrite(void);
int TestApiCBufferRead(void);
int TestApiCBufferFreeSpace(void);
/*-----------------------End Of Functions Declaration------------------------*/
int main()
{
	TestApiCBufferCreate();
	TestApiCBufferDestroy();
	TestApiCBufferCapacity(); 
	TestApiCBufferIsEmpty(); 
	TestApiCBufferWrite();
	TestApiCBufferRead();
	TestApiCBufferFreeSpace(); 

	return (0);
}
/*-----------------------------Test Functions---------------------------------*/

int TestApiCBufferCreate(void)
{
	c_buffer_t *buffer = NULL;
	size_t capacity = 10;	

	printf("Test Buffer create\n");

	buffer = CBufferCreate(capacity);
	
	if (NULL == buffer)
	{
		return (FAILED);
	}

	printf("Buffer was created. Success!\n");

	CBufferDestroy(buffer);

	printf("------------------------------------------\n");
	
	return (SUCCESS);
}

/*---------------------------------------------------------------------------*/

int TestApiCBufferDestroy(void)
{
	c_buffer_t *buffer = NULL;
	size_t capacity = 10;	

	printf("Test Buffer Destroy\n");

	buffer = CBufferCreate(capacity);
	
	if (NULL == buffer)
	{
		return (FAILED);
	}

	CBufferDestroy(buffer);

	printf("Buffer was destroyed. Success!\n");

	printf("------------------------------------------\n");
	
	return (SUCCESS);
}

/*---------------------------------------------------------------------------*/

int TestApiCBufferRead()
{
	c_buffer_t *buff = NULL;
	ssize_t status = 0;
	size_t capacity = 10;	
	size_t i = 0;	
	char src1[20] = "hello world";
	char src2[20] = "Hey";
	char src3[20] = "Data Structues";
	char src4[20] = "abcdefg";
	char dest[20] = {'\0'};
	char* temp_dest = dest;
	
	printf("Test Buffer Read\n");

	buff = CBufferCreate(capacity);

	if (NULL == buff)
	{
		return (FAILED);
	}

	/* Read from empty buffer */
	status = CBufferRead(buff, temp_dest, 5);

	printf("BUffer capacity is %lu\n", capacity);

	printf("------------------------------------------\n");

	printf("Read from empty buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	printf("Write 7 Bytes to buffer\n\n");

	/* Write to buffer buffer */
	status = CBufferWrite(buff, src1, 7);


	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	printf("Write 2 Bytes to buffer\n\n");

	/* Write to buffer */
	status = CBufferWrite(buff, src2, 2);

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	printf("Write 2 Bytes to buffer\n");

	/* Write to buffer */
	status = CBufferWrite(buff, src3, 2);

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	/* Write to Full buffer buffer */
	status = CBufferWrite(buff, src3, 7);

	printf("Write to full buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	status = CBufferRead(buff, temp_dest, 5);

	printf("Read 5 from Buffer to dest\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	/* Print dest */
	printf("Print dest\n\n");

	for (; i < 20; ++i)
	{
		printf("%c", temp_dest[i]);
	}

	printf("\n");

	printf("------------------------------------------\n");

	/* Read whole buffer */
	status = CBufferRead(buff, temp_dest, 20);

	printf("Read 20 from Buffer to dest\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	/* Print dest */
	printf("Print dest\n\n");

	for (i = 0; i < 20; ++i)
	{
		printf("%c", temp_dest[i]);
	}

	printf("\n");

	printf("------------------------------------------\n");

	/* Read from empty buffer */
	status = CBufferRead(buff, temp_dest, 7);

	printf("Read 7 from empty buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");


	/* Write to buffer */
	status = CBufferWrite(buff, src4, 7);

	printf("Write 7 to buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	status = CBufferRead(buff, temp_dest, 4);

	printf("Read 4 from buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	status = CBufferWrite(buff, src3, 7);

	printf("Write 7 to buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	status = CBufferRead(buff, temp_dest, 5);

	printf("Read 5 from buffer\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	CBufferDestroy(buff);

	return (SUCCESS);

}

/*---------------------------------------------------------------------------*/

int TestApiCBufferWrite()
{
	c_buffer_t *buff = NULL;
	ssize_t status = 0;
	size_t capacity = 20;	
	size_t i = 0;	
	char src1[20] = "hello world";
	char src2[20] = "Hey";
	char src3[20] = "Data Structues";
	char src4[20] = "abcdefg";
	char dest[20] = {'\0'};
	char* temp_dest = dest;

	printf("Test Buffer Write\n");

	buff = CBufferCreate(capacity);

	if (NULL == buff)
	{
		return (FAILED);
	}

	/* Read from empty buffer */
	status = CBufferRead(buff, temp_dest, 20);

	printf("BUffer capacity is %lu\n", capacity);

	printf("------------------------------------------\n");

	printf("Read from empty buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	printf("Write 11 Bytes to buffer\n\n");

	/* Write to buffer buffer */
	status = CBufferWrite(buff, src1, 11);


	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	printf("Write 3 Bytes to buffer\n\n");

	/* Write to buffer buffer */
	status = CBufferWrite(buff, src2, 3);

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	printf("Write 7 Bytes to buffer\n");

	/* Write to buffer */
	status = CBufferWrite(buff, src3, 7);

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	/* Write to Full buffer buffer */
	status = CBufferWrite(buff, src3, 7);

	printf("Write to full buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	status = CBufferRead(buff, temp_dest, 5);

	printf("Read 5 from Buffer to dest\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	/* Print dest */
	printf("Print dest\n\n");

	for (; i < 20; ++i)
	{
		printf("%c", temp_dest[i]);
	}

	printf("\n");

	printf("------------------------------------------\n");

	/* Read whole buffer */
	status = CBufferRead(buff, temp_dest, 20);

	printf("Read 20 from Buffer to dest\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	/* Print dest */
	printf("Print dest\n\n");

	for (i = 0; i < 20; ++i)
	{
		printf("%c", temp_dest[i]);
	}

	printf("\n");

	printf("------------------------------------------\n");

	/* Read from empty buffer */
	status = CBufferRead(buff, temp_dest, 7);

	printf("Read from empty buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");


	/* Write to buffer */
	status = CBufferWrite(buff, src4, 7);

	printf("Write 7 to buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	status = CBufferRead(buff, temp_dest, 4);

	printf("Read 4 from buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	status = CBufferWrite(buff, src3, 7);

	printf("Write 7 to buffer\n\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	status = CBufferRead(buff, temp_dest, 5);

	printf("Read 5 from buffer\n");

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Free space is %lu\n", CBufferFreeSpace(buff));

	printf("------------------------------------------\n");

	CBufferDestroy(buff);

	return (SUCCESS);
}

/*---------------------------------------------------------------------------*/

int TestApiCBufferIsEmpty(void)
{
	c_buffer_t *buff = NULL;
	size_t capacity = 10;
	char src3[20] = "Hey Guy";
	ssize_t status = 0;	

	printf("Test IsEmpty\n");

	printf("Create empty buffer\n");

	buff = CBufferCreate(capacity);

	if (NULL == buff)
	{
		return (FAILED);
	}

	printf("Is Buffer empty? - %d\n", CBufferIsEmpty(buff));

	printf("Write to buffer\n");

	/* Write to buffer */
	status = CBufferWrite(buff, src3, 7);

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	printf("Is Buffer empty? - %d\n", CBufferIsEmpty(buff));

	printf("----------------------------------\n");

	CBufferDestroy(buff);

	return (SUCCESS);
}

/*---------------------------------------------------------------------------*/

int TestApiCBufferFreeSpace()
{
	c_buffer_t *buff = NULL;
	size_t capacity = 10;
	char src3[20] = "Hello World";
	ssize_t status = 0;	

	printf("Test TestApiCBufferFreeSpace\n");

	printf("Create empty buffer\n");

	buff = CBufferCreate(capacity);

	if (NULL == buff)
	{
		return (FAILED);
	}

	printf("Free space = %lu\n", CBufferFreeSpace(buff));

	printf("Write to buffer\n");

	/* Write to buffer */
	status = CBufferWrite(buff, src3, 7);

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}
	printf("Free space = %lu\n", CBufferFreeSpace(buff));

	CBufferDestroy(buff);

	printf("----------------------------------\n");

	return (SUCCESS);

}

/*---------------------------------------------------------------------------*/

int TestApiCBufferCapacity(void)
{
	c_buffer_t *buff = NULL;
	size_t capacity = 10;
	char src3[20] = "Hey Guy";
	ssize_t status = 0;	

	printf("Test CBufferCapacity\n");

	printf("Create empty buffer\n");

	buff = CBufferCreate(capacity);

	if (NULL == buff)
	{
		return (FAILED);
	}

	printf("Write to buffer\n");

	/* Write to buffer */
	status = CBufferWrite(buff, src3, 7);

	if (ERROR == status)
	{
		perror("Error is: ");
	}
	else
	{
		printf("Count = %ld\n", status);
	}

	if (buff->capacity == CBufferCapacity(buff))
	{
		printf("buffer->capacity == CBufferCapacity(buffer) = %lu\n", 
				CBufferCapacity(buff));
	} 
	else
	{
		printf("Test Failed");
	}

	CBufferDestroy(buff);

	printf("----------------------------------\n");

	return (SUCCESS);
}

/*---------------------------------------------------------------------------*/

