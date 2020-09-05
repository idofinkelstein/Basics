#define _POSIX_C_SOURCE 199309L

#include <stdio.h>		/* puts */
#include <stdlib.h>		/* EXIT_STATUS */
#include <signal.h>		/* sigaction, kill */
#include <unistd.h>		/* sleep, fork, pause */
#include <sys/types.h>	/* fork, waitpid */
#include <sys/wait.h>   /* waitpid */

static pid_t pid = 0;

typedef struct sigaction sigact_t;

static void ParentHandler()
{
	sleep(1);
	puts("ping");
	kill(getppid(), SIGUSR2);
	sleep(1);	
}

static void ChildHandler()
{	
	sleep(1);
	puts("pong");
	kill(pid, SIGUSR1);	
	sleep(1);
}

int PingPong()
{
	sigact_t sa1 = {0};
	sigact_t sa2 = {0};
	
	sa1.sa_handler = ParentHandler;
	sa2.sa_handler = ChildHandler;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);

	pid = fork();

	if (-1 == pid)
	{
		return(EXIT_FAILURE);
	}
	else if (pid > 0)/* in the parent process */
	{		
		kill(pid, SIGUSR1);
		sleep(1);
		pause();
		waitpid(pid, NULL, 0);	
	}
	else
	{		
		kill(getppid(), SIGUSR2);
		sleep(1);
		pause();		
	}

	return(EXIT_SUCCESS);
}
