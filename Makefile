all: test test_float_slice test_sub test_from_arr cat rev tac tac_value test_long_long_slice test_int_slice test_short

CC := gcc
CFLAGS := -Wpedantic -Wall -Werror -Wextra -O3

smalloc.o: smalloc.c smalloc.h
	$(CC) $(CFLAGS) -c $<

slice.o: slice.c slice.h
	$(CC) $(CFLAGS) -c $<

long_long_slice.o: long_long_slice.c long_long_slice.h slice.h
	$(CC) $(CFLAGS) -c $<

int_slice.o: int_slice.c int_slice.h slice.h
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

test_short.o: test_short.c slice.h short_slice.h
	$(CC) $(CFLAGS) -c $<

test_short: test_short.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

test_from_arr.o: test_from_arr.c slice.h
	$(CC) $(CFLAGS) -c $<

test_from_arr: test_from_arr.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

cat.o: cat.c slice.h
	$(CC) $(CFLAGS) -c $<

cat: cat.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

rev.o: rev.c slice.h
	$(CC) $(CFLAGS) -c $<

rev: rev.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

tac.o: tac.c slice.h
	$(CC) $(CFLAGS) -c $<

tac: tac.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

tac_value.o: tac_value.c slice.h
	$(CC) $(CFLAGS) -c $<

tac_value: tac_value.o slice.o smalloc.o
	$(CC) $(CFLAGS) $^ -o $@

test_long_long_slice.o: test_long_long_slice.c slice.h
	$(CC) $(CFLAGS) -c $<

test_long_long_slice: test_long_long_slice.o slice.o smalloc.o long_long_slice.o
	$(CC) $(CFLAGS) $^ -o $@

test_int_slice.o: test_int_slice.c slice.h
	$(CC) $(CFLAGS) -c $<

test_int_slice: test_int_slice.o slice.o smalloc.o int_slice.o
	$(CC) $(CFLAGS) $^ -o $@
