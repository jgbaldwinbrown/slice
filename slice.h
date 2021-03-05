#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "smalloc.h"
#include <stdbool.h>

typedef struct dynarray {
    size_t cap;
    size_t item_width;
    char * array;
} dynarray;

typedef struct slice {
    size_t start;
    size_t len;
    dynarray *parent;
} slice;

slice new_slice(size_t cap, size_t item_width);
dynarray *new_dynarray(size_t cap, size_t item_width);
void free_slice(slice aslice);
slice dup_slice(slice inslice);

void grow_dynarray(dynarray *darray, size_t length_needed);
slice append_slice(slice aslice, const void *item);
slice extend_slice(slice s, const void *item, size_t nmemb);
slice set_slice_arr(slice s, const void *item, size_t nmemb);
slice set_slice(slice dest, slice source);
slice concat_slices(slice dest, slice source);

void print_slice(slice aslice, void (*fp) (void *));
void introspect_slice(slice aslice, void (*fp) (void *));
void print_double(void *d);
void print_char(void *d);
void print_long_long(void *d);

struct slice sub_slice(slice parent, size_t start, size_t len);
void slice_extract(void *dest, slice source);
void *slice_get_ptr(slice source);
