/* Lab 4 Task 1 */
/*
* To compile the code: gcc -o task1 33411808_Lab4_Task1.c 
* To run the code: ./task1 <date_format> <filename>
* Example: ./task1 "+%Y-%m-%d" task1.txt
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: %s <date_format> <filename>\n", argv[0]);
		exit(1);
	}

	pid_t pid = fork(); // Create a new process
	
	if (pid < 0) {
		perror("Fork failed");
		exit(1);

	} else if (pid == 0){
		//In the child process
		// execute the "date" command with format string
		execlp("date", "date", argv[1], NULL);
		// If execlp fails
		perror("Execlp date command failed");
		exit(1);

	} else {
		// In the parent process
		// Wait for the child to finish
		int status;
		waitpid(pid, &status, 0);
		
		// Ensure the file exists and is rewritten
		FILE *file = fopen(argv[2], "w");
		if (file == NULL) {
			perror("Failed to create or open file");
			exit(1);
		}
		// Write some content to the file
		fprintf(file, "This is a placeholder content.\n");
		fclose(file);

		// Execute the "cat" command to display contents of a file
		execlp("cat", "cat", argv[2], NULL);
		// If execlp failed
		perror("Execlp command failed");
		exit(1);
	}

	return 0;
}
