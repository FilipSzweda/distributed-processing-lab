#include <unistd.h>
#include <stdio.h>
#define READ 0
#define WRITE 1
#define WORKERS 10
#define ACCESS 2

int semaphor[2];

void LOCK() {
    int x;
    read(semaphor[READ], &x, sizeof(x));
}

void UNLOCK() {
    int x = 0;
    write(semaphor[WRITE], &x, sizeof(x));
}

void worker(int id, int pipe_k) {
    int x = 0, i, j;
    printf("Worker %d starts\n", id);
    LOCK();

    for(i = 0; i < 7; i++) {
        printf("[%d] ", id);
        fflush(stdout);
        sleep(1);
    }

    UNLOCK();
    printf("Worker %d ends\n", id);
    write(pipe_k, &x, sizeof(x));
}

int main() {
    int pipe_e[2], i, x;
    pipe(pipe_e);
    pipe(semaphor);
    for(int i=0; i< ACCESS; i++) {
        UNLOCK();
    }

    for(i = 0;i < WORKERS; i++) {
    if(!fork()) {
        worker(i, pipe_e[WRITE]);
        return 0;
        }
    }

    for(i = 0; i < WORKERS; i++)
        read(pipe_e[READ], &x, sizeof(x));

    puts("koniec");

}
