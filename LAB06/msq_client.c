/* msq_client.c */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
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
  char input[MSQSIZE];

  // Get a message queue. The server must have created it.
  key = MSQKEY;
  if ((msqid = msgget(key, 0666)) < 0)
  {
    perror("client: msgget");
    exit(1);
  }

  /**************************************************************************************
  * YOUR TASK:                                                                          *
  * Continuously read data from standard input and send the data as messages of type 1. *
  ***************************************************************************************/
  while (fgets(input, MSQSIZE, stdin) != NULL)
  {
    mbuf.mtype = 1;
    strncpy(mbuf.mtext, input, MSQSIZE);
    
    if (msgsnd(msqid, &mbuf, strlen(mbuf.mtext) + 1, 0) < 0)
    {
      perror("client: msgsnd");
      exit(1);
    }
  }
  /**************************************************************************************
  * YOUR TASK:                                                                          *
  * When an empty message is read, send a message of type 2 to indicate no more data.   *
  ***************************************************************************************/
    // Send a message of type 2 to indicate no more data
  mbuf.mtype = 2;
  strcpy(mbuf.mtext, "No more data");
  
  if (msgsnd(msqid, &mbuf, strlen(mbuf.mtext) + 1, 0) < 0)
  {
    perror("client: msgsnd");
    exit(1);
  }
  exit(0);
}
