#pragma GCC push_options
#pragma GCC optimize("O0")

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int PAGESIZE = 4096; // Approximate page size on Mac

/* int NUMITERS = 100000000; */
/* int NUMPAGES = 10; */

int main(int argc, char *argv[]) {
    int numpages, numiters;
    if (argc == 3){
        numiters = atoi(argv[1]);
        numpages = atoi(argv[2]);
    }
    struct timeval start, end;    
    int jump = PAGESIZE / sizeof(int);

    int a[jump * numpages];

    gettimeofday(&start, NULL);

    int i, j;
    for (j = 0; j < numiters; j++){
        for (i = 0; i < numpages * jump; i += jump){
            a[i] += 1;
        }
    }

    gettimeofday(&end, NULL);

    double total_time = (double) ((end.tv_sec * 1000000 + end.tv_usec)
                - (start.tv_sec * 1000000 + start.tv_usec)); // microseconds
    total_time = total_time * 1000; // nanoseconds

    double time_per_access = (double) total_time / (numpages * numiters);

    printf("%f\n", time_per_access);
    return 0;
}

#pragma GCC pop_options
