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
               dxf_I32 size) {
    return NULL;
}

dxf_I32 hashtab_insert(struct hash_table *ht, dxf_POINTER key, dxf_POINTER datum) {
    return 0;
}

dxf_POINTER hashtab_search(struct hash_table *ht, dxf_POINTER key) { return NULL; }

void hashtab_free(struct hash_table *ht) {}

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

struct link_list *list_create(void (*destroy_data)(dxf_POINTER)) { return NULL; }

void list_free(struct link_list *ls) {}

void list_insert(struct link_list *ls, dxf_POINTER data, dxf_U32 index) {}

dxf_POINTER list_data(struct link_list *ls, dxf_U32 index) { return NULL; }

/* -------------------------------- dxf document struct ------------------------------- */
typedef struct dxf_document_t {
    enum Version version;

    dxf_CHAR polylineLayer[512];
    dxf_F64 *vertices;
    dxf_I32  maxVertices;
    dxf_I32  vertexIndex;

    dxf_F64 *knots;
    dxf_I32  maxKnots;
    dxf_I32  knotIndex;

    dxf_F64 *weights;
    dxf_I32  weightIndex;

    dxf_F64 *controlPoints;
    dxf_I32  maxControlPoints;
    dxf_I32  controlPointIndex;

    dxf_F64 *fitPoints;
    dxf_I32  maxFitPoints;
    dxf_I32  fitPointIndex;

    dxf_F64 *leaderVertices;
    dxf_I32  maxLeaderVertices;
    dxf_I32  leaderVertexIndex;

    dxf_BOOL            firstHatchLoop;
    dxf_hatch_edge_data hatchEdge;
    struct link_list  **hatchEdges; /* dxf_hatch_edge_data second rank pointer */

    dxf_BOOL xRecordValues;

    /* ...same as integer */
    dxf_U32 groupCode;
    /* Only the useful part of the group value */
    dxf_CHAR groupValue[DL_DXF_MAX_LINE];
    /* Current entity type */
    dxf_I32 currentObjectType;
    /* Value of the current setting */
    dxf_CHAR settingValue[DL_DXF_MAX_LINE + 1];
    /* Key of the current setting */
    dxf_CHAR settingKey[DL_DXF_MAX_LINE];
    /* Stores the group codes */
    struct hash_table *values;
    /* First call of this method. We initialize all group values in the first call. */
    dxf_BOOL firstCall;
    /* Attributes of the current entity (layer, color, width, line type) */
    dxf_attributes attrib;
    /* library version. hex: 0x20003001 = 2.0.3.1 */
    dxf_I32 libVersion;
    /* app specific dictionary handle: */
    dxf_U32 appDictionaryHandle;
    /* handle of standard text style, referenced by dim style: */
    dxf_U32 styleHandleStd;
} dxf_document_t;

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

#ifdef __cplusplus
}
#endif

#endif // DXF_DOCUMENT_H