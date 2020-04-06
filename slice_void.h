#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "smalloc.h"
#include <stdbool.h>

struct slice {
    size_t len;
    size_t item_width;
    char *array;
    size_t start;
    size_t end;
    struct slice *parent;
    bool owner;
};

struct slice init_slice(size_t len, size_t item_width);
void free_slice(struct slice aslice);
struct slice * dup_slice(struct slice *inslice);

void double_slice(struct slice *aslice, size_t length_needed);
void slice_append(struct slice *aslice, const void *item);
void slice_extend(struct slice *aslice, const void *item, size_t nmemb);

void print_slice(const struct slice *aslice, void (*fp) (void *));
void introspect_slice(const struct slice *aslice, void (*fp) (void *));
void print_double(void *d);
void print_char(void *d);
void print_long_long(void *d);

struct slice sub_slice(struct slice *parent, size_t start, size_t end);
struct slice sub_slice_array(void *array, size_t start, size_t end, size_t item_width, size_t nmemb);
void slice_extract(void *dest, struct slice *source, size_t pos, size_t nmemb);
void slice_pop1(void *dest, struct slice *source, size_t pos);

struct slice sub_slice_abs(struct slice *parent, size_t start, size_t end);
void slice_extract_abs(void *dest, struct slice *source, size_t pos, size_t nmemb);
void slice_pop1_abs(void *dest, struct slice *source, size_t pos);
