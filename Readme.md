# Slice

A Go slice-inspired library for easy, memory-safe slice manipulation in C.

## Introduction

I'm a big C fan, but I can't help but be impresed by Go's slices. They automatically manage
buffer capacity and the starts and ends of arrays such that you don't have to think about
memory when you're using one. It's a nice, lightweight abstraction that C can really use.
This library fills that niche for C.

## Dependencies

```
make
gcc
```

## Installation

This library is written in portable ANSI C99. It should be possible to build with

```sh
make
```

## Usage

### Initialization

Each slice contains a pointer to an array, plus the start and end positions of
data in the array, the length of the array, and the width of items in the
array. A new slice can be initialized as follows:

```c
struct slice * my_slice = init_slice(len, item_width)
```

This generates a new slice with the start and end positions set to 0, and a
buffer capacity of `len`. The item width refers to the number of bytes used by
the array member, and is stored so that the slice can correctly index items in
the array.

### Adding to the slice

Append new items one at a time to the slice using the following function invocation:

```c
double a = 3.5;
slice_append(my_slice, &a)
```

Or, extend the slice by multiple elements that are contiguous in an array using the following:

```c
double b[] = {3.5, 7,8, 9.3}
slice_extend(my_slice, &b[0], 3)
```

### Extracting elements from a slice

Extract a single element with the `slice_pop1` function:

```c
double a;
slice_pop1(a, my_slice, 2)
```

Extract multiple contiguous elements to an array with  the `slice_extract` function:

```c
double a;
slice_extract(b, my_slice, 1, 2)
```

### Sub-slices

Slices initialized with `init_slice` are the owners of their respective arrays. These are
generated by `malloc` and must be freed before release using `free_slice`. Alternatively,
slices may index other slices. These sub-slices are stack-allocated and do not need to be
freed. Slices of this type are read-only and should not be used to alter the contents of the array
that they point to. All sub-slices are considered children of the parent slice from which they are
created. The field `.parent` in a slice contains a pointer to the parent if the slice is a child,
or a pointer to `NULL` if the slice is the owner of the array.

```c
struct slice my_sub_slice = sub_slice(my_slice, 1, 3) {
```

### Printing a slice

To print the full contents of a slice, simply provide a pointer to the slice and a
function pointer for printing an individual element of the slice:

```c
void print_double(void *d) {
    double d2;
    memcpy(&d2, d, sizeof(double));
    printf("%10lg", d2);
}

print_slice(myslice, print_double);
```

Alternatively, to print the entire contents of a slice, including all indexes and pointers, for debugging,
use the following invocation:

```c
introspect_slice(myslice, print_double);
```

### A full example

To make an array of `double`s, the following code is acceptable:

```c
#include "slice_void.h"

int main() {
    double d[] = {1.5, 3.7, 3.8, 9.9, 10.10};
    struct slice my_slice = init_slice(3, sizeof(double));
    double d2[10];
    
    slice_extend(&my_slice, &d[0], 5);
    struct slice my_subslice = sub_slice(my_slice, 1, 4);
    
    print_slice(my_slice, print_double);
    print_slice(my_subslice, print_double);
    
    slice_extract(&d2[0], my_subslice, 1, 1);
    printf("%lg\n", d2[0]);
    
    free_slice(my_slice);
}
```

This should produce the following output:

```
	1.5	3.7	3.8	9.9	10.10
	3.7	3.8	9.9
3.8
```
