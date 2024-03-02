#include "dxf.h"
#include "dxf_document.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------------------------------- dxf writer struct -------------------------------- */
struct dxf_writer_t {
    FILE           *fp;
    enum Version    version;
    dxf_U32         m_handle;
    dxf_U32         modelSpaceHandle;
    dxf_U32         paperSpaceHandle;
    dxf_U32         paperSpace0Handle;
    dxf_document_t *doc;
};

/* ------------------------------- dxf write functions -------------------------------- */

dxf_I32 dxf_create_writer(dxf_writer_t **w, const dxf_CHAR *filename) { return 1; }

dxf_I32 dxf_destroy_writer(dxf_writer_t *w) { return 1; }

dxf_I32 dxf_write_real(dxf_writer_t *w, dxf_I32 gc, dxf_F64 value) { return 1; }

dxf_I32 dxf_write_int(dxf_writer_t *w, dxf_I32 gc, dxf_I32 value) { return 1; }

dxf_I32 dxf_write_boolean(dxf_writer_t *w, dxf_I32 gc, dxf_BOOL value) { return 1; }

dxf_I32 dxf_write_hex(dxf_writer_t *w, dxf_I32 gc, dxf_I32 value) { return 1; }

dxf_I32 dxf_write_string(dxf_writer_t *w, dxf_I32 gc, const dxf_CHAR *value) { return 1; }

dxf_I32 dxf_write_header(dxf_writer_t *w) { return 1; }

dxf_I32
dxf_write_point(dxf_writer_t *w, const dxf_point_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32
dxf_write_line(dxf_writer_t *w, const dxf_line_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32
dxf_write_xline(dxf_writer_t *w, const dxf_xline_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32
dxf_write_ray(dxf_writer_t *w, const dxf_ray_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32 dxf_write_polyline(dxf_writer_t            *w,
                           const dxf_polyline_data *data,
                           const dxf_attributes    *attr) {
    return 1;
}

dxf_I32 dxf_write_vertex(dxf_writer_t *w, const dxf_vertex_data *data) { return 1; }

dxf_I32 dxf_write_polyline_end(dxf_writer_t *w) { return 1; }

dxf_I32 dxf_write_spline(dxf_writer_t          *w,
                         const dxf_spline_data *data,
                         const dxf_attributes  *attr) {
    return 1;
}

dxf_I32 dxf_write_control_point(dxf_writer_t *w, const dxf_control_point_data *data) {
    return 1;
}

dxf_I32 dxf_write_fit_point(dxf_writer_t *w, const dxf_fit_point_data *data) { return 1; }

dxf_I32 dxf_write_knot(dxf_writer_t *w, const dxf_knot_data *data) { return 1; }

dxf_I32 dxf_write_circle(dxf_writer_t          *w,
                         const dxf_circle_data *data,
                         const dxf_attributes  *attr) {
    return 1;
}

dxf_I32
dxf_write_arc(dxf_writer_t *w, const dxf_arc_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32 dxf_write_ellipse(dxf_writer_t           *w,
                          const dxf_ellipse_data *data,
                          const dxf_attributes   *attr) {
    return 1;
}

dxf_I32
dxf_write_solid(dxf_writer_t *w, const dxf_solid_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32
dxf_write_trace(dxf_writer_t *w, const dxf_trace_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32 dxf_write_3dFace(dxf_writer_t           *w,
                         const dxf_3d_face_data *data,
                         const dxf_attributes   *attr) {
    return 1;
}

dxf_I32 dxf_write_insert(dxf_writer_t          *w,
                         const dxf_insert_data *data,
                         const dxf_attributes  *attr) {
    return 1;
}

dxf_I32
dxf_write_mText(dxf_writer_t *w, const dxf_mText_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32
dxf_write_text(dxf_writer_t *w, const dxf_text_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32 dxf_write_attribute(dxf_writer_t             *w,
                            const dxf_attribute_data *data,
                            const dxf_attributes     *attr) {
    return 1;
}

dxf_I32 dxf_write_dim_style_overrides(dxf_writer_t *w, const dxf_dimension_data *data) {
    return 1;
}

dxf_I32 dxf_write_dim_aligned(dxf_writer_t               *w,
                              const dxf_dimension_data   *data,
                              const dxf_dim_aligned_data *edata,
                              const dxf_attributes       *attr) {
    return 1;
}

dxf_I32 dxf_write_dim_linear(dxf_writer_t         *w,
                             dxf_dimension_data   *data,
                             dxf_dim_linear_data  *edata,
                             const dxf_attributes *attr) {
    return 1;
}

dxf_I32 dxf_write_dim_radial(dxf_writer_t              *w,
                             const dxf_dimension_data  *data,
                             const dxf_dim_radial_data *edata,
                             const dxf_attributes      *attr) {
    return 1;
}

dxf_I32 dxf_write_dim_diametric(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_diametric_data *edata,
                                const dxf_attributes         *attr) {
    return 1;
}

dxf_I32 dxf_write_dim_angular2L(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_angular2L_data *edata,
                                const dxf_attributes         *attr) {
    return 1;
}

dxf_I32 dxf_write_dim_angular3P(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_angular3P_data *edata,
                                const dxf_attributes         *attr) {
    return 1;
}

dxf_I32 dxf_write_dim_ordinate(dxf_writer_t                *w,
                               const dxf_dimension_data    *data,
                               const dxf_dim_ordinate_data *edata,
                               const dxf_attributes        *attr) {
    return 1;
}

dxf_I32 dxf_write_leader(dxf_writer_t          *w,
                         const dxf_leader_data *data,
                         const dxf_attributes  *attr) {
    return 1;
}

dxf_I32 dxf_write_leader_vertex(dxf_writer_t *w, const dxf_leader_vertex_data *data) {
    return 1;
}

dxf_I32 dxf_write_leader_end(dxf_writer_t *w, const dxf_leader_data *data) { return 1; }

dxf_I32 dxf_write_hatch1(dxf_writer_t         *w,
                         const dxf_hatch_data *data,
                         const dxf_attributes *attr) {
    return 1;
}

dxf_I32 dxf_write_hatch2(dxf_writer_t         *w,
                         const dxf_hatch_data *data,
                         const dxf_attributes *attr) {
    return 1;
}

dxf_I32 dxf_write_hatch_loop1(dxf_writer_t *w, const dxf_hatch_loop_data *data) {
    return 1;
}

dxf_I32 dxf_write_hatch_loop2(dxf_writer_t *w, const dxf_hatch_loop_data *data) {
    return 1;
}

dxf_I32 dxf_write_hatch_edge(dxf_writer_t *w, const dxf_hatch_edge_data *data) {
    return 1;
}

uint32_t
dxf_write_image(dxf_writer_t *w, const dxf_image_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32
dxf_write_image_def(dxf_writer_t *w, const dxf_I32 handle, const dxf_image_data *data) {
    return 1;
}

dxf_I32
dxf_write_layer(dxf_writer_t *w, const dxf_layer_data *data, const dxf_attributes *attr) {
    return 1;
}

dxf_I32 dxf_write_line_type(dxf_writer_t *w, const dxf_line_type_data *data) { return 1; }

dxf_I32 dxf_write_appid(dxf_writer_t *w, const dxf_CHAR *name) { return 1; }

dxf_I32 dxf_write_block(dxf_writer_t *w, const dxf_block_data *data) { return 1; }

dxf_I32 dxf_write_end_block(dxf_writer_t *w, const dxf_CHAR *name) { return 1; }

dxf_I32 dxf_write_view_port(dxf_writer_t *w) { return 1; }

dxf_I32 dxf_write_style(dxf_writer_t *w, const dxf_style_data *style) { return 1; }

dxf_I32 dxf_write_view(dxf_writer_t *w) { return 1; }

dxf_I32 dxf_write_ucs(dxf_writer_t *w) { return 1; }

dxf_I32 dxf_write_dim_style(dxf_writer_t *w,
                            dxf_F64       dimasz,
                            dxf_F64       dimexe,
                            dxf_F64       dimexo,
                            dxf_F64       dimgap,
                            dxf_F64       dimtxt,
                            dxf_I32       dimtad,
                            dxf_BOOL      dimtih) {
    return 1;
}

dxf_I32 dxf_write_block_record(dxf_writer_t *w, const dxf_CHAR *name) { return 1; }

dxf_I32 dxf_write_objects(dxf_writer_t *w, const dxf_CHAR *appDictionaryName) {
    return 1;
}

dxf_I32 dxf_write_app_dictionary(dxf_writer_t *w) { return 1; }

uint32_t dxf_write_dictionary_entry(dxf_writer_t *w, const dxf_CHAR *name) { return 1; }

dxf_I32 dxf_write_x_record_int(dxf_writer_t *w, dxf_I32 handle, dxf_I32 value) {
    return 1;
}

dxf_I32 dxf_write_x_record_double(dxf_writer_t *w, dxf_I32 handle, dxf_F64 value) {
    return 1;
}

dxf_I32 dxf_write_x_record_BOOLean(dxf_writer_t *w, dxf_I32 handle, dxf_BOOL value) {
    return 1;
}

dxf_I32
dxf_write_x_record_string(dxf_writer_t *w, dxf_I32 handle, const dxf_CHAR *value) {
    return 1;
}

dxf_I32 dxf_write_objects_end(dxf_writer_t *w) { return 1; }
dxf_I32 dxf_write_comment(dxf_writer_t *w, const dxf_CHAR *comment) { return 0; }
