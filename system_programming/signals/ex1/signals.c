#define _POSIX_C_SOURCE 199309L

#include <stdio.h>		/* puts */
#include <stdlib.h>		/* EXIT_STATUS */
#include <signal.h>		/* sigaction, kill */
#include <unistd.h>		/* sleep, fork, pause */
#include <sys/types.h>	/* fork, waitpid */
#include <sys/wait.h>   /* waitpid */
#include <errno.h> 		/* errno, perror */

static pid_t pid = 0;

typedef struct sigaction sigact_t;

static void ParentHandler()
{
	sleep(1);
	puts("ping");
	kill(pid, SIGUSR1);	
	sleep(1);	
}

static void ChildHandler()
{	
	sleep(1);
	puts("pong");
	kill(getppid(), SIGUSR2);
	sleep(1);
}

int PingPong()
{
	sigact_t sa1 = {0};
	sigact_t sa2 = {0};
	
	sa1.sa_handler = ChildHandler;
	sa2.sa_handler = ParentHandler;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);

	pid = fork();

	if (-1 == pid)
	{
		perror("fork failed\n");
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
		sleep(1);
		pause();		
	}

	return(EXIT_SUCCESS);
}
