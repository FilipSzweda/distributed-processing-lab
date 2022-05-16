#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1
#define TEXT_SIZE 32

int main() {
    int pipe2[2];
    pipe(pipe2);
    if(fork()) {
        // process 3
        close(pipe2[WRITE]);
        size_t textSize = TEXT_SIZE;
        char text[TEXT_SIZE];
        read(pipe2[READ], text, textSize);
        close(pipe2[READ]);
        printf("%s", text);
    }
    else {
        int pipe1[2];
        pipe(pipe1);
        if(fork()) {
            // process 2
            size_t textSize = TEXT_SIZE;
            char text[TEXT_SIZE];
            read(pipe1[READ], text, textSize);
            close(pipe1[READ]);
            for(size_t i = 0; i < textSize; i++) {
                if (text[i] == '\0') break;
                if (text[i] >= 'a' && text[i] <= 'z') text[i] -= 32;
            }
            write(pipe2[WRITE], text, sizeof(text));
            close(pipe2[WRITE]);
        }
        else {
            // process 1
            close(pipe1[READ]);
            size_t textSize = TEXT_SIZE;
            char* text = (char*) malloc(textSize);
            getline(&text, &textSize, stdin);
            write(pipe1[WRITE], text, textSize);
            close(pipe1[WRITE]);
            free(text);
        }
    }
    return 0;
}