#define _POSIX_SOURCE
/******************************************************************************
* Project name:					 	Pingpong_ex2
* Developer: 						Matan Yankovich
* Project Lauch: 					Aug 31, 2020
* Submitted for review:				02/09/2020
* Reviewer:
******************************************************************************/

/**********************   PREPROCESSOR DIRECTIVES   **************************/

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/****************************   DECLARATIONS   *******************************/

void Sigusr1Handler(int signal_num);
sig_atomic_t nof_pings = 0;

/********************************  MAIN  *************************************/

int main(void)
{
    signal(SIGUSR1, Sigusr1Handler);
    
    while (nof_pings < 10)
    {
        signal(SIGUSR1, Sigusr1Handler);
        pause();
    }
    
    printf("10 pings received! Child process terminating\n");

    return (0);
}

/*---------------------------------------------------------------------------*/

void Sigusr1Handler(int signal_num)
{
    int status = 0;
    (void)signal_num;

    ++nof_pings;

    printf("pong\n");

    status = kill(getppid(), SIGUSR2);
    
    if (0 != status)
    {
        perror("Error: kill parent sigusr2");
    }
}

/*****************************************************************************/
