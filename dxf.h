#ifndef DXF_H
#define DXF_H

#include "dxf_entities.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __dxf_document dxf_document_t;
typedef struct __dex_write dxf_write_t;

dxf_document_t *create_document();
dxf_write_t *out(dxf_document_t *doc, const char *filename);
void destroy_document(dxf_document_t *doc);
void destroy_write(dxf_write_t *w);

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
void write_vertex(dxf_document_t *doc, dxf_write_t *w, dxf_vertex_data *data,
                  dxf_attributes *attr);

#ifdef __cplusplus
}
#endif

#endif // DXF_H