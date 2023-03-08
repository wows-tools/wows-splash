#include <stdint.h>

typedef struct {
    uint32_t entry_count;
    void *entries; // struct *hashmap
} wows_splash;

typedef struct {
    uint32_t name_len;
    char *name;
    uint32_t
        data[6]; // 192 bits of data, maybe 6 x 32 bits fields (int or float) describing an (hit)box (x y z dx dy dz);
} wows_splash_entry;

int wows_parse_splash(char *input, wows_splash **splash_content);
int wows_splash_print(wows_splash *splash_content);
int wows_splash_free(wows_splash *splash_content);
