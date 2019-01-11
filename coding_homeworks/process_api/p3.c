#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0){
        printf("Hello\n");
    } else {
        /* wait(NULL); */
        sleep(1);
        printf("Goodbye\n");
    }
    return 0;
}
