#include "dxf.h"
#include <stdint.h>
#include <stdio.h>

/* -------------------------------------------------------------------------- */
/*                                 hash table                                 */
/* -------------------------------------------------------------------------- */
struct hashtab_node {
  void *key;
  void *datum;
  struct hashtab_node *next;
};

struct hash_table {
  struct hashtab_node **htable;
  uint32_t size;
  uint32_t nel;
  uint32_t (*hash)(struct hash_table *, void *);
  int32_t (*compare)(struct hash_table *, void *key1, void *key2);
};

struct hash_table *hashtab_create(uint32_t (*hash)(struct hash_table *, void *),
                                  int32_t (*compare)(struct hash_table *,
                                                     void *key1, void *key2),
                                  int32_t size);
int hashtab_insert(struct hash_table *ht, void *key, void *datum);
void *hashtab_search(struct hash_table *ht, void *key);
void hashtab_free(struct hash_table *ht);

/* -------------------------------------------------------------------------- */
/*                             dxf document struct                            */
/* -------------------------------------------------------------------------- */
struct __dxf_document {
  enum Version version;

  const char *polylineLayer;
  double *vertices;
  int maxVertices;
  int vertexIndex;

  double *knots;
  int maxKnots;
  int knotIndex;

  double *weights;
  int weightIndex;

  double *controlPoints;
  int maxControlPoints;
  int controlPointIndex;

  double *fitPoints;
  int maxFitPoints;
  int fitPointIndex;

  double *leaderVertices;
  int maxLeaderVertices;
  int leaderVertexIndex;

  bool firstHatchLoop;
  struct dxf_hatch_edge_data hatchEdge;
  struct dxf_hatch_edge_data **hatchEdges;

  const char *xRecordHandle;
  bool xRecordValues;

  // Only the useful part of the group code
  const char *groupCodeTmp;
  // ...same as integer
  unsigned int groupCode;
  // Only the useful part of the group value
  const char *groupValue;
  // Current entity type
  int currentObjectType;
  // Value of the current setting
  char settingValue[DL_DXF_MAX_LINE + 1];
  // Key of the current setting
  const char *settingKey;
  // Stores the group codes
  struct hash_table *values;
  // First call of this method. We initialize all group values in
  //  the first call.
  bool firstCall;
  // Attributes of the current entity (layer, color, width, line type)
  struct dxf_attributes attrib;
  // library version. hex: 0x20003001 = 2.0.3.1
  int libVersion;
  // app specific dictionary handle:
  unsigned long appDictionaryHandle;
  // handle of standard text style, referenced by dim style:
  unsigned long styleHandleStd;
};

/* -------------------------------------------------------------------------- */
/*                              dxf write struct                              */
/* -------------------------------------------------------------------------- */
struct __dxf_write {
  FILE *fp;
  enum Version version;
  unsigned long m_handle;
  unsigned long modelSpaceHandle;
  unsigned long paperSpaceHandle;
  unsigned long paperSpace0Handle
};

/* -------------------------------------------------------------------------- */
/*                            dxf document function                           */
/* -------------------------------------------------------------------------- */

dxf_document_t *create_document() { return NULL; }

dxf_write_t *out(dxf_document_t *doc, const char *filename) { return NULL; }

void destroy_document(dxf_document_t *doc) {}

void destroy_write(dxf_write_t *w) {}

/* -------------------------------------------------------------------------- */
/*                             dxf write function                             */
/* -------------------------------------------------------------------------- */
void write_dxf_real(dxf_write_t *w, int gc, double value) {}

void write_dxf_int(dxf_write_t *w, int gc, int value) {}

void write_dxf_bool(dxf_write_t *w, int gc, bool value) {}

void write_dxf_hex(dxf_write_t *w, int gc, int value) {}

void write_dxf_string(dxf_write_t *w, int gc, const char *value) {}

void write_header(dxf_document_t *doc, dxf_write_t *w) {}

void write_point(dxf_document_t *doc, dxf_write_t *w, dxf_point_data *data,
                 dxf_attributes *attr) {}

void write_line(dxf_document_t *doc, dxf_write_t *w, dxf_line_data *data,
                dxf_attributes *attr) {}

void write_xline(dxf_document_t *doc, dxf_write_t *w, dxf_xline_data *data,
                 dxf_attributes *attr) {}

void write_ray(dxf_document_t *doc, dxf_write_t *w, dxf_ray_data *data,
               dxf_attributes *attr) {}

void write_polyline(dxf_document_t *doc, dxf_write_t *w,
                    dxf_polyline_data *data, dxf_attributes *attr) {}

void write_vertex(dxf_document_t *doc, dxf_write_t *w, dxf_vertex_data *data) {}

void write_polyline_end(dxf_document_t *doc, dxf_write_t *w) {}

void write_spline(dxf_document_t *doc, dxf_write_t *w, dxf_spline_data *data,
                  dxf_attributes *attr) {}

void write_control_point(dxf_document_t *doc, dxf_write_t *w,
                         dxf_control_point_data *data) {}

void write_fit_point(dxf_document_t *doc, dxf_write_t *w,
                     dxf_fit_point_data *data) {}

void write_knot(dxf_document_t *doc, dxf_write_t *w, dxf_knot_data *data) {}

void write_circle(dxf_document_t *doc, dxf_write_t *w, dxf_circle_data *data,
                  dxf_attributes *attr) {}

void write_arc(dxf_document_t *doc, dxf_write_t *w, dxf_arc_data *data,
               dxf_attributes *attr) {}

void write_ellipse(dxf_document_t *doc, dxf_write_t *w, dxf_ellipse_data *data,
                   dxf_attributes *attr) {}

void write_solid(dxf_document_t *doc, dxf_write_t *w, dxf_solid_data *data,
                 dxf_attributes *attr) {}

void write_trace(dxf_document_t *doc, dxf_write_t *w, dxf_trace_data *data,
                 dxf_attributes *attr) {}

void write_3dFace(dxf_document_t *doc, dxf_write_t *w, dxf_3d_face_data *data,
                  dxf_attributes *attr) {}

void write_insert(dxf_document_t *doc, dxf_write_t *w, dxf_insert_data *data,
                  dxf_attributes *attr) {}

void write_mText(dxf_document_t *doc, dxf_write_t *w, dxf_mText_data *data,
                 dxf_attributes *attr) {}

void write_text(dxf_document_t *doc, dxf_write_t *w, dxf_text_data *data,
                dxf_attributes *attr) {}

void write_attribute(dxf_document_t *doc, dxf_write_t *w,
                     dxf_attribute_data *data, dxf_attributes *attr) {}

void write_dim_style_overrides(dxf_document_t *doc, dxf_write_t *w,
                               dxf_dimension_data *data) {}

void write_dim_aligned(dxf_document_t *doc, dxf_write_t *w,
                       dxf_dimension_data *data, dxf_dim_aligned_data *edata,
                       dxf_attributes *attr) {}

void write_dim_linear(dxf_document_t *doc, dxf_write_t *w,
                      dxf_dimension_data *data, dxf_dim_linear_data *edata,
                      dxf_attributes *attr) {}

void write_dim_radial(dxf_document_t *doc, dxf_write_t *w,
                      dxf_dimension_data *data, dxf_dim_radial_data *edata,
                      dxf_attributes *attr) {}

void write_dim_diametric(dxf_document_t *doc, dxf_write_t *w,
                         dxf_dimension_data *data,
                         dxf_dim_diametric_data *edata, dxf_attributes *attr) {}

void write_dim_angular2L(dxf_document_t *doc, dxf_write_t *w,
                         dxf_dimension_data *data,
                         dxf_dim_angular2L_data *edata, dxf_attributes *attr) {}

void write_dim_angular3P(dxf_document_t *doc, dxf_write_t *w,
                         dxf_dimension_data *data,
                         dxf_dim_angular3P_data *edata, dxf_attributes *attr) {}

void write_dim_ordinate(dxf_document_t *doc, dxf_write_t *w,
                        dxf_dimension_data *data, dxf_dim_ordinate_data *edata,
                        dxf_attributes *attr) {}

void write_leader(dxf_document_t *doc, dxf_write_t *w, dxf_leader_data *data,
                  dxf_attributes *attr) {}

void write_leader_vertex(dxf_document_t *doc, dxf_write_t *w,
                         dxf_leader_vertex_data *data) {}

void write_leader_end(dxf_document_t *doc, dxf_write_t *w,
                      dxf_leader_data *data) {}

void write_hatch1(dxf_document_t *doc, dxf_write_t *w, dxf_hatch_data *data,
                  dxf_attributes *attr) {}

void write_hatch2(dxf_document_t *doc, dxf_write_t *w, dxf_hatch_data *data,
                  dxf_attributes *attr) {}

void write_hatch_loop1(dxf_document_t *doc, dxf_write_t *w,
                       dxf_hatch_loop_data *data) {}

void write_hatch_loop2(dxf_document_t *doc, dxf_write_t *w,
                       dxf_hatch_loop_data *data) {}

void write_hatch_edge(dxf_document_t *doc, dxf_write_t *w,
                      dxf_hatch_edge_data *data) {}

unsigned long write_image(dxf_document_t *doc, dxf_write_t *w,
                          dxf_image_data *data, dxf_attributes *attr) {
  return 0;
}

void write_image_def(dxf_document_t *doc, dxf_write_t *w, int handle,
                     dxf_image_data *data) {}

void write_layer(dxf_document_t *doc, dxf_write_t *w, dxf_layer_data *data,
                 dxf_attributes *attr) {}

void write_line_type(dxf_document_t *doc, dxf_write_t *w,
                     dxf_line_type_data *data) {}

void write_appid(dxf_document_t *doc, dxf_write_t *w, const char *name) {}

void write_block(dxf_document_t *doc, dxf_write_t *w, dxf_block_data *data) {}

void write_end_block(dxf_document_t *doc, dxf_write_t *w, const char *name) {}

void write_view_port(dxf_document_t *doc, dxf_write_t *w) {}

void write_style(dxf_document_t *doc, dxf_write_t *w, dxf_style_data *style) {}

void write_view(dxf_document_t *doc, dxf_write_t *w) {}

void write_ucs(dxf_document_t *doc, dxf_write_t *w) {}

void write_dim_style(dxf_document_t *doc, dxf_write_t *w, double dimasz,
                     double dimexe, double dimexo, double dimgap, double dimtxt,
                     int dimtad, bool dimtih) {}

void write_block_record(dxf_document_t *doc, dxf_write_t *w) {}

void write_block_record(dxf_document_t *doc, dxf_write_t *w, const char *name) {
}

void write_objects(dxf_document_t *doc, dxf_write_t *w,
                   const char *appDictionaryName) {}

void write_app_dictionary(dxf_document_t *doc, dxf_write_t *w) {}

unsigned long write_dictionary_entry(dxf_document_t *doc, dxf_write_t *w,
                                     const char *name) {
  return 0;
}

void write_x_record(dxf_document_t *doc, dxf_write_t *w, int handle,
                    int value) {}

void write_x_record(dxf_document_t *doc, dxf_write_t *w, int handle,
                    double value) {}

void write_x_record(dxf_document_t *doc, dxf_write_t *w, int handle,
                    bool value) {}

void write_x_record(dxf_document_t *doc, dxf_write_t *w, int handle,
                    const char *value) {}

void write_objects_end(dxf_document_t *doc, dxf_write_t *w) {}

void write_comment(dxf_document_t *doc, dxf_write_t *w, const char *comment) {}

/* -------------------------------------------------------------------------- */
/*                            hash table functions                            */
/* -------------------------------------------------------------------------- */

struct hash_table *hashtab_create(uint32_t (*hash)(struct hash_table *, void *),
                                  int32_t (*compare)(struct hash_table *,
                                                     void *key1, void *key2),
                                  int32_t size) {
  return NULL;
}

int hashtab_insert(struct hash_table *ht, void *key, void *datum) { return 0; }

void *hashtab_search(struct hash_table *ht, void *key) { return NULL; }

void hashtab_free(struct hash_table *ht) {}
