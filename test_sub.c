#include <stdio.h>
#include "slice.h"

int main() {
    slice a = new_slice(8, 0, sizeof(long long));
    for (long long i=0; i<10; i++) {
        a = append_slice(a, &i);
        print_slice(a, print_long_long);
    }
    print_slice(sub_slice(a, 5, 3), print_long_long);
    set_slice_arr(sub_slice(a, 7, 2), (long long[]) {100, 1000}, 2);
    print_slice(a, print_long_long);

    slice b = new_slice(8, 5, sizeof(long long));
    for (long long i=0; i<10; i++) {
        b = append_slice(b, &i);
        print_slice(b, print_long_long);
    }
    print_slice(sub_slice(b, 5, 3), print_long_long);
    set_slice_arr(sub_slice(b, 7, 2), (long long[]) {100, 1000}, 2);
    print_slice(b, print_long_long);
    introspect_slice(b, print_long_long);
    shift_dynarray(b.parent, 100);
    introspect_slice(b, print_long_long);
    return 0;
}
