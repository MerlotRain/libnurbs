#include "dxf.h"
#include "dxf_document.h"

#include <ctype.h>
#include <math.h>
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

static dxf_I32 dxf_handle(dxf_writer_t *w, dxf_I32 gc) {
    dxf_write_hex(w, gc, w->m_handle);
    return w->m_handle++;
}

static dxf_I32 dxf_table(dxf_writer_t *w, const dxf_CHAR *name, dxf_I32 num, dxf_I32 h) {
    dxf_write_string(w, 0, "TABLE");
    dxf_write_string(w, 2, name);
    if (w->version >= DL_VERSION_2000) {
        if (h == 0) {
            dxf_handle(w, 5);
        } else {
            dxf_write_hex(w, 5, h);
        }
        dxf_write_string(w, 100, "AcDbSymbolTable");
    }
    dxf_write_int(w, 70, num);
    return DXF_SUCCESS;
}

static dxf_I32 dxf_coordinate(dxf_writer_t *w, int gc, dxf_F64 x, dxf_F64 y, dxf_F64 z) {
    dxf_write_real(w, gc, x);
    dxf_write_real(w, gc + 10, y);
    dxf_write_real(w, gc + 20, z);
    return DXF_SUCCESS;
}

static dxf_I32 dxf_coordinate_triplet(dxf_writer_t *w, int gc, const dxf_F64 *value) {
    assert(value);
    dxf_write_real(w, gc, *value++);
    dxf_write_real(w, gc + 10, *value++);
    dxf_write_real(w, gc + 20, *value++);
    return DXF_SUCCESS;
}

dxf_I32
dxf_create_writer(dxf_writer_t **w, const dxf_CHAR *filename, enum Version version) {
    assert(w);
    assert(filename);
    *w = (dxf_writer_t *)malloc(sizeof(dxf_writer_t));
    if (*w == NULL)
        return DXF_FAILURE;

    memset(*w, 0, sizeof(dxf_writer_t));
    dxf_document_t *doc = (dxf_document_t *)malloc(sizeof(dxf_document_t));
    if (doc == NULL) {
        dxf_destroy_writer(*w);
        return DXF_FAILURE;
    }
    (*w)->doc = doc;

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        dxf_destroy_writer(*w);
        return DXF_FAILURE;
    }
    (*w)->fp                = fp;
    (*w)->version           = version;
    (*w)->m_handle          = 0;
    (*w)->modelSpaceHandle  = 0;
    (*w)->paperSpace0Handle = 0;
    (*w)->paperSpace0Handle = 0;
    return DXF_SUCCESS;
}

dxf_I32 dxf_destroy_writer(dxf_writer_t *w) {
    assert(w);
    if (w->fp) {
        fclose(w->fp);
        w->fp = NULL;
    }
    if (w->doc) {
        dxf_destroy_document(w->doc);
        w->doc = NULL;
    }
    free(w);
    return DXF_SUCCESS;
}

/* ------------------------------- dxf write functions -------------------------------- */

dxf_I32 dxf_write_real(dxf_writer_t *w, dxf_I32 gc, dxf_F64 value) {
    char str[256] = {0};
    if (w->version == AC1009_MIN) {
        sprintf(str, "%.6lf", value);
    } else {
        sprintf(str, "%.16lf", value);
    }

    // fix for german locale:
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }

    // cut away those zeros at the end:
    dxf_BOOL dot = FALSE;
    dxf_I32  end = -1;
    for (dxf_U32 i = 0; i < strlen(str); ++i) {
        if (str[i] == '.') {
            dot = TRUE;
            end += 2;
            continue;
        } else if (dot && str[i] != '0') {
            end = i + 1;
        }
    }
    if (end > 0 && end < (dxf_I32)strlen(str)) {
        str[end] = '\0';
    }

    dxf_write_string(w, gc, str);
    fflush(w->fp);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_int(dxf_writer_t *w, dxf_I32 gc, dxf_I32 value) {
    dxf_U8 size   = gc < 10 ? 2 : (gc < 100 ? 1 : 0);
    char   buf[2] = {0};
    memset(buf, ' ', size);
    fprintf(w->fp, "%s%d\n%d\n", buf, gc, value);
    fflush(w->fp);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_boolean(dxf_writer_t *w, dxf_I32 gc, dxf_BOOL value) {
    return dxf_write_int(w, gc, (dxf_I32)value);
}

dxf_I32 dxf_write_hex(dxf_writer_t *w, dxf_I32 gc, dxf_I32 value) {
    char str[12] = {0};
    sprintf(str, "%0X", value);
    return dxf_write_string(w, gc, str);
}

dxf_I32 dxf_write_string(dxf_writer_t *w, dxf_I32 gc, const dxf_CHAR *value) {
    if (value == NULL) {
        return DXF_SUCCESS;
    }
    dxf_U8 size   = gc < 10 ? 2 : (gc < 100 ? 1 : 0);
    char   buf[2] = {0};
    memset(buf, ' ', size);
    fprintf(w->fp, "%s%d\n%s\n", buf, gc, value);
}

dxf_I32 dxf_section(dxf_writer_t *w, const dxf_CHAR *name) {
    dxf_write_string(w, 0, "SECTION");
    dxf_write_string(w, 2, name);
    return DXF_SUCCESS;
}

dxf_I32 dxf_section_header(dxf_writer_t *w) { return dxf_section(w, "HEADER"); }

dxf_I32 dxf_section_tables(dxf_writer_t *w) { return dxf_section(w, "TABLES"); }

dxf_I32 dxf_section_blocks(dxf_writer_t *w) { return dxf_section(w, "BLOCKS"); }

dxf_I32 dxf_section_entities(dxf_writer_t *w) { return dxf_section(w, "ENTITIES"); }

dxf_I32 dxf_section_classes(dxf_writer_t *w) { return dxf_section(w, "CLASSES"); }

dxf_I32 dxf_section_object(dxf_writer_t *w) { return dxf_section(w, "OBJECTS"); }

dxf_I32 dxf_section_end(dxf_writer_t *w) { return dxf_section(w, "ENDSEC"); }

dxf_I32 dxf_table_layers(dxf_writer_t *w, dxf_I32 num) { return DXF_SUCCESS; }

dxf_I32 dxf_table_linetypes(dxf_writer_t *w, dxf_I32 num) { return DXF_SUCCESS; }

dxf_I32 dxf_table_appid(dxf_writer_t *w, dxf_I32 num) { return DXF_SUCCESS; }

dxf_I32 dxf_table_style(dxf_writer_t *w, dxf_I32 num) { return DXF_SUCCESS; }

dxf_I32 dxf_table_end(dxf_writer_t *w) { return DXF_SUCCESS; }

dxf_I32 dxf_EOF(dxf_writer_t *w) { return DXF_SUCCESS; }

dxf_I32 dxf_write_entity(dxf_writer_t *w, const dxf_CHAR *text) { return DXF_SUCCESS; }

dxf_I32 dxf_entity_attributes(dxf_writer_t *w, const dxf_attributes *attr) {
    // layer name:
    dxf_write_string(w, 8, attr->layer);

    // R12 doesn't accept BYLAYER values. The value has to be missing
    //   in that case.
    if (w->version >= DL_VERSION_2000 || attr->color != 256) {
        dxf_write_int(w, 62, attr->color);
    }
    if (w->version >= DL_VERSION_2000 || attr->color24 != -1) {
        dxf_write_int(w, 420, attr->color24);
    }
    if (w->version >= DL_VERSION_2000) {
        dxf_write_int(w, 370, attr->width);
    }
    if (w->version >= DL_VERSION_2000) {
        dxf_write_real(w, 48, attr->line_type_scale);
    }
    dxf_CHAR *line_type = attr->line_type;
    for (int i = 0; i < strlen(line_type); ++i) {
        line_type[i] = toupper(line_type[i]);
    }
    if (w->version >= DL_VERSION_2000 || EQUAL(line_type, "BYLAYER")) {
        dxf_write_string(w, 6, line_type);
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_header(dxf_writer_t *w) {
    dxf_write_comment(w, "dxflib " LIBDXF_VERSION);
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_point(dxf_writer_t *w, const dxf_point_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "POINT");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbPoint");
    }
    dxf_coordinate(w, DL_POINT_COORD_CODE, data->x, data->y, data->z);
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_line(dxf_writer_t *w, const dxf_line_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "LINE");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbLine");
    }
    dxf_coordinate(w, DL_LINE_START_CODE, data->x1, data->y1, data->z1);
    dxf_coordinate(w, DL_LINE_END_CODE, data->x2, data->y2, data->z2);
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_xline(dxf_writer_t *w, const dxf_xline_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "XLINE");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbLine");
    }
    dxf_coordinate(w, DL_LINE_START_CODE, data->bx, data->by, data->bz);
    dxf_coordinate(w, DL_LINE_END_CODE, data->dx, data->dy, data->dz);
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_ray(dxf_writer_t *w, const dxf_ray_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "RAY");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version = DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbLine");
    }
    dxf_coordinate(w, DL_LINE_START_CODE, data->bx, data->by, data->bz);
    dxf_coordinate(w, DL_LINE_END_CODE, data->dx, data->dy, data->dz);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_polyline(dxf_writer_t            *w,
                           const dxf_polyline_data *data,
                           const dxf_attributes    *attr) {
    if (w->version == DL_VERSION_2000) {
        dxf_write_entity(w, "LWPOLYLINE");
        dxf_write_string(w, 100, "AcDbEntity");
        dxf_entity_attributes(w, attr);
        dxf_write_string(w, 100, "AcDbPolyline");
        dxf_write_int(w, 90, (dxf_I32)(data->number));
        dxf_write_int(w, 70, data->flags);
    } else {
        dxf_write_entity(w, "POLYLINE");
        dxf_entity_attributes(w, attr);
        memcpy(w->doc->polylineLayer, attr->layer, strlen(attr->layer));
        dxf_write_int(w, 66, 1);
        fxf_write_int(w, 70, data->flags);
        dxf_coordinate(w, DL_VERTEX_COORD_CODE, 0.0, 0.0, 0.0);
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_vertex(dxf_writer_t *w, const dxf_vertex_data *data) {
    if (w->version == DL_VERSION_2000) {
        dxf_write_real(w, 10, data->x);
        dxf_write_real(w, 20, data->y);
        if (fabs(data->bulge) > 1.0e-10) {
            dxf_write_real(w, 42, data->bulge);
        }
    } else {
        dxf_write_entity(w, "VERTEX");
        dxf_write_string(w, 8, w->doc->polylineLayer);
        dxf_coordinate(w, DL_VERTEX_COORD_CODE, data->x, data->y, data->z);
        if (fabs(data->bulge) > 1.0e-10) {
            dxf_write_real(w, 42, data->bulge);
        }
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_polyline_end(dxf_writer_t *w) {
    if (w->version != DL_VERSION_2000) {
        dxf_write_entity(w, "SEQEND");
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_spline(dxf_writer_t          *w,
                         const dxf_spline_data *data,
                         const dxf_attributes  *attr) {
    dxf_write_entity(w, "SPLINE");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbSpline");
    }
    dxf_write_int(w, 70, data->flags);
    dxf_write_int(w, 71, data->degree);
    dxf_write_int(w, 72, data->nKnots);
    dxf_write_int(w, 73, data->nControl);
    dxf_write_int(w, 74, data->nFit);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_control_point(dxf_writer_t *w, const dxf_control_point_data *data) {
    dxf_write_real(w, 10, data->x);
    dxf_write_real(w, 20, data->y);
    dxf_write_real(w, 30, data->z);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_fit_point(dxf_writer_t *w, const dxf_fit_point_data *data) {
    dxf_write_real(w, 11, data->x);
    dxf_write_real(w, 21, data->y);
    dxf_write_real(w, 31, data->z);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_knot(dxf_writer_t *w, const dxf_knot_data *data) {
    dxf_write_real(w, 40, data->k);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_circle(dxf_writer_t          *w,
                         const dxf_circle_data *data,
                         const dxf_attributes  *attr) {
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_arc(dxf_writer_t *w, const dxf_arc_data *data, const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_ellipse(dxf_writer_t           *w,
                          const dxf_ellipse_data *data,
                          const dxf_attributes   *attr) {
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_solid(dxf_writer_t *w, const dxf_solid_data *data, const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_trace(dxf_writer_t *w, const dxf_trace_data *data, const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_3dFace(dxf_writer_t           *w,
                         const dxf_3d_face_data *data,
                         const dxf_attributes   *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_insert(dxf_writer_t          *w,
                         const dxf_insert_data *data,
                         const dxf_attributes  *attr) {
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_mText(dxf_writer_t *w, const dxf_mText_data *data, const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_text(dxf_writer_t *w, const dxf_text_data *data, const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_attribute(dxf_writer_t             *w,
                            const dxf_attribute_data *data,
                            const dxf_attributes     *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_style_overrides(dxf_writer_t *w, const dxf_dimension_data *data) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_aligned(dxf_writer_t               *w,
                              const dxf_dimension_data   *data,
                              const dxf_dim_aligned_data *edata,
                              const dxf_attributes       *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_linear(dxf_writer_t         *w,
                             dxf_dimension_data   *data,
                             dxf_dim_linear_data  *edata,
                             const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_radial(dxf_writer_t              *w,
                             const dxf_dimension_data  *data,
                             const dxf_dim_radial_data *edata,
                             const dxf_attributes      *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_diametric(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_diametric_data *edata,
                                const dxf_attributes         *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_angular2L(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_angular2L_data *edata,
                                const dxf_attributes         *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_angular3P(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_angular3P_data *edata,
                                const dxf_attributes         *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_ordinate(dxf_writer_t                *w,
                               const dxf_dimension_data    *data,
                               const dxf_dim_ordinate_data *edata,
                               const dxf_attributes        *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_leader(dxf_writer_t          *w,
                         const dxf_leader_data *data,
                         const dxf_attributes  *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_leader_vertex(dxf_writer_t *w, const dxf_leader_vertex_data *data) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_leader_end(dxf_writer_t *w, const dxf_leader_data *data) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch1(dxf_writer_t         *w,
                         const dxf_hatch_data *data,
                         const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch2(dxf_writer_t         *w,
                         const dxf_hatch_data *data,
                         const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch_loop1(dxf_writer_t *w, const dxf_hatch_loop_data *data) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch_loop2(dxf_writer_t *w, const dxf_hatch_loop_data *data) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch_edge(dxf_writer_t *w, const dxf_hatch_edge_data *data) {
    return DXF_SUCCESS;
}

uint32_t
dxf_write_image(dxf_writer_t *w, const dxf_image_data *data, const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_image_def(dxf_writer_t *w, const dxf_I32 handle, const dxf_image_data *data) {
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_layer(dxf_writer_t *w, const dxf_layer_data *data, const dxf_attributes *attr) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_line_type(dxf_writer_t *w, const dxf_line_type_data *data) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_appid(dxf_writer_t *w, const dxf_CHAR *name) { return DXF_SUCCESS; }

dxf_I32 dxf_write_block(dxf_writer_t *w, const dxf_block_data *data) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_end_block(dxf_writer_t *w, const dxf_CHAR *name) { return DXF_SUCCESS; }

dxf_I32 dxf_write_view_port(dxf_writer_t *w) { return DXF_SUCCESS; }

dxf_I32 dxf_write_style(dxf_writer_t *w, const dxf_style_data *style) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_view(dxf_writer_t *w) { return DXF_SUCCESS; }

dxf_I32 dxf_write_ucs(dxf_writer_t *w) { return DXF_SUCCESS; }

dxf_I32 dxf_write_dim_style(dxf_writer_t *w,
                            dxf_F64       dimasz,
                            dxf_F64       dimexe,
                            dxf_F64       dimexo,
                            dxf_F64       dimgap,
                            dxf_F64       dimtxt,
                            dxf_I32       dimtad,
                            dxf_BOOL      dimtih) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_block_record(dxf_writer_t *w, const dxf_CHAR *name) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_objects(dxf_writer_t *w, const dxf_CHAR *appDictionaryName) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_app_dictionary(dxf_writer_t *w) { return DXF_SUCCESS; }

uint32_t dxf_write_dictionary_entry(dxf_writer_t *w, const dxf_CHAR *name) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_x_record_int(dxf_writer_t *w, dxf_I32 handle, dxf_I32 value) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_x_record_double(dxf_writer_t *w, dxf_I32 handle, dxf_F64 value) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_x_record_BOOLean(dxf_writer_t *w, dxf_I32 handle, dxf_BOOL value) {
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_x_record_string(dxf_writer_t *w, dxf_I32 handle, const dxf_CHAR *value) {
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_objects_end(dxf_writer_t *w) { return DXF_SUCCESS; }
dxf_I32 dxf_write_comment(dxf_writer_t *w, const dxf_CHAR *comment) { return 0; }
