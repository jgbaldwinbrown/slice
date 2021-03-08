#include <stdio.h>
#include "slice.h"
#include "short_slice.h"

int main() {
    slice a = ns(8, 0, sizeof(long long));
    for (long long i=0; i<10; i++) {
        a = as(a, &i);
        ps(a, print_long_long);
    }
    ps(s(a, 5, 3), print_long_long);
    ssa(s(a, 7, 2), ((long long[]) {100, 1000}), 2);
    ps(a, print_long_long);

    slice b = ns(8, 5, sizeof(long long));
    for (long long i=0; i<10; i++) {
        b = as(b, &i);
        ps(b, print_long_long);
    }
    ps(s(b, 5, 3), print_long_long);
    ssa(s(b, 7, 2), ((long long[]) {100, 1000}), 2);
    ps(b, print_long_long);
    is(b, print_long_long);
    ssa(s(b, -10, 2), ((long long[]) {15, 16}), 2);
    is(b, print_long_long);
    slice big = s(b, -10, 20);
    is(big, print_long_long);
    long long to_add = 18;
    big = las(big, &to_add);
    is(big, print_long_long);
    big = les(big, ((long long[]){19, 20, 21}), 3);
    is(big, print_long_long);
    slice sub_to_set = s(big, 5, 2);
    sub_to_set = ss(sub_to_set, s(big, 8, 2));
    is(big, print_long_long);
    /*
    shift_dynarray(b.parent, 100);
    is(b, print_long_long);
    */
    return 0;
}
