#include "slice_void.h"

#define ARSIZ 10

int main() {
    double darray[ARSIZ];
    for (size_t i=0; i<ARSIZ; i++) {
        darray[i] = i;
    }
    struct slice dslice = sub_slice_array(darray, 3, 7, sizeof(double), ARSIZ);
    print_slice(dslice, print_double);
    return(0);
}
