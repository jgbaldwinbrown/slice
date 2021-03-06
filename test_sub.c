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
    set_slice_arr(sub_slice(b, -10, 2), (long long[]) {15, 16}, 2);
    introspect_slice(b, print_long_long);
    slice big = sub_slice(b, -10, 20);
    introspect_slice(big, print_long_long);
    long long to_add = 18;
    big = lappend_slice(big, &to_add);
    introspect_slice(big, print_long_long);
    big = lextend_slice(big, (long long[]){19, 20, 21}, 3);
    introspect_slice(big, print_long_long);
    slice sub_to_set = sub_slice(big, 5, 2);
    sub_to_set = set_slice(sub_to_set, sub_slice(big, 8, 2));
    introspect_slice(big, print_long_long);
    /*
    shift_dynarray(b.parent, 100);
    introspect_slice(b, print_long_long);
    */
    return 0;
}
