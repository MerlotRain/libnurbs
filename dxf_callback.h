#ifndef DXF_CALLBACK_H
#define DXF_CALLBACK_H

#include "dxf_entities.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*dxf_callback_add_layer)(dxf_layer_data *data);
typedef void (*dxf_callback_add_line_type)(dxf_line_type_data *data);
typedef void (*dxf_callback_add_line_type_dash)(double length);
typedef void (*dxf_callback_add_block)(dxf_block_data *data);
typedef void (*dxf_callback_end_block)();
typedef void (*dxf_callback_add_text_style)(dxf_style_data *data);
typedef void (*dxf_callback_add_point)(dxf_point_data *data);
typedef void (*dxf_callback_add_line)(dxf_line_data *data);
typedef void (*dxf_callback_add_xline)(dxf_xline_data *data);
typedef void (*dxf_callback_add_ray)(dxf_ray_data *data);
typedef void (*dxf_callback_add_arc)(dxf_arc_data *data);
typedef void (*dxf_callback_add_circle)(dxf_circle_data *data);
typedef void (*dxf_callback_ellipse)(dxf_ellipse_data *data);

#ifdef __cplusplus
}
#endif

#endif // DXF_CALLBACK_H
