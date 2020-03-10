all: slice test

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

test.o: test.c slice_void.h
	$(CC) $(CFLAGS) -c $<

test: test.o slice_void.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@