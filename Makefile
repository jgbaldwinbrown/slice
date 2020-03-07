all: slice slice_void

CC := gcc
CFLAGS := -Wpedantic -Wall -Werror -Wextra -O3

smalloc.o: smalloc.c smalloc.h
	$(CC) $(CFLAGS) -c $<

slice.o: slice.c slice.h
	$(CC) $(CFLAGS) -c $<

slice: slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

slice_void.o: slice_void.c slice_void.h
	$(CC) $(CFLAGS) -c $<

slice_void: slice_void.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@
