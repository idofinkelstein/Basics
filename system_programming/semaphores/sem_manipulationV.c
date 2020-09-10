#include <stdio.h> 		/* printf 						   */
#include <stdlib.h> 	/* malloc, free, exit 			   */
#include <string.h> 	/* strcmp, strtok, strcat, strcpy  */
#include <sys/types.h>  /* semctl, semget, semop 		   */
#include <sys/ipc.h> 	/* semctl, semget, semop 		   */
#include <sys/sem.h>	/* semctl, semget, semop, semid_ds */

typedef struct sembuf sembuf_t;

union semun
{
	int              val;    /* Value for SETVAL 			 */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL 	 */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                       (Linux-specific) 	 */
};
/*-----------------------------------------------------------------------------*/

static void InitSops(sembuf_t *sops, unsigned short sem_num, short sem_op, short sem_flg);
static char **BreakInput(char *input);

/*-----------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	key_t key;
	int semid;
	sembuf_t *sops = NULL;
	char *partial_path = "/home/ido/git/system_programming/semaphores/";
	char *path = NULL;
	size_t path_len = 0;
	char input[200];
	size_t partial_path_len = strlen(partial_path);
	char **command = NULL;
	int val = 0;
	union semun arg;

	if (argc == 1)
	{
		puts("no name specified");
		exit(EXIT_FAILURE);
	}
	if (argc > 1)
	{
		path_len = strlen(argv[1]);
		path = (char*)malloc(path_len + partial_path_len + 1);

		strcpy(path, partial_path);
		strcat(path, argv[1]);
	}

	sops = (sembuf_t*)malloc(sizeof(sembuf_t));

	if (NULL == sops)
	{
		exit(1);
	}

	key = ftok(path, 'S');
	semid = semget(key, 1, 0664 | IPC_CREAT);

	free(path);
		
	while (1)
	{
		printf(">>>");
	
		fgets(input, 200, stdin);
		input[strlen(input) - 1] = '\0';

		/* in case of empty input continue to next iteration */
		if (*input == '\0')
		{
			continue;
		}
		command = BreakInput(input);

		switch (*command[0])
		{
			case 'D': /* decrease value */
				if (command[1])
				{
					val = (-1) * atoi(command[1]);
					if (command[2] && 0 == strcmp(command[2], "undo"))
					{
						InitSops(sops, 0, val, SEM_UNDO);
					}
					else
					{
						InitSops(sops, 0, val, 0);
					}
					semop(semid, sops, 1);
				}
				else
				{
					puts("value not entered");
				}
				break;

			case 'I': /* increase value */
				if (command[1])
				{
					val = atoi(command[1]);
					if (command[2] && 0 == strcmp(command[2], "undo"))
					{
						InitSops(sops, 0, val, SEM_UNDO);
					}
					else
					{
						InitSops(sops, 0, val, 0);
					}
					semop(semid, sops, 1);
				}
				else
				{
					puts("value not entered");
				}
				break;

			case 'V': /* get semaphore value */
				printf("value = %d\n",semctl(semid, 0, GETVAL, arg));				
				break;

			case 'X': /* exit program */
				free(sops);
				free(command);
				exit(0);
				break;

			case 'R': /* remove semaphore and exit */
				semctl(semid, 0, IPC_RMID);
				free(sops);
				free(command);
				exit(0);
				break;

			default:
				break;
		}
		
		free(command);
	}

	return 0;
}
/*-----------------------------------------------------------------------------*/

/* initializes struct by which command is passing to semop */
static void InitSops(sembuf_t *sops, unsigned short sem_num, short sem_op, short sem_flg)
{
	sops->sem_num = sem_num;        
	sops->sem_op = sem_op;         
	sops->sem_flg = sem_flg;
}
/*-----------------------------------------------------------------------------*/

static char **BreakInput(char *input)
{	
	char *str = NULL;
	char **command = NULL;
	char **start = NULL;
	int i = 3;

	command = (char**)malloc(3 * sizeof(char*));

	if (NULL == command)
	{
		return (NULL);
	}

	start = command;
	str = strtok(input, " ");
	 
   /* walk through other tokens */
	while (i--)
	{
		*command++ = str;
		str = strtok(NULL, " ");			
	}

	return(start);
}

