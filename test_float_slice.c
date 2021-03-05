#include "slice.h"

#define ARSIZ 10

int main() {
    double darray[ARSIZ];
    for (size_t i=0; i<ARSIZ; i++) {
        darray[i] = i + .5;
    }
    
    slice dslice = new_slice(5, sizeof(double));
    dslice = extend_slice(dslice, darray, ARSIZ);
    print_slice(dslice, print_double);
    return(0);
}
