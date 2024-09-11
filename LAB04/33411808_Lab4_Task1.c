/* Lab 4 Task 1 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: %s <date_format> <filename>\n", argv[0]);
		exit(1);
	}

	pid_t pid = fork(); // Create a new process
	
	if ((pid < 0) {
		perror("Fork failed");
		exit(1);
	} else if (pid == 0){
		//In the child process
		// execute the "date" command with format string
		execlp("date", "date", "+%s", argv[1], NULL);
		// If execlp fails
		perror("Execlp date command failed");
		exit(1);
	} else {
		// In the parent process
		// Wait for the child to finish
		int status;
		waitpid(pid, &status, 0);

		// Execute the "cat" command to display contents of a file
		execlp("cat", "cat", argv[2], NULL);
		// If execlp failed
		perror("Execlp command failed")
		exit(1);
	}

	return 0;
}
