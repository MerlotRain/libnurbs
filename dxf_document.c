#include "dxf_document.h"

/* ------------------------------------ hash table ------------------------------------ */

struct hash_table *
hashtab_create(dxf_U32 (*hash)(struct hash_table *, dxf_POINTER),
               dxf_I32 (*compare)(struct hash_table *, dxf_POINTER, dxf_POINTER),
               dxf_I32 size) {
    return NULL;
}

dxf_I32 hashtab_insert(struct hash_table *ht, dxf_POINTER key, dxf_POINTER datum) {
    return 0;
}

dxf_POINTER hashtab_search(struct hash_table *ht, dxf_POINTER key) { return NULL; }

void hashtab_free(struct hash_table *ht) {}

/* ------------------------------------- link list ------------------------------------ */

struct link_list *list_create(void (*destroy_data)(dxf_POINTER)) { return NULL; }

void list_free(struct link_list *ls) {}

void list_insert(struct link_list *ls, dxf_POINTER data, dxf_U32 index) {}

dxf_POINTER list_data(struct link_list *ls, dxf_U32 index) { return NULL; }

/* -------------------------------- dxf document struct ------------------------------- */

void dxf_destroy_document(dxf_document_t *doc) {
    assert(doc);
#define FREE_POINTER(x)                                                                  \
    if (doc->x) {                                                                        \
        free(doc->x);                                                                    \
        doc->x = 0;                                                                      \
    }

    FREE_POINTER(vertices)
    FREE_POINTER(knots)
    FREE_POINTER(weights)
    FREE_POINTER(fitPoints)
    FREE_POINTER(leaderVertices)

#undef FREE_POINTER
    free(doc);
}
