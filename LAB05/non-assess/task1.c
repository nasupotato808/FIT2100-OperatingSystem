#include <pthread.h>
#include <stdio.h>
//Explanation: The two threads run concurrently. Depending on how the CPU schedules them, the interleaving may cause one thread to decrement x and another to increment it, allowing the print condition x == 10 to be satisfied.
int x = 10;  // Shared variable

void* P1(void* arg) {
    while (1) {
        x = x - 1;
        x = x + 1;
        if (x == 10) {
            printf("x is %d\n", x);
        }
    }
}

void* P2(void* arg) {
    while (1) {
        x = x - 1;
        x = x + 1;
        if (x == 10) {
            printf("x is %d\n", x);
        }
    }
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, P1, NULL);
    pthread_create(&thread2, NULL, P2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
