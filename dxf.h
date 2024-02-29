#ifndef DXF_H
#define DXF_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BOOL  int32_t
#define FALSE 0
#define TRUE  1

#define DL_DXF_MAX_LINE       1024
#define DL_DXF_MAX_GROUP_CODE 1100

enum Color {
    black     = 250,
    green     = 3,
    red       = 1,
    brown     = 15,
    yellow    = 2,
    cyan      = 4,
    magenta   = 6,
    gray      = 8,
    blue      = 5,
    l_blue    = 163,
    l_green   = 121,
    l_cyan    = 131,
    l_red     = 23,
    l_magenta = 221,
    l_gray    = 252,
    white     = 7
};

/*
 * Version numbers for the DXF Format.
 */
enum Version {
    AC1009_MIN = 0, // R12, minimalistic
    AC1009,         // R12
    AC1012,
    AC1014,
    AC1015 // R2000
};

// Extended color palette:
// The first entry is only for direct indexing starting with [1]
// Color 1 is red (1,0,0)
const double dxfColors[][3] = {
#include "dxf_color.inl"
};

// AutoCAD VERSION aliases
#define DL_VERSION_R12  AC1009
#define DL_VERSION_LT2  AC1009
#define DL_VERSION_R13  AC1012 // not supported yet
#define DL_VERSION_LT95 AC1012 // not supported yet
#define DL_VERSION_R14  AC1014 // not supported yet
#define DL_VERSION_LT97 AC1014 // not supported yet
#define DL_VERSION_LT98 AC1014 // not supported yet
#define DL_VERSION_2000 AC1015
#define DL_VERSION_2002 AC1015

// DXF Group Codes:

// Strings
#define DL_STRGRP_START 0
#define DL_STRGRP_END   9

// Coordinates
#define DL_CRDGRP_START 10
#define DL_CRDGRP_END   19

// Real values
#define DL_RLGRP_START 38
#define DL_RLGRP_END   59

// Short integer values
#define DL_SHOGRP_START 60
#define DL_SHOGRP_END   79

// New in Release 13,
#define DL_SUBCLASS 100

// More coordinates
#define DL_CRD2GRP_START 210
#define DL_CRD2GRP_END   239

// Extended data strings
#define DL_ESTRGRP_START 1000
#define DL_ESTRGRP_END   1009

// Extended data reals
#define DL_ERLGRP_START 1010
#define DL_ERLGRP_END   1059

#define DL_Y8_COORD_CODE 28
#define DL_Z0_COORD_CODE 30
#define DL_Z8_COORD_CODE 38

#define DL_POINT_COORD_CODE  10
#define DL_INSERT_COORD_CODE 10

#define DL_CRD2GRP_START 210
#define DL_CRD2GRP_END   239

#define DL_THICKNESS        39
#define DL_FIRST_REAL_CODE  THICKNESS
#define DL_LAST_REAL_CODE   59
#define DL_FIRST_INT_CODE   60
#define DL_ATTFLAGS_CODE    70
#define DL_PLINE_FLAGS_CODE 70
#define DL_LAYER_FLAGS_CODE 70
#define DL_FLD_LEN_CODE     73 // Inside ATTRIB
#define DL_LAST_INT_CODE    79
#define DL_X_EXTRU_CODE     210
#define DL_Y_EXTRU_CODE     220
#define DL_Z_EXTRU_CODE     230
#define DL_COMMENT_CODE     999

// Start and endpoints of a line
#define DL_LINE_START_CODE 10 // Followed by x coord
#define DL_LINE_END_CODE   11 // Followed by x coord

// Some codes used by blocks
#define DL_BLOCK_FLAGS_CODE 70 // An int32_t containing flags
#define DL_BLOCK_BASE_CODE  10 // Origin of block definition
#define DL_XREF_DEPENDENT   16 // If a block contains an XREF
#define DL_XREF_RESOLVED    32 // If a XREF resolved ok
#define DL_REFERENCED       64 // If a block is ref'd in DWG

#define DL_XSCALE_CODE    41
#define DL_YSCALE_CODE    42
#define DL_ANGLE_CODE     50
#define DL_INS_POINT_CODE 10 // Followed by x of ins pnt
#define DL_NAME2_CODE     3  // Second appearance of name

// Some codes used by circle entities
#define DL_CENTER_CODE 10 // Followed by x of center
#define DL_RADIUS_CODE 40 // Followed by radius of circle

#define DL_COND_OP_CODE -4 // Conditional op,ads_sgetn

// When using ads_build's you MUST use RTDXF0 instead of these
#define DL_ENTITY_TYPE_CODE  0 // Then there is LINE, 3DFACE..
#define DL_SES_CODE          0 // Start End String Code
#define DL_FILE_SEP_CODE     0 // File separator
#define DL_SOT_CODE          0 // Start Of Table
#define DL_TEXTVAL_CODE      1
#define DL_NAME_CODE         2
#define DL_BLOCK_NAME_CODE   2
#define DL_SECTION_NAME_CODE 2
#define DL_ENT_HAND_CODE     5  // What follows is hex string
#define DL_TXT_STYLE_CODE    7  // Inside attributes
#define DL_LAYER_NAME_CODE   8  // What follows is layer name
#define DL_FIRST_XCOORD_CODE 10 // Group code x of 1st coord
#define DL_FIRST_YCOORD_CODE 20 // Group code y of 1st coord
#define DL_FIRST_ZCOORD_CODE 30 // Group code z of 1st coord
#define DL_L_START_CODE      10
#define DL_L_END_CODE        11
#define DL_TXTHI_CODE        40
#define DL_SCALE_X_CODE      41
#define DL_SCALE_Y_CODE      42
#define DL_SCALE_Z_CODE      43
#define DL_BULGE_CODE        42 // Used in PLINE vertex's for arcs
#define DL_ROTATION_CODE     50
#define DL_COLOUR_CODE       62 // What follows is a color int32_t
#define DL_LTYPE_CODE        6  // What follows is a linetype

// Attribute flags
#define DL_ATTS_FOLLOW_CODE 66
#define DL_ATT_TAG_CODE     2
#define DL_ATT_VAL_CODE     1
#define DL_ATT_FLAGS_CODE   70 // 4 1 bit flags as follows...
#define DL_ATT_INVIS_FLAG   1
#define DL_ATT_CONST_FLAG   2
#define DL_ATT_VERIFY_FLAG  4 // Prompt and verify
#define DL_ATT_PRESET_FLAG  8 // No prompt and no verify

// PLINE defines
// Flags
#define DL_OPEN_PLINE   0x00
#define DL_CLOSED_PLINE 0x01
#define DL_POLYLINE3D   0x08
#define DL_PFACE_MESH   0x40
#define DL_PGON_MESH    0x10
// Vertices follow entity, required in POLYLINES
#define DL_VERTS_FOLLOW_CODE 66 // Value should always be 1
#define DL_VERTEX_COORD_CODE 10

// LAYER flags
#define DL_FROZEN        1
#define DL_FROZEN_BY_DEF 2
#define DL_LOCKED        4
#define DL_OBJECT_USED   64 // Object is ref'd in the dwg

#define DL_BLOCK_EN_CODE -2 // Block entity definition
#define DL_E_NAME        -1 // Entity name

// Extended data codes
#define DL_EXTD_SENTINEL (-3)
#define DL_EXTD_STR      1000
#define DL_EXTD_APP_NAME 1001
#define DL_EXTD_CTL_STR  1002
#define DL_EXTD_LYR_STR  1003
#define DL_EXTD_CHUNK    1004
#define DL_EXTD_HANDLE   1005
#define DL_EXTD_POINT    1010
#define DL_EXTD_POS      1011
#define DL_EXTD_DISP     1012
#define DL_EXTD_DIR      1013
#define DL_EXTD_FLOAT    1040
#define DL_EXTD_DIST     1041
#define DL_EXTD_SCALE    1042
#define DL_EXTD_INT16    1070
#define DL_EXTD_INT32    1071

// UCS codes for use in ads_trans
#define DL_WCS_TRANS_CODE 0
#define DL_UCS_TRANS_CODE 1
#define DL_DCS_TRANS_CODE 2
#define DL_PCS_TRANS_CODE 3

#define DL_UNKNOWN               0
#define DL_LAYER                 10
#define DL_BLOCK                 11
#define DL_ENDBLK                12
#define DL_LINETYPE              13
#define DL_STYLE                 20
#define DL_SETTING               50
#define DL_ENTITY_POINT          100
#define DL_ENTITY_LINE           101
#define DL_ENTITY_POLYLINE       102
#define DL_ENTITY_LWPOLYLINE     103
#define DL_ENTITY_VERTEX         104
#define DL_ENTITY_SPLINE         105
#define DL_ENTITY_KNOT           106
#define DL_ENTITY_CONTROLPOINT   107
#define DL_ENTITY_ARC            108
#define DL_ENTITY_CIRCLE         109
#define DL_ENTITY_ELLIPSE        110
#define DL_ENTITY_INSERT         111
#define DL_ENTITY_TEXT           112
#define DL_ENTITY_MTEXT          113
#define DL_ENTITY_DIMENSION      114
#define DL_ENTITY_LEADER         115
#define DL_ENTITY_HATCH          116
#define DL_ENTITY_ATTRIB         117
#define DL_ENTITY_IMAGE          118
#define DL_ENTITY_IMAGEDEF       119
#define DL_ENTITY_TRACE          120
#define DL_ENTITY_SOLID          121
#define DL_ENTITY_3DFACE         122
#define DL_ENTITY_XLINE          123
#define DL_ENTITY_RAY            124
#define DL_ENTITY_ARCALIGNEDTEXT 125
#define DL_ENTITY_SEQEND         126
#define DL_XRECORD               200
#define DL_DICTIONARY            210

/*
 * Storing and passing around attributes. Attributes
 * are the layer name, color, width and line type.
 */
typedef struct dxf_attributes {
    const char *layer;
    const char *line_type;
    int32_t     color;
    int32_t     color24;
    int32_t     width;
    int32_t     handle;
    double      line_type_scale;
    BOOL        is_paper_space;
} dxf_attributes;

/*
 * Layer Data.
 */
typedef struct dxf_layer_data {
    /* Layer name. */
    char *name;
    /* Layer flags. (1 = frozen, 2 = frozen by default, 4 = locked) */
    int32_t flags;
    /* Layer is off */
    BOOL off;
} dxf_layer_data;

/*
 * Block Data.
 */
typedef struct dxf_block_data {
    /* Block name. */
    char *name;
    /* Block flags. (not used currently) */
    int32_t flags;
    /* X Coordinate of base point. */
    double bpx;
    /* Y Coordinate of base point. */
    double bpy;
    /* Z Coordinate of base point. */
    double bpz;
} dxf_block_data;

/*
 * Line Type Data.
 */
typedef struct dxf_line_type_data {
    /* Linetype name */
    char *name;
    /* Linetype description */
    char *description;
    /* Linetype flags */
    int32_t flags;
    /* Number of dashes */
    int32_t numberOfDashes;
    /* Pattern length */
    double patternLength;
    /* Pattern */
    double *pattern;
} dxf_line_type_data;

/*
 * Text style data.
 */
typedef struct dxf_style_data {
    /* Style name */
    char *name;
    /* Style flags */
    int32_t flags;
    /* Fixed text height or 0 for not fixed. */
    double fixedTextHeight;
    /* Width factor */
    double widthFactor;
    /* Oblique angle */
    double obliqueAngle;
    /* Text generation flags */
    int32_t textGenerationFlags;
    /* Last height used */
    double lastHeightUsed;
    /* Primary font file name */
    char *primaryFontFile;
    /* Big font file name */
    char *bigFontFile;

    BOOL bold;
    BOOL italic;
} dxf_style_data;

/*
 * Point Data.
 */
typedef struct dxf_point_data {
    /* X Coordinate of the point. */
    double x;
    /* Y Coordinate of the point. */
    double y;
    /* Z Coordinate of the point. */
    double z;
} dxf_point_data;

/*
 * Line Data.
 */
typedef struct dxf_line_data {
    /* X Start coordinate of the point. */
    double x1;
    /* Y Start coordinate of the point. */
    double y1;
    /* Z Start coordinate of the point. */
    double z1;

    /* X End coordinate of the point. */
    double x2;
    /* Y End coordinate of the point. */
    double y2;
    /* Z End coordinate of the point. */
    double z2;
} dxf_line_data;

/*
 * XLine Data.
 */
typedef struct dxf_xline_data {
    /* X base point. */
    double bx;
    /* Y base point. */
    double by;
    /* Z base point. */
    double bz;

    /* X direction vector. */
    double dx;
    /* Y direction vector. */
    double dy;
    /* Z direction vector. */
    double dz;
} dxf_xline_data;

/*
 * Ray Data.
 */
typedef struct dxf_ray_data {
    /* X base point. */
    double bx;
    /* Y base point. */
    double by;
    /* Z base point. */
    double bz;

    /* X direction vector. */
    double dx;
    /* Y direction vector. */
    double dy;
    /* Z direction vector. */
    double dz;
} dxf_ray_data;

/*
 * Arc Data.
 */
typedef struct dxf_arc_data {
    /* X Coordinate of center point. */
    double cx;
    /* Y Coordinate of center point. */
    double cy;
    /* Z Coordinate of center point. */
    double cz;

    /* Radius of arc. */
    double radius;
    /* Startangle of arc in degrees. */
    double angle1;
    /* Endangle of arc in degrees. */
    double angle2;
} dxf_arc_data;

/*
 * Circle Data.
 */
typedef struct dxf_circle_data {
    /* X Coordinate of center point. */
    double cx;
    /* Y Coordinate of center point. */
    double cy;
    /* Z Coordinate of center point. */
    double cz;

    /* Radius of arc. */
    double radius;
} dxf_circle_data;

/*
 * Polyline Data.
 */
typedef struct dxf_polyline_data {
    /* Number of vertices in this polyline. */
    uint32_t number;

    /* Number of vertices in m direction if polyline is a polygon mesh. */
    uint32_t m;

    /* Number of vertices in n direction if polyline is a polygon mesh. */
    uint32_t n;

    /* elevation of the polyline. */
    double elevation;

    /* Flags */
    int32_t flags;
} dxf_polyline_data;

/*
 * Vertex Data.
 */
typedef struct dxf_vertex_data {
    /* X Coordinate of the vertex. */
    double x;
    /* Y Coordinate of the vertex. */
    double y;
    /* Z Coordinate of the vertex. */
    double z;
    /* Bulge of vertex.
     * (The tangent of 1/4 of the arc angle or 0 for lines) */
    double bulge;
} dxf_vertex_data;

/*
 * Trace Data / solid data / 3d face data.
 */
typedef struct dxf_trace_data {
    /* Thickness */
    double thickness;

    /* Points */
    double x[4];
    double y[4];
    double z[4];
} dxf_trace_data;

/*
 * Solid Data.
 */
typedef dxf_trace_data dxf_solid_data;

/*
 * 3dface Data.
 */
typedef dxf_trace_data dxf_3d_face_data;

/*
 * Spline Data.
 */
typedef struct dxf_spline_data {
    /* Degree of the spline curve. */
    uint32_t degree;

    /* Number of knots. */
    uint32_t nKnots;

    /* Number of control points. */
    uint32_t nControl;

    /* Number of fit points. */
    uint32_t nFit;

    /* Flags */
    int32_t flags;

    double tangentStartX;
    double tangentStartY;
    double tangentStartZ;
    double tangentEndX;
    double tangentEndY;
    double tangentEndZ;
} dxf_spline_data;

/*
 * Spline knot data.
 */
typedef struct dxf_knot_data {
    /* Knot value. */
    double k;
} dxf_knot_data;

/*
 * Spline control point data.
 */
typedef struct dxf_control_point_data {
    /* X coordinate of the control point. */
    double x;
    /* Y coordinate of the control point. */
    double y;
    /* Z coordinate of the control point. */
    double z;
    /* Weight of control point. */
    double w;
} dxf_control_point_data;

/*
 * Spline fit point data.
 */
typedef struct dxf_fit_point_data {
    /* X coordinate of the fit point. */
    double x;
    /* Y coordinate of the fit point. */
    double y;
    /* Z coordinate of the fit point. */
    double z;
} dxf_fit_point_data;

/*
 * Ellipse Data.
 */
typedef struct dxf_ellipse_data {
    /* X Coordinate of center point. */
    double cx;
    /* Y Coordinate of center point. */
    double cy;
    /* Z Coordinate of center point. */
    double cz;

    /* X coordinate of the endpoint of the major axis. */
    double mx;
    /* Y coordinate of the endpoint of the major axis. */
    double my;
    /* Z coordinate of the endpoint of the major axis. */
    double mz;

    /* Ratio of minor axis to major axis.. */
    double ratio;
    /* Startangle of ellipse in rad. */
    double angle1;
    /* Endangle of ellipse in rad. */
    double angle2;
} dxf_ellipse_data;

/*
 * Insert Data.
 */
typedef struct dxf_insert_data {
    /* Name of the referred block. */
    char *name;
    /* X Coordinate of insertion point. */
    double ipx;
    /* Y Coordinate of insertion point. */
    double ipy;
    /* Z Coordinate of insertion point. */
    double ipz;
    /* X Scale factor. */
    double sx;
    /* Y Scale factor. */
    double sy;
    /* Z Scale factor. */
    double sz;
    /* Rotation angle in degrees. */
    double angle;
    /* Number of columns if we insert an array of the block or 1. */
    int32_t cols;
    /* Number of rows if we insert an array of the block or 1. */
    int32_t rows;
    /* Values for the spacing between cols. */
    double colSp;
    /* Values for the spacing between rows. */
    double rowSp;
} dxf_insert_data;

/*
 * MText Data.
 */
typedef struct dxf_mText_data {
    /* X Coordinate of insertion point. */
    double ipx;
    /* Y Coordinate of insertion point. */
    double ipy;
    /* Z Coordinate of insertion point. */
    double ipz;
    /* X Coordinate of X direction vector. */
    double dirX;
    /* Y Coordinate of X direction vector. */
    double dirY;
    /* Z Coordinate of X direction vector. */
    double dirZ;
    /* Text height */
    double height;
    /* Width of the text box. */
    double width;
    /*
     * Attachment point.
     *
     * 1 = Top left, 2 = Top center, 3 = Top right,
     * 4 = Middle left, 5 = Middle center, 6 = Middle right,
     * 7 = Bottom left, 8 = Bottom center, 9 = Bottom right
     */
    int32_t attachmentPoint;
    /*
     * Drawing direction.
     *
     * 1 = left to right, 3 = top to bottom, 5 = by style
     */
    int32_t drawingDirection;
    /*
     * Line spacing style.
     *
     * 1 = at least, 2 = exact
     */
    int32_t lineSpacingStyle;
    /*
     * Line spacing factor. 0.25 .. 4.0
     */
    double lineSpacingFactor;
    /* Text string. */
    char *text;
    /* Style string. */
    char *style;
    /* Rotation angle. */
    double angle;
} dxf_mText_data;

/*
 * Text Data.
 */
typedef struct dxf_text_data {
    /* X Coordinate of insertion point. */
    double ipx;
    /* Y Coordinate of insertion point. */
    double ipy;
    /* Z Coordinate of insertion point. */
    double ipz;

    /* X Coordinate of alignment point. */
    double apx;
    /* Y Coordinate of alignment point. */
    double apy;
    /* Z Coordinate of alignment point. */
    double apz;

    /* Text height */
    double height;
    /* Relative X scale factor. */
    double xScaleFactor;
    /* 0 = default, 2 = Backwards, 4 = Upside down */
    int32_t textGenerationFlags;
    /*
     * Horizontal justification.
     *
     * 0 = Left (default), 1 = Center, 2 = Right,
     * 3 = Aligned, 4 = Middle, 5 = Fit
     * For 3, 4, 5 the vertical alignment has to be 0.
     */
    int32_t hJustification;
    /*
     * Vertical justification.
     *
     * 0 = Baseline (default), 1 = Bottom, 2 = Middle, 3= Top
     */
    int32_t vJustification;
    /* Text string. */
    char *text;
    /* Style (font). */
    char *style;
    /* Rotation angle of dimension text away from default orientation. */
    double angle;
} dxf_text_data;

/*
 * Arc Aligned Text Data.
 */
typedef struct dxf_arc_aligned_text_data {

    /* Text string */
    char *text;
    /* Font name */
    char *font;
    /* Style */
    char *style;

    /* X coordinate of arc center point. */
    double cx;
    /* Y coordinate of arc center point. */
    double cy;
    /* Z coordinate of arc center point. */
    double cz;
    /* Arc radius. */
    double radius;

    /* Relative X scale factor. */
    double xScaleFactor;
    /* Text height */
    double height;
    /* Character spacing */
    double spacing;
    /* Offset from arc */
    double offset;
    /* Right offset */
    double rightOffset;
    /* Left offset */
    double leftOffset;
    /* Start angle (radians) */
    double startAngle;
    /* End angle (radians) */
    double endAngle;
    /* Reversed character order:
     * false: normal
     * true: reversed
     */
    BOOL reversedCharacterOrder;
    /* Direction
     * 1: outward from center
     * 2: inward from center
     */
    int32_t direction;
    /* Alignment:
     * 1: fit
     * 2: left
     * 3: right
     * 4: center
     */
    int32_t alignment;
    /* Side
     * 1: convex
     * 2: concave
     */
    int32_t side;
    /* Bold flag */
    BOOL bold;
    /* Italic flag */
    BOOL italic;
    /* Underline flag */
    BOOL underline;
    /* Character set value. Windows character set identifier. */
    int32_t characterSet;
    /* Pitch and family value. Windows pitch and character family identifier.
     */
    int32_t pitch;
    /* Font type:
     * false: TTF
     * true: SHX
     */
    BOOL shxFont;
    /* Wizard flag */
    BOOL wizard;
    /* Arc handle/ID */
    int32_t arcHandle;
} dxf_arc_aligned_text_data;

/*
 * Block attribute data.
 */
typedef struct dxf_attribute_data {
    double ipx;
    double ipy;
    double ipz;

    double apx;
    double apy;
    double apz;

    double  height;
    double  xScaleFactor;
    int32_t textGenerationFlags;
    int32_t hJustification;
    int32_t vJustification;
    char   *text;
    char   *style;
    double  angle;
    /* Tag. */
    char *tag;
} dxf_attribute_data;

/*
 * Generic Dimension Data.
 */
typedef struct dxf_dimension_data {
    /* X Coordinate of definition point. */
    double dpx;
    /* Y Coordinate of definition point. */
    double dpy;
    /* Z Coordinate of definition point. */
    double dpz;
    /* X Coordinate of middle point of the text. */
    double mpx;
    /* Y Coordinate of middle point of the text. */
    double mpy;
    /* Z Coordinate of middle point of the text. */
    double mpz;
    /*
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
    int32_t type;
    /*
     * Attachment point.
     *
     * 1 = Top left, 2 = Top center, 3 = Top right,
     * 4 = Middle left, 5 = Middle center, 6 = Middle right,
     * 7 = Bottom left, 8 = Bottom center, 9 = Bottom right,
     */
    int32_t attachmentPoint;
    /*
     * Line spacing style.
     *
     * 1 = at least, 2 = exact
     */
    int32_t lineSpacingStyle;
    /*
     * Line spacing factor. 0.25 .. 4.0
     */
    double lineSpacingFactor;
    /*
     * Text string.
     *
     * Text string entered explicitly by user or null
     * or "<>" for the actual measurement or " " (one blank space).
     * for supressing the text.
     */
    char *text;
    /* Dimension style (font name). */
    char *style;
    /*
     * Rotation angle of dimension text away from
     * default orientation.
     */
    double angle;
    /*
     * Linear factor style override.
     */
    double linearFactor;
    /*
     * Dimension scale (dimScale) style override.
     */
    double dimScale;
    BOOL   arrow1Flipped;
    BOOL   arrow2Flipped;
} dxf_dimension_data;

/*
 * Aligned Dimension Data.
 */
typedef struct dxf_dim_aligned_data {
    /* X Coordinate of Extension point 1. */
    double epx1;
    /* Y Coordinate of Extension point 1. */
    double epy1;
    /* Z Coordinate of Extension point 1. */
    double epz1;

    /* X Coordinate of Extension point 2. */
    double epx2;
    /* Y Coordinate of Extension point 2. */
    double epy2;
    /* Z Coordinate of Extension point 2. */
    double epz2;
} dxf_dim_aligned_data;

/*
 * Linear (rotated) Dimension Data.
 */
typedef struct dxf_dim_linear_data {
    /* X Coordinate of Extension point 1. */
    double dpx1;
    /* Y Coordinate of Extension point 1. */
    double dpy1;
    /* Z Coordinate of Extension point 1. */
    double dpz1;

    /* X Coordinate of Extension point 2. */
    double dpx2;
    /* Y Coordinate of Extension point 2. */
    double dpy2;
    /* Z Coordinate of Extension point 2. */
    double dpz2;

    /* Rotation angle (angle of dimension line) in degrees. */
    double angle;
    /* Oblique angle in degrees. */
    double oblique;
} dxf_dim_linear_data;

/*
 * Radial Dimension Data.
 */
typedef struct dxf_dim_radial_data {
    /* X Coordinate of definition point. */
    double dpx;
    /* Y Coordinate of definition point. */
    double dpy;
    /* Z Coordinate of definition point. */
    double dpz;

    /* Leader length */
    double leader;
} dxf_dim_radial_data;

/*
 * Diametric Dimension Data.
 */
typedef struct dxf_dim_diametric_data {
    /* X Coordinate of definition point (DXF 15). */
    double dpx;
    /* Y Coordinate of definition point (DXF 25). */
    double dpy;
    /* Z Coordinate of definition point (DXF 35). */
    double dpz;

    /* Leader length */
    double leader;
} dxf_dim_diametric_data;

/*
 * Angular Dimension Data.
 */
typedef struct dxf_dim_angular2L_data {
    /* X Coordinate of definition point 1. */
    double dpx1;
    /* Y Coordinate of definition point 1. */
    double dpy1;
    /* Z Coordinate of definition point 1. */
    double dpz1;

    /* X Coordinate of definition point 2. */
    double dpx2;
    /* Y Coordinate of definition point 2. */
    double dpy2;
    /* Z Coordinate of definition point 2. */
    double dpz2;

    /* X Coordinate of definition point 3. */
    double dpx3;
    /* Y Coordinate of definition point 3. */
    double dpy3;
    /* Z Coordinate of definition point 3. */
    double dpz3;

    /* X Coordinate of definition point 4. */
    double dpx4;
    /* Y Coordinate of definition point 4. */
    double dpy4;
    /* Z Coordinate of definition point 4. */
    double dpz4;
} dxf_dim_angular2L_data;

/*
 * Angular Dimension Data (3 points version).
 */
typedef struct dxf_dim_angular3P_data {
    /* X Coordinate of definition point 1 (extension line 1 end). */
    double dpx1;
    /* Y Coordinate of definition point 1. */
    double dpy1;
    /* Z Coordinate of definition point 1. */
    double dpz1;

    /* X Coordinate of definition point 2 (extension line 2 end). */
    double dpx2;
    /* Y Coordinate of definition point 2. */
    double dpy2;
    /* Z Coordinate of definition point 2. */
    double dpz2;

    /* X Coordinate of definition point 3 (center). */
    double dpx3;
    /* Y Coordinate of definition point 3. */
    double dpy3;
    /* Z Coordinate of definition point 3. */
    double dpz3;
} dxf_dim_angular3P_data;

/*
 * Ordinate Dimension Data.
 */
typedef struct dxf_dim_ordinate_data {
    /* X Coordinate of definition point 1. */
    double dpx1;
    /* Y Coordinate of definition point 1. */
    double dpy1;
    /* Z Coordinate of definition point 1. */
    double dpz1;

    /* X Coordinate of definition point 2. */
    double dpx2;
    /* Y Coordinate of definition point 2. */
    double dpy2;
    /* Z Coordinate of definition point 2. */
    double dpz2;

    /* True if the dimension indicates the X-value, false for Y-value */
    BOOL xtype;
} dxf_dim_ordinate_data;

/*
 * Leader (arrow).
 */
typedef struct dxf_leader_data {
    /* Arrow head flag (71). */
    int32_t arrowHeadFlag;
    /* Leader path type (72). */
    int32_t leaderPathType;
    /* Leader creation flag (73). */
    int32_t leaderCreationFlag;
    /* Hookline direction flag (74). */
    int32_t hooklineDirectionFlag;
    /* Hookline flag (75) */
    int32_t hooklineFlag;
    /* Text annotation height (40). */
    double textAnnotationHeight;
    /* Text annotation width (41) */
    double textAnnotationWidth;
    /* Number of vertices in leader (76). */
    int32_t number;
    /* Dimension scale (dimScale) style override. */
    double dimScale;
} dxf_leader_data;

/*
 * Leader Vertex Data.
 */
typedef struct dxf_leader_vertex_data {
    /* X Coordinate of the vertex. */
    double x;
    /* Y Coordinate of the vertex. */
    double y;
    /* Z Coordinate of the vertex. */
    double z;
} dxf_leader_vertex_data;

/*
 * Hatch data.
 */
typedef struct dxf_hatch_data {
    /* Number of boundary paths (loops). */
    int32_t numLoops;
    /* Solid fill flag (true=solid, false=pattern). */
    BOOL solid;
    /* Pattern scale or spacing */
    double scale;
    /* Pattern angle in degrees */
    double angle;
    /* Pattern name. */
    char *pattern;
    /* Pattern origin */
    double originX;
    double originY;
} dxf_hatch_data;

/*
 * Hatch boundary path (loop) data.
 */
typedef struct dxf_hatch_loop_data {
    /* Number of edges in this loop. */
    int32_t numEdges;
} dxf_hatch_loop_data;

/*
 * Hatch edge data.
 */
typedef struct dxf_hatch_edge_data {
    /*
     * Set to true if this edge is fully defined.
     */
    BOOL defined;

    /*
     * Edge type. 1=line, 2=arc, 3=elliptic arc, 4=spline.
     */
    int32_t type;

    // line edges:

    /* Start point (X). */
    double x1;
    /* Start point (Y). */
    double y1;
    /* End point (X). */
    double x2;
    /* End point (Y). */
    double y2;

    /* Center point of arc or ellipse arc (X). */
    double cx;
    /* Center point of arc or ellipse arc (Y). */
    double cy;
    /* Arc radius. */
    double radius;
    /* Start angle of arc or ellipse arc. */
    double angle1;
    /* End angle of arc or ellipse arc. */
    double angle2;
    /* Counterclockwise flag for arc or ellipse arc. */
    BOOL ccw;

    /* Major axis end point (X). */
    double mx;
    /* Major axis end point (Y). */
    double my;
    /* Axis ratio */
    double ratio;

    /* Spline degree */
    uint32_t degree;
    BOOL     rational;
    BOOL     periodic;
    /* Number of knots. */
    uint32_t nKnots;
    /* Number of control points. */
    uint32_t nControl;
    /* Number of fit points. */
    uint32_t nFit;

    double *controlPoints;
    double *knots;
    double *weights;
    double *fitPoints;

    double startTangentX;
    double startTangentY;

    double endTangentX;
    double endTangentY;

    /* Polyline boundary vertices (x y [bulge])*/
    double *vertices;
    // BOOL closed;
} dxf_hatch_edge_data;

/*
 * Image Data.
 */
typedef struct dxf_image_data {
    /* Reference to the image file
        (unique, used to refer to the image def object). */
    char *ref;
    /* X Coordinate of insertion point. */
    double ipx;
    /* Y Coordinate of insertion point. */
    double ipy;
    /* Z Coordinate of insertion point. */
    double ipz;
    /* X Coordinate of u vector along bottom of image. */
    double ux;
    /* Y Coordinate of u vector along bottom of image. */
    double uy;
    /* Z Coordinate of u vector along bottom of image. */
    double uz;
    /* X Coordinate of v vector along left side of image. */
    double vx;
    /* Y Coordinate of v vector along left side of image. */
    double vy;
    /* Z Coordinate of v vector along left side of image. */
    double vz;
    /* Width of image in pixel. */
    int32_t width;
    /* Height of image in pixel. */
    int32_t height;
    /* Brightness (0..100, default = 50). */
    int32_t brightness;
    /* Contrast (0..100, default = 50). */
    int32_t contrast;
    /* Fade (0..100, default = 0). */
    int32_t fade;
} dxf_image_data;

/*
 * Image Definition Data.
 */
typedef struct dxf_image_def_data {
    /* Reference to the image file
        (unique, used to refer to the image def object). */
    char *ref;

    /* Image file */
    char *file;
} dxf_image_def_data;

/*
 * Dictionary data.
 */
typedef struct dxf_dictionary_data {
    char *handle;
} dxf_dictionary_data;

/*
 * Dictionary entry data.
 */
typedef struct dxf_dictionary_entry_data {
    char *name;
    char *handle;
} dxf_dictionary_entry_data;

typedef struct __dxf_document dxf_document_t;
typedef struct __dxf_write    dxf_write_t;

/* -------------------------------------------------------------------------- */
/*                           dxf document functions                           */
/* -------------------------------------------------------------------------- */

dxf_document_t *create_document();
dxf_write_t    *out(dxf_document_t *doc, const char *filename);
void            destroy_document(dxf_document_t *doc);
void            destroy_write(dxf_write_t *w);

/* -------------------------------------------------------------------------- */
/*                             dxf write functions                            */
/* -------------------------------------------------------------------------- */

int32_t dxf_write_real(dxf_write_t *w, int32_t gc, double value);
int32_t dxf_write_int(dxf_write_t *w, int32_t gc, int32_t value);
int32_t dxf_write_BOOL(dxf_write_t *w, int32_t gc, BOOL value);
int32_t dxf_write_hex(dxf_write_t *w, int32_t gc, int32_t value);
int32_t dxf_write_string(dxf_write_t *w, int32_t gc, const char *value);

int32_t dxf_write_header(dxf_document_t *doc, dxf_write_t *w);

int32_t dxf_write_point(dxf_document_t *doc,
                        dxf_write_t    *w,
                        dxf_point_data *data,
                        dxf_attributes *attr);
int32_t dxf_write_line(dxf_document_t *doc,
                       dxf_write_t    *w,
                       dxf_line_data  *data,
                       dxf_attributes *attr);
int32_t dxf_write_xline(dxf_document_t *doc,
                        dxf_write_t    *w,
                        dxf_xline_data *data,
                        dxf_attributes *attr);
int32_t dxf_write_ray(dxf_document_t *doc,
                      dxf_write_t    *w,
                      dxf_ray_data   *data,
                      dxf_attributes *attr);
int32_t dxf_write_polyline(dxf_document_t    *doc,
                           dxf_write_t       *w,
                           dxf_polyline_data *data,
                           dxf_attributes    *attr);
int32_t
dxf_write_vertex(dxf_document_t *doc, dxf_write_t *w, dxf_vertex_data *data);
int32_t dxf_write_polyline_end(dxf_document_t *doc, dxf_write_t *w);
int32_t dxf_write_spline(dxf_document_t  *doc,
                         dxf_write_t     *w,
                         dxf_spline_data *data,
                         dxf_attributes  *attr);
int32_t dxf_write_control_point(dxf_document_t         *doc,
                                dxf_write_t            *w,
                                dxf_control_point_data *data);
int32_t dxf_write_fit_point(dxf_document_t     *doc,
                            dxf_write_t        *w,
                            dxf_fit_point_data *data);
int32_t
dxf_write_knot(dxf_document_t *doc, dxf_write_t *w, dxf_knot_data *data);
int32_t dxf_write_circle(dxf_document_t  *doc,
                         dxf_write_t     *w,
                         dxf_circle_data *data,
                         dxf_attributes  *attr);
int32_t dxf_write_arc(dxf_document_t *doc,
                      dxf_write_t    *w,
                      dxf_arc_data   *data,
                      dxf_attributes *attr);
int32_t dxf_write_ellipse(dxf_document_t   *doc,
                          dxf_write_t      *w,
                          dxf_ellipse_data *data,
                          dxf_attributes   *attr);
int32_t dxf_write_solid(dxf_document_t *doc,
                        dxf_write_t    *w,
                        dxf_solid_data *data,
                        dxf_attributes *attr);
int32_t dxf_write_trace(dxf_document_t *doc,
                        dxf_write_t    *w,
                        dxf_trace_data *data,
                        dxf_attributes *attr);
int32_t dxf_write_3dFace(dxf_document_t   *doc,
                         dxf_write_t      *w,
                         dxf_3d_face_data *data,
                         dxf_attributes   *attr);
int32_t dxf_write_insert(dxf_document_t  *doc,
                         dxf_write_t     *w,
                         dxf_insert_data *data,
                         dxf_attributes  *attr);
int32_t dxf_write_mText(dxf_document_t *doc,
                        dxf_write_t    *w,
                        dxf_mText_data *data,
                        dxf_attributes *attr);
int32_t dxf_write_text(dxf_document_t *doc,
                       dxf_write_t    *w,
                       dxf_text_data  *data,
                       dxf_attributes *attr);
int32_t dxf_write_attribute(dxf_document_t     *doc,
                            dxf_write_t        *w,
                            dxf_attribute_data *data,
                            dxf_attributes     *attr);
int32_t dxf_write_dim_style_overrides(dxf_document_t     *doc,
                                      dxf_write_t        *w,
                                      dxf_dimension_data *data);
int32_t dxf_write_dim_aligned(dxf_document_t       *doc,
                              dxf_write_t          *w,
                              dxf_dimension_data   *data,
                              dxf_dim_aligned_data *edata,
                              dxf_attributes       *attr);
int32_t dxf_write_dim_linear(dxf_document_t      *doc,
                             dxf_write_t         *w,
                             dxf_dimension_data  *data,
                             dxf_dim_linear_data *edata,
                             dxf_attributes      *attr);
int32_t dxf_write_dim_radial(dxf_document_t      *doc,
                             dxf_write_t         *w,
                             dxf_dimension_data  *data,
                             dxf_dim_radial_data *edata,
                             dxf_attributes      *attr);
int32_t dxf_write_dim_diametric(dxf_document_t         *doc,
                                dxf_write_t            *w,
                                dxf_dimension_data     *data,
                                dxf_dim_diametric_data *edata,
                                dxf_attributes         *attr);
int32_t dxf_write_dim_angular2L(dxf_document_t         *doc,
                                dxf_write_t            *w,
                                dxf_dimension_data     *data,
                                dxf_dim_angular2L_data *edata,
                                dxf_attributes         *attr);
int32_t dxf_write_dim_angular3P(dxf_document_t         *doc,
                                dxf_write_t            *w,
                                dxf_dimension_data     *data,
                                dxf_dim_angular3P_data *edata,
                                dxf_attributes         *attr);
int32_t dxf_write_dim_ordinate(dxf_document_t        *doc,
                               dxf_write_t           *w,
                               dxf_dimension_data    *data,
                               dxf_dim_ordinate_data *edata,
                               dxf_attributes        *attr);
int32_t dxf_write_leader(dxf_document_t  *doc,
                         dxf_write_t     *w,
                         dxf_leader_data *data,
                         dxf_attributes  *attr);
int32_t dxf_write_leader_vertex(dxf_document_t         *doc,
                                dxf_write_t            *w,
                                dxf_leader_vertex_data *data);
int32_t dxf_write_leader_end(dxf_document_t  *doc,
                             dxf_write_t     *w,
                             dxf_leader_data *data);
int32_t dxf_write_hatch1(dxf_document_t *doc,
                         dxf_write_t    *w,
                         dxf_hatch_data *data,
                         dxf_attributes *attr);
int32_t dxf_write_hatch2(dxf_document_t *doc,
                         dxf_write_t    *w,
                         dxf_hatch_data *data,
                         dxf_attributes *attr);
int32_t dxf_write_hatch_loop1(dxf_document_t      *doc,
                              dxf_write_t         *w,
                              dxf_hatch_loop_data *data);
int32_t dxf_write_hatch_loop2(dxf_document_t      *doc,
                              dxf_write_t         *w,
                              dxf_hatch_loop_data *data);
int32_t dxf_write_hatch_edge(dxf_document_t      *doc,
                             dxf_write_t         *w,
                             dxf_hatch_edge_data *data);

uint32_t dxf_write_image(dxf_document_t *doc,
                         dxf_write_t    *w,
                         dxf_image_data *data,
                         dxf_attributes *attr);

int32_t dxf_write_image_def(dxf_document_t *doc,
                            dxf_write_t    *w,
                            int32_t         handle,
                            dxf_image_data *data);

int32_t dxf_write_layer(dxf_document_t *doc,
                        dxf_write_t    *w,
                        dxf_layer_data *data,
                        dxf_attributes *attr);

int32_t dxf_write_line_type(dxf_document_t     *doc,
                            dxf_write_t        *w,
                            dxf_line_type_data *data);

int32_t dxf_write_appid(dxf_document_t *doc, dxf_write_t *w, const char *name);

int32_t
dxf_write_block(dxf_document_t *doc, dxf_write_t *w, dxf_block_data *data);
int32_t
dxf_write_end_block(dxf_document_t *doc, dxf_write_t *w, const char *name);

int32_t dxf_write_view_port(dxf_document_t *doc, dxf_write_t *w);
int32_t
dxf_write_style(dxf_document_t *doc, dxf_write_t *w, dxf_style_data *style);
int32_t dxf_write_view(dxf_document_t *doc, dxf_write_t *w);
int32_t dxf_write_ucs(dxf_document_t *doc, dxf_write_t *w);
int32_t dxf_write_dim_style(dxf_document_t *doc,
                            dxf_write_t    *w,
                            double          dimasz,
                            double          dimexe,
                            double          dimexo,
                            double          dimgap,
                            double          dimtxt,
                            int32_t         dimtad,
                            BOOL            dimtih);
int32_t
dxf_write_block_record(dxf_document_t *doc, dxf_write_t *w, const char *name);
int32_t  dxf_write_objects(dxf_document_t *doc,
                           dxf_write_t    *w,
                           const char     *appDictionaryName);
int32_t  dxf_write_app_dictionary(dxf_document_t *doc, dxf_write_t *w);
uint32_t dxf_write_dictionary_entry(dxf_document_t *doc,
                                    dxf_write_t    *w,
                                    const char     *name);
int32_t  dxf_write_x_record_int(dxf_document_t *doc,
                                dxf_write_t    *w,
                                int32_t         handle,
                                int32_t         value);
int32_t  dxf_write_x_record_double(dxf_document_t *doc,
                                   dxf_write_t    *w,
                                   int32_t         handle,
                                   double          value);
int32_t  dxf_write_x_record_BOOLean(dxf_document_t *doc,
                                    dxf_write_t    *w,
                                    int32_t         handle,
                                    BOOL            value);
int32_t  dxf_write_x_record_string(dxf_document_t *doc,
                                   dxf_write_t    *w,
                                   int32_t         handle,
                                   const char     *value);
int32_t  dxf_write_objects_end(dxf_document_t *doc, dxf_write_t *w);

int32_t
dxf_write_comment(dxf_document_t *doc, dxf_write_t *w, const char *comment);

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
    void (*add_dim_angular)(dxf_dimension_data *,
                            const dxf_dim_angular2L_data *);
    void (*add_dim_angular3P)(dxf_dimension_data *,
                              const dxf_dim_angular3P_data *);
    void (*add_dim_ordinate)(dxf_dimension_data *,
                             const dxf_dim_ordinate_data *);
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
    void (*add_x_record_string)(int32_t, const char *);
    void (*add_x_record_real)(int32_t, double);
    void (*add_x_record_int)(int32_t, int32_t);
    void (*add_x_record_BOOL)(int32_t, BOOL);

    void (*add_x_data_app)(const char *);
    void (*add_x_data_string)(int32_t, const char *);
    void (*add_x_data_real)(int32_t, double);
    void (*add_x_data_int)(int32_t, int32_t);

    void (*add_dictionary)(dxf_dictionary_data *);
    void (*add_dictionary_entry)(dxf_dictionary_entry_data *);

    void (*end_entity)();

    void (*add_comment)(const char *);

    void (*set_variable_vector)(const char *, double, double, double, int32_t);
    void (*set_variable_string)(const char *, const char *, int32_t);
    void (*set_variable_int)(const char *, int32_t, int32_t);
    void (*set_variable_double)(const char *, double, int32_t);

    void (*end_sequence)();
} dxf_reader_t;

#ifdef __cplusplus
}
#endif

#endif // DXF_H