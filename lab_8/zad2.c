#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1
#define TEXT_SIZE 32

int main() {
    mkfifo("fifo1", S_IRWXU);
    mkfifo("fifo2", S_IRWXU); 
    if(fork()) {
        // process 3
        size_t textSize = TEXT_SIZE;
        char text[TEXT_SIZE];
        int f2 = open("fifo2", O_RDONLY);
        read(f2, text, textSize);
        close(f2);
        printf("%s", text);
    }
    else {
        int pipe1[2];
        pipe(pipe1);
        if(fork()) {
            // process 2
            size_t textSize = TEXT_SIZE;
            char text[TEXT_SIZE];
            int f = open("fifo1", O_RDONLY); 
            read(f, text, textSize);
            close(f);
            for(size_t i = 0; i < textSize; i++) {
                if (text[i] == '\0') break;
                if (text[i] >= 'a' && text[i] <= 'z') text[i] -= 32;
            }
            int f2 = open("fifo2", O_WRONLY);
            write(f2, text, sizeof(text));
            close(f2);
        }
        else {
            // process 1
            size_t textSize = TEXT_SIZE;
            char* text = (char*) malloc(textSize);
            getline(&text, &textSize, stdin);
            int f = open("fifo1", O_WRONLY);
            write(f, text, textSize);
            close(f);
            free(text);
        }
    }
    unlink("fifo1");
    unlink("fifo2"); 
    return 0;
}