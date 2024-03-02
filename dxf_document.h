#ifndef DXF_DOCUMENT_H
#define DXF_DOCUMENT_H

#include "dxf.h"

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------ hash table ------------------------------------ */
struct hashtab_node {
    void                *key;
    void                *datum;
    struct hashtab_node *next;
};

struct hash_table {
    struct hashtab_node **htable;
    dxf_U32               size;
    dxf_U32               nel;
    dxf_U32 (*hash)(struct hash_table *, void *);
    dxf_I32 (*compare)(struct hash_table *, void *key1, void *key2);
};

struct hash_table *
hashtab_create(dxf_U32 (*hash)(struct hash_table *, void *),
               dxf_I32 (*compare)(struct hash_table *, void *key1, void *key2),
               dxf_I32 size) {
    return NULL;
}

dxf_I32 hashtab_insert(struct hash_table *ht, void *key, void *datum) { return 0; }

void *hashtab_search(struct hash_table *ht, void *key) { return NULL; }

void hashtab_free(struct hash_table *ht) {}

/* -------------------------------- dxf document struct ------------------------------- */
typedef struct dxf_document_t {
    enum Version version;

    const dxf_CHAR *polylineLayer;
    dxf_F64        *vertices;
    dxf_I32         maxVertices;
    dxf_I32         vertexIndex;

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

    dxf_BOOL                     firstHatchLoop;
    struct dxf_hatch_edge_data   hatchEdge;
    struct dxf_hatch_edge_data **hatchEdges;

    const dxf_CHAR *xRecordHandle;
    dxf_BOOL        xRecordValues;

    // Only the useful part of the group code
    const dxf_CHAR *groupCodeTmp;
    // ...same as integer
    dxf_U32 groupCode;
    // Only the useful part of the group value
    const dxf_CHAR *groupValue;
    // Current entity type
    dxf_I32 currentObjectType;
    // Value of the current setting
    dxf_CHAR settingValue[DL_DXF_MAX_LINE + 1];
    // Key of the current setting
    const dxf_CHAR *settingKey;
    // Stores the group codes
    struct hash_table *values;
    // First call of this method. We initialize all group values in
    //  the first call.
    dxf_BOOL firstCall;
    // Attributes of the current entity (layer, color, width, line type)
    struct dxf_attributes attrib;
    // library version. hex: 0x20003001 = 2.0.3.1
    dxf_I32 libVersion;
    // app specific dictionary handle:
    dxf_U32 appDictionaryHandle;
    // handle of standard text style, referenced by dim style:
    dxf_U32 styleHandleStd;
} dxf_document_t;

#ifdef __cplusplus
}
#endif

#endif // DXF_DOCUMENT_H