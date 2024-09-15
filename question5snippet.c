#include <pthread.h>
#include <stdio.h>

int global_sum = 0; // Shared global variable
pthread_mutex_t lock; 

void* thread_func(void* arg) {
    int local_sum = *(int*)arg; // Local variable (thread-specific)
    pthread_mutex_lock(&lock);
    global_sum += local_sum; // Access shared global variable
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int val1 = 10, val2 = 20;
    pthread_mutex_init(&lock, NULL);
    
    pthread_create(&t1, NULL, thread_func, &val1);
    pthread_create(&t2, NULL, thread_func, &val2);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Global sum: %d\n", global_sum); // Shared result
    pthread_mutex_destroy(&lock);
    return 0;
}
