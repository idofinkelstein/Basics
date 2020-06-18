/***************************
File name: c_buffer_test.c
Author: Ido Finkelstein
Reviewer: Rita Lempert
Date: 17/6/2020
****************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "c_buffer.h"

void Scenario1Test(void);
void Scenario2Test(void);

int main()
{
	c_buffer_t *buffer = CBufferCreate(100);
	char src[150] = "AAAADSGddddddssfshfgtutyughjghfd"
					"ddddFFDHdddddddddddddddhtrhhaaxxppwwqqzz";
	char dest[110] = {'\0'};

	printf("Emptiness = %d\n", CBufferIsEmpty(buffer));
	printf("Capacity = %ld\n", CBufferCapacity(buffer));
	printf("Free space = %ld\n", CBufferFreeSpace(buffer));

	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src, 1));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src, 9));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src, 12));

	printf("Emptiness = %d\n", CBufferIsEmpty(buffer));
	printf("Free space = %ld\n", CBufferFreeSpace(buffer));

	printf("bytes read to buffer = %ld\n",CBufferRead(buffer, dest, 45));
	printf("%s\n", dest);
	printf("bytes written to buffer = %ld\n",CBufferWrite(buffer, src, 5));
	printf("bytes written to buffer = %ld\n",CBufferWrite(buffer, src, 20));
	
	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 25));
	printf("%s\n", dest);
	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 7)); 
	printf("Free space = %ld\n", CBufferFreeSpace(buffer));
	printf("The error message is : %s\n", strerror(errno));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src, 20));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src, 6));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, "hello", 20));
	printf("%s\n", dest);
	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 20));
	printf("Free space = %ld\n", CBufferFreeSpace(buffer));
	CBufferRead(buffer, dest, 7);
	printf("%s\n", dest);
	CBufferRead(buffer, dest, 2);
	printf("%s\n", dest);
	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 0));
	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 5));
	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 4));
	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 1));
	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 3));

	printf("The error message is : %s\n", strerror(errno));

	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, "jtdsdfgdf", 4));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, "hhhhhh", 4));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src, 70));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src, 13));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, "dddd", 14));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, "hey hey", 3));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, "fffffffffff", 9));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, "vvvvvvvvvv", 4));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src, 20));

	printf("The error message is : %s\n", strerror(errno));

	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest, 100));

	printf("The error message is : %s\n", strerror(errno));

	printf("Emptiness = %d\n", CBufferIsEmpty(buffer));
	printf("Free space = %ld\n", CBufferFreeSpace(buffer));

	printf("%s\n", dest);
	
	CBufferDestroy(buffer);

	Scenario1Test();
	Scenario2Test();

	return 0;
}
 
/* tests writing and reading array of ints */
void Scenario1Test(void)
{
	size_t i = 0;
	size_t capacity = 200;
	int src_arr[50]= {0};
	int dest_arr[50] = {0};

	c_buffer_t *buffer = CBufferCreate(capacity);

	for (i = 0; i < 50; ++i)
	{
		src_arr[i] = i * i;
	}

	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src_arr, 200));

	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest_arr, capacity));

	printf("Capacity = %ld\n", CBufferCapacity(buffer));
	printf("Free space = %ld\n", CBufferFreeSpace(buffer));

	for (i = 0; i < 50; ++i)
	{
		printf("%d, ", dest_arr[i]);
	}

	printf("\n");

	CBufferDestroy(buffer);

}
/* tests writing and reading multiple arrays of ints and checks the
   order of them in dest array. */
void Scenario2Test(void)
{
	size_t i = 0;
	size_t capacity = 360;
	int src_arr1[30]= {0};
	int src_arr2[30]= {0};
	int src_arr3[30]= {0};
	int dest_arr[90] = {0};

	c_buffer_t *buffer = CBufferCreate(capacity);

	for (i = 0; i < 30; ++i)
	{
		src_arr1[i] = i;
	}

	for (i = 0; i < 30; ++i)
	{
		src_arr2[i] = 30 + i;
	}

	for (i = 0; i < 30; ++i)
	{
		src_arr3[i] = 60 + i;
	}

	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src_arr1, 120));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src_arr2, 120));
	printf("bytes written to buffer = %ld\n", CBufferWrite(buffer, src_arr3, 120));

	printf("bytes read to buffer = %ld\n", CBufferRead(buffer, dest_arr, capacity));

	printf("Capacity = %ld\n", CBufferCapacity(buffer));
	printf("Free space = %ld\n", CBufferFreeSpace(buffer));

	for (i = 0; i < 90; ++i)
	{
		printf("%d, ", dest_arr[i]);
	}

	printf("\n");

	CBufferDestroy(buffer);

}

