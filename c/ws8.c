/**********************************
file name: ws8.c
author: Ido Finkelstein
reviewer: Shahrazad Tarboush Sirhan
date: 26.5.2020
***********************************/

#include <stdio.h>   /* printf, sprintf */
#include <stdlib.h>  /* malloc, realloc, free */
#include <string.h>  /* strcpy, strcat */
#include <assert.h>  /* assert */

#define SIZE 5
#define MAX_DIGITS_TO_INT 12
#define STR2_SIZE 13
#define STR4_SIZE 8
#define SUCCESS 0
#define FAILURE -1

/* typedef of function pointers */
typedef int (*add_t)(void**, void*);
typedef void (*print_t) (void*);
typedef void (*free_t) (void**);
	
typedef struct element
{
	void *data;
	print_t print;
	add_t add;
	free_t free_s;

}element_t;


/* function declarations */
static void PrintInt(void *data);
static void PrintFloat(void *data);
static void PrintString(void *data);
static int AddToInt(void **data, void *num);
static int AddToFloat(void **data, void *num);
static int AddToString(void **data, void *num);
static void FreeString(void **data);
static void FreeNonString(void **data);

static int InitArray(element_t *hetrogeneneous_array);

int main()
{
	element_t *hetrogeneneous_array; 
	
	int i = 0;
	void *number = NULL;

	number = (int*)25;

	hetrogeneneous_array = malloc(sizeof(element_t) * SIZE);

	InitArray(hetrogeneneous_array);
	
	/* prints the array */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].print(hetrogeneneous_array[i].data);
	}

	/* adds values to array */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].add(&hetrogeneneous_array[i].data, number);
	}

	/* adds again */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].add(&hetrogeneneous_array[i].data, number);
	}

	/* prints again */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].print(hetrogeneneous_array[i].data);
	}

	/* frees memory */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].free_s(hetrogeneneous_array[i].data);
	}

	free(hetrogeneneous_array);

	return 0;
}

static void PrintInt(void *data)
{
	printf("%d\n",*(int*)&data);
}

static void PrintFloat(void *data)
{
	printf("%f\n",*(float*)&data);
}

static void PrintString(void *data)
{
	printf("%s\n",(char*)data);
}

static int AddToInt(void **data, void *num)
{
	assert(num);

	*(int*)data += *(int*)&num;

	return(SUCCESS);
}

static int AddToFloat(void **data, void *num)
{
	assert(num);

	*(float*)data += *(int*)&num;

	return(SUCCESS);
}

static int AddToString(void **data, void *num)
{	
	size_t append_str_len = 0;
	size_t str_len = strlen(*data);
	char *tmp_str = NULL;
	char *append_str = (char*)malloc(MAX_DIGITS_TO_INT * sizeof(char)); 

	assert(num);

	if (NULL == append_str)
	{
		printf("malloc failed!");
		return (FAILURE);
	}

	sprintf(append_str, "%d", *(int*)&num);

	append_str_len = strlen(append_str);

	tmp_str = realloc((char*)*data, append_str_len + str_len + 1);

	if (NULL == tmp_str)
	{
		printf("realloc failed!");

		free(append_str);

		append_str = NULL;

		return (FAILURE);
	}

	*data = tmp_str;

	strcat(*data, append_str);
	
	free(append_str);

	append_str = NULL;

	return(SUCCESS);
}

static void FreeString(void **data)
{
	free((char*)data);

	data = NULL;
}

static void FreeNonString(void **data)
{
	(void)data;
}

static int InitArray(element_t *hetrogeneneous_array)
{	
	*(int*)&hetrogeneneous_array[0].data = 123;
	hetrogeneneous_array[0].print = PrintInt;
	hetrogeneneous_array[0].add = AddToInt;
	hetrogeneneous_array[0].free_s = FreeNonString;

	*(float*)&hetrogeneneous_array[1].data = 234.456;
	hetrogeneneous_array[1].print = PrintFloat;
	hetrogeneneous_array[1].add = AddToFloat;
	hetrogeneneous_array[1].free_s = FreeNonString;

	hetrogeneneous_array[2].data = (char*)malloc(STR2_SIZE * sizeof(char));

	if(NULL == hetrogeneneous_array[2].data)
	{
		return (FAILURE);
	}

	strcpy((char*)hetrogeneneous_array[2].data,"hello world!");
	hetrogeneneous_array[2].print = PrintString;
	hetrogeneneous_array[2].add = AddToString;
	hetrogeneneous_array[2].free_s = FreeString;
	
	*(float*)&hetrogeneneous_array[3].data = 0.00435;
	hetrogeneneous_array[3].print = PrintFloat;
	hetrogeneneous_array[3].add = AddToFloat;
	hetrogeneneous_array[3].free_s = FreeNonString;

	hetrogeneneous_array[4].data = (char*)malloc(STR4_SIZE * sizeof(char));

	if(NULL == hetrogeneneous_array[4].data)
	{
		return (FAILURE);
	}

	strcpy((char*)hetrogeneneous_array[4].data,"EPISODE");
	hetrogeneneous_array[4].print = PrintString;
	hetrogeneneous_array[4].add = AddToString;
	hetrogeneneous_array[4].free_s = FreeString;

	return (SUCCESS);
}
