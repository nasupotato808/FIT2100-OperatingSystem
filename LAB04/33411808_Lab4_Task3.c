/*
 * Author: Wong Jia Xuan
 * Student ID: [33411808
 * Unit: FIT2100 Operating Systems
 * Description: This program demonstrates the use of threads for concurrent processing by dividing an array of integers into chunks, 
 * each processed by a separate thread to compute a partial sum, and then combining the partial sums to get the final sum.
 * The array size and number of threads are specified as command-line arguments. 
 * Each thread computes the sum of its chunk of the array and stores the result in a shared array of partial sums. 
 * The main thread then computes the final sum by adding up the partial sums.
 *
 * Compiling: gcc -o sum sum.c -lpthread
 * Running: ./sum <array_size> <num_threads>
 * Example: ./sum 1000 4
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Struct to pass arguments to the thread function
typedef struct {
    int thread_id; // the ID of the thread
    int *array;     // A pointer to the shared array of integers
    int start_index; // the index in the array where this thread should start processing
    int chunk_size; // the bumber of elements this thread should process
    int *partial_sums;  // A shared array where the partial sum from each thread will be stored
	pthread_mutex_t *mutex;
} thread_args;

// Thread function
void *partial_sum(void *args) {
    thread_args *targs = (thread_args *) args;
    int start = targs->start_index;
    int end = start + targs->chunk_size;
    int sum = 0;
    
    // Compute partial sum for this thread's chunk
    for (int i = start; i < end; i++) {
        // TODO: Compute partial sum
        sum += targs->array[i];
    }

	// lock the mutex before modifying the shared resource
	pthread_mutex_lock(targs->mutex);

    // TODO: Store partial sum in partial_sums array
    targs->partial_sums[targs->thread_id] = sum;
    
	// unlock the mutex after modification
	pthread_mutex_unlock(targs->mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <array_size> <num_threads>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);  // Array size
    int T = atoi(argv[2]);  // Number of threads

    if (N % T != 0) {
        printf("Array size must be evenly divisible by number of threads.\n");
        return 1;
    }

    int *array = malloc(N * sizeof(int));
    int *partial_sums = malloc(T * sizeof(int));
    pthread_t threads[T];
    thread_args targs[T];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    // Initialize array with random integers
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        array[i] = rand() % 100;
    }

    // Create threads
    for (int i = 0; i < T; i++) {
        targs[i].thread_id = i;
        targs[i].array = array;
        targs[i].start_index = i * (N / T);
        targs[i].chunk_size = N / T;
        targs[i].partial_sums = partial_sums;
        pthread_create(&threads[i], NULL, partial_sum, &targs[i]);
    }
	// wait for threads to finish
    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    // TODO: Compute final sum
    int final_sum = 0;
    for (int i = 0; i < T; i++) {
        final_sum += partial_sums[i];
    }
    

    // TODO: Print final sum
    printf("Final sum: %d\n", final_sum);

	// clean up
	pthread_mutex_destroy(&mutex);
    free(array);
    free(partial_sums);

    return 0;
}

