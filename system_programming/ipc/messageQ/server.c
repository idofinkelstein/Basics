#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_KEY_PATHNAME "/tmp/mqueue_server_key"
#define PROJECT_ID 'M'
#define QUEUE_PERMISSIONS 0660

struct message_text 
{
    int qid;
    char buf [200];
};

struct message 
{
    long message_type;
    struct message_text message_text;
};

int main()
{
    key_t msg_queue_key;
    int qid;
    struct message message;

    if ((msg_queue_key = ftok (SERVER_KEY_PATHNAME, PROJECT_ID)) == -1)
	{
        perror ("ftok");
        exit (1);
    }

    if ((qid = msgget (msg_queue_key, IPC_CREAT | QUEUE_PERMISSIONS)) == -1) 
	{
        perror ("msgget");
        exit (1);
    }

    printf ("Server: Hello, World!\n");

    while (1) 
	{
        char buf [20];
		int length = 0;
		int client_qid = 0;

        /* read an incoming message */
        if (-1 == msgrcv (qid, &message, sizeof (struct message_text), 0, 0)) 
		{
            perror ("msgrcv");
            exit (1);
        }

        printf ("Server: message received.\n");

        /* process message */
        length = strlen(message.message_text.buf);
        sprintf(buf, " %d", length);
        strcat(message.message_text.buf, buf);

        client_qid = message.message_text.qid;
        message.message_text.qid = qid;

        /* send reply message to client */
        if (-1 == msgsnd(client_qid, &message, sizeof (struct message_text), 0)) 
		{  
            perror("msgget");
            exit(EXIT_FAILURE);
        }

        printf ("Server: response sent to client.\n");
    }

	return 0;
}
