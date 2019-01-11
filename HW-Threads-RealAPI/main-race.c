#include <stdio.h>

#include "mythreads.h"

int balance = 0;

pthread_mutex_t lock_main = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    pthread_mutex_lock(&lock_main);
    balance++; // unprotected access 
    pthread_mutex_unlock(&lock_main);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    pthread_mutex_lock(&lock_main);
    balance++; // unprotected access
    pthread_mutex_unlock(&lock_main);
    Pthread_join(p, NULL);
    return 0;
}
