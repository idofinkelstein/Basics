
/******************************
* Project name:	Ping.c
* Developer: Ido Finkelstein
* Date:
* Reviewer: Matan Yankovich
*******************************/

#define _POSIX_SOURCE

#include <stdio.h> 		/* printf, perror */
#include <stdlib.h> 	/* exit 		  */
#include <signal.h> 	/* signal 		  */
#include <errno.h>
#include <sys/types.h>  /* waitpid, fork  */
#include <sys/wait.h>   /* waitpid 		  */
#include <unistd.h> 	/* fork 		  */

/****************************   DECLARATIONS   *******************************/

void Sigusr2Handler(int signal_num);
void Sigusr1Handler(int signal_num);
void SendSigToChild(int child_pid);

/*---------------------------------------------------------------------------*/

int main(void)
{
    int child_pid;
    int child_status;

    signal(SIGUSR2, Sigusr2Handler);
    child_pid = fork();

    if (child_pid < 0)
    {
        perror("Error: fork");
        return (-1);
    }

    /* inside child */
    else if (0 == child_pid)
    {
        execl("./b.out", "./b.out", (char *)NULL);
        perror("Error: evecl"); /* can't exec */
        exit(EXIT_FAILURE);
    }
    
    /* inside parent */
 
    sleep(1);
    SendSigToChild(child_pid);
    waitpid(child_pid, &child_status, 0);


    printf("Parent process terminating\n");  
    return (0);
}

/*---------------------------------------------------------------------------*/

void SendSigToChild(int child_pid)
{
	int status = 0;

    printf("ping\n");
    status = kill(child_pid, SIGUSR1);

	if (0 != status)
	{
		perror("Error: kill parent sigusr1");
	}
}

/*---------------------------------------------------------------------------*/

void Sigusr2Handler(int signal_num)
{
    (void)signal_num;
	sleep(1);
    printf("ping\n");
	
	
	
}

/*****************************************************************************/
