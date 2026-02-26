#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // child process
        printf("Child Process\n");
    } else if (pid > 0) {
        // parent process
        printf("Parent Process\n");
    } else {
        printf("Fork error\n");
    }

    return 0;
}