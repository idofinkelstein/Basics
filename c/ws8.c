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

/* declaration of struct element*/
typedef struct element element; 

/* typedef of function pointers */
typedef void (*add_t)(void*, int i);
typedef void (*print_t) (int);
typedef void (*free_t) (int i);
	
static struct element
{
	void *data;
	print_t print;
	add_t add;
	free_t free_s;

}hetrogeneneous_array[SIZE];

/* function declarations */
static void PrintInt(int i);
static void PrintFloat(int i);
static void PrintString(int i);
static void AddToInt(void *num, int i);
static void AddToFloat(void *num, int i);
static void AddToString(void *string, int i);
static void FreeString();
static void FreeNonString();

static void InitArray(void);

int main()
{
	int i = 0;
	void *number = NULL;

	number  = (int*)-44561;
	
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

static void AddToInt(void *num, int i)
{
	assert(num);

	*(int*)&hetrogeneneous_array[i].data += *(int*)&num;
}

static void AddToFloat(void *num, int i)
{
	assert(num);

	*(float*)&hetrogeneneous_array[i].data += *(int*)&num;
}

static void AddToString(void *num, int i)
{	
	size_t append_str_len = 0;
	size_t str_len = strlen(hetrogeneneous_array[i].data);
	/* append_str = max size of int in digits + sign + end of string */
	char *append_str = (char*)malloc(12 * sizeof(char)); 

	assert(num);

	if (NULL == append_str)
	{
		printf("malloc failed!");
		return;
	}

	sprintf(append_str, "%d", *(int*)&num);

	append_str_len = strlen(append_str);

	hetrogeneneous_array[i].data = 
	realloc((char*)hetrogeneneous_array[i].data, append_str_len + str_len + 1);

	if (NULL == hetrogeneneous_array[i].data)
	{
		printf("realloc failed!");

		free(append_str);

		append_str = NULL;

		return;
	}

	strcat((char*)hetrogeneneous_array[i].data, append_str);
	
	free(append_str);

	append_str = NULL;
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

static void InitArray(void)
{	
	*(int*)&hetrogeneneous_array[0].data = 123;
	hetrogeneneous_array[0].print = PrintInt;
	hetrogeneneous_array[0].add = AddToInt;
	hetrogeneneous_array[0].free_s = FreeNonString;

	*(float*)&hetrogeneneous_array[1].data = 234.456;
	hetrogeneneous_array[1].print = PrintFloat;
	hetrogeneneous_array[1].add = AddToFloat;
	hetrogeneneous_array[1].free_s = FreeNonString;

	hetrogeneneous_array[2].data = (char*)malloc(13 * sizeof(char));

	strcpy((char*)hetrogeneneous_array[2].data,"hello world!");
	hetrogeneneous_array[2].print = PrintString;
	hetrogeneneous_array[2].add = AddToString;
	hetrogeneneous_array[2].free_s = FreeString;
	
	*(float*)&hetrogeneneous_array[3].data = 0.00435;
	hetrogeneneous_array[3].print = PrintFloat;
	hetrogeneneous_array[3].add = AddToFloat;
	hetrogeneneous_array[3].free_s = FreeNonString;

	hetrogeneneous_array[4].data = (char*)malloc(8 * sizeof(char));

	strcpy((char*)hetrogeneneous_array[4].data,"EPISODE");
	hetrogeneneous_array[4].print = PrintString;
	hetrogeneneous_array[4].add = AddToString;
	hetrogeneneous_array[4].free_s = FreeString;
}
