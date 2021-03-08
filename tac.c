#include <stdio.h>
#include "slice.h"

int main() {
	slice bufarr = new_slice(0, 5, sizeof(slice));
	slice buf = new_slice(0, 5, sizeof(char));
	bufarr = lappend_slice(bufarr, &buf);
	int c;
	while ((c = getchar()) != EOF) {
		slice *buf_ptr;
		switch (c) {
		case '\n':
			buf = new_slice(0, 5, sizeof(char));
			bufarr = lappend_slice(bufarr, &buf);
			break;
		default:
			buf_ptr = slice_get_ptr(bufarr);
			*buf_ptr = append_slice(*buf_ptr, &c);
		}
        }
	for (ssize_t i=0; i<bufarr.len; i++) {
		slice_extract(&buf, sub_slice(bufarr, i, 1));
		print_slice(buf, print_char);
	}
	for (ssize_t i=0; i<bufarr.len; i++) {
		slice_extract(&buf, sub_slice(bufarr, i, 1));
		free_slice(buf);
	}
	free_slice(bufarr);
	return(0);
}
