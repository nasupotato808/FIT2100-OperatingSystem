/* socket_server.c */
/*
* gcc -o socket_server socket_server.c
gcc -o socket_client socket_client.c
*/
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
  char buffer[1024];
  int n, sock, nsock, len;
  struct sockaddr_un name;

  /**********************************************************
  * YOUR TASK:                                              *
  * Create a new socket.                                    *
  **********************************************************/
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("server: socket");
    exit(1);
  }

  // Create the address of the server.
  memset(&name, 0, sizeof(struct sockaddr_un));
  name.sun_family = AF_UNIX;
  strcpy(name.sun_path, SOCKETNAME);
  len = sizeof(name.sun_family) + strlen(name.sun_path);

  // Remove any previous socket.
  unlink(name.sun_path);

  // Bind the socket to the address.
  if (bind(sock, (struct sockaddr *)&name, SUN_LEN(&name)) < 0)
  {
    perror("server: bind");
    exit(1);
  }

  // Listen for connections.
  if (listen(sock, 5) < 0)
  {
    perror("server: listen");
    exit(1);
  }

  // Accept a connection.
  if ((nsock = accept(sock, (struct sockaddr *)&name, &len)) < 0)
  {
    perror("server: accept");
    exit(1);
  }

  /**********************************************************
  * YOUR TASK:                                              *
  * Read from the new socket until end-of-file and          *
  * print all the data received on the standard output.     *
  **********************************************************/
// Read from the new socket until end-of-file and print all data received
  while ((n = read(nsock, buffer, sizeof(buffer))) > 0) {
    if (write(STDOUT_FILENO, buffer, n) < 0) {
      perror("server: write");
      exit(1);
    }
  }

  if (n < 0) {
    perror("server: read");
    exit(1);
  }
	/*nsock is the file descriptor for the new socket created by the accept() call.*/
	/*This socket represents the specific connection with a client.
Closing this socket signifies the end of communication with that particular client.
It releases the resources associated with this connection.
If you don't close this socket, you might leak file descriptors, potentially leading to resource exhaustion if the server runs for a long time and handles many connections.*/
  close(nsock);
 /*
 sock is the file descriptor for the original socket created by the socket() call.
This is the listening socket that the server uses to accept new connections.
Closing this socket signifies that the server is no longer accepting new connections.
It's good practice to close this when you're done with the server, as it releases the system resources associated with the socket.
In this case, since the program is about to exit, the operating system would close this socket anyway, but explicitly closing it is a good habit for more complex programs where you might want to stop listening but keep the program running.
 */
  close(sock);
  exit(0);
}
