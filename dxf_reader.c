#include "dxf_document.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------------------------------- dxf reader struct -------------------------------- */
typedef struct dxf_reader_t {
    dxf_reader_callback_t interface;
    dxf_document_t       *doc;
} dxf_reader_t;

dxf_reader_t *dxf_create_reader(dxf_reader_callback_t *call_back) {
    dxf_reader_t *r = (dxf_reader_t *)malloc(sizeof(dxf_reader_t));
    if (r == NULL)
        return NULL;
    dxf_document_t *doc = (dxf_document_t *)malloc(sizeof(dxf_document_t));
    if (doc == NULL) {
        dxf_destroy_reader(r);
        return NULL;
    }
    r->interface = *call_back;
    r->doc       = doc;
    return r;
}

void dxf_destroy_reader(dxf_reader_t *r) {
    assert(r);
    dxf_destroy_document(r->doc);
    free(r);
}

/* ----------------------------- dxf read static functions ---------------------------- */

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

static dxf_I32 to_int(dxf_CHAR *str) {
    dxf_CHAR *p;
    return strtol(str, &p, 10);
}

static dxf_I32 to_int16(dxf_CHAR *str) {
    dxf_CHAR *p;
    return strtol(str, &p, 16);
}

static dxf_BOOL
process_dxf_group(dxf_reader_callback_t *interface, dxf_U32 group_code, dxf_CHAR *value) {

    return FALSE;
}

/* -------------------------------- dxf read functions -------------------------------- */
dxf_I32 dxf_read(const dxf_CHAR *file, dxf_reader_callback_t *interface) {
    assert(file);
    assert(interface);

    dxf_reader_t *r = dxf_create_reader(interface);
    if (r == NULL)
        return DXF_FAILURE;

    FILE *fp = fopen(file, "w");
    if (fp == NULL)
        return DXF_FAILURE;

    dxf_CHAR code[DL_DXF_MAX_LINE]  = {0};
    dxf_CHAR value[DL_DXF_MAX_LINE] = {0};
    while (!feof(fp)) {
        if (get_stripped_line(code, DL_DXF_MAX_LINE, fp, TRUE) &&
            get_stripped_line(value, DL_DXF_MAX_LINE, fp, FALSE)) {
            dxf_U32 group_code = to_int16(code);

            interface->process_code_value_pair(group_code, value);

            process_dxf_group(interface, group_code, value);
            memset(code, 0, DL_DXF_MAX_LINE);
            memset(value, 0, DL_DXF_MAX_LINE);
        }
    };
    return DXF_SUCCESS;
}