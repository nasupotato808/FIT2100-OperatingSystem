/* msq_server.c */
/* FIT2100 Lab 6 - Task 1*/
/**************************************** 
gcc -o msq_server msq_server.c
gcc -o msq_client msq_client.c
Run the server program in one terminal：
./msq_server
Run the client program in another terminal:
./msq_client

Type messages in the client terminal. They will be sent to the server and displayed in the server terminal.

Press Ctrl+D in the client terminal to end input and send the "no more data" message.
******************************************/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSQKEY 34858
#define MSQSIZE 32

struct msgbuf
{
  long mtype;
  char mtext[MSQSIZE];
};

int main(int argc, char *argv[])
{
  key_t key;
  int n, msqid;
  struct msgbuf mbuf;

  key = MSQKEY;

  /************************************************************************ 
  * YOUR TASK:                                                            *
  * Create a new message queue.                                           *
  * Assume that the key defined in MSQKEY isn't in use by another process.*
  ************************************************************************/
 // Create a new message queue
 // 666 is the permission for the message queue, which allows the owner,  group, and others to read and write to the message queue.
 // IPC_CREAT is a flag that tells the system to create a new message queue if it doesn't already exist.
  if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0)
  {
    // Print an error message and exit if the message queue can't be created.
    perror("server: msgget");
    exit(1);
  }
  /*
  * Receive messages from the queue. 
  * Messages of type 1 are to be printed on the standard output; 
  * a message of type 2 indicates that no more data.
  */
  while ((n = msgrcv(msqid, &mbuf, MSQSIZE, 0, 0)) > 0)
  {
    /************************************************************************ 
    * YOUR TASK:                                                            *
    * Write messages of type 1 to standard output.                          *
    ************************************************************************/
   
    if (mbuf.mtype == 1)
    {
      printf("Received: %s", mbuf.mtext);
    }
    if (mbuf.mtype == 2)
    {
      // Remove the message queue from the system.
      if (msgctl(msqid, IPC_RMID, (struct msqid_ds *)0) < 0)
      {
        perror("server: msgctl");
        exit(1);
      }
    }
  }

  // Check for errors.
  if (n<0)
  {
    perror("server: msgrcv");
    exit(1);
  }

  exit(0);
}
