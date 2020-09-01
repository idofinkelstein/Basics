#define _POSIX_C_SOURCE 100

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>	/* fork */
#include <sys/wait.h>   /* wait */

static pid_t pid = 0;

typedef struct sigaction sigact_t;

static void ParentHandler ()
{
	sleep(3);
	puts("ping");
	kill(getppid(), SIGUSR2);
	
}

static void ChildHandler ()
{	
	sleep(3);
	puts("pong");
	kill(pid, SIGUSR1);	
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
