#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Shared account balance variable
int account_balance = 0;

// Mutex for synchronizing access to the account balance
pthread_mutex_t balance_mutex;

// Struct for thread arguments
typedef struct {
    int deposit_amount;
    int num_deposits;
} ThreadArgs;

// Function to be executed by each thread
void *deposit_money(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    int deposit_amount = thread_args->deposit_amount;
    int num_deposits = thread_args->num_deposits;

    // TODO: Lock the mutex
    // ...

    // TODO: Deposit the specified amount into the account balance
    // ...

    // TODO: Unlock the mutex
    // ...

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s num_atms\n", argv[0]);
        return 1;
    }

    int num_atms = atoi(argv[1]);

    pthread_t atms[num_atms];
    ThreadArgs thread_args[num_atms];

    // TODO: Initialize the mutex
    // ...

    // Create the ATMs (threads)
    for (int i = 0; i < num_atms; i++) {
        printf("Enter the deposit amount and the number of deposits for ATM %d (e.g. 10 1000): ", i);
        scanf("%d %d", &thread_args[i].deposit_amount, &thread_args[i].num_deposits);
        // TODO: Create the thread
        // ...
    }

    // Wait for all ATMs to finish
    for (int i = 0; i < num_atms; i++) {
        // TODO: Wait for the thread to finish
        // ...
    }

    // Print the final account balance
    printf("Final account balance: %d\n", account_balance);

    // TODO: Destroy the mutex
    // ...

    return 0;
}
