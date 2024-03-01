#include "dxf_document.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static dxf_BOOL strip_white_space(dxf_CHAR **s, dxf_BOOL strip_space) {
    dxf_I32 lastChar = strlen(*s) - 1;

    while ((lastChar >= 0) &&
           (((*s)[lastChar] == 10) || ((*s)[lastChar] == 13) ||
            (strip_space && ((*s)[lastChar] == ' ' || ((*s)[lastChar] == '\t'))))) {
        (*s)[lastChar] = '\0';
        lastChar--;
    }

    if (strip_space) {
        while ((*s)[0] == ' ' || (*s)[0] == '\t') {
            ++(*s);
        }
    }

    return ((*s) ? TRUE : FALSE);
}

static dxf_BOOL
get_stripped_line(dxf_CHAR *s, dxf_U32 size, FILE *fp, dxf_BOOL strip_space) {
    if (!feof(fp)) {
        dxf_CHAR *whole_line = (dxf_CHAR *)malloc(size);
        if (!whole_line)
            return FALSE;

        dxf_CHAR *line = fgets(whole_line, size, fp);
        if (line != NULL && line[0] != '\0') {
            strip_white_space(&line, strip_space);
            memcpy(s, line, strlen(line));
        }
        free(whole_line);
        return TRUE;
    }
    return FALSE;
}

static dxf_I32 to_dxf_I32(dxf_CHAR *str) {
    dxf_CHAR *p;
    return strtol(str, &p, 10);
}

static dxf_I32 to_dxf_I3216(dxf_CHAR *str) {
    dxf_CHAR *p;
    return strtol(str, &p, 16);
}
