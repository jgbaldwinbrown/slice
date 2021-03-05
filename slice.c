#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "smalloc.h"
#include <stdbool.h>
#include "slice.h"

slice new_slice(size_t cap, size_t item_width) {
    struct slice aslice;
    aslice.len = 0;
    aslice.start = 0;
    aslice.parent = new_dynarray(cap, item_width);
    return(aslice);
}

dynarray *new_dynarray(size_t cap, size_t item_width) {
    dynarray *darray = smalloc(sizeof(dynarray));
    darray->cap = cap;
    darray->item_width = item_width;
    darray->array = smalloc(cap * sizeof(char) * item_width);
    return(darray);
}

struct slice dup_slice(slice inslice) {
    slice outslice = inslice;
    outslice.parent = new_dynarray(inslice.parent->cap, inslice.parent->item_width);
    dynarray inp = *inslice.parent;
    dynarray outp = *outslice.parent;
    memcpy(outp.array, inp.array, outp.cap * outp.item_width);
    return(outslice);
}

void free_slice(slice aslice) {
    free(aslice.parent->array);
    free(aslice.parent);
}

void grow_dynarray(dynarray *d, size_t length_needed) {
    d->cap = length_needed;
    d->array = srealloc(d->array, length_needed * sizeof(char) * d->item_width);
}

slice append_slice(slice aslice, const void *item) {
    return extend_slice(aslice, item, 1);
}

slice extend_slice(slice s, const void *item, size_t nmemb) {
    dynarray *d = s.parent;
    size_t cap_needed = s.start + s.len + nmemb;
    while (cap_needed >= d->cap) {
        grow_dynarray(d, cap_needed * 2);
    }
    memcpy(slice_get_ptr(s, s.start + s.len), item, d->item_width * nmemb);
    s.len += nmemb;
    return s;
}

slice concat_slices(slice dest, slice source) {
    return extend_slice(dest, slice_get_ptr(source, 0), source.len);
}

void print_slice(slice s, void (*fp) (void *)) {
    for (size_t i=s.start; i<s.start + s.len; i++) {
        fp(s.parent->array + (i * s.parent->item_width));
    }
    printf("\n");
}

void introspect_slice(slice s, void (*fp) (void *)) {
    dynarray d = *s.parent;
    printf("len: %ld\nstart: %ld\nparent: %p\ncap: %ld\nitem_width: %ld\narray: %p\n",
        s.len,
        s.start,
        (void *) s.parent,
        d.cap,
        d.item_width,
        (void *) d.array
    );
    print_slice(s, fp);
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


slice sub_slice(slice ins, size_t start, size_t len) {
    slice outs = ins;
    outs.start = start + outs.start;
    outs.len = len;
    return(outs);
}

void slice_extract(void *dest, struct slice source, size_t pos, size_t nmemb) {
    dynarray d = *source.parent;
    memcpy(dest, d.array + ((source.start + pos) * d.item_width), nmemb * d.item_width);
}

void slice_get_item(void *dest, slice source, size_t pos) {
    slice_extract(dest, source, pos, 1);
}

void * slice_get_ptr(slice s, size_t pos) {
    return s.parent->array + (pos * s.parent->item_width);
}
