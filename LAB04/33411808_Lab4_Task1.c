/* Lab 4 Task 1 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	pid_t pid;

	pid = fork(); // Create a new process
	
	if ((pid < 0) {
		perror("Fork failed");
		exit(1);
	} else if (pid == 0){
		//In the child process
		// execute the "date" command with format string
		execlp("date","date", "+%Y-%m-%d %H:%M:%S", NULL);
		// If execlp fails
		perror("Execlp date failed");
		exit(1);
	} else {
		// In the parent process
		// Wait for the child to finish
		wait(&status);

		// Execute the "cat" command to display contents of a file
		execlp("cat", "cat", "sample.txt", NULL);
		// If execlp failed
		perror("Execlp cat failed")
		exit(1);
	}

	return 0;
}
