#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0){
        close(STDOUT_FILENO);
        printf("Hello\n");
        execl("/bin/ls", ".");
    } else {
        int stat;
        wait(&stat);
        printf("child process stat: %d\n", stat);
        printf("Goodbye\n");
    }
    return 0;
}
