#include "slice_void.h"

int main() {
    double d[] = {1.5, 3.7, 3.8, 9.9, 10.10};
    struct slice *my_slice = init_slice(3, sizeof(double));
    double d2[10];
    
    slice_extend(my_slice, &d[0], 5);
    struct slice my_subslice = sub_slice(my_slice, 1, 4);
    
    print_slice(my_slice, print_double);
    print_slice(&my_subslice, print_double);
    
    slice_extract(&d2[0], &my_subslice, 1, 1);
    printf("%lg\n", d2[0]);
    
    free_slice(my_slice);
}

