#include <stdint.h>

typedef struct {
    uint32_t entry_count;
    void *entries; // struct *hashmap
} wows_splash;

typedef struct {
    uint32_t name_len;
    char *name;
    uint8_t data[24]; // 192 bits of data, maybe 3 x 64 bits fields
} wows_splash_entry;

int wows_parse_splash(char *input, wows_splash **splash_content);
int wows_splash_print(wows_splash *splash_content);
int wows_splash_free(wows_splash *splash_content);
