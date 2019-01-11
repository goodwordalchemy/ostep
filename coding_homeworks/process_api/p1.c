#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("Hello world (pid:%d)\n", (int) getpid());
    int x = 0;
    int rc = fork();
    x = 100;
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0){
        x += 1;
        printf("Hello.  I am a child (pid:%d).  x=%d\n", (int) getpid(), x);
    } else {
        x += 2;
        wait(NULL);
        printf("Hello, I am a parent of %d (pid:%d). x=%d\n", rc, (int) getpid(), x);
    }
    return 0;
}
