#ifndef DXF_H
#define DXF_H

#include "dxf_codes.h"
#include "dxf_entities.h"

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off
#define DL_UNKNOWN                    0
#define DL_LAYER                     10
#define DL_BLOCK                     11
#define DL_ENDBLK                    12
#define DL_LINETYPE                  13
#define DL_STYLE                     20
#define DL_SETTING                   50
#define DL_ENTITY_POINT             100
#define DL_ENTITY_LINE              101
#define DL_ENTITY_POLYLINE          102
#define DL_ENTITY_LWPOLYLINE        103
#define DL_ENTITY_VERTEX            104
#define DL_ENTITY_SPLINE            105
#define DL_ENTITY_KNOT              106
#define DL_ENTITY_CONTROLPOINT      107
#define DL_ENTITY_ARC               108
#define DL_ENTITY_CIRCLE            109
#define DL_ENTITY_ELLIPSE           110
#define DL_ENTITY_INSERT            111
#define DL_ENTITY_TEXT              112
#define DL_ENTITY_MTEXT             113
#define DL_ENTITY_DIMENSION         114
#define DL_ENTITY_LEADER            115
#define DL_ENTITY_HATCH             116
#define DL_ENTITY_ATTRIB            117
#define DL_ENTITY_IMAGE             118
#define DL_ENTITY_IMAGEDEF          119
#define DL_ENTITY_TRACE             120
#define DL_ENTITY_SOLID             121
#define DL_ENTITY_3DFACE            122
#define DL_ENTITY_XLINE             123
#define DL_ENTITY_RAY               124
#define DL_ENTITY_ARCALIGNEDTEXT    125
#define DL_ENTITY_SEQEND            126
#define DL_XRECORD                  200
#define DL_DICTIONARY               210
// clang-format on

typedef struct __dxf_document dxf_document_t;
typedef struct __dxf_write dxf_write_t;

/* -------------------------------------------------------------------------- */
/*                           dxf document functions                           */
/* -------------------------------------------------------------------------- */

dxf_document_t *create_document();
dxf_write_t *out(dxf_document_t *doc, const char *filename);
void destroy_document(dxf_document_t *doc);
void destroy_write(dxf_write_t *w);

/* -------------------------------------------------------------------------- */
/*                             dxf write functions                            */
/* -------------------------------------------------------------------------- */

void write_dxf_real(dxf_write_t *w, int gc, double value);
void write_dxf_int(dxf_write_t *w, int gc, int value);
void write_dxf_bool(dxf_write_t *w, int gc, bool value);
void write_dxf_hex(dxf_write_t *w, int gc, int value);
void write_dxf_string(dxf_write_t *w, int gc, const char *value);

void write_header(dxf_document_t *doc, dxf_write_t *w);

void write_point(dxf_document_t *doc, dxf_write_t *w, dxf_point_data *data,
                 dxf_attributes *attr);
void write_line(dxf_document_t *doc, dxf_write_t *w, dxf_line_data *data,
                dxf_attributes *attr);
void write_xline(dxf_document_t *doc, dxf_write_t *w, dxf_xline_data *data,
                 dxf_attributes *attr);
void write_ray(dxf_document_t *doc, dxf_write_t *w, dxf_ray_data *data,
               dxf_attributes *attr);
void write_polyline(dxf_document_t *doc, dxf_write_t *w,
                    dxf_polyline_data *data, dxf_attributes *attr);
void write_vertex(dxf_document_t *doc, dxf_write_t *w, dxf_vertex_data *data);
void write_polyline_end(dxf_document_t *doc, dxf_write_t *w);
void write_spline(dxf_document_t *doc, dxf_write_t *w, dxf_spline_data *data,
                  dxf_attributes *attr);
void write_control_point(dxf_document_t *doc, dxf_write_t *w,
                         dxf_control_point_data *data);
void write_fit_point(dxf_document_t *doc, dxf_write_t *w,
                     dxf_fit_point_data *data);
void write_knot(dxf_document_t *doc, dxf_write_t *w, dxf_knot_data *data);
void write_circle(dxf_document_t *doc, dxf_write_t *w, dxf_circle_data *data,
                  dxf_attributes *attr);
void write_arc(dxf_document_t *doc, dxf_write_t *w, dxf_arc_data *data,
               dxf_attributes *attr);
void write_ellipse(dxf_document_t *doc, dxf_write_t *w, dxf_ellipse_data *data,
                   dxf_attributes *attr);
void write_solid(dxf_document_t *doc, dxf_write_t *w, dxf_solid_data *data,
                 dxf_attributes *attr);
void write_trace(dxf_document_t *doc, dxf_write_t *w, dxf_trace_data *data,
                 dxf_attributes *attr);
void write_3dFace(dxf_document_t *doc, dxf_write_t *w, dxf_3d_face_data *data,
                  dxf_attributes *attr);
void write_insert(dxf_document_t *doc, dxf_write_t *w, dxf_insert_data *data,
                  dxf_attributes *attr);
void write_mText(dxf_document_t *doc, dxf_write_t *w, dxf_mText_data *data,
                 dxf_attributes *attr);
void write_text(dxf_document_t *doc, dxf_write_t *w, dxf_text_data *data,
                dxf_attributes *attr);
void write_attribute(dxf_document_t *doc, dxf_write_t *w,
                     dxf_attribute_data *data, dxf_attributes *attr);
void write_dim_style_overrides(dxf_document_t *doc, dxf_write_t *w,
                               dxf_dimension_data *data);
void write_dim_aligned(dxf_document_t *doc, dxf_write_t *w,
                       dxf_dimension_data *data, dxf_dim_aligned_data *edata,
                       dxf_attributes *attr);
void write_dim_linear(dxf_document_t *doc, dxf_write_t *w,
                      dxf_dimension_data *data, dxf_dim_linear_data *edata,
                      dxf_attributes *attr);
void write_dim_radial(dxf_document_t *doc, dxf_write_t *w,
                      dxf_dimension_data *data, dxf_dim_radial_data *edata,
                      dxf_attributes *attr);
void write_dim_diametric(dxf_document_t *doc, dxf_write_t *w,
                         dxf_dimension_data *data,
                         dxf_dim_diametric_data *edata, dxf_attributes *attr);
void write_dim_angular2L(dxf_document_t *doc, dxf_write_t *w,
                         dxf_dimension_data *data,
                         dxf_dim_angular2L_data *edata, dxf_attributes *attr);
void write_dim_angular3P(dxf_document_t *doc, dxf_write_t *w,
                         dxf_dimension_data *data,
                         dxf_dim_angular3P_data *edata, dxf_attributes *attr);
void write_dim_ordinate(dxf_document_t *doc, dxf_write_t *w,
                        dxf_dimension_data *data, dxf_dim_ordinate_data *edata,
                        dxf_attributes *attr);
void write_leader(dxf_document_t *doc, dxf_write_t *w, dxf_leader_data *data,
                  dxf_attributes *attr);
void write_leader_vertex(dxf_document_t *doc, dxf_write_t *w,
                         dxf_leader_vertex_data *data);
void write_leader_end(dxf_document_t *doc, dxf_write_t *w,
                      dxf_leader_data *data);
void write_hatch1(dxf_document_t *doc, dxf_write_t *w, dxf_hatch_data *data,
                  dxf_attributes *attr);
void write_hatch2(dxf_document_t *doc, dxf_write_t *w, dxf_hatch_data *data,
                  dxf_attributes *attr);
void write_hatch_loop1(dxf_document_t *doc, dxf_write_t *w,
                       dxf_hatch_loop_data *data);
void write_hatch_loop2(dxf_document_t *doc, dxf_write_t *w,
                       dxf_hatch_loop_data *data);
void write_hatch_edge(dxf_document_t *doc, dxf_write_t *w,
                      dxf_hatch_edge_data *data);

unsigned long write_image(dxf_document_t *doc, dxf_write_t *w,
                          dxf_image_data *data, dxf_attributes *attr);

void write_image_def(dxf_document_t *doc, dxf_write_t *w, int handle,
                     dxf_image_data *data);

void write_layer(dxf_document_t *doc, dxf_write_t *w, dxf_layer_data *data,
                 dxf_attributes *attr);

void write_line_type(dxf_document_t *doc, dxf_write_t *w,
                     dxf_line_type_data *data);

void write_appid(dxf_document_t *doc, dxf_write_t *w, const char *name);

void write_block(dxf_document_t *doc, dxf_write_t *w, dxf_block_data *data);
void write_end_block(dxf_document_t *doc, dxf_write_t *w, const char *name);

void write_view_port(dxf_document_t *doc, dxf_write_t *w);
void write_style(dxf_document_t *doc, dxf_write_t *w, dxf_style_data *style);
void write_view(dxf_document_t *doc, dxf_write_t *w);
void write_ucs(dxf_document_t *doc, dxf_write_t *w);
void write_dim_style(dxf_document_t *doc, dxf_write_t *w, double dimasz,
                     double dimexe, double dimexo, double dimgap, double dimtxt,
                     int dimtad, bool dimtih);
void write_block_record(dxf_document_t *doc, dxf_write_t *w, const char *name);
void write_objects(dxf_document_t *doc, dxf_write_t *w,
                   const char *appDictionaryName);
void write_app_dictionary(dxf_document_t *doc, dxf_write_t *w);
unsigned long write_dictionary_entry(dxf_document_t *doc, dxf_write_t *w,
                                     const char *name);
void write_x_record_int(dxf_document_t *doc, dxf_write_t *w, int handle, int value);
void write_x_record_double(dxf_document_t *doc, dxf_write_t *w, int handle,
                    double value);
void write_x_record_boolean(dxf_document_t *doc, dxf_write_t *w, int handle,
                    bool value);
void write_x_record_string(dxf_document_t *doc, dxf_write_t *w, int handle,
                    const char *value);
void write_objects_end(dxf_document_t *doc, dxf_write_t *w);

void write_comment(dxf_document_t *doc, dxf_write_t *w, const char *comment);

/* -------------------------------------------------------------------------- */
/*                                reader struct                               */
/* -------------------------------------------------------------------------- */
typedef struct {
  void (*end_section)();
  void (*add_layer)(dxf_layer_data *);
  void (*add_line_type)(dxf_line_type_data *);
  void (*add_line_type_dash)(double);
  void (*add_block)(dxf_block_data *);
  void (*end_block)();
  void (*add_text_style)(dxf_style_data *);
  void (*add_point)(dxf_point_data *);
  void (*add_line)(dxf_line_data *);
  void (*add_xline)(dxf_xline_data *);
  void (*add_ray)(dxf_ray_data *);

  void (*add_arc)(dxf_arc_data *);
  void (*add_circle)(dxf_circle_data *);
  void (*add_ellipse)(dxf_ellipse_data *);

  void (*add_polyline)(dxf_polyline_data *);
  void (*add_vertex)(dxf_vertex_data *);

  void (*add_spline)(dxf_spline_data *);
  void (*add_control_point)(dxf_control_point_data *);
  void (*add_fit_point)(dxf_fit_point_data *);
  void (*add_knot)(dxf_knot_data *);

  void (*add_insert)(dxf_insert_data *);

  void (*add_mText)(dxf_mText_data *);
  void (*add_mText_chunk)(const char *);
  void (*add_text)(dxf_text_data *);
  void (*add_arc_aligned_text)(dxf_arc_aligned_text_data *);
  void (*add_attribute)(dxf_attribute_data *);

  void (*add_dim_align)(dxf_dimension_data *, const dxf_dim_aligned_data *);
  void (*add_dim_linear)(dxf_dimension_data *, const dxf_dim_linear_data *);
  void (*add_dim_radial)(dxf_dimension_data *, const dxf_dim_radial_data *);
  void (*add_dim_diametric)(dxf_dimension_data *,
                            const dxf_dim_diametric_data *);
  void (*add_dim_angular)(dxf_dimension_data *, const dxf_dim_angular2L_data *);
  void (*add_dim_angular3P)(dxf_dimension_data *,
                            const dxf_dim_angular3P_data *);
  void (*add_dim_ordinate)(dxf_dimension_data *, const dxf_dim_ordinate_data *);
  void (*add_leader)(dxf_leader_data *);
  void (*add_leader_vertex)(dxf_leader_vertex_data *);

  void (*add_hatch)(dxf_hatch_data *);

  void (*add_trace)(dxf_trace_data *);
  void (*add_3dFace)(dxf_3d_face_data *);
  void (*add_solid)(dxf_solid_data *);

  void (*add_image)(dxf_image_data *);
  void (*link_image)(dxf_image_def_data *);
  void (*add_hatch_loop)(dxf_hatch_loop_data *);
  void (*add_hatch_edge)(dxf_hatch_edge_data *);

  void (*add_x_record)(const char *);
  void (*add_x_record_string)(int, const char *);
  void (*add_x_record_real)(int, double);
  void (*add_x_record_int)(int, int);
  void (*add_x_record_bool)(int, bool);

  void (*add_x_data_app)(const char *);
  void (*add_x_data_string)(int, const char *);
  void (*add_x_data_real)(int, double);
  void (*add_x_data_int)(int, int);

  void (*add_dictionary)(dxf_dictionary_data *);
  void (*add_dictionary_entry)(dxf_dictionary_entry_data *);

  void (*end_entity)();

  void (*add_comment)(const char *);

  void (*set_variable_vector)(const char *, double, double, double, int);
  void (*set_variable_string)(const char *, const char *, int);
  void (*set_variable_int)(const char *, int, int);
  void (*set_variable_double)(const char *, double, int);

  void (*end_sequence)();
} dxf_reader_t;

#ifdef __cplusplus
}
#endif

#endif // DXF_H