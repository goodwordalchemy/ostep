#include <stdio.h>
#include <sys/time.h>

int NUM_ITERS = 20;

long gtod_seconds(){
    struct timeval tv;
    long tv_sec;

    gettimeofday(&tv, NULL);
    printf("tv_sec: %lu\n", tv.tv_sec);
    tv_sec = (long) tv.tv_sec;
    printf("tv_sec2: %lu\n", tv_sec);
    return tv_sec;
}

long consec_timer_diff() {
    long before, after, diff;
    before = gtod_seconds();
    printf("before: %lu\n", before);
    after = gtod_seconds();
    printf("after: %lu\n", after);
    diff = after - before;
    return diff;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < NUM_ITERS; i++){
        printf("trial %d of %d: %lu\n", i+1, NUM_ITERS, consec_timer_diff());
    }
}
