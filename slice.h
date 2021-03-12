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
slice split_slice(slice to_split, slice separators);
slice tokenize_slice(slice to_split, slice separators);

void print_slice(slice aslice, void (*fp) (void *));
void introspect_slice(slice aslice, void (*fp) (void *));
void print_double(void *d);
void print_char(void *d);
void print_long_long(void *d);

struct slice sub_slice(slice parent, ssize_t start, ssize_t len);
void slice_extract(void *dest, slice source);
slice slice_extract_slice(slice source);
void *slice_get_ptr(slice source);

#define NEW_SLICE_TYPE_HEADER( MY_TYPE, MY_NAME ) \
typedef struct MY_NAME ## _slice {\
    ssize_t start;\
    ssize_t len;\
    dynarray *parent;\
} MY_NAME ## _slice;\
\
MY_NAME ## _slice MY_NAME ## _append_slice(MY_NAME ## _slice aslice, MY_TYPE to_add);\
MY_NAME ## _slice MY_NAME ## _lappend_slice(MY_NAME ## _slice aslice, MY_TYPE to_add);\
MY_TYPE slice_extract_ ## MY_NAME(MY_NAME ## _slice source);\
MY_TYPE slice_extract_one_ ## MY_NAME(MY_NAME ## _slice source);\
MY_NAME ## _slice MY_NAME ## _new_slice(ssize_t cap, ssize_t base);\
MY_NAME ## _slice MY_NAME ## _new_slice_from_arr(MY_TYPE *arr, ssize_t cap, ssize_t base);\
MY_NAME ## _slice MY_NAME ## _extend_slice(MY_NAME ## _slice s, const MY_TYPE *item, ssize_t nmemb);\
MY_NAME ## _slice MY_NAME ## _lextend_slice(MY_NAME ## _slice s, const MY_TYPE *item, ssize_t nmemb);\
MY_NAME ## _slice MY_NAME ## _set_slice_arr(MY_NAME ## _slice s, const MY_TYPE *item, ssize_t nmemb);\
\
void MY_NAME ## _free_slice(MY_NAME ## _slice aslice);\
MY_NAME ## _slice MY_NAME ## _dup_slice(MY_NAME ## _slice inslice);\
MY_NAME ## _slice MY_NAME ## _set_slice(MY_NAME ## _slice dest, MY_NAME ## _slice source);\
MY_NAME ## _slice MY_NAME ## _concat_slices(MY_NAME ## _slice dest, MY_NAME ## _slice source);\
void MY_NAME ## _print_slice(MY_NAME ## _slice aslice, void (*fp) (void *));\
void MY_NAME ## _introspect_slice(MY_NAME ## _slice aslice, void (*fp) (void *));\
struct MY_NAME ## _slice MY_NAME ## _sub_slice(MY_NAME ## _slice parent, ssize_t start, ssize_t len);\
MY_TYPE * MY_NAME ## _slice_get_ptr(MY_NAME ## _slice source);\
MY_NAME ## _slice MY_NAME ## _slice_gen2type(slice s);\
slice MY_NAME ## _slice_type2gen(MY_NAME ## _slice t);

#define NEW_SLICE_TYPE( MY_TYPE, MY_NAME ) \
\
MY_NAME ## _slice MY_NAME ## _slice_gen2type(slice s) {\
    MY_NAME ## _slice t;\
    t.len = s.len;\
    t.parent = s.parent;\
    t.start = s.start;\
    return t;\
}\
\
slice MY_NAME ## _slice_type2gen(MY_NAME ## _slice t) {\
    slice s;\
    s.len = t.len;\
    s.parent = t.parent;\
    s.start = t.start;\
    return s;\
}\
\
MY_NAME ## _slice MY_NAME ## _append_slice(MY_NAME ## _slice aslice, MY_TYPE item) {\
    return MY_NAME ## _slice_gen2type(append_slice(MY_NAME ## _slice_type2gen(aslice), &item));\
}\
\
MY_NAME ## _slice MY_NAME ## _lappend_slice(MY_NAME ## _slice aslice, MY_TYPE item) {\
    return MY_NAME ## _slice_gen2type(lextend_slice(MY_NAME ## _slice_type2gen(aslice), &item, 1));\
}\
\
MY_TYPE slice_extract_## MY_NAME(struct MY_NAME ## _slice source) {\
    MY_TYPE buf;\
    dynarray d = *source.parent;\
    memcpy(&buf, slice_get_ptr(MY_NAME ## _slice_type2gen(source)), d.item_width);\
    return buf;\
}\
\
MY_NAME ## _slice MY_NAME ## _new_slice(ssize_t cap, ssize_t base) {\
    return MY_NAME ## _slice_gen2type(new_slice(cap, base, sizeof(MY_TYPE)));\
}\
\
MY_NAME ## _slice MY_NAME ## _new_slice_from_arr(MY_TYPE *arr, ssize_t cap, ssize_t base) {\
    return MY_NAME ## _slice_gen2type(new_slice_from_arr(arr, cap, base, sizeof(MY_TYPE)));\
}\
\
MY_NAME ## _slice MY_NAME ## _extend_slice(MY_NAME ## _slice s, const MY_TYPE *item, ssize_t nmemb) {\
    return MY_NAME ## _slice_gen2type(extend_slice(MY_NAME ## _slice_type2gen(s), item, nmemb));\
}\
\
MY_NAME ## _slice MY_NAME ## _lextend_slice(MY_NAME ## _slice s, const MY_TYPE *item, ssize_t nmemb) {\
    return MY_NAME ## _slice_gen2type(lextend_slice(MY_NAME ## _slice_type2gen(s), item, nmemb));\
}\
\
MY_NAME ## _slice MY_NAME ## _set_slice_arr(MY_NAME ## _slice s, const MY_TYPE *item, ssize_t nmemb) {\
    return MY_NAME ## _slice_gen2type(set_slice_arr(MY_NAME ## _slice_type2gen(s), item, nmemb));\
}\
\
\
void MY_NAME ## _free_slice(MY_NAME ## _slice aslice) {\
    free_slice(MY_NAME ## _slice_type2gen(aslice));\
}\
\
MY_NAME ## _slice MY_NAME ## _dup_slice(MY_NAME ## _slice inslice) {\
    return MY_NAME ## _slice_gen2type(dup_slice(MY_NAME ## _slice_type2gen(inslice)));\
}\
\
MY_NAME ## _slice MY_NAME ## _set_slice(MY_NAME ## _slice dest, MY_NAME ## _slice source) {\
    return MY_NAME ## _slice_gen2type(set_slice(MY_NAME ## _slice_type2gen(dest), MY_NAME ## _slice_type2gen(source)));\
}\
\
MY_NAME ## _slice MY_NAME ## _concat_slices(MY_NAME ## _slice dest, MY_NAME ## _slice source) {\
    return MY_NAME ## _slice_gen2type(concat_slices(MY_NAME ## _slice_type2gen(dest), MY_NAME ## _slice_type2gen(source)));\
}\
\
void MY_NAME ## _print_slice(MY_NAME ## _slice aslice, void (*fp) (void *)) {\
    print_slice(MY_NAME ## _slice_type2gen(aslice), fp);\
}\
\
void MY_NAME ## _introspect_slice(MY_NAME ## _slice aslice, void (*fp) (void *)) {\
    introspect_slice(MY_NAME ## _slice_type2gen(aslice), fp);\
}\
\
struct MY_NAME ## _slice MY_NAME ## _sub_slice(MY_NAME ## _slice parent, ssize_t start, ssize_t len) {\
    return MY_NAME ## _slice_gen2type(sub_slice(MY_NAME ## _slice_type2gen(parent), start, len));\
}\
\
MY_TYPE * MY_NAME ## _slice_get_ptr(MY_NAME ## _slice source) {\
    return (MY_TYPE *) slice_get_ptr(MY_NAME ## _slice_type2gen(source));\
}

#endif
