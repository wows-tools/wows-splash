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

int wows_splash_entry_print(wows_splash_entry *entry) {
    printf("* name_len: %d\n", entry->name_len);
    printf("* name:     %s\n", entry->name);
    printf("* x:        %f\n", entry->x);
    printf("* y:        %f\n", entry->y);
    printf("* z:        %f\n", entry->z);
    printf("* dx:       %f\n", entry->dx);
    printf("* dy:       %f\n", entry->dy);
    printf("* dz:       %f\n", entry->dz);
    return 0;
}

int wows_splash_print(wows_splash *splash) {
    printf("* number_entries: %d\n", splash->entry_count);
    for (int i = 0; i < splash->entry_count; i++) {
        printf("====================\n");
        wows_splash_entry_print(splash->entries[i]);
    }
    return 0;
}

int wows_parse_splash(char *input, wows_splash **splash_content) {
    // TODO error handling in case the file is sketchy

    int ret = 0;

    // Open the index file
    FILE *fp = fopen(input, "ro");
    if (fp <= 0) {
        return -1;
    }

    wows_splash *splash = calloc(sizeof(wows_splash), 1);

    fread(&(splash->entry_count), sizeof(uint32_t), 1, fp);

    splash->entry_map =
        hashmap_new(sizeof(wows_splash_entry **), 0, 0, 0, splash_entry_hash, splash_entry_compare, NULL, NULL);

    splash->entries = calloc(sizeof(wows_splash_entry), splash->entry_count);

    for (int i = 0; i < splash->entry_count; i++) {
        wows_splash_entry *entry = calloc(sizeof(wows_splash_entry), 1);
        fread(&(entry->name_len), sizeof(uint32_t), 1, fp);
        entry->name = calloc(sizeof(char), entry->name_len + 1);
        fread(entry->name, sizeof(char), entry->name_len, fp);
        fread(&(entry->x), sizeof(float), 1, fp);
        fread(&(entry->y), sizeof(float), 1, fp);
        fread(&(entry->z), sizeof(float), 1, fp);
        fread(&(entry->dx), sizeof(float), 1, fp);
        fread(&(entry->dy), sizeof(float), 1, fp);
        fread(&(entry->dz), sizeof(float), 1, fp);
        hashmap_set(splash->entry_map, &entry);
        splash->entries[i] = entry;
    }

    ret = feof(fp);
    *splash_content = splash;
    fclose(fp);
    return ret;
}

int wows_splash_free(wows_splash *splash) {
    for (int i = 0; i < splash->entry_count; i++) {
        wows_splash_entry *entry = splash->entries[i];
        free(entry->name);
        free(entry);
    }
    free(splash->entries);
    hashmap_free(splash->entry_map);
    free(splash);
    return 0;
}
