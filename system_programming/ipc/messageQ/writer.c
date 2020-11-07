#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define QUEUE_PERMISSIONS 0660
#define PROJECT_ID 'M'

struct message 
{
    long message_type;
    char buf [200];
};

int main()
{
    key_t server_queue_key;
    int server_qid;
    struct message my_message;

	/* gets unique key */
    if ((server_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1)
	{
        perror ("ftok");
        exit (1);
    }

	/* gets message queue ID */
    if ((server_qid = msgget (server_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1)
	{
        perror ("msgget: server_qid");
        exit (1);
    }

    my_message.message_type = 1;
    
    strcpy(my_message.buf, "message from writer");

   
    /* send message to server */
    if (-1 == msgsnd(server_qid, &my_message, sizeof(my_message.buf), 0))
	{
        perror ("client: msgsnd");
        exit (1);
    }       
    
    /* remove message queue */
    /*if (msgctl (myqid, IPC_RMID, NULL) == -1)
	{
            perror ("client: msgctl");
            exit (1);
    }*/

    exit(EXIT_SUCCESS);
}
