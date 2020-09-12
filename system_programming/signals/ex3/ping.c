#define _DEFAULT_SOURCE
/*****************************
* File name: ping.c
* Developer: IdoFinkelstein
* Reviewer:  Matan Yancovich		
******************************/

#include <stdio.h>  	/* printf, perror		  */
#include <stdlib.h> 	/* sleep 				  */
#include <signal.h> 	/* sigaction, sigemptyset */
#include <errno.h>		/* errno, perror		  */
#include <unistd.h> 	/* pause 				  */
#include <sys/types.h>  /* getpid, kill			  */
#include <sys/wait.h>

/* Function declarations */
void Sigusr2Handler(int signal_num, siginfo_t *info, void *context);


int main(void)
{  
	struct sigaction sigusr2action;
	sigusr2action.sa_sigaction = Sigusr2Handler;
	sigusr2action.sa_flags = SA_SIGINFO; 
	sigemptyset(&sigusr2action.sa_mask);
	sigaction(SIGUSR2, &sigusr2action, NULL);
    
	printf("my pid (ping) is: %d\n", getpid());

	while (1)
	{
		pause();
		printf("ping\n");
	}
    
	return (0);
}

/*---------------------------------------------------------------------------*/

void Sigusr2Handler(int signal_num, siginfo_t *info, void *context)
{
	(void)signal_num;
	(void)context;

	
	sleep(1);
	if (0 != kill(info->si_pid, SIGUSR1))
	{
		perror("Error: kill sigusr1 failed");
	}
}

/*****************************************************************************/
