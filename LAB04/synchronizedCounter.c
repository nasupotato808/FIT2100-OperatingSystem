# include <stdio.h>
# include <pthread.h>

#define NUM_THREADS 2

// Shared counter
int counter = 0;

// Mutex for synchronizing access to the shared counter
pthread_mutex_t mutex; = PTHREAD_MUTEX_INITIALIZER;

// Function that will be executed by each thread
void* incrementCounter(void *args){
    int localCounter;
    for (int i = 0; i < 1000000; i++){
        // Lock the mutex before accessing the shared variable
        pthread_mutex_lock(&mutex);
        localCounter = counter;
        localCounter++;
        counter = localCounter;
        // Unlock the mutex after accessing the shared variable
        pthread_mutex_unlock(&mutex);
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

    //Destroy the mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}