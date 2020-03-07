#include <stdlib.h>
#include <stdio.h>
#include "smalloc.h"

void *smalloc(size_t size) {
    void *mptr = malloc(size);
    if (mptr == NULL) {
        fputs("Error: out of memory", stderr);
        exit(1);
    }
    return(mptr);
}

void *scalloc(size_t nmemb, size_t size) {
    void *mptr = calloc(nmemb, size);
    if (mptr == NULL) {
        fputs("Error: out of memory", stderr);
        exit(1);
    }
    return(mptr);
}

void *srealloc(void *mptr, size_t size) {
    mptr = realloc(mptr, size);
    if (mptr == NULL) {
        fputs("Error: out of memory", stderr);
        exit(1);
    }
    return(mptr);
}
