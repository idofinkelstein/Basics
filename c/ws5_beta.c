#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED (void) argv
#define TRUE 1

static void ExitFile();
static FILE *Comparison(char *str,FILE *file_ptr, char *file_name);
static FILE *CountFileLines(FILE *file_ptr, char *file_name);
static FILE *WriteFirstLine(char *str,FILE *file_ptr, char *file_name);
static void RemoveFile(char *file_name);
static FILE* WriteToFile(char *str,FILE *file_ptr, char *file_name);

int main(int argv, char **argc)
{
	char str[100] = "";

	FILE *file_ptr = NULL;

	UNUSED;

	printf("enter text to to file\nfor exit type -exit and press Enter"
		   "\nfor outputing number of lines type -count"
		   " end press enter\nfor writting the first line"
		   " type < before the text.\n");

	while (TRUE)
	{
		fgets(str, 100, stdin);

		file_ptr = Comparison(str, file_ptr, argc[1]);
	}
	return 0;
}

static FILE *CountFileLines(FILE *file_ptr, char *file_name)
{
	char c = 0;
	int cnt = 0;

	file_ptr = fopen(file_name, "r");

	if(NULL == file_ptr)
	{
		printf("failure, no such file\n");
		
		return file_ptr;
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
	
	return file_ptr;
}

static void ExitFile()
{
	exit(0);
}

static FILE *WriteFirstLine(char *str,FILE *file_ptr, char *file_name)
{
	FILE *tmp_file_ptr = NULL;
	char c = '\0';
	
	++str;

	if(file_ptr != NULL)
	{
		tmp_file_ptr = fopen("tmp_txt", "a");
		fwrite(str, sizeof(char), strlen(str), tmp_file_ptr);
	}
	else
	{
		printf("the file does not exist\n");
		
		return file_ptr;
	}

	file_ptr = fopen(file_name, "r");

	while((c = fgetc(file_ptr)) && c != EOF)
	{
		fputc(c, tmp_file_ptr);
	}

	fclose(file_ptr);
	fclose(tmp_file_ptr);

	remove(file_name);

	rename("tmp_txt", file_name);

	return file_ptr;
}

static void RemoveFile(char *file_name)
{
	remove(file_name);
}

static FILE* WriteToFile(char *str,FILE *file_ptr, char *file_name)
{
	file_ptr = fopen(file_name, "a");

	if(file_ptr != NULL)
	{
		fwrite(str, sizeof(char), strlen(str), file_ptr);
		fclose(file_ptr);
	}

	return file_ptr;
}

static FILE *Comparison(char *str,FILE *file_ptr, char *file_name)
{
	char exit_str[7] = {'-', 'e', 'x', 'i', 't', '\n', '\0'};
	char count_str[8] = {'-', 'c', 'o', 'u', 'n', 't', '\n', '\0'};
	char remove_str[9] = {'-', 'r', 'e', 'm', 'o', 'v', 'e', '\n', '\0'};
	char ch = '<';
		
	if (strcmp(str, exit_str) == 0)
	{
		ExitFile();
	}
	else if (strcmp(str, count_str) == 0)
	{
		file_ptr = CountFileLines(file_ptr, file_name);
	}
	else if (str[0] == ch)
	{
		file_ptr = WriteFirstLine(str, file_ptr, file_name);
	} 
	else if(strcmp(str, remove_str) == 0)
	{
		RemoveFile(file_name);
	}
	else
	{
		file_ptr = WriteToFile(str, file_ptr, file_name);
	}	

	return file_ptr;
}

