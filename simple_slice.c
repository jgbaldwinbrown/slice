#include <stdio.h>

void slicep(char * toprint, size_t start, size_t end) {
    printf("%.*s\n", (int) (end - start), toprint + start);
}

int main() {
    char a[] = "Here is a test string.";
    puts(a);
    slicep(a, 0, 3);
    slicep(a, 5, 7);
}
