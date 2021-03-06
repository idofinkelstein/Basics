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
char **BreakInput(char *input);
void CleanUp(char **arg);
/*---------------------------------------------------------------------------*/
/* API functions definitions */
/*---------------------------------------------------------------------------*/
void Shell(void)
{
	char input[200];
	pid_t pid = 0;
	pid_t bg_pid = 0;
	int status = 0;
	int foreground = false;
	size_t len = 0;
	char **arg = NULL;


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

		arg = BreakInput(input);
	
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
			execvp(arg[0], arg);	
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
			puts("process running in the foreground");
			foreground = !foreground;
		}
		
		waitpid(-1, &status, WNOHANG);

		free(arg);
	}
}
/*---------------------------------------------------------------------------*/
/* Utils functions definitions */
/*---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

char **BreakInput(char *input)
{
	char **arg = NULL;
	char *str = NULL;
	char **start = NULL;

	arg = (char**)malloc(sizeof(char*) * 20);

	if(NULL == arg)
	{
		return (NULL);
	}

	start = arg;

	str = strtok(input, " ");
	 
   /* walk through other tokens */
	while(str != NULL)
	{
		*arg++ = str;
		str = strtok(NULL, " ");			
	}

	*arg = 0;
	
	return(start);
}

