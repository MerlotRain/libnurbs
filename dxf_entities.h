#ifndef DXF_ENTITIES_H
#define DXF_ENTITIES_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Storing and passing around attributes. Attributes
 * are the layer name, color, width and line type.
 */
typedef struct dxf_attributes {
  const char *layer;
  const char *line_type;
  int color;
  int color24;
  int width;
  int handle;
  double line_type_scale;
  bool is_paper_space;
} dxf_attributes;

/**
 * Layer Data.
 */
typedef struct dxf_layer_data {
  /** Layer name. */
  char *name;
  /** Layer flags. (1 = frozen, 2 = frozen by default, 4 = locked) */
  int flags;
  /** Layer is off */
  bool off;
} dxf_layer_data;

/**
 * Block Data.
 */
typedef struct dxf_block_data {
  /** Block name. */
  char *name;
  /** Block flags. (not used currently) */
  int flags;
  /** X Coordinate of base point. */
  double bpx;
  /** Y Coordinate of base point. */
  double bpy;
  /** Z Coordinate of base point. */
  double bpz;
} dxf_block_data;

/**
 * Line Type Data.
 */
typedef struct dxf_line_type_data {
  /** Linetype name */
  char *name;
  /** Linetype description */
  char *description;
  /** Linetype flags */
  int flags;
  /** Number of dashes */
  int numberOfDashes;
  /** Pattern length */
  double patternLength;
  /** Pattern */
  double *pattern;
} dxf_line_type_data;

/**
 * Text style data.
 */
typedef struct dxf_style_data {
  /** Style name */
  char *name;
  /** Style flags */
  int flags;
  /** Fixed text height or 0 for not fixed. */
  double fixedTextHeight;
  /** Width factor */
  double widthFactor;
  /** Oblique angle */
  double obliqueAngle;
  /** Text generation flags */
  int textGenerationFlags;
  /** Last height used */
  double lastHeightUsed;
  /** Primary font file name */
  char *primaryFontFile;
  /** Big font file name */
  char *bigFontFile;

  bool bold;
  bool italic;
} dxf_style_data;

/**
 * Point Data.
 */
typedef struct dxf_point_data {
  /*! X Coordinate of the point. */
  double x;
  /*! Y Coordinate of the point. */
  double y;
  /*! Z Coordinate of the point. */
  double z;
} dxf_point_data;

/**
 * Line Data.
 */
typedef struct dxf_line_data {
  /*! X Start coordinate of the point. */
  double x1;
  /*! Y Start coordinate of the point. */
  double y1;
  /*! Z Start coordinate of the point. */
  double z1;

  /*! X End coordinate of the point. */
  double x2;
  /*! Y End coordinate of the point. */
  double y2;
  /*! Z End coordinate of the point. */
  double z2;
} dxf_line_data;

/**
 * XLine Data.
 */
typedef struct dxf_xline_data {
  /*! X base point. */
  double bx;
  /*! Y base point. */
  double by;
  /*! Z base point. */
  double bz;

  /*! X direction vector. */
  double dx;
  /*! Y direction vector. */
  double dy;
  /*! Z direction vector. */
  double dz;
} dxf_xline_data;

/**
 * Ray Data.
 */
typedef struct dxf_ray_data {
  /*! X base point. */
  double bx;
  /*! Y base point. */
  double by;
  /*! Z base point. */
  double bz;

  /*! X direction vector. */
  double dx;
  /*! Y direction vector. */
  double dy;
  /*! Z direction vector. */
  double dz;
} dxf_ray_data;

/**
 * Arc Data.
 */
typedef struct dxf_arc_data {
  /*! X Coordinate of center point. */
  double cx;
  /*! Y Coordinate of center point. */
  double cy;
  /*! Z Coordinate of center point. */
  double cz;

  /*! Radius of arc. */
  double radius;
  /*! Startangle of arc in degrees. */
  double angle1;
  /*! Endangle of arc in degrees. */
  double angle2;
} dxf_arc_data;

/**
 * Circle Data.
 */
typedef struct dxf_circle_data {
  /*! X Coordinate of center point. */
  double cx;
  /*! Y Coordinate of center point. */
  double cy;
  /*! Z Coordinate of center point. */
  double cz;

  /*! Radius of arc. */
  double radius;
} dxf_circle_data;

/**
 * Polyline Data.
 */
typedef struct dxf_polyline_data {
  /*! Number of vertices in this polyline. */
  unsigned int number;

  /*! Number of vertices in m direction if polyline is a polygon mesh. */
  unsigned int m;

  /*! Number of vertices in n direction if polyline is a polygon mesh. */
  unsigned int n;

  /*! elevation of the polyline. */
  double elevation;

  /*! Flags */
  int flags;
} dxf_polyline_data;

/**
 * Vertex Data.
 */
typedef struct dxf_vertex_data {
  /*! X Coordinate of the vertex. */
  double x;
  /*! Y Coordinate of the vertex. */
  double y;
  /*! Z Coordinate of the vertex. */
  double z;
  /*! Bulge of vertex.
   * (The tangent of 1/4 of the arc angle or 0 for lines) */
  double bulge;
} dxf_vertex_data;

/**
 * Trace Data / solid data / 3d face data.
 */
typedef struct dxf_trace_data {
  /*! Thickness */
  double thickness;

  /*! Points */
  double x[4];
  double y[4];
  double z[4];
} dxf_trace_data;

/**
 * Solid Data.
 */
typedef dxf_trace_data dxf_solid_data;

/**
 * 3dface Data.
 */
typedef dxf_trace_data dxf_3d_face_data;

/**
 * Spline Data.
 */
typedef struct dxf_spline_data {
  /*! Degree of the spline curve. */
  unsigned int degree;

  /*! Number of knots. */
  unsigned int nKnots;

  /*! Number of control points. */
  unsigned int nControl;

  /*! Number of fit points. */
  unsigned int nFit;

  /*! Flags */
  int flags;

  double tangentStartX;
  double tangentStartY;
  double tangentStartZ;
  double tangentEndX;
  double tangentEndY;
  double tangentEndZ;
} dxf_spline_data;

/**
 * Spline knot data.
 */
typedef struct dxf_knot_data {
  /*! Knot value. */
  double k;
} dxf_knot_data;

/**
 * Spline control point data.
 */
typedef struct dxf_control_point_data {
  /*! X coordinate of the control point. */
  double x;
  /*! Y coordinate of the control point. */
  double y;
  /*! Z coordinate of the control point. */
  double z;
  /*! Weight of control point. */
  double w;
} dxf_control_point_data;

/**
 * Spline fit point data.
 */
typedef struct dxf_fit_point_data {
  /*! X coordinate of the fit point. */
  double x;
  /*! Y coordinate of the fit point. */
  double y;
  /*! Z coordinate of the fit point. */
  double z;
} dxf_fit_point_data;

/**
 * Ellipse Data.
 */
typedef struct dxf_ellipse_data {
  /*! X Coordinate of center point. */
  double cx;
  /*! Y Coordinate of center point. */
  double cy;
  /*! Z Coordinate of center point. */
  double cz;

  /*! X coordinate of the endpoint of the major axis. */
  double mx;
  /*! Y coordinate of the endpoint of the major axis. */
  double my;
  /*! Z coordinate of the endpoint of the major axis. */
  double mz;

  /*! Ratio of minor axis to major axis.. */
  double ratio;
  /*! Startangle of ellipse in rad. */
  double angle1;
  /*! Endangle of ellipse in rad. */
  double angle2;
} dxf_ellipse_data;

/**
 * Insert Data.
 */
typedef struct dxf_insert_data {
  /*! Name of the referred block. */
  char *name;
  /*! X Coordinate of insertion point. */
  double ipx;
  /*! Y Coordinate of insertion point. */
  double ipy;
  /*! Z Coordinate of insertion point. */
  double ipz;
  /*! X Scale factor. */
  double sx;
  /*! Y Scale factor. */
  double sy;
  /*! Z Scale factor. */
  double sz;
  /*! Rotation angle in degrees. */
  double angle;
  /*! Number of colums if we insert an array of the block or 1. */
  int cols;
  /*! Number of rows if we insert an array of the block or 1. */
  int rows;
  /*! Values for the spacing between cols. */
  double colSp;
  /*! Values for the spacing between rows. */
  double rowSp;
} dxf_insert_data;

/**
 * MText Data.
 */
typedef struct dxf_mText_data {
  /*! X Coordinate of insertion point. */
  double ipx;
  /*! Y Coordinate of insertion point. */
  double ipy;
  /*! Z Coordinate of insertion point. */
  double ipz;
  /*! X Coordinate of X direction vector. */
  double dirx;
  /*! Y Coordinate of X direction vector. */
  double diry;
  /*! Z Coordinate of X direction vector. */
  double dirz;
  /*! Text height */
  double height;
  /*! Width of the text box. */
  double width;
  /**
   * Attachment point.
   *
   * 1 = Top left, 2 = Top center, 3 = Top right,
   * 4 = Middle left, 5 = Middle center, 6 = Middle right,
   * 7 = Bottom left, 8 = Bottom center, 9 = Bottom right
   */
  int attachmentPoint;
  /**
   * Drawing direction.
   *
   * 1 = left to right, 3 = top to bottom, 5 = by style
   */
  int drawingDirection;
  /**
   * Line spacing style.
   *
   * 1 = at least, 2 = exact
   */
  int lineSpacingStyle;
  /**
   * Line spacing factor. 0.25 .. 4.0
   */
  double lineSpacingFactor;
  /*! Text string. */
  char *text;
  /*! Style string. */
  char *style;
  /*! Rotation angle. */
  double angle;
} dxf_mText_data;

/**
 * Text Data.
 */
typedef struct dxf_text_data {
  /*! X Coordinate of insertion point. */
  double ipx;
  /*! Y Coordinate of insertion point. */
  double ipy;
  /*! Z Coordinate of insertion point. */
  double ipz;

  /*! X Coordinate of alignment point. */
  double apx;
  /*! Y Coordinate of alignment point. */
  double apy;
  /*! Z Coordinate of alignment point. */
  double apz;

  /*! Text height */
  double height;
  /*! Relative X scale factor. */
  double xScaleFactor;
  /*! 0 = default, 2 = Backwards, 4 = Upside down */
  int textGenerationFlags;
  /**
   * Horizontal justification.
   *
   * 0 = Left (default), 1 = Center, 2 = Right,
   * 3 = Aligned, 4 = Middle, 5 = Fit
   * For 3, 4, 5 the vertical alignment has to be 0.
   */
  int hJustification;
  /**
   * Vertical justification.
   *
   * 0 = Baseline (default), 1 = Bottom, 2 = Middle, 3= Top
   */
  int vJustification;
  /*! Text string. */
  char *text;
  /*! Style (font). */
  char *style;
  /*! Rotation angle of dimension text away from default orientation. */
  double angle;
} dxf_text_data;

/**
 * Arc Aligned Text Data.
 */
typedef struct dxf_arc_aligned_text_data {

  /*! Text string */
  char *text;
  /*! Font name */
  char *font;
  /*! Style */
  char *style;

  /*! X coordinate of arc center point. */
  double cx;
  /*! Y coordinate of arc center point. */
  double cy;
  /*! Z coordinate of arc center point. */
  double cz;
  /*! Arc radius. */
  double radius;

  /*! Relative X scale factor. */
  double xScaleFactor;
  /*! Text height */
  double height;
  /*! Character spacing */
  double spacing;
  /*! Offset from arc */
  double offset;
  /*! Right offset */
  double rightOffset;
  /*! Left offset */
  double leftOffset;
  /*! Start angle (radians) */
  double startAngle;
  /*! End angle (radians) */
  double endAngle;
  /*! Reversed character order:
   * false: normal
   * true: reversed
   */
  bool reversedCharacterOrder;
  /*! Direction
   * 1: outward from center
   * 2: inward from center
   */
  int direction;
  /*! Alignment:
   * 1: fit
   * 2: left
   * 3: right
   * 4: center
   */
  int alignment;
  /*! Side
   * 1: convex
   * 2: concave
   */
  int side;
  /*! Bold flag */
  bool bold;
  /*! Italic flag */
  bool italic;
  /*! Underline flag */
  bool underline;
  /*! Character set value. Windows character set identifier. */
  int characerSet;
  /*! Pitch and family value. Windows pitch and character family identifier. */
  int pitch;
  /*! Font type:
   * false: TTF
   * true: SHX
   */
  bool shxFont;
  /*! Wizard flag */
  bool wizard;
  /*! Arc handle/ID */
  int arcHandle;
} dxf_arc_aligned_text_data;

/**
 * Block attribute data.
 */
typedef struct dxf_attribute_data {
  double ipx;
  double ipy;
  double ipz;

  double apx;
  double apy;
  double apz;

  double height;
  double xScaleFactor;
  int textGenerationFlags;
  int hJustification;
  int vJustification;
  char *text;
  char *style;
  double angle;
  /*! Tag. */
  char *tag;
} dxf_attribute_data;

/**
 * Generic Dimension Data.
 */
typedef struct dxf_dimension_data {
  /*! X Coordinate of definition point. */
  double dpx;
  /*! Y Coordinate of definition point. */
  double dpy;
  /*! Z Coordinate of definition point. */
  double dpz;
  /*! X Coordinate of middle point of the text. */
  double mpx;
  /*! Y Coordinate of middle point of the text. */
  double mpy;
  /*! Z Coordinate of middle point of the text. */
  double mpz;
  /**
   * Dimension type.
   *
   * 0   Rotated, horizontal, or vertical
   * 1   Aligned
   * 2   Angular
   * 3   Diametric
   * 4   Radius
   * 5   Angular 3-point
   * 6   Ordinate
   * 64  Ordinate type. This is a bit value (bit 7)
   *     used only with integer value 6. If set,
   *     ordinate is X-type; if not set, ordinate is
   *     Y-type
   * 128 This is a bit value (bit 8) added to the
   *     other group 70 values if the dimension text
   *     has been positioned at a user-defined
   *    location rather than at the default location
   */
  int type;
  /**
   * Attachment point.
   *
   * 1 = Top left, 2 = Top center, 3 = Top right,
   * 4 = Middle left, 5 = Middle center, 6 = Middle right,
   * 7 = Bottom left, 8 = Bottom center, 9 = Bottom right,
   */
  int attachmentPoint;
  /**
   * Line spacing style.
   *
   * 1 = at least, 2 = exact
   */
  int lineSpacingStyle;
  /**
   * Line spacing factor. 0.25 .. 4.0
   */
  double lineSpacingFactor;
  /**
   * Text string.
   *
   * Text string entered explicitly by user or null
   * or "<>" for the actual measurement or " " (one blank space).
   * for supressing the text.
   */
  char *text;
  /*! Dimension style (font name). */
  char *style;
  /**
   * Rotation angle of dimension text away from
   * default orientation.
   */
  double angle;
  /**
   * Linear factor style override.
   */
  double linearFactor;
  /**
   * Dimension scale (dimscale) style override.
   */
  double dimScale;
  bool arrow1Flipped;
  bool arrow2Flipped;
} dxf_dimension_data;

/**
 * Aligned Dimension Data.
 */
typedef struct dxf_dim_aligned_data {
  /*! X Coordinate of Extension point 1. */
  double epx1;
  /*! Y Coordinate of Extension point 1. */
  double epy1;
  /*! Z Coordinate of Extension point 1. */
  double epz1;

  /*! X Coordinate of Extension point 2. */
  double epx2;
  /*! Y Coordinate of Extension point 2. */
  double epy2;
  /*! Z Coordinate of Extension point 2. */
  double epz2;
} dxf_dim_aligned_data;

/**
 * Linear (rotated) Dimension Data.
 */
typedef struct dxf_dim_linear_data {
  /*! X Coordinate of Extension point 1. */
  double dpx1;
  /*! Y Coordinate of Extension point 1. */
  double dpy1;
  /*! Z Coordinate of Extension point 1. */
  double dpz1;

  /*! X Coordinate of Extension point 2. */
  double dpx2;
  /*! Y Coordinate of Extension point 2. */
  double dpy2;
  /*! Z Coordinate of Extension point 2. */
  double dpz2;

  /*! Rotation angle (angle of dimension line) in degrees. */
  double angle;
  /*! Oblique angle in degrees. */
  double oblique;
} dxf_dim_linear_data;

/**
 * Radial Dimension Data.
 */
typedef struct dxf_dim_radial_data {
  /*! X Coordinate of definition point. */
  double dpx;
  /*! Y Coordinate of definition point. */
  double dpy;
  /*! Z Coordinate of definition point. */
  double dpz;

  /*! Leader length */
  double leader;
} dxf_dim_radial_data;

/**
 * Diametric Dimension Data.
 */
typedef struct dxf_dim_diametric_data {
  /*! X Coordinate of definition point (DXF 15). */
  double dpx;
  /*! Y Coordinate of definition point (DXF 25). */
  double dpy;
  /*! Z Coordinate of definition point (DXF 35). */
  double dpz;

  /*! Leader length */
  double leader;
} dxf_dim_diametric_data;

/**
 * Angular Dimension Data.
 */
typedef struct dxf_dim_angular2L_data {
  /*! X Coordinate of definition point 1. */
  double dpx1;
  /*! Y Coordinate of definition point 1. */
  double dpy1;
  /*! Z Coordinate of definition point 1. */
  double dpz1;

  /*! X Coordinate of definition point 2. */
  double dpx2;
  /*! Y Coordinate of definition point 2. */
  double dpy2;
  /*! Z Coordinate of definition point 2. */
  double dpz2;

  /*! X Coordinate of definition point 3. */
  double dpx3;
  /*! Y Coordinate of definition point 3. */
  double dpy3;
  /*! Z Coordinate of definition point 3. */
  double dpz3;

  /*! X Coordinate of definition point 4. */
  double dpx4;
  /*! Y Coordinate of definition point 4. */
  double dpy4;
  /*! Z Coordinate of definition point 4. */
  double dpz4;
} dxf_dim_angular2L_data;

/**
 * Angular Dimension Data (3 points version).
 */
typedef struct dxf_dim_angular3P_data {
  /*! X Coordinate of definition point 1 (extension line 1 end). */
  double dpx1;
  /*! Y Coordinate of definition point 1. */
  double dpy1;
  /*! Z Coordinate of definition point 1. */
  double dpz1;

  /*! X Coordinate of definition point 2 (extension line 2 end). */
  double dpx2;
  /*! Y Coordinate of definition point 2. */
  double dpy2;
  /*! Z Coordinate of definition point 2. */
  double dpz2;

  /*! X Coordinate of definition point 3 (center). */
  double dpx3;
  /*! Y Coordinate of definition point 3. */
  double dpy3;
  /*! Z Coordinate of definition point 3. */
  double dpz3;
} dxf_dim_angular3P_data;

/**
 * Ordinate Dimension Data.
 */
typedef struct dxf_dim_ordinate_data {
  /*! X Coordinate of definition point 1. */
  double dpx1;
  /*! Y Coordinate of definition point 1. */
  double dpy1;
  /*! Z Coordinate of definition point 1. */
  double dpz1;

  /*! X Coordinate of definition point 2. */
  double dpx2;
  /*! Y Coordinate of definition point 2. */
  double dpy2;
  /*! Z Coordinate of definition point 2. */
  double dpz2;

  /*! True if the dimension indicates the X-value, false for Y-value */
  bool xtype;
} dxf_dim_ordinate_data;

/**
 * Leader (arrow).
 */
typedef struct dxf_leader_data {
  /*! Arrow head flag (71). */
  int arrowHeadFlag;
  /*! Leader path type (72). */
  int leaderPathType;
  /*! Leader creation flag (73). */
  int leaderCreationFlag;
  /*! Hookline direction flag (74). */
  int hooklineDirectionFlag;
  /*! Hookline flag (75) */
  int hooklineFlag;
  /*! Text annotation height (40). */
  double textAnnotationHeight;
  /*! Text annotation width (41) */
  double textAnnotationWidth;
  /*! Number of vertices in leader (76). */
  int number;
  /*! Dimension scale (dimscale) style override. */
  double dimScale;
} dxf_leader_data;

/**
 * Leader Vertex Data.
 */
typedef struct dxf_leader_vertex_data {
  /*! X Coordinate of the vertex. */
  double x;
  /*! Y Coordinate of the vertex. */
  double y;
  /*! Z Coordinate of the vertex. */
  double z;
} dxf_leader_vertex_data;

/**
 * Hatch data.
 */
typedef struct dxf_hatch_data {
  /*! Number of boundary paths (loops). */
  int numLoops;
  /*! Solid fill flag (true=solid, false=pattern). */
  bool solid;
  /*! Pattern scale or spacing */
  double scale;
  /*! Pattern angle in degrees */
  double angle;
  /*! Pattern name. */
  char *pattern;
  /*! Pattern origin */
  double originX;
  double originY;
} dxf_hatch_data;

/**
 * Hatch boundary path (loop) data.
 */
typedef struct dxf_hatch_loop_data {
  /*! Number of edges in this loop. */
  int numEdges;
} dxf_hatch_loop_data;

/**
 * Hatch edge data.
 */
typedef struct dxf_hatch_edge_data {
  /**
   * Set to true if this edge is fully defined.
   */
  bool defined;

  /**
   * Edge type. 1=line, 2=arc, 3=elliptic arc, 4=spline.
   */
  int type;

  // line edges:

  /*! Start point (X). */
  double x1;
  /*! Start point (Y). */
  double y1;
  /*! End point (X). */
  double x2;
  /*! End point (Y). */
  double y2;

  /*! Center point of arc or ellipse arc (X). */
  double cx;
  /*! Center point of arc or ellipse arc (Y). */
  double cy;
  /*! Arc radius. */
  double radius;
  /*! Start angle of arc or ellipse arc. */
  double angle1;
  /*! End angle of arc or ellipse arc. */
  double angle2;
  /*! Counterclockwise flag for arc or ellipse arc. */
  bool ccw;

  /*! Major axis end point (X). */
  double mx;
  /*! Major axis end point (Y). */
  double my;
  /*! Axis ratio */
  double ratio;

  /*! Spline degree */
  unsigned int degree;
  bool rational;
  bool periodic;
  /*! Number of knots. */
  unsigned int nKnots;
  /*! Number of control points. */
  unsigned int nControl;
  /*! Number of fit points. */
  unsigned int nFit;

  double *controlPoints;
  double *knots;
  double *weights;
  double *fitPoints;

  double startTangentX;
  double startTangentY;

  double endTangentX;
  double endTangentY;

  /** Polyline boundary vertices (x y [bulge])*/
  double *vertices;
  // bool closed;
} dxf_hatch_edge_data;

/**
 * Image Data.
 */
typedef struct dxf_image_data {
  /*! Reference to the image file
      (unique, used to refer to the image def object). */
  char *ref;
  /*! X Coordinate of insertion point. */
  double ipx;
  /*! Y Coordinate of insertion point. */
  double ipy;
  /*! Z Coordinate of insertion point. */
  double ipz;
  /*! X Coordinate of u vector along bottom of image. */
  double ux;
  /*! Y Coordinate of u vector along bottom of image. */
  double uy;
  /*! Z Coordinate of u vector along bottom of image. */
  double uz;
  /*! X Coordinate of v vector along left side of image. */
  double vx;
  /*! Y Coordinate of v vector along left side of image. */
  double vy;
  /*! Z Coordinate of v vector along left side of image. */
  double vz;
  /*! Width of image in pixel. */
  int width;
  /*! Height of image in pixel. */
  int height;
  /*! Brightness (0..100, default = 50). */
  int brightness;
  /*! Contrast (0..100, default = 50). */
  int contrast;
  /*! Fade (0..100, default = 0). */
  int fade;
} dxf_image_data;

/**
 * Image Definition Data.
 */
typedef struct dxf_image_def_data {
  /*! Reference to the image file
      (unique, used to refer to the image def object). */
  char *ref;

  /*! Image file */
  char *file;
} dxf_image_def_data;

/**
 * Dictionary data.
 */
typedef struct dxf_dictionary_data {
  char *handle;
} dxf_dictionary_data;

/**
 * Dictionary entry data.
 */
typedef struct dxf_dictionary_entry_data {
  char *name;
  char *handle;
} dxf_dictionary_entry_data;

#ifdef __cplusplus
}
#endif

#endif // DXF_ENTITIES_H