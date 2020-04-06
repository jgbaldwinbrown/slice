#include "slice_void.h"

int main() {
    struct slice *aslice = init_slice(3, sizeof(char));
    char *string = "hello";
    char *string2 = "This is a very long string. I'm writing it "
        "to be super long to make sure that my array resizing works correctly "
        "after updating it to check the size of the appended item.";
    slice_append(aslice, &string[0]);
    slice_append(aslice, &string[1]);
    slice_append(aslice, &string[2]);
    slice_append(aslice, &string[3]);
    slice_append(aslice, &string[4]);
    print_slice(aslice, &print_char);
    slice_extend(aslice, string2, strlen(string2) + 1);
    print_slice(aslice, &print_char);
    introspect_slice(aslice, &print_char);
    free_slice(aslice);
    
    aslice = init_slice(5, sizeof(long long));
    long long dat = 5;
    slice_append(aslice, &dat);
    dat++;
    slice_append(aslice, &dat);
    dat++;
    slice_append(aslice, &dat);
    dat++;
    slice_append(aslice, &dat);
    dat++;
    slice_append(aslice, &dat);
    print_slice(aslice, &print_long_long);
    free_slice(aslice);
    
    aslice = init_slice(5, sizeof(double));
    double dat2 = 11.1;
    slice_append(aslice, &dat2);
    dat2++;
    slice_append(aslice, &dat2);
    dat2++;
    slice_append(aslice, &dat2);
    dat2++;
    slice_append(aslice, &dat2);
    dat2++;
    slice_append(aslice, &dat2);
    print_slice(aslice, &print_double);
    printf("%lg\n", ((float *) aslice->array)[0]);
    free_slice(aslice);
    
    aslice = init_slice(5, sizeof(double));
    double dat3[] = {11.27, 58.36, -13.0, 25.8, 33.1};
    slice_extend(aslice, dat3, 3);
    print_slice(aslice, &print_double);
    double temp_double;
    slice_pop1(&temp_double, aslice, 2);
    double double_array[2];
    slice_extract(&double_array, aslice, 1, 2);
    printf("%lg\t%lg\n", double_array[0], double_array[1]);
    
    struct slice sub = sub_slice(aslice, 1, 3);
    print_slice(&sub, print_double);
    introspect_slice(&sub, print_double);
    introspect_slice(aslice, print_double);
    
    struct slice *duped = dup_slice(aslice);
    print_slice(duped, print_double);
    free_slice(aslice);
    
    double *dptr = &dat3[0];
    struct slice arrslice = sub_slice_array(dptr, 1, 3, sizeof(double), 5);
    print_slice(&arrslice, print_double);
    
    return(0);
}
