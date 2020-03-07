enum type {
    CHAR,
    LLINT,
    DOUBLE
};

union generic {
    char *c;
    long long *l;
    double *d;
};

struct slice {
    size_t len;
    enum type type;
    union generic array;
    size_t start;
    size_t end;
};

struct slice *init_slice(enum type type, size_t len);
void free_slice(struct slice *aslice);
void double_slice(struct slice *aslice);
void slice_append(struct slice *aslice, const void *item);
void print_slice(struct slice *aslice);
int main();
