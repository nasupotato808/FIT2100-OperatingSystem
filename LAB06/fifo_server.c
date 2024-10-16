/* fifo_server.c */

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

  //The server removes any existing FIFO with the same name using unlink().
  // Remove any previous FIFO.
  unlink(FIFONAME);

  //It creates a new FIFO named "myfifo" with permissions 0666 using mkfifo().
  // Create the FIFO.
  if (mkfifo(FIFONAME, 0666) < 0)
  {
    perror("server: mkfifo");
    exit(1);
  }

  //The server opens the FIFO for reading using open() with O_RDONLY flag
  // Open the FIFO for reading.
  if ((fd = open(FIFONAME, O_RDONLY)) < 0)
  {
    perror("server: open");
    exit(1);
  }
  // It enters a loop where it reads data from the FIFO into a buffer using read().
  // Read from the FIFO until end-of-file and
  // print what we get on the standard input.
  while ((n = read(fd, buffer, sizeof(buffer))) > 0)
  {
    // The read data is then written to standard output (file descriptor 1) using write().
    write(1, buffer, n);
  }
  //This loop continues until end-of-file is reached (when all clients close their write end).
  //Finally, the server closes the FIFO and exits.
  close(fd);
  exit(0);
}

//The server creates and manages the FIFO.
//It only reads from the FIFO, expecting clients to write to it.
//The server will block on open() until a client opens the FIFO for writing.