//Explanation: This code uses a mutex lock to prevent race conditions when tally is incremented. Both threads will increment the shared tally in a synchronized manner, ensuring that no updates are lost. The final value of tally will be in the range 51 <= tally <= 102 based on how thread execution is interleaved


"""
Part (a): Lower Bound and Upper Bound for Two Instances of total()
Problem Statement: Two instances of total() run concurrently, each attempting to increment the shared variable tally. You are asked to determine the range of final values for tally, considering the potential for race conditions.

Key Assumptions:

The processes can execute at any relative speed.
Each increment involves loading tally into a register, incrementing the value, and then storing it back into memory. This means that increments may overlap, causing some increments to be "lost."
Race Condition Explanation: Without synchronization, both instances of total() can read the same value of tally, increment it, and write the same incremented value back. As a result, some increments may be lost. This leads to a lower bound where the processes interfere maximally, and an upper bound where the processes work without interference.

Lower Bound: In the worst-case scenario, both processes might read the same value of tally, increment it, and then store the same result. In this case, only one effective increment will happen for each iteration of total(). Since each total() function runs for n + 1 iterations (i.e., 51 iterations), the lower bound is that only one of the processes effectively increments tally, resulting in a final value of tally = n + 1 (51).

Upper Bound: In the best-case scenario (no race conditions), both processes can successfully increment tally for all their iterations. Each process would increment tally 51 times (once for each iteration of total()), resulting in a final tally of tally = 2 * (n + 1) (102).

Thus, the final value of tally will be between 51 and 102, depending on how much the race condition interferes with concurrent increments.

Part (b): Arbitrary Number of Processes (N Instances of total())
Now, you are asked to consider the scenario where N processes are concurrently running total() and determining how the range of tally's final values will change.

Lower Bound: In the worst-case scenario, all N processes can read the same value of tally, increment it, and store the same value back. Effectively, this would result in only one increment per iteration across all processes. The lower bound, therefore, remains as in part (a): tally = n + 1 (51). This is because, in the worst case, the race conditions would cause all processes to overlap, leading to no additional increments.

Upper Bound: In the best-case scenario, all N processes can increment tally without interference. Each process increments tally 51 times, so the upper bound will now be:

Upper bound=𝑁×(𝑛+1)=𝑁×51
Upper bound=N×(n+1)=N×51
Thus, as N increases, the upper bound increases proportionally. The final value of tally can be between 51 and N \times 51, depending on the level of interference.

Summary of Results
Part (a) - Two Instances of total():

Lower bound: tally = n + 1 = 51 (worst case, maximum race condition interference).
Upper bound: tally = 2 \times (n + 1) = 102 (best case, no interference).
Part (b) - N Instances of total():

Lower bound: tally = n + 1 = 51 (worst case, all processes interfere).
Upper bound: tally = N \times (n + 1) = N \times 51 (best case, no interference between processes).
"""

#include <pthread.h>
#include <stdio.h>

const int n = 50;
int tally = 0;
pthread_mutex_t lock;

void* total(void* arg) {
    int count;
    for (count = 1; count <= n; count++) {
        pthread_mutex_lock(&lock);
        tally++;
        pthread_mutex_unlock(&lock);
    }
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&lock, NULL);
    
    pthread_create(&thread1, NULL, total, NULL);
    pthread_create(&thread2, NULL, total, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final tally: %d\n", tally);

    pthread_mutex_destroy(&lock);

    return 0;
}
