#include "int_slice.h"
#include "slice.h"

void print_int(void *d) {
    int d2;
    memcpy(&d2, d, sizeof(int));
    printf("%10d", d2);
}

int main() {
    slice buf = int_new_slice(5, 0);
    buf = int_append_slice(buf, 123);
    buf = int_extend_slice(buf, (int[]) {456, 789}, 2);
    print_slice(buf, print_int);
    free_slice(buf);
    return(0);
}
