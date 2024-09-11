/*
* Unit: FIT2100 Operating Systems
* Description: A C program to demonstrate race conditions in multithreaded programs.
* The program creates two threads, each of which increments a shared counter
* one million times. Due to the lack of synchronization, the final value of the
* counter is unpredictable and usually less than two million.
* Compile and run:
    gcc -o raceCondition raceCondition.c -lpthread
    ./raceCondition
* to see mutual exclusion version using mutex -? synchronizedCounter.c
*/

# include <stdio.h>
# include <pthread.h>

#define NUM_THREADS 2

// Shared counter
int counter = 0;

// Function that will be executed by each thread
void* incrementCounter(void *args){
    int localCounter;
    for (int i = 0; i < 1000000; i++){
        localCounter = counter;
        localCounter++;
        counter = localCounter;
    }
    return NULL;
}

int main(){
    pthread_t threads[NUM_THREADS];
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++){
        rc = pthread_create(&threads[i], NULL, incrementCounter, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);
    return 0;
}