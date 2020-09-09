#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>


char *SetName(char *input);
sem_t *SemCreate(char *name);
int SemAction(sem_t *sem_addr, char *argv[]);
int SemValue(sem_t *sem_addr, char *argv[]);

int main(int argc, char *argv[])
{
	sem_t *sem_addr = NULL;
	int status = 0;
	char *name = NULL;

	if (argc == 1)
	{
		puts("no name specified");
		exit(EXIT_FAILURE);
	}
	/* in case of sem already exists, semcreate obtains the address of it */
	if (argc > 1) 
	{
		name = SetName(argv[1]);
		sem_addr = SemCreate(name);
	}	
	if (argc == 3 && sem_addr)
	{
		SemValue(sem_addr, argv);

		if (0 == strcmp(argv[2], "X"))
		{
			status = sem_unlink(argv[1]);

			if (!status)
			{
				printf("sem: %s destroied\n", argv[1]);
			}
		}
	}
	else if (argc == 4 && sem_addr)
	{
		SemAction(sem_addr, argv);
	}

	if (NULL != name)
	{
		free(name);
	}

	sem_close(sem_addr);

	return 0;	
}

sem_t *SemCreate(char *name)
{
	sem_t *sem_addr = NULL;
	
	sem_addr = sem_open(name, O_CREAT, 0664, 0); /* +rw for user and group */

	if (NULL == sem_addr)
	{
		puts("creation failed!");
		exit(EXIT_FAILURE);
	}

	return (sem_addr);
}

int SemAction(sem_t *sem_addr, char *argv[])
{
	int status = 0;
	size_t i = 0;
	size_t size = atoi(argv[3]);;

	if (0 == strcmp(argv[2], "I"))
		{ 

			for (i = 0; i < size && !status; ++i)
			{
				status = sem_post(sem_addr);
			}

			if (0 == status)
			{
				puts("incremation success");
			}
			else
			{
				puts("faild");
			}
		} 
		else if (0 == strcmp(argv[2], "D"))
		{
			
			for (i = 0; i < size && !status; ++i)
			{
				status = sem_wait(sem_addr);
			}

			if (0 == status)
			{
				puts("decremetion success");
			}
			else
			{
				puts("faild");
			}
		}	

	return (status);	
}

int SemValue(sem_t *sem_addr, char *argv[])
{
	int status = 0;
	int sem_val = 0;

	if (0 == strcmp(argv[2], "V"))
		{
			status = sem_getvalue(sem_addr, &sem_val);

			if (0 == status)
			{
				printf("sem: %s value = %d\n", argv[1], sem_val);
			}
		}

	return (status);
}

char *SetName(char *input)
{
	char *name = NULL;

	name = (char*)malloc(251);

	if (NULL == name)
	{
		return (NULL);
	}

	name[0] = '/';

	strcpy(name + 1, input);

	if(NULL != strchr(name + 1, '/'))
	{
		puts("invalid name: slash is not allowed");
		free(name);
		exit(EXIT_FAILURE);
	}

	return (name);
}
