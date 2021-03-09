#include "slice.h"

NEW_SLICE_TYPE_HEADER(float, float)
NEW_SLICE_TYPE(float, float)

void print_float(void *d) {
    float d2;
    memcpy(&d2, d, sizeof(float));
    printf("% 10f", d2);
}

int main() {
    float_slice buf = float_new_slice(5, 0);
    buf = float_append_slice(buf, 123);
    buf = float_extend_slice(buf, (float[]) {456, 789, 101112, 131415, 161718, 192021, 222324, 252627, 282930}, 9);
    float_print_slice(buf, print_float);
    float *i;
    i = float_slice_get_ptr(buf);
    printf("%f\n", *i);

    float_slice sub_buf = float_sub_slice(buf, 1, 2);
    float_introspect_slice(sub_buf, print_float);
    float_free_slice(buf);
    return(0);
}
