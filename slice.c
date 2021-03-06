#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "smalloc.h"
#include <stdbool.h>
#include "slice.h"

slice new_slice(ssize_t cap, ssize_t base, ssize_t item_width) {
    struct slice aslice;
    aslice.len = 0;
    aslice.start = 0;
    aslice.parent = new_dynarray(cap, base, item_width);
    return(aslice);
}

dynarray *new_dynarray(ssize_t cap, ssize_t base, ssize_t item_width) {
    dynarray *darray = smalloc(sizeof(dynarray));
    darray->cap = cap;
    darray->base = base;
    darray->item_width = item_width;
    darray->array = smalloc(cap * sizeof(char) * item_width);
    return(darray);
}

slice new_slice_from_arr(void *arr, ssize_t cap, ssize_t base, ssize_t item_width) {
    slice s = new_slice(cap, base, item_width);
    s = set_slice_arr(s, arr, cap);
    return s;
}

slice dup_slice(slice inslice) {
    slice outslice = inslice;
    outslice.parent = new_dynarray(inslice.parent->cap, inslice.parent->base, inslice.parent->item_width);
    dynarray inp = *inslice.parent;
    dynarray outp = *outslice.parent;
    memcpy(outp.array, inp.array, outp.cap * outp.item_width);
    return(outslice);
}

void free_slice(slice aslice) {
    free(aslice.parent->array);
    free(aslice.parent);
}

void grow_dynarray(dynarray *d, ssize_t length_needed) {
    d->cap = length_needed;
    d->array = srealloc(d->array, length_needed * sizeof(char) * d->item_width);
}

void shift_dynarray(dynarray *d, ssize_t shift_dist) {
    ssize_t old_cap = d->cap;
    ssize_t cap_needed = d->cap + shift_dist;
    while (cap_needed >= d->cap) {
        grow_dynarray(d, cap_needed * 2);
    }
    for (ssize_t i=old_cap; i>=0; i--) {
        memcpy(d->array + ((i + shift_dist) * d->item_width), d->array + (i * d->item_width), d->item_width);
    };
    d->base = d->base + shift_dist;
}

slice append_slice(slice aslice, const void *item) {
    return extend_slice(aslice, item, 1);
}

slice lappend_slice(slice aslice, const void *item) {
    return lextend_slice(aslice, item, 1);
}

slice extend_slice(slice s, const void *item, ssize_t nmemb) {
    slice s_end = set_slice_arr(sub_slice(s, s.len, 0), item, nmemb);
    s.len = s.len + s_end.len;
    return s;
}

slice lextend_slice(slice s, const void *item, ssize_t nmemb) {
    slice s_new = set_slice_arr(sub_slice(s, -nmemb, 0), item, nmemb);
    s.len = s.len + s_new.len;
    s.start = s.start - nmemb;
    return s;
}

slice concat_slices(slice dest, slice source) {
    return extend_slice(dest, slice_get_ptr(source), source.len);
}

slice set_slice_arr(slice s, const void *item, ssize_t nmemb) {
    dynarray *d = s.parent;
    ssize_t shift_needed = -(d->base + s.start);
    if (shift_needed > 0) {
        shift_dynarray(d, shift_needed);
    }
    ssize_t cap_needed = d->base + s.start + nmemb;
    while (cap_needed >= d->cap) {
        grow_dynarray(d, cap_needed * 2);
    }
    memcpy(slice_get_ptr(s), item, d->item_width * nmemb);
    s.len += nmemb;
    return s;
}

slice set_slice(slice dest, slice source) {
    return set_slice_arr(dest, slice_get_ptr(source), source.len);
}

void print_slice(slice s, void (*fp) (void *)) {
    for (ssize_t i=s.start; i<s.start + s.len; i++) {
        fp(s.parent->array + ((i + s.parent->base) * s.parent->item_width));
    }
    printf("\n");
}

void introspect_slice(slice s, void (*fp) (void *)) {
    dynarray d = *s.parent;
    printf("len: %ld\nstart: %ld\nparent: %p\ncap: %ld\nbase: %ld\nitem_width: %ld\narray: %p\n",
        s.len,
        s.start,
        (void *) s.parent,
        d.cap,
        d.base,
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


slice sub_slice(slice ins, ssize_t start, ssize_t len) {
    slice outs = ins;
    outs.start = start + outs.start;
    outs.len = len;
    return(outs);
}

void slice_extract(void *dest, struct slice source) {
    dynarray d = *source.parent;
    memcpy(dest, slice_get_ptr(source), source.len * d.item_width);
}

void * slice_get_ptr(slice s) {
    return s.parent->array + ((s.parent->base + s.start) * s.parent->item_width);
}
