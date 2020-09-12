#define _DEFAULT_SOURCE
/******************************************************************************
* File name:					 	ping.c
* Developer: 						IdoFinkelstein
* Reviewer:
******************************************************************************/

#include <stdio.h>  	/* printf, perror		  */
#include <stdlib.h> 	/* sleep 				  */
#include <signal.h> 	/* sigaction, sigemptyset */
#include <errno.h>		/* errno, perror		  */
#include <unistd.h> 	/* pause 				  */
#include <sys/types.h>  /* getpid, kill			  */
#include <sys/wait.h>


void Sigusr1Handler(int signal_num, siginfo_t *info, void *context);
sig_atomic_t nof_pings = 0;

/********************************  MAIN  *************************************/

int main(int argc, char const *argv[])
{
	struct sigaction sigusr1action;

	pid_t ping_pid = 0;
	if (argc < 2)
	{
		printf("I need ping's pid! try again\n");
		return (-1);
	}
	ping_pid = (pid_t)atoi(argv[1]);

	sigusr1action.sa_sigaction = Sigusr1Handler;
	sigusr1action.sa_flags = SA_SIGINFO;
	sigemptyset(&sigusr1action.sa_mask);
	sigaction(SIGUSR1, &sigusr1action, 0);

	printf("pong\n");

	if (0 != kill(ping_pid, SIGUSR2))
    {
        perror("Error: kill parent sigusr2");
    }


    while (nof_pings < 10)
    {
		pause();
		printf("pong\n");
    }
   
	printf("10 pings received! killing ping and terminating\n");
	kill(ping_pid, SIGTERM);

    return (0);
}

/*---------------------------------------------------------------------------*/

void Sigusr1Handler(int signal_num, siginfo_t *info, void *context)
{

	(void)signal_num;
	(void)context;
	++nof_pings;

	
	if (0 != kill(info->si_pid, SIGUSR2))
	{
		perror("Error: kill sigusr2 failed");
	}
	sleep(1);
}

/*****************************************************************************/
