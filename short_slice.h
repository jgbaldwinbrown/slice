#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "smalloc.h"
#include <stdbool.h>
#include "slice.h"

#ifndef SHORT_SLICE_H
#define SHORT_SLICE_H

#define ns(CAP, BASE, ITEM_WIDTH) new_slice((CAP), (BASE), (ITEM_WIDTH))
#define nsa(ARR, CAP, BASE, ITEM_WIDTH) new_slice_from_arr((ARR), (CAP), (BASE), (ITEM_WIDTH))
#define fs(ASLICE) free_slice(ASLICE)
#define ds(INSLICE) dup_slice(INSLICE)

#define as(ASLICE, ITEM) append_slice((ASLICE), (ITEM))
#define sas(ASLICE, ITEM) slice_append_slice((ASLICE), (ITEM))
#define las(ASLICE, ITEM) lappend_slice((ASLICE), (ITEM))
#define sas(ASLICE, ITEM) slice_append_slice((ASLICE), (ITEM))
#define slas(ASLICE, ITEM) slice_lappend_slice((ASLICE), (ITEM))
#define es(ASLICE, ITEM, NMEMB) extend_slice((ASLICE), (ITEM), (NMEMB))
#define les(ASLICE, ITEM, NMEMB) lextend_slice((ASLICE), (ITEM), (NMEMB))
#define ssa(ASLICE, ITEM, NMEMB) set_slice_arr((ASLICE), (ITEM), (NMEMB))
#define ss(DEST, SOURCE) set_slice((DEST), (SOURCE))
#define cs(DEST, SOURCE) concat_slices((DEST), (SOURCE))

#define ps(ASLICE, FP) print_slice((ASLICE), (FP))
#define is(ASLICE, FP) introspect_slice((ASLICE), (FP))
/*
#define pd(D) print_double(D)
#define pc(D) print_char(D)
#define pll(D) print_long_long(D)
*/

#define s(PARENT, START, LEN) sub_slice((PARENT), (START), (LEN))
#define se(DEST, SOURCE) slice_extract((DEST), (SOURCE))
#define ses(SOURCE) slice_extract(SOURCE)
#define sp(SOURCE) slice_get_ptr(SOURCE)

#endif
