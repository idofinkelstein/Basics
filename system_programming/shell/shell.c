#include <stdio.h>		/* scanf, exit, EXIT_FAILURE */
#include <stdlib.h>		/* exit */
#include <string.h>		/* strtok */
#include <sys/types.h>	/* fork */
#include <sys/wait.h>
#include <unistd.h>		

#include "shell.h"		/* API functions */
/*---------------------------------------------------------------------------*/
enum creation_status
{
	CREATION_FAILED = -1
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Utils functions declarations */
/*---------------------------------------------------------------------------*/
void CreateProcess(char *input);
/*---------------------------------------------------------------------------*/
/* API functions definitions */
/*---------------------------------------------------------------------------*/
void Shell(void)
{
	char input[200];

	while (1)	
	{
		scanf("%s", input);
		CreateProcess(input);
	}
}
/*---------------------------------------------------------------------------*/
/* Utils functions definitions */
/*---------------------------------------------------------------------------*/
void CreateProcess(char *input)
{
	pid_t pid = 0;
	int status = 0;

	/* fork() returns the process identifier (pid) of the child process in the
 	   parent, and returns 0 in the child. */
	pid = fork();

	if (0 == strcmp(input, "exit"))
	{
		exit(0);
	}


	if (CREATION_FAILED == pid)
	{
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{			
		/* goes in only from the child process */
		execlp(input, input, (char *)NULL);	
		exit(0);
	}
	else
	{
		wait(&status);
	}
	
}
/*----------------------------------------------------------------------------*/

