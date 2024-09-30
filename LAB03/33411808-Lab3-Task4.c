#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to calculate the factorial of a given number
int factorial(int n) {
    // TODO: Implement the factorial function
	// Recursive
	if (n == 0 || n == 1) return 1; // input 0 or 1, return 1
	return n * factorial(n - 1);
}

int main() {
    int N, i;
    printf("Enter the number of child processes to create: ");
    scanf("%d", &N);

    for (i = 0; i < N; i++) {
		// multiple processes
        pid_t pid = fork();

		// Error handling for fork()
        if (pid < 0) {
            // Fork failed
			perror("Fork failed");
            printf("Fork failed for child %d\n", i);
            exit(1);
        } else if (pid == 0) {
            // Child process
            printf("Child process with PID: %d and Parent PID: %d\n", getpid(), getppid());
            
            int result = factorial(i + 1); // Example calculation input
            // TODO: Print the result
			// Child calculates the factorial of i+1, helps track which child is being created and its PID
            printf("Child %d calculated %d!= %d\n", i + 1, i + 1, result);
            exit(0); // Child process ends
        } else {
            // Parent process
            // TODO: Print appropriate message indicating the creation of a child process
        	printf("Created child process %d with PID: %d\n", i + 1, pid);
		}
    }

    // TODO: Write a loop to wait for all child processes
	// ensures parent waits for all child processes to complete before exiting
	// process synchronization
	for (i = 0; i < N; i++){
		pid_t terminated_pid = wait(NULL);
		if (terminated_pid == -1){
			perror("Wait failed");
			exit(1);
		}
		// I/O operations, by removing this printf, the parent process creates child processes faster
		// without pausing for I/O
		// Gives child processes more opportunity
		printf("Child process with PID %d has terminated\n", terminated_pid);
	}

    printf("All children have terminated. Parent process exiting.\n");
    return 0;
}
