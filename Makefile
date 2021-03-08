all: test test_float_slice test_sub test_from_arr cat

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

test_sub.o: test_sub.c slice.h
	$(CC) $(CFLAGS) -c $<

test_sub: test_sub.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

test_from_arr.o: test_from_arr.c slice.h
	$(CC) $(CFLAGS) -c $<

test_from_arr: test_from_arr.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

cat.o: cat.c slice.h
	$(CC) $(CFLAGS) -c $<

cat: cat.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@
