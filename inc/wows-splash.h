#include <stdint.h>

typedef struct {
    uint32_t name_len;
    char *name;
    // 192 bits of data, maybe 6 x 32 bits fields (int or float) describing an (hit)box (x y z dx dy dz);
    // Order of coordinates is unknown (don't trust the current names)
    float x;
    float y;
    float z;
    float dx;
    float dy;
    float dz;
} wows_splash_entry;

typedef struct {
    uint32_t entry_count;
    void *entry_map;             // struct *hashmap
    wows_splash_entry **entries; // array of entries
} wows_splash;

int wows_parse_splash(char *input, wows_splash **splash_content);
int wows_parse_splash_fp(FILE *input, wows_splash **splash_content);
int wows_splash_print(wows_splash *splash_content);
int wows_splash_free(wows_splash *splash_content);

// TODO
int wows_splash_get_entry_by_name(wows_splash *splash_content, char *entry_name, wows_splash_entry **entry);
