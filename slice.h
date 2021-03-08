#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "smalloc.h"
#include <stdbool.h>

#ifndef SLICE_H
#define SLICE_H

typedef struct dynarray {
    ssize_t cap;
    ssize_t base;
    ssize_t item_width;
    char * array;
} dynarray;

typedef struct slice {
    ssize_t start;
    ssize_t len;
    dynarray *parent;
} slice;

slice new_slice(ssize_t cap, ssize_t base, ssize_t item_width);
slice new_slice_from_arr(void *arr, ssize_t cap, ssize_t base, ssize_t item_width);
dynarray *new_dynarray(ssize_t cap, ssize_t base, ssize_t item_width);
void free_slice(slice aslice);
slice dup_slice(slice inslice);

void grow_dynarray(dynarray *darray, ssize_t length_needed);
void shift_dynarray(dynarray *darray, ssize_t shift_dist);
slice append_slice(slice aslice, const void *item);
slice slice_append_slice(slice aslice, slice to_add);
slice lappend_slice(slice aslice, const void *item);
slice slice_lappend_slice(slice aslice, slice to_add);
slice extend_slice(slice s, const void *item, ssize_t nmemb);
slice lextend_slice(slice s, const void *item, ssize_t nmemb);
slice set_slice_arr(slice s, const void *item, ssize_t nmemb);
slice set_slice(slice dest, slice source);
slice concat_slices(slice dest, slice source);

void print_slice(slice aslice, void (*fp) (void *));
void introspect_slice(slice aslice, void (*fp) (void *));
void print_double(void *d);
void print_char(void *d);
void print_long_long(void *d);

struct slice sub_slice(slice parent, ssize_t start, ssize_t len);
void slice_extract(void *dest, slice source);
slice slice_extract_slice(slice source);
void *slice_get_ptr(slice source);

#endif
