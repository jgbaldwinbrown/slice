struct slice {
    size_t len;
    size_t item_width;
    char *array;
    size_t start;
    size_t end;
};

struct slice *init_slice(size_t len, size_t item_width);
void free_slice(struct slice *aslice);
void double_slice(struct slice *aslice);
void slice_append(struct slice *aslice, const void *item);
void slice_extend(struct slice *aslice, const void *item, size_t nmemb);
void print_slice(struct slice *aslice, void (*fp) (void *));
int main();
