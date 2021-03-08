#include "long_long_slice.h"

slice long_long_append_slice(slice aslice, long long item) {
    return extend_slice(aslice, &item, 1);
}

slice long_long_lappend_slice(slice aslice, long long item) {
    return lextend_slice(aslice, &item, 1);
}

long long slice_extract_long_long(struct slice source) {
    long long buf;
    dynarray d = *source.parent;
    memcpy(&buf, slice_get_ptr(source), source.len * d.item_width);
    return buf;
}
