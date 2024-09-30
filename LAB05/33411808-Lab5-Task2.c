// Lab5-Task2.c
// gcc -o Task2 33411808-Lab5-Task2.c -lpthread
//Result:
// Thread 1 finished. Counter = 1918679
// Thread 0 finished. Counter = 2000000
// Final value of counter: 2000000
//  the final value of counter always being exactly 2,000,000.
#include <stdio.h>
#include <pthread.h>

#define NUM_ITERATIONS 1000000
#define NUM_THREADS 2

// Shared counter variable
int counter = 0;
// Global mutex variable
pthread_mutex_t mutex;


// Function to be executed by each thread
void *updateCounter(void *args) {
    int id = *(int *)args;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // lock the mutex
        pthread_mutex_lock(&mutex);
        int temp = counter;
        temp = temp + 1;
        counter = temp;
        // unlock the mutex
        pthread_mutex_unlock(&mutex);
    }
    printf("Thread %d finished. Counter = %d\n", id, counter);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Initialise the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, updateCounter, &thread_ids[i]);
    }
    
    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Print the final value of the counter
    printf("Final value of counter: %d\n", counter);
    
    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

