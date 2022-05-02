#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define INTERVAL_END 100
#define NUMBERS_COUNT (INTERVAL_END - 1)
#define THREADS_COUNT 4

int numbers[NUMBERS_COUNT] = {};
int primes[NUMBERS_COUNT] = {};
int curr_p = 0;
pthread_mutex_t mtx;

struct args {
    int startIndex;
    int endIndex;
};

int remove_element(int*from, int total, int index) {
    if((total - index - 1) > 0) {
        memmove(from + index, from + index + 1, sizeof(int) * (total - index - 1));
    }
    return total - 1;
}

void *eratosthenes_sieve(void *arguments) {
    struct args* interval = (struct args*) arguments;
    for(int i = interval->startIndex; i < interval->endIndex; i++) {
        if(numbers[i] != INTERVAL_END + 1) {
            pthread_mutex_lock(&mtx);
            primes[curr_p] = numbers[i];
            curr_p += 1;
            pthread_mutex_unlock(&mtx);
        }
        for(int j = 0; j < NUMBERS_COUNT; j++) {
            if (numbers[j] != numbers[i] && numbers[j] % numbers[i] == 0) {
                for(int k = 0; k < curr_p; k++) {
                    if(primes[k] == numbers[j]) {
                        curr_p = remove_element(primes, curr_p, k);
                    }
                }
                numbers[j] = INTERVAL_END + 1;
            }
        }
    }
}

int main() {
    for(int i = 2; i <= INTERVAL_END; i++) {
        numbers[i - 2] = i;
    }

    pthread_t threads[THREADS_COUNT];
    struct args* intervals = (struct args*)malloc(THREADS_COUNT * sizeof(struct args));

    for(int i = 0; i < THREADS_COUNT; i++) {
        int startIndex = i * NUMBERS_COUNT / THREADS_COUNT;
        int endIndex = (i + 1) * NUMBERS_COUNT / THREADS_COUNT;
        intervals[i].startIndex = startIndex;
        intervals[i].endIndex = endIndex;
        pthread_create(&threads[i], NULL, eratosthenes_sieve, (void*)&intervals[i]);
    }

    for(int i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    free(intervals);

    printf("curr_p: %i\n", curr_p);
    for(int i = 0; i < NUMBERS_COUNT; i++) {
        if(numbers[i] != INTERVAL_END + 1) {
            printf("%i, ", numbers[i]);
        }
    }
    printf("\n");

    return 0;
}