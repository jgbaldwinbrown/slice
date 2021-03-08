#include <stdio.h>
#include "slice.h"

int main() {
	slice bufarr = new_slice(0, 5, sizeof(slice));
	bufarr = slice_lappend_slice(bufarr, new_slice(0, 5, sizeof(char)));
	int c;
	while ((c = getchar()) != EOF) {
		slice *buf_ptr;
		switch (c) {
		case '\n':
			bufarr = slice_lappend_slice(bufarr, new_slice(0, 5, sizeof(char)));
			break;
		default:
			buf_ptr = slice_get_ptr(bufarr);
			*buf_ptr = append_slice(*buf_ptr, &c);
		}
        }
	for (ssize_t i=0; i<bufarr.len; i++) {
		print_slice(
			slice_extract_slice(sub_slice(bufarr, i, 1)),
			print_char
		);
	}
	for (ssize_t i=0; i<bufarr.len; i++) {
		free_slice(slice_extract_slice(sub_slice(bufarr, i, 1)));
	}
	free_slice(bufarr);
	return(0);
}
