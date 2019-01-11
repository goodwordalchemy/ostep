#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int NUM_ITERATIONS = 100000;
char *FILENAME = "small_file.txt";

long gtod_seconds(){
    struct timeval tv;
    long tv_sec;

    gettimeofday(&tv, NULL);
    tv_sec = (long) tv.tv_sec;
    return tv_sec;
}

int main(int argc, char *argv[]){
    long before, after;
    FILE *fp;
    double final;

    before = gtod_seconds();
    for (int i = 0; i < NUM_ITERATIONS; i++){
        fp = fopen(FILENAME, "r");
        fclose(fp);
    }
    after = gtod_seconds();

    final = (after - before) / (double) NUM_ITERATIONS;
    printf("seconds for an open: %f\n", final);
    
    return 0;
}
