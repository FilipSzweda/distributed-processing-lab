#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define INTERVAL_END 100
#define NUMBERS_COUNT (INTERVAL_END - 1)
#define THREADS_COUNT 4

int numbers[NUMBERS_COUNT] = {};

pthread_mutex_t mtx;

struct args {
    int startIndex;
    int endIndex;
};

void *eratosthenes_sieve(void *arguments) {
    struct args* interval = (struct args*) arguments;
    for(int i = interval->startIndex; i < interval->endIndex; i++) {
        for(int j = 0; j < NUMBERS_COUNT; j++) {
            pthread_mutex_lock(&mtx);
            if (numbers[j] != numbers[i] && numbers[j] % numbers[i] == 0) {
                numbers[j] = INTERVAL_END + 1;
            }
            pthread_mutex_unlock(&mtx);
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

    for(int i = 0; i < NUMBERS_COUNT; i++) {
        if(numbers[i] != INTERVAL_END + 1) {
            printf("%i, ", numbers[i]);
        }
    }

    return 0;
}