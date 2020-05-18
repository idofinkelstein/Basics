/*******************
file name: ws5.c
author: Ido Finkelstein
reviewer: Shiran Hodeda
date: 18.5.2020
********************/

#include <stdio.h>  /* printf, fgetc, fgets, fputc, write, */
					/* fopen, fclose, rename, remove 	   */
#include <stdlib.h> /* exit                          	   */
#include <string.h> /* strcmp, strlen                	   */
#include <assert.h>

#define UNUSED (void) argv

#define APPEND 0
#define REMOVE 1
#define COUNT 2
#define WRITE 3
#define QUIT 4
#define SIZE 5

enum STATUS {SECCESS, OPEN_FAILED};
 
int Comparison(char*);

/* operation functions declaretion */
enum STATUS Append(char*, int, char *name);
enum STATUS Remove(char*, int, char *name);
enum STATUS Count(char*, int, char *name);
enum STATUS Write(char*, int, char *name);
enum STATUS Quit(char*, int, char *name);


struct what_to_do
{
 	char *str;
	int (*cmpr_ptr)(char*);
	enum STATUS (*opr_ptr)(char*, int, char *name);
}arr[SIZE];

/*initializing struct what_to_do variables */
struct what_to_do append = {"", Comparison, Append};
struct what_to_do delete = {"-remove\n", Comparison, Remove};
struct what_to_do count = {"-count\n", Comparison, Count};
struct what_to_do write_to_start = {"<", Comparison, Write};
struct what_to_do quit = {"-exit\n", Comparison, Quit};


int main(int argv, char **argc)
{
	int status = 0; /* for recieving output from compare function
					   and to know which operation function to
					   refer to */
	char s[100] = "";
	int i = 0;
	
	arr[0] = append;
	arr[1] = delete;
	arr[2] = count;
	arr[3] = write_to_start;
	arr[4] = quit;

	UNUSED;

	printf("enter text to to file\nfor exit type -exit and press Enter"
		   "\nfor outputing number of lines type -count"
		   " end press enter\nfor writting the first line"
		   " type < before the text.\n");

	while (1)
	{
		fgets(s, 100, stdin);
		for(i = 0; i < SIZE; ++i)
		{
			status = arr[i].cmpr_ptr(s);
			arr[i].opr_ptr(s, status, argc[1]);	
		}
	}
	return 0;
}

/* compares input string to operation string */
int Comparison(char* str)
{
	assert(str);

	if (strcmp(quit.str, str) == 0)
	{
		return QUIT;
	}
	else if (strcmp(count.str, str) == 0)
	{
		return COUNT;
	}
	else if (write_to_start.str[0] == str[0])
	{
		return WRITE;
	} 
	else if (strcmp(delete.str, str) == 0)
	{
		return REMOVE;
	}
	else
	{
		return APPEND;
	}	
}

/* appends text to the end of the file given by the user */
enum STATUS Append(char* str, int status, char *name)
{
	assert(str);	

	if(status == APPEND && name != NULL)
	{
		FILE *file_ptr = fopen(name, "a"); 

		fwrite(str, sizeof(char), strlen(str), file_ptr);
		fclose(file_ptr);

		return SECCESS;			
	}

	if (status == APPEND && name == NULL)
	{
		printf("file name was not entered\n");
	}
	
	return OPEN_FAILED;	
}

/* deletes the file */
enum STATUS Remove(char* str, int status, char *name)
{
	assert(str);
	
	if (status == REMOVE)	
	{
		(void)str;
		(void)status;
		
		if (NULL != name)
		{
			remove(name);
			return SECCESS;
		}
	}
	
	return OPEN_FAILED;
}

/* counts number of lines */
enum STATUS Count(char* str, int status, char *name)
{
	assert(str);

	if (status == COUNT && name != NULL)
	{
		char c = '\0';
		int cnt = 0;
		FILE *file_ptr = fopen(name, "r");

		(void)str;

		if(NULL == file_ptr)
		{
			printf("failure, no such file\n");
		
			return OPEN_FAILED;
		}

		while((c = fgetc(file_ptr)) && c != EOF)
		{
			if ('\n' == c)
			{ 
				++cnt;
			}
		}				
			
		fclose(file_ptr);

		printf("nuber of lines: %d\n", cnt);

		return SECCESS;
	}

	if (status == COUNT && name == NULL)
	{
		printf("file name was not entered\n");
	}
	
	return OPEN_FAILED;	
}

/* writes to the beginning of the file */
enum STATUS Write(char* str, int status, char *name)
{
	assert(str);

	if (status == WRITE && name != NULL)
	{
		FILE *file_ptr = fopen(name, "r");
		FILE *tmp_file_ptr = NULL;
		char c = '\0';
	
		++str;

		/* creates temporery file and writes the input
		   to the head of the file */
		if(NULL != file_ptr)
		{
			tmp_file_ptr = fopen("tmp_txt", "a");
			fwrite(str, sizeof(char), strlen(str), tmp_file_ptr);
		}
		else
		{
			printf("the file does not exist\n");
		
			return OPEN_FAILED;
		}
	
		/*appends the original file to temp file */
		while((c = fgetc(file_ptr)) && c != EOF)
		{
			fputc(c, tmp_file_ptr);
		}

		fclose(file_ptr);
		fclose(tmp_file_ptr);

		remove(name);

		rename("tmp_txt", name);

		return SECCESS;
	}
	
	if (status == WRITE && name == NULL)
	{
		printf("file name was not entered\n");
	}
	
		return OPEN_FAILED;	
}

/* exits the program */
enum STATUS Quit(char* str, int status, char *name)
{
	if (status == QUIT)
	{
		(void)str;
		(void)status;
		(void)name;

		exit(0);
	}
	else
	{
		return OPEN_FAILED;
	}
}

