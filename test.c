#include "slice.h"

int main() {
    slice s = new_slice(3, sizeof(char));
    char *string = "hello";
    char *string2 = "This is a very long string. I'm writing it "
        "to be super long to make sure that my array resizing works correctly "
        "after updating it to check the size of the appended item.";
    s = append_slice(s, &string[0]);
    s = append_slice(s, &string[1]);
    s = append_slice(s, &string[2]);
    s = append_slice(s, &string[3]);
    s = append_slice(s, &string[4]);
    print_slice(s, &print_char);
    s = extend_slice(s, string2, strlen(string2) + 1);
    print_slice(s, &print_char);
    introspect_slice(s, &print_char);
    char *cp = slice_get_ptr(s, 5);
    printf("cp: %p\n", (void *) cp);
    free_slice(s);
    
    s = new_slice(5, sizeof(long long));
    long long dat = 5;
    s = append_slice(s, &dat);
    dat++;
    s = append_slice(s, &dat);
    dat++;
    s = append_slice(s, &dat);
    dat++;
    s = append_slice(s, &dat);
    dat++;
    s = append_slice(s, &dat);
    print_slice(s, &print_long_long);
    introspect_slice(s, &print_long_long);
    char *llp = slice_get_ptr(s, 5);
    printf("llp: %p\n", (void *) llp);
    free_slice(s);
    
    s = new_slice(5, sizeof(double));
    double dat2 = 11.1;
    s = append_slice(s, &dat2);
    dat2++;
    s = append_slice(s, &dat2);
    dat2++;
    s = append_slice(s, &dat2);
    dat2++;
    s = append_slice(s, &dat2);
    dat2++;
    s = append_slice(s, &dat2);
    print_slice(s, &print_double);
    introspect_slice(s, &print_double);
    free_slice(s);
    
    s = new_slice(5, sizeof(double));
    double dat3[] = {11.27, 58.36, -13.0, 25.8, 33.1};
    s = extend_slice(s, dat3, 3);
    print_slice(s, &print_double);
    double temp_double;
    slice_get_item(&temp_double, s, 2);
    double double_array[2];
    slice_extract(&double_array, s, 1, 2);
    printf("%lg\t%lg\n", double_array[0], double_array[1]);
    
    struct slice sub = sub_slice(s, 1, 3);
    print_slice(sub, print_double);
    introspect_slice(sub, print_double);
    introspect_slice(s, print_double);
    
    slice duped = dup_slice(s);
    print_slice(duped, print_double);
    free_slice(s);
    free_slice(duped);
    
    return(0);
}
