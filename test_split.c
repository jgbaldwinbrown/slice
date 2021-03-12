#include <stdio.h>
#include "slice.h"

int main() {
    char input_string[] = "The quick brown fox\njumps\t\tover\tthe\tlazy\tdog\n";
    char separators[] = " \t\n";
    slice in = new_slice_from_arr(input_string, strlen(input_string), 0, sizeof(char));
    slice sep = new_slice_from_arr(separators, strlen(separators), 0, sizeof(char));
    slice split = split_slice(in, sep);
    for (ssize_t i=0; i<split.len; i++) {
        print_slice(slice_extract_slice(sub_slice(split, i, 1)), print_char);
    }
    
    free_slice(in);
    free_slice(sep);
    return 0;
}
