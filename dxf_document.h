#ifndef DXF_DOCUMENT_H
#define DXF_DOCUMENT_H

#include "dxf.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------ hash table ------------------------------------ */
struct hashtab_node {
    dxf_POINTER          key;
    dxf_POINTER          datum;
    struct hashtab_node *next;
};

struct hash_table {
    struct hashtab_node **htable;
    dxf_U32               size;
    dxf_U32               nel;
    dxf_U32 (*hash)(struct hash_table *, dxf_POINTER);
    dxf_I32 (*compare)(struct hash_table *, dxf_POINTER, dxf_POINTER);
};

struct hash_table *
hashtab_create(dxf_U32 (*hash)(struct hash_table *, dxf_POINTER),
               dxf_I32 (*compare)(struct hash_table *, dxf_POINTER, dxf_POINTER),
               dxf_I32 size);

dxf_I32 hashtab_insert(struct hash_table *ht, dxf_POINTER key, dxf_POINTER datum);

dxf_POINTER hashtab_search(struct hash_table *ht, dxf_POINTER key);

void hashtab_free(struct hash_table *ht);

/* ------------------------------------- link list ------------------------------------ */

struct list_node {
    dxf_POINTER       data;
    struct list_node *next;
};

struct link_list {
    dxf_U32           size;
    struct list_node *head;
    void (*destroy_data)(dxf_POINTER);
};

struct link_list *list_create(void (*destroy_data)(dxf_POINTER));

void list_free(struct link_list *ls);

void list_insert(struct link_list *ls, dxf_POINTER data, dxf_U32 index);

dxf_POINTER list_data(struct link_list *ls, dxf_U32 index);

void dxf_destroy_document(dxf_document_t *doc);

#ifdef __cplusplus
}
#endif

#endif // DXF_DOCUMENT_H