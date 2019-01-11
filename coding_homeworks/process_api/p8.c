#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int pipefd[2];
    char buf;
    pid_t cpid1, cpid2;
    if (pipe(pipefd) == -1){
        fprintf(stderr, "pipe failure");
    }
    cpid1 = fork();
    if (cpid1 < 0){
        fprintf(stderr, "first fork failed");
    } else if (cpid1 == 0){
        close(pipefd[1]);
        while (read(pipefd[0], &buf, 1) > 0){
            write(STDOUT_FILENO, &buf, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
    } else {
        cpid2 = fork();
        if (cpid2 < 0){
            fprintf(stderr, "second fork failed");
        } else if (cpid2 == 0){
            close(STDOUT_FILENO);
            write(pipefd[1], "Hay...", 10);
        } else {
            wait(NULL);
        }
    }
    return 0;
}

