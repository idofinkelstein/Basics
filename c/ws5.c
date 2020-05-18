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

#define UNUSED (void) argc

#define TRUE 1
#define FALSE 0
#define SIZE 5
#define MAX_LINE_SIZE 250

enum STATUS {SECCESS = 0, FAILED};

/* comperison functions declaretion */
int AppendComparison(char*);
int RemoveComparison(char*);
int CountComparison(char*);
int WriteComparison(char*);
int QuitComparison(char*);

/* operation functions declaretion */
enum STATUS Append(char *line_input, char *file_name);
enum STATUS Remove(char *line_input, char *file_name);
enum STATUS Count(char *line_input, char *file_name);
enum STATUS Write(char *line_input, char *file_name);
enum STATUS Quit(char *line_input, char *file_name);


struct what_to_do
{
 	char *cmpr_input;
	int (*cmpr_ptr)(char*);
	enum STATUS (*opr_ptr)(char*, char*);

}arr[SIZE];

/*initializing struct what_to_do variables */
struct what_to_do append = {"", AppendComparison, Append};
struct what_to_do delete = {"-remove\n", RemoveComparison, Remove};
struct what_to_do count = {"-count\n", CountComparison, Count};
struct what_to_do write_to_start = {"<", WriteComparison, Write};
struct what_to_do quit = {"-exit\n", QuitComparison, Quit};


int main(int argc, char **argv)
{
	char line_input[MAX_LINE_SIZE] = "";
	char *file_name = argv[1];
	int i = 0;
	
	arr[0] = quit;
	arr[1] = delete;
	arr[2] = count;
	arr[3] = write_to_start;

	/* future features should be placed here */

	arr[4] = append;

	UNUSED;

	printf("enter text to file\nfor exit type -exit and press Enter"
		   "\nfor outputing number of lines type -count"
		   " and press enter\nfor writting the first line"
		   " type < before the text.\n");

	while (TRUE)
	{
		fgets(line_input, MAX_LINE_SIZE, stdin);

		for(i = 0; i < SIZE; ++i)
		{
			if (TRUE == arr[i].cmpr_ptr(line_input))
			{
				arr[i].opr_ptr(line_input, file_name);

				break;
			}	
		}
	}
	return (SECCESS);
}

int AppendComparison(char* line_input)
{
	assert(line_input);
	
	(void)line_input;

	return (TRUE);
}

int RemoveComparison(char* line_input)
{
	assert(line_input);
 
	if (strcmp(delete.cmpr_input, line_input) == 0)
	{
		return (TRUE);
	}	

	return (FALSE);
}

int CountComparison(char* line_input)
{
	assert(line_input);

	if (strcmp(count.cmpr_input, line_input) == 0)
	{
		return (TRUE);
	}
	
	return (FALSE);	
}

int WriteComparison(char* line_input)
{
	assert(line_input);

	if (write_to_start.cmpr_input[0] == line_input[0])
	{
		return (TRUE);
	} 
	
	return (FALSE);	
}

int QuitComparison(char* line_input)
{
	assert(line_input);

	if (strcmp(quit.cmpr_input, line_input) == 0)
	{
		return (TRUE);
	}
	
	return (FALSE);
	
}
/* appends text to the end of the file given by the user */
enum STATUS Append(char* line_input, char *file_name)
{
	assert(line_input);	

	if(NULL != file_name)
	{
		FILE *file_ptr = fopen(file_name, "a");
 
		if(NULL != file_ptr)
		{
			fwrite(line_input, sizeof(char), strlen(line_input), file_ptr);
		}

		if(SECCESS == fclose(file_ptr))
		{
			return (SECCESS);
		}

		return (FAILED);	
	}

	printf("file name was not entered\n");
	
	return (FAILED);	
}

/* deletes the file */
enum STATUS Remove(char* line_input, char *file_name)
{
	assert(line_input);
	
	(void)line_input;
		
	if (NULL != file_name)
	{
		remove(file_name);	

		return (SECCESS);
	}
	
	printf("no file to remove\n");	

	return (FAILED);
}

/* counts number of lines */
enum STATUS Count(char* line_input, char *file_name)
{
	assert(line_input);

	if (NULL != file_name)
	{
		char c = '\0';
		int cnt = 0;
		FILE *file_ptr = fopen(file_name, "r");

		(void)line_input;

		if(NULL == file_ptr)
		{
			printf("failure, no such file\n");
		
			return (FAILED);
		}

		while((c = fgetc(file_ptr)) && c != EOF)
		{
			if ('\n' == c)
			{ 
				++cnt;
			}
		}				
		printf("nuber of lines: %d\n", cnt);	
		
		if(SECCESS == fclose(file_ptr))
		{
			return (SECCESS);
		}
		
		return (FAILED);
		
	}

	printf("file name was not entered\n");
	
	return (FAILED);	
}

/* writes to the beginning of the file */
enum STATUS Write(char* line_input, char *file_name)
{
	assert(line_input);

	if (NULL != file_name)
	{
		FILE *file_ptr = fopen(file_name, "r");
		FILE *tmp_file_ptr = NULL;
		char c = '\0';
	
		++line_input;

		if(NULL != file_ptr)
		{
		 /* creates temporery file and writes the input
	        to the head of the file */
			tmp_file_ptr = fopen("tmp_txt", "a");

			if (NULL != tmp_file_ptr)
			{
				fwrite(line_input, sizeof(char), strlen(line_input), tmp_file_ptr);
			}
			else
			{
				return (FAILED);
			}

		}
		else
		{
			printf("the file does not exist\n");
		
			return FAILED;
		}
	
		/*appends the original file to temp file */
		while((c = fgetc(file_ptr)) && c != EOF)
		{
			fputc(c, tmp_file_ptr);
		}

		if (SECCESS == fclose(file_ptr) && SECCESS == fclose(tmp_file_ptr))
		{
			remove(file_name);

			rename("tmp_txt", file_name);

			return SECCESS;
		}

		remove(file_name);

		rename("tmp_txt", file_name);

		return FAILED;
	}
	
	printf("file name was not entered\n");	
	
	return FAILED;	
}

/* exits the program */
enum STATUS Quit(char* line_input, char *file_name)
{
		(void)line_input;
		(void)file_name;

		exit(0);
}

