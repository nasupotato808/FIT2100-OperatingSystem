#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For usleep
// Global variables: Protected by a mutex. Removing (pthread_mutex_lock)
// and (pthread_mutex_unlock) may cause inconsistent results.
int global_sum = 0; // Shared global variable
pthread_mutex_t lock; 
void* thread_func(void* arg) {
    int local_sum = *(int*)arg; // Local variable (thread-specific)
    // Loop to repeatedly modify the global sum to increase race condition chances
    for (int i = 0; i < 100000; i++) {
        // Introduce a small sleep to simulate thread interleaving
        usleep(1); // 1 microsecond sleep
        // Without the mutex, this is prone to race conditions
        pthread_mutex_lock(&lock);
        global_sum += 1;  // Increment shared global variable
        pthread_mutex_unlock(&lock);
        // with mutex, the global sum is 200000(100000inrements by each thread)
        // without mutex, the final sum less than 200000
    }
    return NULL;
}
// Race condition: Both threads increment global_sum 100,000 times each.
// The correct sum should be 200,000, but the final sum may be less due to lost increments.
int main() {
    pthread_t t1, t2;
    int val1 = 10, val2 = 20;
    // Create two threads that both update global_sum
    pthread_create(&t1, NULL, thread_func, &val1);
    pthread_create(&t2, NULL, thread_func, &val2);
    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    // Print the final global sum (should be incorrect due to race conditions)
    printf("Global sum: %d\n", global_sum);
    return 0;
}
