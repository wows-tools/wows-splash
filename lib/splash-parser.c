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

int wows_parse_splash(char *input, wows_splash **splash_content) {
    // Open the index file
    int fd = open(input, O_RDONLY);
    if (fd <= 0) {
        return -1;
    }
    wows_splash *splash = calloc(sizeof(wows_splash), 1);

    // Recover the file size
    struct stat s;
    fstat(fd, &s);

    /* index content size */
    size_t length = s.st_size;

    // Map the whole content in memory
    char *content = mmap(0, length, PROT_READ, MAP_PRIVATE, fd, 0);

    *splash_content = splash;
    close(fd);
    return 0;
}

int wows_splash_print(wows_splash *splash_content) {
    // TODO
    return 0;
}

int wows_splash_free(wows_splash *splash_content) {
    // TODO
    return 0;
}
