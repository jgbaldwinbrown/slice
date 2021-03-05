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

slice init_slice(size_t cap, size_t item_width);
void free_slice(sslice slice aslice);
slice dup_slice(slice inslice);

void grow_dynarray(dynarray darray, size_t length_needed);
void slice_append(slice *aslice, const void *item);
void slice_extend(slice *aslice, const void *item, size_t nmemb);

void print_slice(slice aslice, void (*fp) (void *));
void introspect_slice(slice aslice, void (*fp) (void *));
void print_double(void *d);
void print_char(void *d);
void print_long_long(void *d);

struct slice sub_slice(slice parent, size_t start, size_t len);
void slice_extract(void *dest, slice source, size_t pos, size_t nmemb);
void slice_get_item(void *dest, slice source, size_t pos);
