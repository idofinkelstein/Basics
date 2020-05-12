/***********************
file name: ws3_env.c
author: Ido Finkelstein
reviewer: Reut Ben Harush
date: 11.5.2020
************************/

#include <stdio.h>  /* printf       */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcpy       */
#include <ctype.h>  /* tolower      */
#include <assert.h>

#define UNUSED (void)argc, (void)argv

void EnvPrint(char **envp);
void ToLowerStr(char *str);
char **EnvCopy(char **envp, size_t size);
size_t EnvSize(char **envp);
void EnvFree(char **envp);

/* the function EnvPrint prints all the enviorment variables */
void EnvPrint(char **envp)
{
	assert(envp);

	while (0 != *envp)
	{
		printf("%s\n",*envp++);	
	}
}

/* the function ToLower converts str to lower case letters */
void ToLowerStr(char *str)
{
	assert(str);

	while('\0' != *str)
	{
		*str = tolower(*str);
		++str;
	}
}

/* the function EnvCopy copies all the enviorment variables to 
   array of pointers of char type */
char **EnvCopy(char **envp, size_t size)
{
	char **new_envp = NULL;
	char **start = NULL;

	assert(envp);

	new_envp = (char**) malloc((size + 1) * sizeof(char*));
	
	if (new_envp == NULL)
	{
		return (NULL);
	}

	start = new_envp;

	while (0 != *envp)
	{	
		*new_envp = (char*) malloc(sizeof(char) * (strlen(*envp) + 1)); 

		if(*new_envp == NULL)
		{
			EnvFree(new_envp);
			return (NULL);
		}

		ToLowerStr(strcpy(*new_envp++, *envp++));		
	}	

	*new_envp = 0;

	return (start);
}

/* the function EnvSize finds the size of an array of pointers */
size_t EnvSize(char **envp)
{
	size_t size = 0;

	assert(envp);
	
	while (0 != *envp++)
	{
		++size;
	}

	return size;
}

/* the function EnvFree frees the memory of an array of pointers */
void EnvFree(char **envp)
{
	assert(envp);

	while (0 != *envp)
	{	
		free(*envp++);
	}
	
	free(*envp);
}


int main(int argc, char *argv[], char *envp[])
{
	char **new_envp = NULL;
	size_t size = EnvSize(envp);

	UNUSED;

	new_envp = EnvCopy(envp, size);

	EnvPrint(new_envp);

	EnvFree(new_envp);

	free(new_envp);

	return 0;
}



