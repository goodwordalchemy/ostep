#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0){
        printf("Hello\n");
        /* wait(NULL); */
        execl("/bin/ls", ".");
    } else {
        wait(NULL);
        printf("Goodbye\n");
    }
    return 0;
}
