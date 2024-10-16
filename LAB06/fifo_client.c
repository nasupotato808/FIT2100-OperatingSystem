/* fifo_client.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFONAME "myfifo"

int main(int argc, char *argv[])
{
  int n, fd;
  char buffer[1024];

  // Open the FIFO for writing. It was created by the server.
  if ((fd = open(FIFONAME, O_WRONLY)) < 0)
  {
    perror("client: open");
    exit(1);
  }

  /*
  * YOUR TASK:
  * Read from the standard input, and copy the data to the FIFO.
  */
 /* We use a while loop to continuously read from standard input (STDIN_FILENO) into the buffer.*/
  /* The read() function returns the number of bytes read, which we store in n.*/
  /* If n > 0, we write the contents of the buffer to the FIFO using write().*/
  while ((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
  /* continue this process until we reach the end of the input (when read() returns 0) or an error occurs.*/
  {
    if (write(fd, buffer, n) < 0)
    {
      perror("client: write");
      exit(1);
    }
  }
 /*After the loop, we check if n < 0, which would indicate a read error.*/
  if (n < 0)
  {
    perror("client: read");
    exit(1);
  }

  close(fd);
  exit(0);
}
