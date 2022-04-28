#include <stdio.h>
#include <pthread.h>
#include <mutex>

#define INTERVAL_END 100
#define NUMBERS_COUNT (INTERVAL_END - 1)
#define THREADS_COUNT 4

int numbers[NUMBERS_COUNT] = {};
std::mutex mtx;

struct args {
    int startIndex;
    int endIndex;
};

void *eratosthenes_sieve(void *arguments) {
    struct args interval = (struct args*) arguments;
    for(int i = interval.startIndex; i <= interval.endIndex; i++) {
        int number = numbers[i];
    }
}

int main() {
    for(int i = 2; i <= INTERVAL_END; i++) {
        numbers[i - 2] = i;
    }

    pthread_t threads[THREADS_COUNT];

    for(int i = 0; i < THREADS_COUNT; i++) {
        // tutaj podać przedział w args do pthread_create
        // za 10 pkt. uzywac mutexa do wpisywania do tablicy (tablica wspolna)
        int startIndex = i * NUMBERS_COUNT / 2;
        int endIndex = (i + 1) * NUMBERS_COUNT / 2;
        struct args interval {startIndex, endIndex};
        pthread_create(&threads[i], NULL, eratosthenes_sieve, (void*)&interval);
    }

    for(int i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}