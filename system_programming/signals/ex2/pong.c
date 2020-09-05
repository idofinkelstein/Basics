/******************************
* Project name:	pong.c
* Developer: Ido Finkelstein
* Date:
* Reviewer:
*******************************/

#define _POSIX_SOURCE

#include <stdio.h> 		/* printf, perror */
#include <stdlib.h> 	/* exit 		  */
#include <errno.h>
#include <signal.h> 	/* signal 		  */
#include <sys/types.h>  /* waitpid, fork  */
#include <sys/wait.h>   /* waitpid 		  */
#include <unistd.h> 	/* fork 		  */

/****************************   DECLARATIONS   *******************************/

void Sigusr1Handler(int signal_num);

/*---------------------------------------------------------------------------*/

int main(void)
{
    
	signal(SIGUSR1, Sigusr1Handler);
	
	pause();    
	


    return (0);
}

/*---------------------------------------------------------------------------*/

void Sigusr1Handler(int signal_num)
{
	int status = 0;
	(void)signal_num;

	
	
	sleep(1);
	printf("pong\n");
	status = kill(getppid(), SIGUSR2);

	if (0 != status)
	{
		perror("Error: kill parent sigusr2");
	}


}

/*****************************************************************************/
