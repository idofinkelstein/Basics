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

/* declaration of struct element*/
typedef struct element element; 

/* typedef of function pointers */
typedef int (*add_t)(void*, int i);
typedef void (*print_t) (int);
typedef void (*free_t) (int i);
	
static struct element
{
	void *data;
	print_t print;
	add_t add;
	free_t free_s;

}hetrogeneneous_array[SIZE] = {0};

/* function declarations */
static void PrintInt(int i);
static void PrintFloat(int i);
static void PrintString(int i);
static int AddToInt(void *num, int i);
static int AddToFloat(void *num, int i);
static int AddToString(void *string, int i);
static void FreeString();
static void FreeNonString();

static int InitArray(void);

int main()
{
	int i = 0;
	void *number = NULL;

	number = (int*)-44561;

	InitArray();
	
	/* prints the array */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].print(i);
	}

	/* adds values to array */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].add(number, i);
	}

	/* adds again */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].add(number, i);
	}

	/* prints again */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].print(i);
	}

	/* frees memory */
	for (i = 0; i < SIZE; ++i)
	{
		hetrogeneneous_array[i].free_s(i);
	}

	return 0;
}

static void PrintInt(int i)
{
	printf("%d\n",*(int*)&hetrogeneneous_array[i].data);
}

static void PrintFloat(int i)
{
	printf("%f\n",*(float*)&hetrogeneneous_array[i].data);
}

static void PrintString(int i)
{
	printf("%s\n",(char*)hetrogeneneous_array[i].data);
}

static int AddToInt(void *num, int i)
{
	assert(num);

	*(int*)&hetrogeneneous_array[i].data += *(int*)&num;

	return(SUCCESS);
}

static int AddToFloat(void *num, int i)
{
	assert(num);

	*(float*)&hetrogeneneous_array[i].data += *(int*)&num;

	return(SUCCESS);
}

static int AddToString(void *num, int i)
{	
	size_t append_str_len = 0;
	size_t str_len = strlen(hetrogeneneous_array[i].data);
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

	tmp_str = 
	realloc((char*)hetrogeneneous_array[i].data, append_str_len + str_len + 1);

	if (NULL == tmp_str)
	{
		printf("realloc failed!");

		free(append_str);

		append_str = NULL;

		return (FAILURE);
	}

	hetrogeneneous_array[i].data = tmp_str;

	strcat((char*)hetrogeneneous_array[i].data, append_str);
	
	free(append_str);

	append_str = NULL;

	return(SUCCESS);
}

static void FreeString(int i)
{
	free((char*)hetrogeneneous_array[i].data);

	hetrogeneneous_array[i].data = NULL;
}

static void FreeNonString(int i)
{
	(void)i;
}

static int InitArray(void)
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
