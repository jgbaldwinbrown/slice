#include <stdio.h>
#include <stdlib.h>
#include "smalloc.h"
#include "slice.h"

struct slice *init_slice(enum type type, size_t len) {
    struct slice *aslice = smalloc(sizeof(struct slice));
    aslice->type = type;
    aslice->len = len;
    aslice->start = 0;
    aslice->end = 0;
    switch (type) {
        case CHAR:
            aslice->array.c = smalloc(len * sizeof(char));
            break;
        case LLINT:
            aslice->array.l = smalloc(len * sizeof(long long));
            break;
        case DOUBLE:
            aslice->array.d = smalloc(len * sizeof(double));
            break;
        default:
            exit(1);
    }
    return(aslice);
}

void free_slice(struct slice *aslice) {
    switch (aslice->type) {
        case CHAR:
            free(aslice->array.c);
            break;
        case LLINT:
            free(aslice->array.l);
            break;
        case DOUBLE:
            free(aslice->array.d);
            break;
        default:
            exit(1);
    }
    free(aslice);
}

void double_slice(struct slice *aslice) {
    aslice->len *= 2;
    switch (aslice->type) {
        case CHAR:
            aslice->array.c = srealloc(aslice->array.c, aslice->len * sizeof(char));
            break;
        case LLINT:
            aslice->array.l = srealloc(aslice->array.l, aslice->len * sizeof(long long));
            break;
        case DOUBLE:
            aslice->array.d = srealloc(aslice->array.d, aslice->len * sizeof(double));
            break;
        default:
            exit(1);
    }
}

void slice_append(struct slice *aslice, const void *item) {
    if (aslice->end >= aslice->len) {
        double_slice(aslice);
    }
    switch (aslice->type) {
        case CHAR:
            aslice->array.c[aslice->end] = *(char *) item;
            aslice->end++;
            break;
        case LLINT:
            aslice->array.l[aslice->end] = *(long long *) item;
            aslice->end++;
            break;
        case DOUBLE:
            aslice->array.d[aslice->end] = *(double *) item;
            aslice->end++;
            break;
        default:
            exit(1);
    }
}

void print_slice(struct slice *aslice) {
    static char c_format[] = "%c";
    static char l_format[] = "%10lld";
    static char d_format[] = "%10lg";
    char *format;
    switch (aslice->type) {
        case CHAR:
            format = &c_format[0];
            for (size_t i=aslice->start; i<aslice->end; i++) {
                printf(format, aslice->array.c[i]);
            }
            break;
        case LLINT:
            format = &l_format[0];
            for (size_t i=aslice->start; i<aslice->end; i++) {
                printf(format, aslice->array.l[i]);
            }
            aslice->end++;
            break;
        case DOUBLE:
            format = &d_format[0];
            for (size_t i=aslice->start; i<aslice->end; i++) {
                printf(format, aslice->array.d[i]);
            }
            aslice->end++;
            break;
        default:
            exit(1);
    }
    printf("\n");
}

int main() {
    struct slice *aslice = init_slice(CHAR, 3);
    char *string = "hello";
    slice_append(aslice, &string[0]);
    slice_append(aslice, &string[1]);
    slice_append(aslice, &string[2]);
    slice_append(aslice, &string[3]);
    slice_append(aslice, &string[4]);
    print_slice(aslice);
    free_slice(aslice);
    
    aslice = init_slice(LLINT, 5);
    long long dat = 5;
    slice_append(aslice, &dat);
    dat++;
    slice_append(aslice, &dat);
    dat++;
    slice_append(aslice, &dat);
    dat++;
    slice_append(aslice, &dat);
    dat++;
    slice_append(aslice, &dat);
    print_slice(aslice);
    free_slice(aslice);
    
    aslice = init_slice(DOUBLE, 5);
    double dat2 = 11.1;
    slice_append(aslice, &dat2);
    dat2++;
    slice_append(aslice, &dat2);
    dat2++;
    slice_append(aslice, &dat2);
    dat2++;
    slice_append(aslice, &dat2);
    dat2++;
    slice_append(aslice, &dat2);
    print_slice(aslice);
    free_slice(aslice);
}
