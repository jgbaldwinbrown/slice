#include "int_slice.h"
#include "slice.h"

void print_int(void *d) {
    int d2;
    memcpy(&d2, d, sizeof(int));
    printf("%10d", d2);
}

int main() {
    int_slice buf = int_new_slice(5, 0);
    buf = int_append_slice(buf, 123);
    buf = int_extend_slice(buf, (int[]) {456, 789}, 2);
    int_print_slice(buf, print_int);
    int *ip;
    int i;
    ip = int_slice_get_ptr(buf);
    printf("%d\n", *ip);
    i = slice_extract_int(buf);
    printf("%d\n", i);
    int_free_slice(buf);
    return(0);
}
