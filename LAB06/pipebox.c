/* pipebox.c */
// hello
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  pid_t pid;
  int pipefd[2];
  int status;

  // Create a pipe.
  if (pipe(pipefd) < 0)
  {
    perror("pipe");
    exit(1);
  }

  // Create a child process.
  if ((pid = fork()) < 0)
  {
    perror("fork");
    exit(1);
  }

  // The child process executes the command "xmessage -file -".
  // This command reads text from stdin (until end of file or Ctrl-D)
  // and then displays a popup window on the screen.
  if (pid == 0)
  {
    // Re-map file descriptor 0 (standard input)
    // to refer to the pipe resource.
    dup2(pipefd[0], 0); // redicrects its standard input to read end of the pipe using dup2()
    close(pipefd[1]);

    execl("/usr/bin/xmessage", "xmessage", "-file", "-", NULL);// execl() executes xmesssage command
    perror("exec");
    exit(127);
  }

  /* Parent process sends the messsage to the child through a pipe.*/

  // The parent process is not reading from the pipe.
  // pipefd[0] for reading
  close(pipefd[0]);

  // Write a message to the pipe.
  // pipefd[1] for writing
  write(pipefd[1], "Greetings.\n\n", 12);
  write(pipefd[1], "This is your program saying hello.\n", 35);
  write(pipefd[1], "Hope you enjoy this week's prac.\n\n", 34);

  // Close the pipe and wait for the child to exit.
  close(pipefd[1]);
  waitpid(pid, &status, 0);

  exit(0);
}
