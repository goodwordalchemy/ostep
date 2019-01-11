#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("Hello world (pid:%d)\n", (int) getpid());
    FILE *fp;
    fp = fopen("p2file.txt", "w");

    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0){
        fprintf(fp, "Hello.  I am a child (pid:%d)\n", (int) getpid());
    } else {
        wait(NULL);
        fprintf(fp, "Hello, I am a parent of %d (pid:%d)\n", rc, (int) getpid());
    }
    fclose(fp);
    return 0;
}
