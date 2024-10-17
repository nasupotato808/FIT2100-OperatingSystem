/* socket_client.c */
/* FIT2100 Lab 6 - Task 2*/
/************************** 
* gcc -o socket_client socket_client.c
****************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SOCKETNAME "mynewsocket"

int main(int argc, char *argv[])
{
  // Create a buffer to store the data read from standard input.
  char buffer[1024];
  int n, sock, len;
  struct sockaddr_un name;

  /******************************************************************************
  * YOUR TASK:                                                                  *
  * Create a new socket.                                                        *
  ******************************************************************************/
 // AF_UNIX is the address family for Unix domain sockets, SOCK_STREAM is the type of socket, and 0 is the protocol.
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("client: socket");
    exit(1);
  }

  // Create the address of the server.
  memset(&name, 0, sizeof(struct sockaddr_un));
  name.sun_family = AF_UNIX;
  strcpy(name.sun_path, SOCKETNAME);
  // Calculate the length of the address.
  len = sizeof(name.sun_family) + strlen(name.sun_path);

  // Connect to the server.
  if (connect(sock, (struct sockaddr *)&name, SUN_LEN(&name)) < 0)
  {
    perror("client: connect");
    exit(1);
  }

  /******************************************************************************
  * YOUR TASK:                                                                  *
  * Continuously read data from standard input and send the data to the socket. *
  ******************************************************************************/
  if((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
    if (write(sock, buffer, n) < 0) {
      perror("client: write");
      exit(1);
    }
  }

  // Check for read errors.
  if (n < 0) {
    perror("client: read");
    exit(1);
  }
  
  // Close the socket.
  close(sock);
  exit(0);
}
