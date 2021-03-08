#include <stdio.h>
#include "slice.h"

int main() {
    slice buf = new_slice(5, 0, sizeof(char));
    int c;
    while ((c = getchar()) != EOF) {
        switch (c) {
        case '\n':
            print_slice(buf, print_char);
            buf = sub_slice(buf, buf.len, 0);
            break;
        default:
            buf = lappend_slice(buf, &c);
        }
    }
    free_slice(buf);
    return(0);
}
