#include <stdio.h>
#include "slice.h"

NEW_SLICE_TYPE_HEADER(char, char)
NEW_SLICE_TYPE(char, char)

NEW_SLICE_TYPE_HEADER(char_slice, char_slice)
NEW_SLICE_TYPE(char_slice, char_slice)

int main() {
	char_slice_slice bufarr = char_slice_new_slice(0, 5);
	bufarr = char_slice_lappend_slice(bufarr, char_new_slice(0, 5));
	int c;
	while ((c = getchar()) != EOF) {
		char_slice *buf_ptr;
		switch (c) {
		case '\n':
			bufarr = char_slice_lappend_slice(bufarr, char_new_slice(0, 5));
			break;
		default:
			buf_ptr = char_slice_slice_get_ptr(bufarr);
			*buf_ptr = char_append_slice(*buf_ptr, c);
		}
        }
	for (ssize_t i=0; i<bufarr.len; i++) {
		char_print_slice(
			slice_extract_char_slice(char_slice_sub_slice(bufarr, i, 1)),
			print_char
		);
	}
	for (ssize_t i=0; i<bufarr.len; i++) {
		char_free_slice(slice_extract_char_slice(char_slice_sub_slice(bufarr, i, 1)));
	}
	char_slice_free_slice(bufarr);
	return(0);
}
