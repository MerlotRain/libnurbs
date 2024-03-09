#include "dxf.h"
#include "dxf_document.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------------------------------- dxf writer struct -------------------------------- */
struct dxf_writer_t {
    FILE        *fp;
    enum Version version;
    dxf_U32      m_handle;
    dxf_U32      modelSpaceHandle;
    dxf_U32      paperSpaceHandle;
    dxf_U32      paperSpace0Handle;
    dxf_CHAR     polylineLayer[512];
    dxf_U32      appDictionaryHandle;
    dxf_U32      styleHandleStd;
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
    return DXF_SUCCESS;
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

dxf_I32 dxf_table_line_types(dxf_writer_t *w, dxf_I32 num) { return DXF_SUCCESS; }

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
    dxf_CHAR line_type[512] = {0};
    memcpy(line_type, attr->line_type, strlen(attr->line_type));
    for (int i = 0; i < strlen(line_type); ++i) {
        line_type[i] = toupper(line_type[i]);
    }
    if (w->version >= DL_VERSION_2000 || EQUAL(line_type, "BYLAYER")) {
        dxf_write_string(w, 6, line_type);
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_header(dxf_writer_t *w) {
    dxf_write_comment(w, "libdxf " LIBDXF_VERSION);
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
    if (w->version == DL_VERSION_2000) {
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
        memcpy(w->polylineLayer, attr->layer, strlen(attr->layer));
        dxf_write_int(w, 66, 1);
        dxf_write_int(w, 70, data->flags);
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
        dxf_write_string(w, 8, w->polylineLayer);
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
    dxf_write_entity(w, "CIRCLE");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbCircle");
    }
    dxf_coordinate(w, 10, data->cx, data->cy, data->cz);
    dxf_write_real(w, 40, data->radius);
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_arc(dxf_writer_t *w, const dxf_arc_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "ARC");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbCircle");
    }
    dxf_coordinate(w, 10, data->cx, data->cy, data->cz);
    dxf_write_real(w, 40, data->radius);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbArc");
    }
    dxf_write_real(w, 50, data->angle1);
    dxf_write_real(w, 51, data->angle2);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_ellipse(dxf_writer_t           *w,
                          const dxf_ellipse_data *data,
                          const dxf_attributes   *attr) {
    if (w->version > DL_VERSION_R12) {
        dxf_write_entity(w, "ELLIPSE");
        if (w->version == DL_VERSION_2000) {
            dxf_write_string(w, 100, "AcDbEntity");
        }
        dxf_entity_attributes(w, attr);
        if (w->version == DL_VERSION_2000) {
            dxf_write_string(w, 100, "AcDbEllipse");
        }
        dxf_coordinate(w, 10, data->cx, data->cy, data->cz);
        dxf_coordinate(w, 11, data->mx, data->my, data->mz);
        dxf_write_real(w, 40, data->ratio);
        dxf_write_real(w, 41, data->angle1);
        dxf_write_real(w, 42, data->angle2);
    }
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_solid(dxf_writer_t *w, const dxf_solid_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "SOLID");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbTrace");
    }
    dxf_coordinate(w, 10, data->x[0], data->y[0], data->z[0]);
    dxf_coordinate(w, 11, data->x[1], data->y[1], data->z[1]);
    dxf_coordinate(w, 12, data->x[2], data->y[2], data->z[2]);
    dxf_coordinate(w, 13, data->x[3], data->y[3], data->z[3]);
    dxf_write_real(w, 39, data->thickness);
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_trace(dxf_writer_t *w, const dxf_trace_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "TRACE");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbTrace");
    }
    dxf_coordinate(w, 10, data->x[0], data->y[0], data->z[0]);
    dxf_coordinate(w, 11, data->x[1], data->y[1], data->z[1]);
    dxf_coordinate(w, 12, data->x[2], data->y[2], data->z[2]);
    dxf_coordinate(w, 13, data->x[3], data->y[3], data->z[3]);
    dxf_write_real(w, 39, data->thickness);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_3dFace(dxf_writer_t           *w,
                         const dxf_3d_face_data *data,
                         const dxf_attributes   *attr) {
    dxf_write_entity(w, "3DFACE");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbFace");
    }
    dxf_coordinate(w, 10, data->x[0], data->y[0], data->z[0]);
    dxf_coordinate(w, 11, data->x[1], data->y[1], data->z[1]);
    dxf_coordinate(w, 12, data->x[2], data->y[2], data->z[2]);
    dxf_coordinate(w, 13, data->x[3], data->y[3], data->z[3]);
    dxf_write_real(w, 39, data->thickness);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_insert(dxf_writer_t          *w,
                         const dxf_insert_data *data,
                         const dxf_attributes  *attr) {
    if (strlen(data->name) == 0) {
        fprintf(stderr, "dxf_write_insert: Block name must not be empty\n");
        return DXF_FAILURE;
    }

    dxf_write_entity(w, "INSERT");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        if (data->cols != 1 || data->rows != 1) {
            dxf_write_string(w, 100, "AcDbInsertBlock");
        } else {
            dxf_write_string(w, 100, "AcDbBlockReference");
        }
    }
    dxf_write_string(w, 2, data->name);
    dxf_write_real(w, 10, data->ipx);
    dxf_write_real(w, 20, data->ipy);
    dxf_write_real(w, 30, data->ipz);
    if (data->sx != 1.0 || data->sy != 1.0) {
        dxf_write_real(w, 41, data->sx);
        dxf_write_real(w, 42, data->sy);
        dxf_write_real(w, 43, 1.0);
    }
    if (data->angle != 0.0) {
        dxf_write_real(w, 50, data->angle);
    }
    if (data->cols != 1 || data->rows != 1) {
        dxf_write_int(w, 70, data->cols);
        dxf_write_int(w, 71, data->rows);
    }
    if (data->colSp != 0.0 || data->rowSp != 0.0) {
        dxf_write_real(w, 44, data->colSp);
        dxf_write_real(w, 45, data->rowSp);
    }
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_mText(dxf_writer_t *w, const dxf_mText_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "MTEXT");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbMText");
    }
    dxf_write_real(w, 10, data->ipx);
    dxf_write_real(w, 20, data->ipy);
    dxf_write_real(w, 30, data->ipz);
    dxf_write_real(w, 40, data->height);
    dxf_write_real(w, 41, data->width);

    dxf_write_int(w, 71, data->attachmentPoint);
    dxf_write_int(w, 72, data->drawingDirection);

    dxf_I32  length     = strlen(data->text);
    dxf_CHAR chunk[251] = {0};
    dxf_I32  i;
    for (i = 250; i < length; i += 250) {
        strncpy(chunk, &data->text[i - 250], 250);
        chunk[250] = '\0';
        dxf_write_string(w, 3, chunk);
    }
    strncpy(chunk, &data->text[i - 250], 250);
    chunk[250] = '\0';
    dxf_write_string(w, 1, chunk);

    dxf_write_string(w, 7, data->style);

    dxf_write_real(w, 50, data->angle / (2.0 * M_PI) * 360.0);
    dxf_write_int(w, 73, data->lineSpacingStyle);
    dxf_write_real(w, 44, data->lineSpacingFactor);

    return DXF_SUCCESS;
}

dxf_I32
dxf_write_text(dxf_writer_t *w, const dxf_text_data *data, const dxf_attributes *attr) {
    dxf_write_entity(w, "TEXT");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbText");
    }
    dxf_write_real(w, 10, data->ipx);
    dxf_write_real(w, 20, data->ipy);
    dxf_write_real(w, 30, data->ipz);
    dxf_write_real(w, 40, data->height);
    dxf_write_string(w, 1, data->text);
    dxf_write_real(w, 50, data->angle / (2.0 * M_PI) * 360.0);
    dxf_write_real(w, 41, data->xScaleFactor);
    dxf_write_string(w, 7, data->style);

    dxf_write_int(w, 71, data->textGenerationFlags);
    dxf_write_int(w, 72, data->hJustification);

    dxf_write_real(w, 11, data->apx);
    dxf_write_real(w, 21, data->apy);
    dxf_write_real(w, 31, data->apz);

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbText");
    }
    dxf_write_int(w, 73, data->vJustification);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_attribute(dxf_writer_t             *w,
                            const dxf_attribute_data *data,
                            const dxf_attributes     *attr) {
    dxf_write_entity(w, "ATTRIB");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbText");
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_style_overrides(dxf_writer_t *w, const dxf_dimension_data *data) {
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 1001, "ACAD");
        dxf_write_string(w, 1000, "DSTYLE");
        dxf_write_string(w, 1002, "{");
        dxf_write_int(w, 1070, 133);
        dxf_write_real(w, 1040, data->linearFactor);
        dxf_write_int(w, 1070, 40);
        dxf_write_real(w, 1040, data->dimScale);
        dxf_write_string(w, 1002, "}");
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_aligned(dxf_writer_t               *w,
                              const dxf_dimension_data   *data,
                              const dxf_dim_aligned_data *edata,
                              const dxf_attributes       *attr) {
    dxf_write_entity(w, "DIMENSION");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbDimension");
    }

    dxf_write_real(w, 10, data->dpx);
    dxf_write_real(w, 20, data->dpy);
    dxf_write_real(w, 30, data->dpz);

    dxf_write_real(w, 11, data->mpx);
    dxf_write_real(w, 21, data->mpy);
    dxf_write_real(w, 31, 0.0);

    dxf_write_int(w, 70, data->type);
    if (w->version > DL_VERSION_R12) {
        dxf_write_int(w, 71, data->attachmentPoint);
        dxf_write_int(w, 72, data->lineSpacingStyle);
        dxf_write_real(w, 41, data->lineSpacingFactor);
    }

    dxf_write_real(w, 42, data->angle);

    dxf_write_string(w, 1, data->text);
    dxf_write_string(w, 3, "Standard");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbAlignedDimension");
    }

    dxf_write_real(w, 13, edata->epx1);
    dxf_write_real(w, 23, edata->epy1);
    dxf_write_real(w, 33, 0.0);

    dxf_write_real(w, 14, edata->epx2);
    dxf_write_real(w, 24, edata->epy2);
    dxf_write_real(w, 34, 0.0);

    dxf_write_dim_style_overrides(w, data);

    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_linear(dxf_writer_t         *w,
                             dxf_dimension_data   *data,
                             dxf_dim_linear_data  *edata,
                             const dxf_attributes *attr) {
    dxf_write_entity(w, "DIMENSION");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbDimension");
    }

    dxf_write_real(w, 10, data->dpx);
    dxf_write_real(w, 20, data->dpy);
    dxf_write_real(w, 30, data->dpz);

    dxf_write_real(w, 11, data->mpx);
    dxf_write_real(w, 21, data->mpy);
    dxf_write_real(w, 31, 0.0);

    dxf_write_int(w, 70, data->type);
    if (w->version > DL_VERSION_R12) {
        dxf_write_int(w, 71, data->attachmentPoint);
        dxf_write_int(w, 72, data->lineSpacingStyle); // opt
        dxf_write_int(w, 74, data->arrow1Flipped);
        dxf_write_int(w, 75, data->arrow2Flipped);
        dxf_write_real(w, 41, data->lineSpacingFactor); // opt
    }

    dxf_write_real(w, 42, data->angle);
    dxf_write_string(w, 1, data->text);
    dxf_write_string(w, 3, "Standard");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbAlignedDimension");
    }

    dxf_write_real(w, 13, edata->dpx1);
    dxf_write_real(w, 23, edata->dpy1);
    dxf_write_real(w, 33, 0.0);

    dxf_write_real(w, 14, edata->dpx2);
    dxf_write_real(w, 24, edata->dpy2);
    dxf_write_real(w, 34, 0.0);

    dxf_write_real(w, 50, edata->angle / (2.0 * M_PI) * 360.0);

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbRotatedDimension");
    }

    dxf_write_dim_style_overrides(w, data);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_radial(dxf_writer_t              *w,
                             const dxf_dimension_data  *data,
                             const dxf_dim_radial_data *edata,
                             const dxf_attributes      *attr) {
    dxf_write_entity(w, "DIMENSION");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    ;
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbDimension");
    }

    dxf_write_real(w, 10, data->dpx);
    dxf_write_real(w, 20, data->dpy);
    dxf_write_real(w, 30, data->dpz);

    dxf_write_real(w, 11, data->mpx);
    dxf_write_real(w, 21, data->mpy);
    dxf_write_real(w, 31, 0.0);

    dxf_write_int(w, 70, data->type);
    if (w->version > DL_VERSION_R12) {
        dxf_write_int(w, 71, data->attachmentPoint);
        dxf_write_int(w, 72, data->lineSpacingStyle); // opt
        dxf_write_int(w, 74, data->arrow1Flipped);
        // dxf_write_int(w,75, data->arrow2Flipped);
        dxf_write_real(w, 41, data->lineSpacingFactor); // opt
    }

    dxf_write_real(w, 42, data->angle);

    dxf_write_string(w, 1, data->text); // opt
    // dxf_write_string(w,3, data->style);
    dxf_write_string(w, 3, "Standard");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbRadialDimension");
    }

    dxf_write_real(w, 15, edata->dpx);
    dxf_write_real(w, 25, edata->dpy);
    dxf_write_real(w, 35, 0.0);

    dxf_write_real(w, 40, edata->leader);

    dxf_write_dim_style_overrides(w, data);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_diametric(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_diametric_data *edata,
                                const dxf_attributes         *attr) {
    dxf_write_entity(w, "DIMENSION");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    ;
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbDimension");
    }

    dxf_write_real(w, 10, data->dpx);
    dxf_write_real(w, 20, data->dpy);
    dxf_write_real(w, 30, data->dpz);

    dxf_write_real(w, 11, data->mpx);
    dxf_write_real(w, 21, data->mpy);
    dxf_write_real(w, 31, 0.0);

    dxf_write_int(w, 70, data->type);
    if (w->version > DL_VERSION_R12) {
        dxf_write_int(w, 71, data->attachmentPoint);
        dxf_write_int(w, 72, data->lineSpacingStyle); // opt
        dxf_write_int(w, 74, data->arrow1Flipped);
        dxf_write_int(w, 75, data->arrow2Flipped);
        dxf_write_real(w, 41, data->lineSpacingFactor); // opt
    }

    dxf_write_real(w, 42, data->angle);

    dxf_write_string(w, 1, data->text); // opt
    // dxf_write_string(w,3, data->style);
    dxf_write_string(w, 3, "Standard");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbDiametricDimension");
    }

    dxf_write_real(w, 15, edata->dpx);
    dxf_write_real(w, 25, edata->dpy);
    dxf_write_real(w, 35, 0.0);

    dxf_write_real(w, 40, edata->leader);

    dxf_write_dim_style_overrides(w, data);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_angular2L(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_angular2L_data *edata,
                                const dxf_attributes         *attr) {
    dxf_write_entity(w, "DIMENSION");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    ;
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbDimension");
    }

    dxf_write_real(w, 10, data->dpx);
    dxf_write_real(w, 20, data->dpy);
    dxf_write_real(w, 30, data->dpz);

    dxf_write_real(w, 11, data->mpx);
    dxf_write_real(w, 21, data->mpy);
    dxf_write_real(w, 31, 0.0);

    dxf_write_int(w, 70, data->type);
    if (w->version > DL_VERSION_R12) {
        dxf_write_int(w, 71, data->attachmentPoint);
        dxf_write_int(w, 72, data->lineSpacingStyle); // opt
        dxf_write_int(w, 74, data->arrow1Flipped);
        dxf_write_int(w, 75, data->arrow2Flipped);
        dxf_write_real(w, 41, data->lineSpacingFactor); // opt
    }

    dxf_write_real(w, 42, data->angle);

    dxf_write_string(w, 1, data->text); // opt
    // dxf_write_string(w,3, data->style);
    dxf_write_string(w, 3, "Standard");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDb2LineAngularDimension");
    }

    dxf_write_real(w, 13, edata->dpx1);
    dxf_write_real(w, 23, edata->dpy1);
    dxf_write_real(w, 33, 0.0);

    dxf_write_real(w, 14, edata->dpx2);
    dxf_write_real(w, 24, edata->dpy2);
    dxf_write_real(w, 34, 0.0);

    dxf_write_real(w, 15, edata->dpx3);
    dxf_write_real(w, 25, edata->dpy3);
    dxf_write_real(w, 35, 0.0);

    dxf_write_real(w, 16, edata->dpx4);
    dxf_write_real(w, 26, edata->dpy4);
    dxf_write_real(w, 36, 0.0);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_angular3P(dxf_writer_t                 *w,
                                const dxf_dimension_data     *data,
                                const dxf_dim_angular3P_data *edata,
                                const dxf_attributes         *attr) {
    dxf_write_entity(w, "DIMENSION");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    ;
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbDimension");
    }

    dxf_write_real(w, 10, data->dpx);
    dxf_write_real(w, 20, data->dpy);
    dxf_write_real(w, 30, data->dpz);

    dxf_write_real(w, 11, data->mpx);
    dxf_write_real(w, 21, data->mpy);
    dxf_write_real(w, 31, 0.0);

    dxf_write_int(w, 70, data->type);
    if (w->version > DL_VERSION_R12) {
        dxf_write_int(w, 71, data->attachmentPoint);
        dxf_write_int(w, 72, data->lineSpacingStyle); // opt
        dxf_write_int(w, 74, data->arrow1Flipped);
        dxf_write_int(w, 75, data->arrow2Flipped);
        dxf_write_real(w, 41, data->lineSpacingFactor); // opt
    }

    dxf_write_real(w, 42, data->angle);

    dxf_write_string(w, 1, data->text); // opt
    // dxf_write_string(w,3, data->style);
    dxf_write_string(w, 3, "Standard");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDb3PointAngularDimension");
    }

    dxf_write_real(w, 13, edata->dpx1);
    dxf_write_real(w, 23, edata->dpy1);
    dxf_write_real(w, 33, 0.0);

    dxf_write_real(w, 14, edata->dpx2);
    dxf_write_real(w, 24, edata->dpy2);
    dxf_write_real(w, 34, 0.0);

    dxf_write_real(w, 15, edata->dpx3);
    dxf_write_real(w, 25, edata->dpy3);
    dxf_write_real(w, 35, 0.0);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_dim_ordinate(dxf_writer_t                *w,
                               const dxf_dimension_data    *data,
                               const dxf_dim_ordinate_data *edata,
                               const dxf_attributes        *attr) {
    dxf_write_entity(w, "DIMENSION");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    ;
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbDimension");
    }

    dxf_write_real(w, 10, data->dpx);
    dxf_write_real(w, 20, data->dpy);
    dxf_write_real(w, 30, data->dpz);

    dxf_write_real(w, 11, data->mpx);
    dxf_write_real(w, 21, data->mpy);
    dxf_write_real(w, 31, 0.0);

    int type = data->type;
    if (edata->xtype) {
        type |= 0x40;
    }

    dxf_write_int(w, 70, type);
    if (w->version > DL_VERSION_R12) {
        dxf_write_int(w, 71, data->attachmentPoint);
        dxf_write_int(w, 72, data->lineSpacingStyle); // opt
        // dxf_write_int(w,74, data->arrow1Flipped);
        // dxf_write_int(w,75, data->arrow2Flipped);
        dxf_write_real(w, 41, data->lineSpacingFactor); // opt
    }

    dxf_write_string(w, 1, data->text); // opt
    // dxf_write_string(w,3, data->style);
    dxf_write_string(w, 3, "Standard");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbOrdinateDimension");
    }

    dxf_write_real(w, 13, edata->dpx1);
    dxf_write_real(w, 23, edata->dpy1);
    dxf_write_real(w, 33, 0.0);

    dxf_write_real(w, 14, edata->dpx2);
    dxf_write_real(w, 24, edata->dpy2);
    dxf_write_real(w, 34, 0.0);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_leader(dxf_writer_t          *w,
                         const dxf_leader_data *data,
                         const dxf_attributes  *attr) {
    if (w->version > DL_VERSION_R12) {
        dxf_write_entity(w, "LEADER");
        if (w->version == DL_VERSION_2000) {
            dxf_write_string(w, 100, "AcDbEntity");
        }
        dxf_entity_attributes(w, attr);
        ;
        if (w->version == DL_VERSION_2000) {
            dxf_write_string(w, 100, "AcDbLeader");
        }
        dxf_write_string(w, 3, "Standard");
        dxf_write_int(w, 71, data->arrowHeadFlag);
        dxf_write_int(w, 72, data->leaderPathType);
        dxf_write_int(w, 73, data->leaderCreationFlag);
        dxf_write_int(w, 74, data->hooklineDirectionFlag);
        dxf_write_int(w, 75, data->hooklineFlag);
        dxf_write_real(w, 40, data->textAnnotationHeight);
        dxf_write_real(w, 41, data->textAnnotationWidth);
        dxf_write_int(w, 76, data->number);
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_leader_vertex(dxf_writer_t *w, const dxf_leader_vertex_data *data) {
    if (w->version > DL_VERSION_R12) {
        dxf_write_real(w, 10, data->x);
        dxf_write_real(w, 20, data->y);
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_leader_end(dxf_writer_t *w, const dxf_leader_data *data) {
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 1001, "ACAD");
        dxf_write_string(w, 1000, "DSTYLE");
        dxf_write_string(w, 1002, "{");
        dxf_write_int(w, 1070, 40);
        dxf_write_real(w, 1040, data->dimScale);
        dxf_write_string(w, 1002, "}");
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch1(dxf_writer_t         *w,
                         const dxf_hatch_data *data,
                         const dxf_attributes *attr) {
    dxf_write_entity(w, "HATCH");
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbHatch");
    }
    dxf_write_real(w, 10, 0.0); // elevation
    dxf_write_real(w, 20, 0.0);
    dxf_write_real(w, 30, 0.0);
    dxf_write_real(w, 210, 0.0); // extrusion dir.
    dxf_write_real(w, 220, 0.0);
    dxf_write_real(w, 230, 1.0);
    if (data->solid == FALSE) {
        dxf_write_string(w, 2, data->pattern);
    } else {
        dxf_write_string(w, 2, "SOLID");
    }
    dxf_write_int(w, 70, (int)data->solid);
    dxf_write_int(w, 71, 0); // non-associative
    dxf_write_int(w, 91, data->numLoops);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch2(dxf_writer_t         *w,
                         const dxf_hatch_data *data,
                         const dxf_attributes *attr) {
    dxf_write_int(w, 75, 0); // odd parity
    dxf_write_int(w, 76, 1); // pattern type
    if (data->solid == FALSE) {
        dxf_write_real(w, 52, data->angle);
        dxf_write_real(w, 41, data->scale);
        dxf_write_int(w, 77, 0); // not double
        // dxf_write_int(w,78, 0);
        dxf_write_int(w, 78, 1);
        dxf_write_real(w, 53, 45.0);
        dxf_write_real(w, 43, 0.0);
        dxf_write_real(w, 44, 0.0);
        dxf_write_real(w, 45, -0.0883883476483184);
        dxf_write_real(w, 46, 0.0883883476483185);
        dxf_write_int(w, 79, 0);
    }
    dxf_write_int(w, 98, 0);

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 1001, "ACAD");
        dxf_write_real(w, 1010, data->originX);
        dxf_write_real(w, 1020, data->originY);
        dxf_write_int(w, 1030, 0.0);
    }
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch_loop1(dxf_writer_t *w, const dxf_hatch_loop_data *data) {
    dxf_write_int(w, 92, 1);
    dxf_write_int(w, 93, data->numEdges);
    // dxf_write_int(w,97, 0);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch_loop2(dxf_writer_t *w, const dxf_hatch_loop_data *data) {
    dxf_write_int(w, 97, 0);
    return DXF_SUCCESS;
}

dxf_I32 dxf_write_hatch_edge(dxf_writer_t *w, const dxf_hatch_edge_data *data) {
    if (data->type < 1 || data->type > 4) {
        printf("WARNING: unsupported hatch edge type: %d", data->type);
    }

    dxf_write_int(w, 72, data->type);

    switch (data->type) {
    // line:
    case 1:
        dxf_write_real(w, 10, data->x1);
        dxf_write_real(w, 20, data->y1);
        dxf_write_real(w, 11, data->x2);
        dxf_write_real(w, 21, data->y2);
        break;

    // arc:
    case 2:
        dxf_write_real(w, 10, data->cx);
        dxf_write_real(w, 20, data->cy);
        dxf_write_real(w, 40, data->radius);
        dxf_write_real(w, 50, data->angle1 / (2 * M_PI) * 360.0);
        dxf_write_real(w, 51, data->angle2 / (2 * M_PI) * 360.0);
        dxf_write_int(w, 73, (int)(data->ccw));
        break;

    // ellipse arc:
    case 3:
        dxf_write_real(w, 10, data->cx);
        dxf_write_real(w, 20, data->cy);
        dxf_write_real(w, 11, data->mx);
        dxf_write_real(w, 21, data->my);
        dxf_write_real(w, 40, data->ratio);
        dxf_write_real(w, 50, data->angle1 / (2 * M_PI) * 360.0);
        dxf_write_real(w, 51, data->angle2 / (2 * M_PI) * 360.0);
        dxf_write_int(w, 73, (int)(data->ccw));
        break;

    // spline:
    case 4:
        dxf_write_int(w, 94, data->degree);
        dxf_write_boolean(w, 73, data->rational);
        dxf_write_boolean(w, 74, data->periodic);
        dxf_write_int(w, 95, data->nKnots);
        dxf_write_int(w, 96, data->nControl);
        for (unsigned int i = 0; i < data->nKnots; i++) {
            dxf_write_real(w, 40, data->knots[i]);
        }
        for (unsigned int i = 0; i < data->nControl; i++) {
            dxf_write_real(w, 10, data->controlPoints[i * 2]);
            dxf_write_real(w, 20, data->controlPoints[i * 2 + 1]);
        }
        for (unsigned int i = 0; i < data->nWeight; i++) {
            dxf_write_real(w, 42, data->weights[i]);
        }
        if (data->nFit > 0) {
            dxf_write_int(w, 97, data->nFit);
            for (unsigned int i = 0; i < data->nFit; i++) {
                dxf_write_real(w, 11, data->fitPoints[i * 2]);
                dxf_write_real(w, 21, data->fitPoints[i * 2 + 1]);
            }
        }
        if (fabs(data->startTangentX) > 1.0e-4 || fabs(data->startTangentY) > 1.0e-4) {
            dxf_write_real(w, 12, data->startTangentX);
            dxf_write_real(w, 22, data->startTangentY);
        }
        if (fabs(data->endTangentX) > 1.0e-4 || fabs(data->endTangentY) > 1.0e-4) {
            dxf_write_real(w, 13, data->endTangentX);
            dxf_write_real(w, 23, data->endTangentY);
        }
        break;

    default:
        break;
    }
    return DXF_SUCCESS;
}

uint32_t
dxf_write_image(dxf_writer_t *w, const dxf_image_data *data, const dxf_attributes *attr) {

    dxf_write_entity(w, "IMAGE");

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbEntity");
    }
    dxf_entity_attributes(w, attr);
    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbRasterImage");
        dxf_write_int(w, 90, 0);
    }
    // insertion point
    dxf_write_real(w, 10, data->ipx);
    dxf_write_real(w, 20, data->ipy);
    dxf_write_real(w, 30, data->ipz);

    // vector along bottom side (1 pixel long)
    dxf_write_real(w, 11, data->ux);
    dxf_write_real(w, 21, data->uy);
    dxf_write_real(w, 31, data->uz);

    // vector along left side (1 pixel long)
    dxf_write_real(w, 12, data->vx);
    dxf_write_real(w, 22, data->vy);
    dxf_write_real(w, 32, data->vz);

    // image size in pixel
    dxf_write_real(w, 13, data->width);
    dxf_write_real(w, 23, data->height);

    // handle of IMAGEDEF object
    dxf_U32 handle = dxf_handle(w, 340);

    // flags
    dxf_write_int(w, 70, 15);

    // clipping:
    dxf_write_int(w, 280, 0);

    // brightness, contrast, fade
    dxf_write_int(w, 281, data->brightness);
    dxf_write_int(w, 282, data->contrast);
    dxf_write_int(w, 283, data->fade);

    return handle;
}

dxf_I32
dxf_write_image_def(dxf_writer_t *w, const dxf_I32 handle, const dxf_image_data *data) {
    dxf_write_string(w, 0, "IMAGEDEF");
    if (w->version == DL_VERSION_2000) {
        dxf_write_hex(w, 5, handle);
    }

    if (w->version == DL_VERSION_2000) {
        dxf_write_string(w, 100, "AcDbRasterImageDef");
        dxf_write_int(w, 90, 0);
    }
    // file name:
    dxf_write_string(w, 1, data->ref);

    // image size in pixel
    dxf_write_real(w, 10, data->width);
    dxf_write_real(w, 20, data->height);

    dxf_write_real(w, 11, 1.0);
    dxf_write_real(w, 21, 1.0);

    // loaded:
    dxf_write_int(w, 280, 1);
    // units:
    dxf_write_int(w, 281, 0);
    return DXF_SUCCESS;
}

dxf_I32
dxf_write_layer(dxf_writer_t *w, const dxf_layer_data *data, const dxf_attributes *attr) {
    if (strlen(data->name) == 0) {
        fprintf(stderr, "DL_Dxf::writeLayer: Layer name must not be empty\n");
        return DXF_FAILURE;
    }

    int color = attr->color;
    if (color >= 256) {
        fprintf(stderr, "Layer color cannot be %d. Changed to 7.\n", color);
        color = 7;
    }
    if (data->off) {
        // negative color value means layer is off:
        color = -color;
    }

    if (EQUALN(data->name, "0", 1)) {
        dxf_table_layers(w, 0x10);
    } else {
        dxf_table_layers(w, 0UL);
    }

    dxf_write_string(w, 2, data->name);
    dxf_write_int(w, 70, data->flags);
    dxf_write_int(w, 62, color);
    if (w->version >= DL_VERSION_2000 && attr->color24 != -1) {
        dxf_write_int(w, 420, attr->color24);
    }

    dxf_write_string(w, 6,
                     (strlen(attr->line_type) == 0 ? "CONTINUOUS" : attr->line_type));

    if (w->version >= DL_VERSION_2000) {
        // layer defpoints cannot be plotted
        char lstr[512] = {0};
        memcpy(lstr, data->name, strlen(data->name));
        for (int i = 0; i < strlen(lstr); ++i) {
            lstr[i] = tolower(lstr[i]);
        }
        if (EQUAL(lstr, "defpoints")) {
            dxf_write_int(w, 290, 0);
        }
    }
    if (w->version >= DL_VERSION_2000 && attr->width != -1) {
        dxf_write_int(w, 370, attr->width);
    }
    if (w->version >= DL_VERSION_2000) {
        dxf_write_hex(w, 390, 0xF);
    }
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
