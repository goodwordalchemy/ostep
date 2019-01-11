#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int *x = (int*) malloc(sizeof(int));
    x = NULL;
    printf("dereference result: %i", *x);
}
