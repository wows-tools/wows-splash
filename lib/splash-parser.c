#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <libgen.h>
#include <linux/limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "wows-splash.h"
#include "hashmap.h"

int splash_entry_compare(const void *a, const void *b, void *udata) {
    const wows_splash_entry *ea = *(wows_splash_entry **)a;
    const wows_splash_entry *eb = *(wows_splash_entry **)b;
    return strcmp(ea->name, eb->name);
}

uint64_t splash_entry_hash(const void *item, uint64_t seed0, uint64_t seed1) {
    const wows_splash_entry *entry = *(wows_splash_entry **)item;
    return hashmap_sip(entry->name, strlen(entry->name), seed0, seed1);
}

int wows_parse_splash(char *input, wows_splash **splash_content) {
    int ret = 0;
    // Open the index file
    FILE *fp = fopen(input, "ro");
    if (fp <= 0) {
        return -1;
    }

    wows_splash *splash = calloc(sizeof(wows_splash), 1);

    splash->entries =
        hashmap_new(sizeof(wows_splash_entry **), 0, 0, 0, splash_entry_hash, splash_entry_compare, NULL, NULL);

    fread(&(splash->entry_count), sizeof(uint32_t), 1, fp);
    for (int i = 0; i < splash->entry_count; i++) {
        wows_splash_entry *entry = calloc(sizeof(wows_splash_entry), 1);
        fread(&(entry->name_len), sizeof(uint32_t), 1, fp);
        entry->name = calloc(sizeof(char), entry->name_len + 1);
        fread(entry->name, sizeof(char), entry->name_len, fp);
        fread(&(entry->data), sizeof(uint8_t), 24, fp);
        hashmap_set(splash->entries, &entry);
        wows_splash_entry_print(entry);
    }

    ret = feof(fp);
    *splash_content = splash;
    fclose(fp);
    return ret;
}

int wows_splash_print(wows_splash *splash_content) {
    // TODO
    return 0;
}

int wows_splash_entry_print(wows_splash_entry *entry) {
    printf("* name_len: %d\n", entry->name_len);
    printf("* name:     %s\n", entry->name);
    printf("* data:     ");
    for (int i = 0; i < 6; i++) {
        printf("0x%x ", entry->data[i]);
    }
    printf("\n");
}

int wows_splash_free(wows_splash *splash_content) {
    // TODO
    hashmap_free(splash_content->entries);
    free(splash_content);
    return 0;
}
