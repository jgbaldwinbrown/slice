#include <stdio.h>
#include "slice.h"

int main() {
    slice buf = new_slice(5, 0, sizeof(char));
    int c = 0;
    while ((c = getchar()) != EOF) {
        buf = append_slice(buf, &c);
    }
    print_slice(buf, print_char);
    return(0);
}
