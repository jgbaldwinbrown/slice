all: test

CC := gcc
CFLAGS := -Wpedantic -Wall -Werror -Wextra -O3

smalloc.o: smalloc.c smalloc.h
	$(CC) $(CFLAGS) -c $<

slice.o: slice.c slice.h
	$(CC) $(CFLAGS) -c $<

test.o: test.c slice.h
	$(CC) $(CFLAGS) -c $<

test: test.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

test_float_slice.o: test_float_slice.c slice.h
	$(CC) $(CFLAGS) -c $<

test_float_slice: test_float_slice.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@
