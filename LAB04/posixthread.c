/* hreads_test.c in lecture*/
// run with gcc -o posixthread posixthread.c -lpthread
# include <pthread.h>
# include <stdio.h>

// Define the number of threads
# define NUM_THREADS 4

// Structure to pass data to threads
typedef struct {
    int start; // start number of sum
    int end; // end number of sum
    int sum; // variable to store result
} thread_data;

// Thread function to sum numbers
void* SumNumbers(void* arg) {
    thread_data* data = (thread_data*) arg; //Cast argument to thread_data type
    int start = data -> start;
    int end = data -> end;

    // Sum numbers from start to end
    for (int i = start; i <= end; i++) {
        sum += i;
    }
    data -> sum = sum; // stpre result in sum variable of thread_data
    pthread_exit(NULL); // Exit thread
}

int main(int argc, char* argv[]) {
    int N;
    pthread_t threads[NUM_THREADS]; // Array to store thread IDs
    thread_data threadData[NUM_THREADS]; // Array to store thread data
    int sum = 0; // Variable to store final result

    // Get user input for N
    printf("Enter a value for N: ");
    scanf("%d", &N);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].start = i * (N / NUM_THREADS) + 1; // Determine start number for thread
        threadData[i].end = (i + 1) * (N / NUM_THREADS); // Determine end number for thread
        int rc = pthread_create(&threads[i], NULL, SumNumbers, (void*) &threadData[i]); // Create thread
        if (rc) {
            printf("ERROR: return code from pthread create() is %d\n", rc);
            return -1;
        }
    }

    // Handle remaining number s if N is not divisible by 4
    for (int i = NUM_THREADS * (N / NUM_THREADS) + 1; i <= N; i++) {
        sum += i;
    }

    // Join threads and sum the results
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Wait for thread to finish
        sum += threadData[i].sum;   // Add result from thread to final sum
    }

    printf("Total sum = %d\n", sum); // Print final sum
    pthread_exit(NULL); // Exit main thread
    return 0;
}