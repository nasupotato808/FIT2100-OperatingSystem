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
  // Get a message queue, 666 is the permission for the message queue, which allows the owner, group, and others to read and write to the message queue.
  if ((msqid = msgget(key, 0666)) < 0)
  {
    perror("client: msgget");
    exit(1);
  }

  /**************************************************************************************
  * YOUR TASK:                                                                          *
  * Continuously read data from standard input and send the data as messages of type 1. *
  ***************************************************************************************/
  while (fgets(input, MSQSIZE, stdin) != NULL) {
    // Remove newline character
    size_t len = strlen(input);
    if (len > 0 && input[len-1] == '\n') {
      input[len-1] = '\0';
      len--;
    }

    if (strcmp(input, "exit") == 0) {
      printf("Exiting the program.\n");
      break;
    }

    if (len == 0) {
      // Empty line, send as type 2 message
      mbuf.mtype = 2;
      strcpy(mbuf.mtext, "Empty line");
    } else {
      // Non-empty line, send as type 1 message
      mbuf.mtype = 1;
      strncpy(mbuf.mtext, input, MSQSIZE);
    }

    if (msgsnd(msqid, &mbuf, strlen(mbuf.mtext) + 1, 0) < 0) {
      perror("client: msgsnd");
      exit(1);
    }

    printf("Sent message: Type %ld, Content: %s\n", mbuf.mtype, mbuf.mtext);
  }


  /**************************************************************************************
  * YOUR TASK:                                                                          *
  * When an empty message is read, send a message of type 2 to indicate no more data.   *
  ***************************************************************************************/
  mbuf.mtype = 2;
  strcpy(mbuf.mtext, "End of communication");
  if (msgsnd(msqid, &mbuf, strlen(mbuf.mtext) + 1, 0) < 0) {
    perror("client: msgsnd");
    exit(1);
  }
  printf("Sent final message: Type 2, Content: End of communication\n");

  printf("Client finished.\n");
  exit(0);
}