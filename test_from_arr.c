#include <stdio.h>
#include "slice.h"

int main() {
    long long in_arr[] = {1,2,3};
    slice s = new_slice_from_arr(in_arr, 3, 0, sizeof(long long));
    slice s2 = new_slice(3, 0, sizeof(long long));
    s2 = extend_slice(s2, in_arr, 3);
    print_slice(s, print_long_long);
    print_slice(s2, print_long_long);
    free_slice(s);
    free_slice(s2);
    return(0);
}
