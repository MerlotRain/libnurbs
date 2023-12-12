#ifndef DXF_ENTITIES_H
#define DXF_ENTITIES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  const char *layer;
  const char *line_type;
  int color;
  int color24;
  int width;
  int handle;
  double line_type_scale;
  bool is_paper_space;
} dxf_attributes;

typedef struct {
  const char *name;
  int flags;
  bool off;
} dxf_layer_data;

typedef struct {
  const char *name;
  int flags;
  double dpx;
  double dpy;
  double dpz;
} dxf_block_data;

typedef struct {
  const char *name;
  const char &description;
  int flags;
  int number_of_dashes;
  double pattern_length;
  double *pattern;
} dxf_line_type_data;

typedef struct {
  const char *name;
  int flags;
  double fixed_text_height;
  double width_factor;
  double oblique_angle;
  int text_generation_flags;
  double last_height_used;
  const char *primary_font_file;
  const char *bit_font_file;
  bool bold;
  bool italic;
} dxf_style_data;

typedef struct {
  double x;
  double y;
  double z;
} dxf_point_data;

typedef struct {
  double x1;
  double y1;
  double z1;
  double x2;
  double y2;
  double z2;
} dxf_line_data;

typedef struct {
  double bx;
  double by;
  double bz;
  double dx;
  double dy;
  double dz;
} dxf_xline_data;

typedef struct {
  double bx;
  double by;
  double bz;
  double dx;
  double dy;
  double dz;
} dxf_ray_data;

typedef struct {
  double cx;
  double cy;
  double cz;

  double radius;
  double angle1;
  double angle2;
} dxf_arc_data;

typedef struct {
  double cx;
  double cy;
  double cz;

  double radius;
} dxf_circle_data;

typedef struct {
  double cx;
  double cy;
  double cz;

  double mx;
  double my;
  double mz;

  double ratio;
  double angle1;
  double angle2;
} dxf_ellipse_data;

typedef struct {
  unsigned int number;
  unsigned int m;
  unsigned int n;
  double elevation;
  int flags;
} dxf_polyline_data;

typedef struct {
  double x;
  double y;
  double z;
  double bulge;
} dxf_vertex_data;

#ifdef __cplusplus
}
#endif

#endif // DXF_ENTITIES_H