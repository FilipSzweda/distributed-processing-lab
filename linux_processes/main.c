#include <unistd.h>
#include <stdio.h>

int main() {
    char *const libPath[2] = {"LD_LIBRARY_PATH=.", NULL};
    int pidFirst = fork();
    if(pidFirst == 0) {
        execlp("./build.sh", "bash");
    }
    else {
        waitpid(pidFirst, NULL, 0);
        int pidSecond = fork();
        if(pidSecond == 0) {
            execle("./result.out", "./result.out", NULL, libPath);
        }
        else {
            waitpid(pidSecond, NULL, 0);
            execlp("./delete.sh", "bash");
        }
    }
}