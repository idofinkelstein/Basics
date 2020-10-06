/* 
* File Name: vsa.c
* Description: Defenitions of test functions for vsa API functions
* Developer: Guy Chen
* Reviewer: Ido Finkelshtein
* Date: 09.07.2020
*/


#include <stdio.h> /* printf */
#include <assert.h>	/* assert */
#include <stdlib.h> /* calloc, free */
#include <stdbool.h> /* true false */

#include "vsa.h"

/******************************* Define section *******************************/

#define UNUSED(arg) (void)(arg)

/************************ function declaration section ************************/
static void VSAInitTest(void);
static void VSAAllocTest(void);
static void VSAFreeTest(void);
static void BiggestFreeBlockTest(void);
static void  DefragmentationTest(void);

/********************************* main section *******************************/

int main ()
{
	VSAInitTest();
	VSAAllocTest();
	VSAFreeTest();
	BiggestFreeBlockTest();
	 DefragmentationTest();

	UNUSED(VSAInitTest);
	UNUSED(VSAAllocTest);
	UNUSED(VSAFreeTest);
	UNUSED(BiggestFreeBlockTest);

	return (true);
}


/**************************** API testing functions ***************************/
/* 	Test VSAInit:
	Method: insert all needed parameters and checks the new pool
*/
static void VSAInitTest(void)
{
	vsa_t *vsa_pool = NULL;
	void *user_pool_pointer = NULL;
	size_t pool_size = 1000;
	
	printf("\n---------------------- Initiate test ----------------------\n\n");	
	/* Dynamically allocate memory using calloc() */ 
	user_pool_pointer = calloc(pool_size , sizeof(char)); 
	printf("compare between the user given address to the returns address\
from the init function  \n");	
	if (NULL == user_pool_pointer)
	{
		printf("there is a problem with the allocation\n");	
	}
		
	printf("the address of the user calloc is: %p\n",user_pool_pointer);	
	
	/*  sending info to the VSA INIT function */
	vsa_pool = VSAInit(user_pool_pointer,pool_size);
	
	if (NULL == vsa_pool)
	{
		printf("there is a problem with the allocation\n");	
	}

	printf("the address of the vsa after the init function: %p\n",
			(void*)vsa_pool);	
	free(user_pool_pointer);						
}

/*---------------------------------------------------------------------------*/
/* 	Test VSAAlloc:
	Method: Alloc few data memory address and see if its knows to handle with 
	different types of data sizes requests
*/
static void VSAAllocTest(void)
{
	vsa_t *vsa_pool = NULL;
	void *user_pool_pointer = NULL;
	size_t pool_size = 1000;
	
	void *data_address1 = NULL;
	size_t block_size1 = 100;
	void *data_address2 = NULL;
	size_t block_size2 = 200;
	void *data_address3 = NULL;
	size_t block_size3 = 300;
	void *data_address4 = NULL;
	size_t block_size4 = 1000;

	/* Dynamically allocate memory using calloc() */ 
	printf("\n------------------------ Alloc test -----------------------\n\n");	
	user_pool_pointer = calloc(pool_size , sizeof(char)); 
	
	if (NULL == user_pool_pointer)
	{
		printf("there is a problem with the allocation\n");	
	}
	
	vsa_pool = VSAInit(user_pool_pointer,pool_size);

	data_address1 = VSAAlloc(vsa_pool,block_size1);
	if (NULL == data_address1)
	{
		printf("Cant find enough memory for data1!\n");
	}
	else
	{
		printf("the address of the data1 in the pool is: %p\n",data_address1);
	}

	data_address2 = VSAAlloc(vsa_pool,block_size2);
	if (NULL == data_address2)
	{
		printf("Cant find enough memory for data2!\n");
	}
	else
	{
		printf("the address of the data2 in the pool is: %p\n",data_address2);
	}
	/* checks the biggest free block size */	
	data_address3 = VSAAlloc(vsa_pool,block_size3);
	
	if (NULL == data_address3)
	{
		printf("Cant find enough memory for data3!\n");
	}
	else
	{
		printf("the address of the data3 in the pool is: %p\n",data_address3);
	}	
		
	data_address4 = VSAAlloc(vsa_pool,block_size4);
	if (NULL == data_address4)
	{
		printf("Cant find enough memory for data4!\n");
	}
	else
	{
		printf("the address of the data4 in the pool is: %p\n",data_address4);
	}
	free(user_pool_pointer);
}

/*---------------------------------------------------------------------------*/
/* 	Test VSAFree:
	Method: Alloc few data memory address and free a data 
	each time at different location at the pool
*/
static void VSAFreeTest(void)
{
	vsa_t *vsa_pool = NULL;
	void *user_pool_pointer = NULL;
	size_t pool_size = 1000;
	
	void *data_address1 = NULL;
	size_t block_size1 = 100;
	void *data_address2 = NULL;
	size_t block_size2 = 200;
	void *data_address3 = NULL;
	size_t block_size3 = 300;

	void *data_address4 = NULL;
	size_t block_size4 = 50;

	/* Dynamically allocate memory using calloc() */ 
	printf("\n------------------------ Free test ------------------------\n\n");	
	user_pool_pointer = calloc(pool_size , sizeof(char)); 
	
	if (NULL == user_pool_pointer)
	{
		printf("there is a problem with the allocation\n");	
	}
	
	vsa_pool = VSAInit(user_pool_pointer,pool_size);

	printf("\nThe user requested two memory blocks\n");
	data_address1 = VSAAlloc(vsa_pool,block_size1);
	if (NULL == data_address1)
	{
		printf("Cant find enough memory for data1!\n");
	}
	else
	{
		printf("the address of the data1 in the pool is: %p\n",data_address1);
	}
	
	data_address2 = VSAAlloc(vsa_pool,block_size2);
	if (NULL == data_address2)
	{
		printf("Cant find enough memory for data2!\n");
	}
	else
	{
		printf("the address of the data2 in the pool is: %p\n",data_address2);
	}
	
	/* free block 1 - from the begging of the pool */
	printf("\nThe user free the first memory block\n");
	VSAFree(data_address1);

	printf("\nThe user request one memory block\n");		
	data_address3 = VSAAlloc(vsa_pool,block_size3);
	if (NULL == data_address3)
	{
		printf("Cant find enough memory for data3!\n");
	}
	
	else
	{
		printf("the address of the data3 in the pool is: %p\n",data_address3);
	}	

	printf("\nThe user free the seconed memory block\n");	
	VSAFree(data_address2);
	
	/* adding data six to the pool */
	printf("\nThe user request one memory block\n");		
	data_address4 = VSAAlloc(vsa_pool,block_size4);
	if (NULL == data_address4)
	{
		printf("Cant find enough memory for data4!\n");
	}
	else
	{
		printf("the address of the data6 in the pool is: %p\n",data_address4);
	}
	

	
	free(user_pool_pointer);	
}

/*---------------------------------------------------------------------------*/
/* 	Test BiggestFreeBlock:
	Method: Alloc few data memory address and see the changes in 
	the biggest size function info
*/
static void BiggestFreeBlockTest(void)
{
	vsa_t *vsa_pool = NULL;
	void *user_pool_pointer = NULL;
	size_t pool_size = 1000;
	
	void *data_address1 = NULL;
	size_t block_size1 = 100;
	void *data_address2 = NULL;
	size_t block_size2 = 200;
	void *data_address3 = NULL;
	size_t block_size3 = 600;
	
	printf("\n-------------- Biggest free block size test ---------------\n\n");	
	
	/* Dynamically allocate memory using calloc() */ 
	user_pool_pointer = calloc(pool_size , sizeof(char)); 
	
	if (NULL == user_pool_pointer)
	{
		printf("there is a problem with the allocation\n");	
	}
	
	vsa_pool = VSAInit(user_pool_pointer,pool_size);
	/* after init the biggest block size needs to be as pool 
	   size minus the vsa struct */
	printf("The biggest free block is (after init): %lu bytes\n",
			VSABiggestFreeBlock(vsa_pool));
			
	printf("\nThe user requested two memory blocks\n");
			
	data_address1 = VSAAlloc(vsa_pool,block_size1);
	if (NULL == data_address1)
	{
		printf("Cant find enough memory for data1!\n");
	}
	else
	{
		printf("The first address at the pool is: %p\n",data_address1);
	}
	
	data_address2 = VSAAlloc(vsa_pool,block_size2);
	if (NULL == data_address2)
	{
		printf("Cant find enough memory for data2!\n");
	}
	else
	{
		printf("the seconed address at the pool is: %p\n",data_address2);
	}
	
	/* after insert two block of data  */
	printf("The biggest free block is (after allocate two blocks):%lu bytes\n\n"
			, VSABiggestFreeBlock(vsa_pool));	


	/* the problems start here */



	printf("\nThe user requested one more memory blocks\n");				
	data_address3 = VSAAlloc(vsa_pool, block_size3);
	if (NULL == data_address3)
	{
		printf("Cant find enough memory for data3!\n");
	}
	else
	{
		printf("the third address at the pool is: %p\n",data_address3);
	}
		
	/* after insert one more block of data  */
	printf("The biggest free block is (after allocate three blocks):%lu\
 bytes\n", VSABiggestFreeBlock(vsa_pool));

	/* check size after free the first two memory blocks */
	printf("\nThe user freed two memory blocks\n");				
	VSAFree(data_address1);
	VSAFree(data_address2);
	printf("The biggest free block is (after allocate three blocks):%lu\
 bytes\n", VSABiggestFreeBlock(vsa_pool));	
	

	free(user_pool_pointer);		
}

/**************************** utility testing functions ***********************/
/* this function will show that after the free the alloc will be in the middle 
of the list in place that has been degraged the address will be the same */
static void DefragmentationTest(void)
{
	vsa_t *vsa = NULL;
	void *temp = NULL;
	void *temp1 = NULL;
	size_t pool_size = 1000;
	void *mem_pool = NULL;
	

	printf("\n----------------Defragmentation test ----------------------\n\n");

	mem_pool = calloc(pool_size, sizeof(char));
	if(NULL == mem_pool)
	{
		return;
	}
	vsa = VSAInit(mem_pool, pool_size);
	if (NULL == vsa)
	{
		printf("There is no enough bytes to create vsa\n");
		
	}		
	printf("The creation of the vsa has been succeded\n");
	printf("The current size of biggest free block is: %lu\n",\
			VSABiggestFreeBlock(vsa)); 
	printf("The address of new block is: %p\n",VSAAlloc(vsa, 32));
	printf("The current size of biggest free block is: %lu\n",\
			VSABiggestFreeBlock(vsa)); 

	printf("The address of new block is: %p\n",VSAAlloc(vsa, 100));
	temp =VSAAlloc(vsa, 60);
	printf("temp adrees %p\n", (void*)temp);
	temp1 = VSAAlloc(vsa, 100);
	printf("temp adrees %p\n", (void*)temp1);
	printf("The address of new block is: %p\n",VSAAlloc(vsa, 500));
	VSAFree(temp);
	VSAFree(temp1);
	printf("The address of new block is: %p\n",VSAAlloc(vsa, 120));
	printf("The current size of biggest free block is: %lu\n",\
			VSABiggestFreeBlock(vsa)); 
	free(vsa);

}
