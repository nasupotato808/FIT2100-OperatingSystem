/*
 * Author: [Your Name]
 * Student ID: [Your student ID]
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

// Struct to pass arguments to the thread function
typedef struct {
    int thread_id;
    int *array;
    int start_index;
    int chunk_size;
    int *partial_sums;
} thread_args;

// Thread function
void *partial_sum(void *args) {
    thread_args *targs = (thread_args *) args;
    int start = targs->start_index;
    int end = start + targs->chunk_size;
    
    // Compute partial sum for this thread's chunk
    for (int i = start; i < end; i++) {
        // TODO: Compute partial sum
    }

    // TODO: Store partial sum in partial_sums array
    
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <array_size> <num_threads>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int T = atoi(argv[2]);

    if (N % T != 0) {
        printf("Array size must be evenly divisible by number of threads.\n");
        return 1;
    }

    int *array = malloc(N * sizeof(int));
    int *partial_sums = malloc(T * sizeof(int));
    pthread_t threads[T];
    thread_args targs[T];
    
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

    // Wait for threads to finish
    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    // TODO: Compute final sum

    // TODO: Print final sum

    free(array);
    free(partial_sums);

    return 0;
}

