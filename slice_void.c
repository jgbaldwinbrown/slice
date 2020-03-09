#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "smalloc.h"
#include "slice_void.h"

struct slice *init_slice(size_t len, size_t item_width) {
    struct slice *aslice = smalloc(sizeof(struct slice));
    aslice->len = len;
    aslice->start = 0;
    aslice->end = 0;
    aslice->item_width = item_width;
    aslice->array = smalloc(len * sizeof(char) * item_width);
    aslice->parent = NULL;
    return(aslice);
}

void free_slice(struct slice *aslice) {
    free(aslice->array);
    free(aslice);
}

void double_slice(struct slice *aslice, size_t length_needed) {
    aslice->len = length_needed * 2;
    aslice->array = srealloc(aslice->array, length_needed * sizeof(char) * aslice->item_width);
}

void slice_append(struct slice *aslice, const void *item) {
    slice_extend(aslice, item, 1);
}

void slice_extend(struct slice *aslice, const void *item, size_t nmemb) {
    if (aslice->end + nmemb + 1 >= aslice->len) {
        double_slice(aslice, aslice->len + nmemb);
    }
    memcpy(aslice->array + (aslice->end * aslice->item_width), item, aslice->item_width * nmemb);
    aslice->end += nmemb;
}

void print_slice(struct slice *aslice, void (*fp) (void *)) {
    for (size_t i=aslice->start; i<aslice->end; i++) {
        fp(aslice->array + (i * aslice->item_width));
    }
    printf("\n");
}

void introspect_slice(struct slice *aslice, void (*fp) (void *)) {
    printf("len: %ld\nstart: %ld\tend: %ld\nitem_width: %ld\nparent: %p\n",
        aslice->len,
        aslice->start,
        aslice->end,
        aslice->item_width,
        (void *) aslice->parent
    );
    print_slice(aslice, fp);
}

void print_double(void *d) {
    double d2;
    memcpy(&d2, d, sizeof(double));
    printf("%10lg", d2);
}

void print_char(void *d) {
    char d2;
    memcpy(&d2, d, sizeof(char));
    printf("%c", d2);
}

void print_long_long(void *d) {
    long long d2;
    memcpy(&d2, d, sizeof(long long));
    printf("%10lld", d2);
}


struct slice sub_slice(struct slice *parent, size_t start, size_t end) {
    struct slice child = *parent;
    child.parent = parent;
    child.start = start;
    child.end = end;
    return(child);
}

void slice_extract(void *dest, struct slice *source, size_t pos, size_t nmemb) {
    memcpy(dest, source->array + (pos * source->item_width), nmemb * source->item_width);
}

void slice_pop1(void *dest, struct slice *source, size_t pos) {
    slice_extract(dest, source, pos, 1);
}

int main() {
    struct slice *aslice = init_slice(3, sizeof(char));
    char *string = "hello";
    char *string2 = "This is a very long string. I'm writing it "
        "to be super long to make sure that my array resizing works correctly "
        "after updating it to check the size of the appended item.";
    slice_append(aslice, &string[0]);
    slice_append(aslice, &string[1]);
    slice_append(aslice, &string[2]);
    slice_append(aslice, &string[3]);
    slice_append(aslice, &string[4]);
    print_slice(aslice, &print_char);
    slice_extend(aslice, string2, strlen(string2) + 1);
    print_slice(aslice, &print_char);
    introspect_slice(aslice, &print_char);
    free_slice(aslice);
    
    aslice = init_slice(5, sizeof(long long));
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
    print_slice(aslice, &print_long_long);
    free_slice(aslice);
    
    aslice = init_slice(5, sizeof(double));
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
    print_slice(aslice, &print_double);
    printf("%lg\n", ((float *) aslice->array)[0]);
    free_slice(aslice);
    
    aslice = init_slice(5, sizeof(double));
    double dat3[] = {11.27, 58.36, -13.0, 25.8, 33.1};
    slice_extend(aslice, dat3, 3);
    print_slice(aslice, &print_double);
    double temp_double;
    slice_pop1(&temp_double, aslice, 2);
    double double_array[2];
    slice_extract(&double_array, aslice, 1, 2);
    printf("%lg\t%lg\n", double_array[0], double_array[1]);
    
    struct slice sub = sub_slice(aslice, 1, 3);
    print_slice(&sub, print_double);
    free_slice(aslice);
}
