#include <stdio.h>		/* scanf, printf */
#include <stdlib.h>		/* exit */
#include <string.h>		/* strtok, strcmp */
#include <signal.h>		/* signal */
#include <stdbool.h>	/* true, false */
#include <sys/types.h>	/* fork */
#include <sys/wait.h>   /* wait */
#include <unistd.h>		/* exec, fork */

#include "vector.h"
#include "shell.h"		/* API functions */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Utils functions declarations */
/*---------------------------------------------------------------------------*/
void CreateProcess(char *input);
vector_t *BreakInput(char *input);

/*---------------------------------------------------------------------------*/
/* API functions definitions */
/*---------------------------------------------------------------------------*/
void Shell(void)
{
	char input[200];
	pid_t pid = 0;
	int status = 0;
	int foreground = false;
	size_t len = 0;
	char **argv_array = NULL;
	vector_t *argv = NULL;

	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		fprintf (stderr, "Cannot handle SIGINT!\n");
		exit(EXIT_FAILURE);
	}

	while (1)	
	{
		printf(">>>");
	
		fgets(input, 200, stdin);
		input[strlen(input) - 1] = '\0';

		/* in case of empty input continue to next iteration */
		if (*input == '\0')
		{
			continue;
		}

		len = strlen(input);

		if (0 == strcmp(input, "exit"))
		{
			exit(0);
		}

		if ('&' == *(input + len - 1))
		{
			foreground = true;
			*(input + len - 1) = '\0';
		}
	
	 /* fork() returns the process identifier (pid) of the child process in the
 	    parent, and returns 0 in the child. */

		pid = fork();
		
		if (-1 == pid)
		{
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{			
			/* goes in only from the child process */
			argv = BreakInput(input);
			argv_array = (char**)VectorGetArray(argv);

			execvp(argv_array[0], argv_array);	
			VectorDestroy(argv);
			puts("unknown command");
			exit(0);
		}
		else if (!foreground && pid > 0)
		{
			/* goes in only from the parent process 
			   and if command is running in background */
			waitpid(pid, &status, 0);
			puts("process terminated");
		}
		else if (foreground)
		{
			/* goes in only from parent */
			puts("process running in the background");
			foreground = !foreground;
		}
		
		waitpid(-1, &status, WNOHANG);
	}
}
/*---------------------------------------------------------------------------*/
/* Utils functions definitions */
/*---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

vector_t *BreakInput(char *input)
{	
	char *str = NULL;
	vector_t *argv = NULL;

	argv = VectorCreate(10);

	if (NULL == argv)
	{
		return (NULL);
	}

	str = strtok(input, " ");
	 
   /* walk through other tokens */
	while(str != NULL)
	{
		VectorPushBack(argv, str);
		str = strtok(NULL, " ");			
	}

	VectorPushBack(argv, NULL);
	
	return(argv);
}

