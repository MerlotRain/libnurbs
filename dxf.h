#ifndef DXF_H
#define DXF_H

#ifdef _WIN32
#    ifdef DXF_DYN_LINK
#        ifdef DXF_SOURCE
#            define DXF_API __declspec(dllexport)
#        else
#            define DXF_API __declspec(dllimport)
#        endif
#    else
#        define DXF_API
#    endif
#else
#    define DXF_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
typedef int              dxf_BOOL;
typedef unsigned char    dxf_U8;
typedef unsigned short   dxf_U16;
typedef unsigned int     dxf_U32;
typedef unsigned __int64 dxf_U64;
typedef char             dxf_I8;
typedef short            dxf_I16;
typedef int              dxf_I32;
typedef __int64          dxf_I64;
typedef char             dxf_CHAR;
typedef float            dxf_F32;
typedef double           dxf_F64;
typedef void            *dxf_POINTER;
#else
#    include <stdint.h>
typedef int                dxf_BOOL;
typedef unsigned char      dxf_U8;
typedef unsigned short     dxf_U16;
typedef unsigned int       dxf_U32;
typedef unsigned long long dxf_U64;
typedef signed char        dxf_I8;
typedef short              dxf_I16;
typedef int                dxf_I32;
typedef long long          dxf_I64;
typedef char               dxf_CHAR;
typedef float              dxf_F32;
typedef double             dxf_F64;
typedef void              *dxf_POINTER;
#endif

#define FALSE 0
#define TRUE  1

#define DL_DXF_MAX_STRING     1024
#define DL_DXF_MAX_LINE       1024
#define DL_DXF_MAX_GROUP_CODE 1100

/* ------------------------------------------------------------------------------------ */
/*                                   Dxf kernel codes                                   */
/* ------------------------------------------------------------------------------------ */

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

/* Version numbers for the DXF Format. */
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
const dxf_F64 dxfColors[][3] = {
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
#define DL_BLOCK_FLAGS_CODE 70 // An dxf_I32 containing flags
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
#define DL_COLOUR_CODE       62 // What follows is a color dxf_I32
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

/* ------------------------------------------------------------------------------------ */
/*                                 Dxf Entity Structure                                 */
/* ------------------------------------------------------------------------------------ */

/* Storing and passing around attributes. Attributes are the layer name, color, width and
 * line type. */
typedef struct dxf_attributes {
    dxf_CHAR layer[512];
    dxf_CHAR line_type[512];
    dxf_I32  color;
    dxf_I32  color24;
    dxf_I32  width;
    dxf_I32  handle;
    dxf_F64  line_type_scale;
    dxf_BOOL is_paper_space;
} dxf_attributes;

/* Layer Data. */
typedef struct dxf_layer_data {
    dxf_CHAR name[512]; /* Layer name. */
    dxf_I32  flags;     /* Layer flags. (1 = frozen, 2 = frozen by default, 4 =
                           locked) */
    dxf_BOOL off;       /* Layer is off */
} dxf_layer_data;

/* Block Data. */
typedef struct dxf_block_data {
    dxf_CHAR name[512]; /* Block name. */
    dxf_I32  flags;     /* Block flags. (not used currently) */
    dxf_F64  bpx;       /* X Coordinate of base point. */
    dxf_F64  bpy;       /* Y Coordinate of base point. */
    dxf_F64  bpz;       /* Z Coordinate of base point. */
} dxf_block_data;

/* Line Type Data. */
typedef struct dxf_line_type_data {
    dxf_CHAR name[512];        /* Linetype name */
    dxf_CHAR description[512]; /* Linetype description */
    dxf_I32  flags;            /* Linetype flags */
    dxf_I32  numberOfDashes;   /* Number of dashes */
    dxf_F64  patternLength;    /* Pattern length */
    dxf_F64 *pattern;          /* Pattern */
} dxf_line_type_data;

/* Text style data. */
typedef struct dxf_style_data {
    dxf_CHAR name[512];            /* Style name */
    dxf_I32  flags;                /* Style flags */
    dxf_F64  fixedTextHeight;      /* Fixed text height or 0 for not fixed. */
    dxf_F64  widthFactor;          /* Width factor */
    dxf_F64  obliqueAngle;         /* Oblique angle */
    dxf_I32  textGenerationFlags;  /* Text generation flags */
    dxf_F64  lastHeightUsed;       /* Last height used */
    dxf_CHAR primaryFontFile[512]; /* Primary font file name */
    dxf_CHAR bigFontFile[512];     /* Big font file name */
    dxf_BOOL bold;
    dxf_BOOL italic;
} dxf_style_data;

/* Point Data. */
typedef struct dxf_point_data {
    dxf_F64 x; /* X Coordinate of the point. */
    dxf_F64 y; /* Y Coordinate of the point. */
    dxf_F64 z; /* Z Coordinate of the point. */
} dxf_point_data;

/* Line Data. */
typedef struct dxf_line_data {
    dxf_F64 x1; /* X Start coordinate of the point. */
    dxf_F64 y1; /* Y Start coordinate of the point. */
    dxf_F64 z1; /* Z Start coordinate of the point. */
    dxf_F64 x2; /* X End coordinate of the point. */
    dxf_F64 y2; /* Y End coordinate of the point. */
    dxf_F64 z2; /* Z End coordinate of the point. */
} dxf_line_data;

/* XLine Data. */
typedef struct dxf_xline_data {
    dxf_F64 bx; /* X base point. */
    dxf_F64 by; /* Y base point. */
    dxf_F64 bz; /* Z base point. */
    dxf_F64 dx; /* X direction vector. */
    dxf_F64 dy; /* Y direction vector. */
    dxf_F64 dz; /* Z direction vector. */
} dxf_xline_data;

/* Ray Data. */
typedef struct dxf_ray_data {
    dxf_F64 bx; /* X base point. */
    dxf_F64 by; /* Y base point. */
    dxf_F64 bz; /* Z base point. */
    dxf_F64 dx; /* X direction vector. */
    dxf_F64 dy; /* Y direction vector. */
    dxf_F64 dz; /* Z direction vector. */
} dxf_ray_data;

/* Arc Data. */
typedef struct dxf_arc_data {
    dxf_F64 cx;     /* X Coordinate of center point. */
    dxf_F64 cy;     /* Y Coordinate of center point. */
    dxf_F64 cz;     /* Z Coordinate of center point. */
    dxf_F64 radius; /* Radius of arc. */
    dxf_F64 angle1; /* Startangle of arc in degrees. */
    dxf_F64 angle2; /* Endangle of arc in degrees. */
} dxf_arc_data;

/* Circle Data. */
typedef struct dxf_circle_data {
    dxf_F64 cx;     /* X Coordinate of center point. */
    dxf_F64 cy;     /* Y Coordinate of center point. */
    dxf_F64 cz;     /* Z Coordinate of center point. */
    dxf_F64 radius; /* Radius of arc. */
} dxf_circle_data;

/* Polyline Data. */
typedef struct dxf_polyline_data {
    uint32_t number; /* Number of vertices in this polyline. */
    uint32_t m;      /* Number of vertices in m direction if polyline is a polygon
                        mesh. */
    uint32_t n;      /* Number of vertices in n direction if polyline is a polygon
                        mesh. */
    /* elevation of the polyline. */
    dxf_F64 elevation;
    dxf_I32 flags; /* Flags */
} dxf_polyline_data;

/* Vertex Data. */
typedef struct dxf_vertex_data {
    dxf_F64 x;     /* X Coordinate of the vertex. */
    dxf_F64 y;     /* Y Coordinate of the vertex. */
    dxf_F64 z;     /* Z Coordinate of the vertex. */
    dxf_F64 bulge; /* Bulge of vertex. (The tangent of 1/4 of the arc angle or 0
                     for lines) */
} dxf_vertex_data;

/* Trace Data / solid data / 3d face data. */
typedef struct dxf_trace_data {
    dxf_F64 thickness; /* Thickness */
    dxf_F64 x[4];      /* Points */
    dxf_F64 y[4];
    dxf_F64 z[4];
} dxf_trace_data, dxf_solid_data, dxf_3d_face_data;

/* Spline Data. */
typedef struct dxf_spline_data {
    uint32_t degree;   /* Degree of the spline curve. */
    uint32_t nKnots;   /* Number of knots. */
    uint32_t nControl; /* Number of control points. */
    uint32_t nFit;     /* Number of fit points. */
    dxf_I32  flags;    /* Flags */
    dxf_F64  tangentStartX;
    dxf_F64  tangentStartY;
    dxf_F64  tangentStartZ;
    dxf_F64  tangentEndX;
    dxf_F64  tangentEndY;
    dxf_F64  tangentEndZ;
} dxf_spline_data;

/* Spline knot data. */
typedef struct dxf_knot_data {
    dxf_F64 k; /* Knot value. */
} dxf_knot_data;

/* Spline control point data. */
typedef struct dxf_control_point_data {
    dxf_F64 x; /* X coordinate of the control point. */
    dxf_F64 y; /* Y coordinate of the control point. */
    dxf_F64 z; /* Z coordinate of the control point. */
    dxf_F64 w; /* Weight of control point. */
} dxf_control_point_data;

/* Spline fit point data. */
typedef struct dxf_fit_point_data {
    dxf_F64 x; /* X coordinate of the fit point. */
    dxf_F64 y; /* Y coordinate of the fit point. */
    dxf_F64 z; /* Z coordinate of the fit point. */
} dxf_fit_point_data;

/* Ellipse Data. */
typedef struct dxf_ellipse_data {
    dxf_F64 cx;     /* X Coordinate of center point. */
    dxf_F64 cy;     /* Y Coordinate of center point. */
    dxf_F64 cz;     /* Z Coordinate of center point. */
    dxf_F64 mx;     /* X coordinate of the endpoint of the major axis. */
    dxf_F64 my;     /* Y coordinate of the endpoint of the major axis. */
    dxf_F64 mz;     /* Z coordinate of the endpoint of the major axis. */
    dxf_F64 ratio;  /* Ratio of minor axis to major axis. */
    dxf_F64 angle1; /* Startangle of ellipse in rad. */
    dxf_F64 angle2; /* Endangle of ellipse in rad. */
} dxf_ellipse_data;

/* Insert Data. */
typedef struct dxf_insert_data {
    dxf_CHAR name[512]; /* Name of the referred block. */
    dxf_F64  ipx;       /* X Coordinate of insertion point. */
    dxf_F64  ipy;       /* Y Coordinate of insertion point. */
    dxf_F64  ipz;       /* Z Coordinate of insertion point. */
    dxf_F64  sx;        /* X Scale factor. */
    dxf_F64  sy;        /* Y Scale factor. */
    dxf_F64  sz;        /* Z Scale factor. */
    dxf_F64  angle;     /* Rotation angle in degrees. */
    dxf_I32  cols;      /* Number of columns if we insert an array of
                         * the block or 1. */
    dxf_I32 rows;       /* Number of rows if we insert an array of the block or 1. */
    dxf_F64 colSp;      /* Values for the spacing between cols. */
    dxf_F64 rowSp;      /* Values for the spacing between rows. */
} dxf_insert_data;

/* MText Data. */
typedef struct dxf_mText_data {
    dxf_F64 ipx;                /* X Coordinate of insertion point. */
    dxf_F64 ipy;                /* Y Coordinate of insertion point. */
    dxf_F64 ipz;                /* Z Coordinate of insertion point. */
    dxf_F64 dirX;               /* X Coordinate of X direction vector. */
    dxf_F64 dirY;               /* Y Coordinate of X direction vector. */
    dxf_F64 dirZ;               /* Z Coordinate of X direction vector. */
    dxf_F64 height;             /* Text height */
    dxf_F64 width;              /* Width of the text box. */
    dxf_I32 attachmentPoint;    /*
                                 * Attachment point.
                                 *
                                 * 1 = Top left, 2 = Top center, 3 = Top right,
                                 * 4 = Middle left, 5 = Middle center, 6 = Middle
                                 * right, 7 = Bottom left, 8 = Bottom center, 9 =
                                 * Bottom right
                                 */
    dxf_I32 drawingDirection;   /*
                                 * Drawing direction.
                                 *
                                 * 1 = left to right, 3 = top to bottom, 5 = by style
                                 */
    dxf_I32 lineSpacingStyle;   /*
                                 * Line spacing style.
                                 *
                                 * 1 = at least, 2 = exact
                                 */
    dxf_F64  lineSpacingFactor; /* Line spacing factor. 0.25 .. 4.0 */
    dxf_CHAR text[512];         /* Text string. */
    dxf_CHAR style[512];        /* Style string. */
    dxf_F64  angle;             /* Rotation angle. */
} dxf_mText_data;

/* Text Data. */
typedef struct dxf_text_data {
    dxf_F64 ipx;                 /* X Coordinate of insertion point. */
    dxf_F64 ipy;                 /* Y Coordinate of insertion point. */
    dxf_F64 ipz;                 /* Z Coordinate of insertion point. */
    dxf_F64 apx;                 /* X Coordinate of alignment point. */
    dxf_F64 apy;                 /* Y Coordinate of alignment point. */
    dxf_F64 apz;                 /* Z Coordinate of alignment point. */
    dxf_F64 height;              /* Text height */
    dxf_F64 xScaleFactor;        /* Relative X scale factor. */
    dxf_I32 textGenerationFlags; /* 0 = default, 2 = Backwards, 4 = Upside down */
    dxf_I32 hJustification;      /*
                                  * Horizontal justification.
                                  *
                                  * 0 = Left (default), 1 = Center, 2 = Right,
                                  * 3 = Aligned, 4 = Middle, 5 = Fit
                                  * For 3, 4, 5 the vertical alignment has to be 0.
                                  */
    dxf_I32 vJustification;      /*
                                  * Vertical justification.
                                  *
                                  * 0 = Baseline (default), 1 = Bottom, 2 = Middle,
                                  * 3= Top
                                  */
    dxf_CHAR text[512];          /* Text string. */
    dxf_CHAR style[512];         /* Style (font). */
    dxf_F64  angle;              /* Rotation angle of dimension text away from default
                                   orientation. */
} dxf_text_data;

/* Arc Aligned Text Data. */
typedef struct dxf_arc_aligned_text_data {
    dxf_CHAR text[512];              /* Text string */
    dxf_CHAR font[512];              /* Font name */
    dxf_CHAR style[512];             /* Style */
    dxf_F64  cx;                     /* X coordinate of arc center point. */
    dxf_F64  cy;                     /* Y coordinate of arc center point. */
    dxf_F64  cz;                     /* Z coordinate of arc center point. */
    dxf_F64  radius;                 /* Arc radius. */
    dxf_F64  xScaleFactor;           /* Relative X scale factor. */
    dxf_F64  height;                 /* Text height */
    dxf_F64  spacing;                /* Character spacing */
    dxf_F64  offset;                 /* Offset from arc */
    dxf_F64  rightOffset;            /* Right offset */
    dxf_F64  leftOffset;             /* Left offset */
    dxf_F64  startAngle;             /* Start angle (radians) */
    dxf_F64  endAngle;               /* End angle (radians) */
    dxf_BOOL reversedCharacterOrder; /* Reversed character order: FALSE: normal, TRUE:
                                    reverse. */
    dxf_I32  direction;    /* Direction: 1: outward from center,2: inward from center */
    dxf_I32  alignment;    /* Alignment: 1: fit, 2: left, 3: right, 4: center */
    dxf_I32  side;         /* Side: 1: convex, 2: concave */
    dxf_BOOL bold;         /* Bold flag */
    dxf_BOOL italic;       /* Italic flag */
    dxf_BOOL underline;    /* Underline flag */
    dxf_I32  characterSet; /* Character set value. Windows character set identifier. */
    dxf_I32  pitch;        /* Pitch and family value. Windows pitch and character family
                              identifier. */
    dxf_BOOL shxFont;      /* Font type: FALSE: TTF, TRUE: SHX */
    dxf_BOOL wizard;       /* Wizard flag */
    dxf_I32  arcHandle;    /* Arc handle/ID */
} dxf_arc_aligned_text_data;

/* Block attribute data. */
typedef struct dxf_attribute_data {
    dxf_text_data text;
    dxf_CHAR      tag[512]; /* Tag. */
} dxf_attribute_data;

/* Generic Dimension Data. */
typedef struct dxf_dimension_data {
    dxf_F64 dpx; /* X Coordinate of definition point. */
    dxf_F64 dpy; /* Y Coordinate of definition point. */
    dxf_F64 dpz; /* Z Coordinate of definition point. */
    dxf_F64 mpx; /* X Coordinate of middle point of the text. */
    dxf_F64 mpy; /* Y Coordinate of middle point of the text. */
    dxf_F64 mpz; /* Z Coordinate of middle point of the text. */
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
    dxf_I32 type;
    /*
     * Attachment point.
     *
     * 1 = Top left, 2 = Top center, 3 = Top right,
     * 4 = Middle left, 5 = Middle center, 6 = Middle right,
     * 7 = Bottom left, 8 = Bottom center, 9 = Bottom right,
     */
    dxf_I32 attachmentPoint;
    dxf_I32 lineSpacingStyle;  /* Line spacing style. 1 = at least, 2 = exact */
    dxf_F64 lineSpacingFactor; /* Line spacing factor. 0.25 .. 4.0 */
                               /*
                                * Text string.
                                *
                                * Text string entered explicitly by user or null
                                * or "<>" for the actual measurement or " " (one blank space).
                                * for supressing the text.
                                */
    dxf_CHAR text[512];
    dxf_CHAR style[512]; /* Dimension style (font name). */
    dxf_F64  angle; /* Rotation angle of dimension text away from. default orientation. */
    dxf_F64  linearFactor; /* Linear factor style override. */
    dxf_F64  dimScale;     /* Dimension scale (dimScale) style override. */
    dxf_BOOL arrow1Flipped;
    dxf_BOOL arrow2Flipped;
} dxf_dimension_data;

/* Aligned Dimension Data. */
typedef struct dxf_dim_aligned_data {
    dxf_F64 epx1; /* X Coordinate of Extension point 1. */
    dxf_F64 epy1; /* Y Coordinate of Extension point 1. */
    dxf_F64 epz1; /* Z Coordinate of Extension point 1. */
    dxf_F64 epx2; /* X Coordinate of Extension point 2. */
    dxf_F64 epy2; /* Y Coordinate of Extension point 2. */
    dxf_F64 epz2; /* Z Coordinate of Extension point 2. */
} dxf_dim_aligned_data;

/* Linear (rotated) Dimension Data. */
typedef struct dxf_dim_linear_data {
    dxf_F64 dpx1;    /* X Coordinate of Extension point 1. */
    dxf_F64 dpy1;    /* Y Coordinate of Extension point 1. */
    dxf_F64 dpz1;    /* Z Coordinate of Extension point 1. */
    dxf_F64 dpx2;    /* X Coordinate of Extension point 2. */
    dxf_F64 dpy2;    /* Y Coordinate of Extension point 2. */
    dxf_F64 dpz2;    /* Z Coordinate of Extension point 2. */
    dxf_F64 angle;   /* Rotation angle (angle of dimension line) in degrees. */
    dxf_F64 oblique; /* Oblique angle in degrees. */
} dxf_dim_linear_data;

/* Radial Dimension Data. */
typedef struct dxf_dim_radial_data {
    dxf_F64 dpx;    /* X Coordinate of definition point. */
    dxf_F64 dpy;    /* Y Coordinate of definition point. */
    dxf_F64 dpz;    /* Z Coordinate of definition point. */
    dxf_F64 leader; /* Leader length */
} dxf_dim_radial_data;

/* Diametric Dimension Data. */
typedef struct dxf_dim_diametric_data {
    dxf_F64 dpx;    /* X Coordinate of definition point (DXF 15). */
    dxf_F64 dpy;    /* Y Coordinate of definition point (DXF 25). */
    dxf_F64 dpz;    /* Z Coordinate of definition point (DXF 35). */
    dxf_F64 leader; /* Leader length */
} dxf_dim_diametric_data;

/* Angular Dimension Data. */
typedef struct dxf_dim_angular2L_data {
    dxf_F64 dpx1; /* X Coordinate of definition point 1. */
    dxf_F64 dpy1; /* Y Coordinate of definition point 1. */
    dxf_F64 dpz1; /* Z Coordinate of definition point 1. */
    dxf_F64 dpx2; /* X Coordinate of definition point 2. */
    dxf_F64 dpy2; /* Y Coordinate of definition point 2. */
    dxf_F64 dpz2; /* Z Coordinate of definition point 2. */
    dxf_F64 dpx3; /* X Coordinate of definition point 3. */
    dxf_F64 dpy3; /* Y Coordinate of definition point 3. */
    dxf_F64 dpz3; /* Z Coordinate of definition point 3. */
    dxf_F64 dpx4; /* X Coordinate of definition point 4. */
    dxf_F64 dpy4; /* Y Coordinate of definition point 4. */
    dxf_F64 dpz4; /* Z Coordinate of definition point 4. */
} dxf_dim_angular2L_data;

/* Angular Dimension Data (3 points version). */
typedef struct dxf_dim_angular3P_data {
    dxf_F64 dpx1; /* X Coordinate of definition point 1 (extension line 1 end). */
    dxf_F64 dpy1; /* Y Coordinate of definition point 1. */
    dxf_F64 dpz1; /* Z Coordinate of definition point 1. */
    dxf_F64 dpx2; /* X Coordinate of definition point 2 (extension line 2 end). */
    dxf_F64 dpy2; /* Y Coordinate of definition point 2. */
    dxf_F64 dpz2; /* Z Coordinate of definition point 2. */
    dxf_F64 dpx3; /* X Coordinate of definition point 3 (center). */
    dxf_F64 dpy3; /* Y Coordinate of definition point 3. */
    dxf_F64 dpz3; /* Z Coordinate of definition point 3. */
} dxf_dim_angular3P_data;

/* Ordinate Dimension Data. */
typedef struct dxf_dim_ordinate_data {
    dxf_F64  dpx1;  /* X Coordinate of definition point 1. */
    dxf_F64  dpy1;  /* Y Coordinate of definition point 1. */
    dxf_F64  dpz1;  /* Z Coordinate of definition point 1. */
    dxf_F64  dpx2;  /* X Coordinate of definition point 2. */
    dxf_F64  dpy2;  /* Y Coordinate of definition point 2. */
    dxf_F64  dpz2;  /* Z Coordinate of definition point 2. */
    dxf_BOOL xtype; /* TRUE if the dimension indicates the X-value, FALSE for Y-value */
} dxf_dim_ordinate_data;

/* Leader (arrow). */
typedef struct dxf_leader_data {
    dxf_I32 arrowHeadFlag;         /* Arrow head flag (71). */
    dxf_I32 leaderPathType;        /* Leader path type (72). */
    dxf_I32 leaderCreationFlag;    /* Leader creation flag (73). */
    dxf_I32 hooklineDirectionFlag; /* Hookline direction flag (74). */
    dxf_I32 hooklineFlag;          /* Hookline flag (75) */
    dxf_F64 textAnnotationHeight;  /* Text annotation height (40). */
    dxf_F64 textAnnotationWidth;   /* Text annotation width (41) */
    dxf_I32 number;                /* Number of vertices in leader (76). */
    dxf_F64 dimScale;              /* Dimension scale (dimScale) style override. */
} dxf_leader_data;

/* Leader Vertex Data. */
typedef struct dxf_leader_vertex_data {
    dxf_F64 x; /* X Coordinate of the vertex. */
    dxf_F64 y; /* Y Coordinate of the vertex. */
    dxf_F64 z; /* Z Coordinate of the vertex. */
} dxf_leader_vertex_data;

/* Hatch data. */
typedef struct dxf_hatch_data {
    dxf_I32  numLoops;     /* Number of boundary paths (loops). */
    dxf_BOOL solid;        /* Solid fill flag (TRUE=solid, FALSE=pattern). */
    dxf_F64  scale;        /* Pattern scale or spacing */
    dxf_F64  angle;        /* Pattern angle in degrees */
    dxf_CHAR pattern[512]; /* Pattern name. */
    dxf_F64  originX;      /* Pattern origin */
    dxf_F64  originY;
} dxf_hatch_data;

/* Hatch boundary path (loop) data. */
typedef struct dxf_hatch_loop_data {
    dxf_I32 numEdges; /* Number of edges in this loop. */
} dxf_hatch_loop_data;

/* Hatch edge data. */
typedef struct dxf_hatch_edge_data {
    dxf_BOOL defined; /* Set to TRUE if this edge is fully defined. */
    dxf_I32  type;    /* Edge type. 1=line, 2=arc, 3=elliptic arc, 4=spline. */
    dxf_F64  x1;      /* Start point (X). */
    dxf_F64  y1;      /* Start point (Y). */
    dxf_F64  x2;      /* End point (X). */
    dxf_F64  y2;      /* End point (Y). */
    dxf_F64  cx;      /* Center point of arc or ellipse arc (X). */
    dxf_F64  cy;      /* Center point of arc or ellipse arc (Y). */
    dxf_F64  radius;  /* Arc radius. */
    dxf_F64  angle1;  /* Start angle of arc or ellipse arc. */
    dxf_F64  angle2;  /* End angle of arc or ellipse arc. */
    dxf_BOOL ccw;     /* Counterclockwise flag for arc or ellipse arc. */
    dxf_F64  mx;      /* Major axis end point (X). */
    dxf_F64  my;      /* Major axis end point (Y). */
    dxf_F64  ratio;   /* Axis ratio */
    uint32_t degree;  /* Spline degree */
    dxf_BOOL rational;
    dxf_BOOL periodic;
    uint32_t nKnots;        /* Number of knots. */
    uint32_t nControl;      /* Number of control points. */
    uint32_t nFit;          /* Number of fit points. */
    dxf_F64 *controlPoints; /* Coordinate of control points*/
    dxf_F64 *knots;
    dxf_F64 *weights;
    dxf_F64 *fitPoints;
    dxf_F64  startTangentX;
    dxf_F64  startTangentY;
    dxf_F64  endTangentX;
    dxf_F64  endTangentY;
    dxf_F64 *vertices; /* Number of fit points. */
} dxf_hatch_edge_data;

/* Image Data. */
typedef struct dxf_image_data {
    dxf_CHAR ref[512];  /* Reference to the image file (unique, used to refer to the image
                       def  object). */
    dxf_F64 ipx;        /* X Coordinate of insertion point. */
    dxf_F64 ipy;        /* Y Coordinate of insertion point. */
    dxf_F64 ipz;        /* Z Coordinate of insertion point. */
    dxf_F64 ux;         /* X Coordinate of u vector along bottom of image. */
    dxf_F64 uy;         /* Y Coordinate of u vector along bottom of image. */
    dxf_F64 uz;         /* Z Coordinate of u vector along bottom of image. */
    dxf_F64 vx;         /* X Coordinate of v vector along left side of image. */
    dxf_F64 vy;         /* Y Coordinate of v vector along left side of image. */
    dxf_F64 vz;         /* Z Coordinate of v vector along left side of image. */
    dxf_I32 width;      /* Width of image in pixel. */
    dxf_I32 height;     /* Height of image in pixel. */
    dxf_I32 brightness; /* Brightness (0..100, default = 50). */
    dxf_I32 contrast;   /* Contrast (0..100, default = 50). */
    dxf_I32 fade;       /* Fade (0..100, default = 0). */
} dxf_image_data;

/* Image Definition Data. */
typedef struct dxf_image_def_data {
    dxf_CHAR ref[512];  /* Reference to the image file (unique, used to refer to the image
                       def  object). */
    dxf_CHAR file[512]; /* Image file */
} dxf_image_def_data;

/* Dictionary data. */
typedef struct dxf_dictionary_data {
    dxf_CHAR handle[512];
} dxf_dictionary_data;

/* Dictionary entry data. */
typedef struct dxf_dictionary_entry_data {
    dxf_CHAR name[512];
    dxf_CHAR handle[512];
} dxf_dictionary_entry_data;

/* ------------------------------------------------------------------------------------ */
/*                                      Dxf Writer                                      */
/* ------------------------------------------------------------------------------------ */

typedef struct dxf_writer_t dxf_writer_t;

DXF_API dxf_I32 dxf_create_writer(dxf_writer_t **w, const dxf_CHAR *filename);
DXF_API dxf_I32 dxf_destroy_writer(dxf_writer_t *w);

DXF_API dxf_I32 dxf_write_real(dxf_writer_t *w, dxf_I32 gc, dxf_F64 value);
DXF_API dxf_I32 dxf_write_int(dxf_writer_t *w, dxf_I32 gc, dxf_I32 value);
DXF_API dxf_I32 dxf_write_boolean(dxf_writer_t *w, dxf_I32 gc, dxf_BOOL value);
DXF_API dxf_I32 dxf_write_hex(dxf_writer_t *w, dxf_I32 gc, dxf_I32 value);
DXF_API dxf_I32 dxf_write_string(dxf_writer_t *w, dxf_I32 gc, const dxf_CHAR *value);

DXF_API dxf_I32 dxf_write_header(dxf_writer_t *w);

DXF_API dxf_I32 dxf_write_point(dxf_writer_t         *w,
                                const dxf_point_data *data,
                                const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_line(dxf_writer_t         *w,
                               const dxf_line_data  *data,
                               const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_xline(dxf_writer_t         *w,
                                const dxf_xline_data *data,
                                const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_ray(dxf_writer_t         *w,
                              const dxf_ray_data   *data,
                              const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_polyline(dxf_writer_t            *w,
                                   const dxf_polyline_data *data,
                                   const dxf_attributes    *attr);
DXF_API dxf_I32 dxf_write_vertex(dxf_writer_t *w, const dxf_vertex_data *data);
DXF_API dxf_I32 dxf_write_polyline_end(dxf_writer_t *w);
DXF_API dxf_I32 dxf_write_spline(dxf_writer_t          *w,
                                 const dxf_spline_data *data,
                                 const dxf_attributes  *attr);
DXF_API dxf_I32 dxf_write_control_point(dxf_writer_t                 *w,
                                        const dxf_control_point_data *data);
DXF_API dxf_I32 dxf_write_fit_point(dxf_writer_t *w, const dxf_fit_point_data *data);
DXF_API dxf_I32 dxf_write_knot(dxf_writer_t *w, const dxf_knot_data *data);
DXF_API dxf_I32 dxf_write_circle(dxf_writer_t          *w,
                                 const dxf_circle_data *data,
                                 const dxf_attributes  *attr);
DXF_API dxf_I32 dxf_write_arc(dxf_writer_t         *w,
                              const dxf_arc_data   *data,
                              const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_ellipse(dxf_writer_t           *w,
                                  const dxf_ellipse_data *data,
                                  const dxf_attributes   *attr);
DXF_API dxf_I32 dxf_write_solid(dxf_writer_t         *w,
                                const dxf_solid_data *data,
                                const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_trace(dxf_writer_t         *w,
                                const dxf_trace_data *data,
                                const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_3dFace(dxf_writer_t           *w,
                                 const dxf_3d_face_data *data,
                                 const dxf_attributes   *attr);
DXF_API dxf_I32 dxf_write_insert(dxf_writer_t          *w,
                                 const dxf_insert_data *data,
                                 const dxf_attributes  *attr);
DXF_API dxf_I32 dxf_write_mText(dxf_writer_t         *w,
                                const dxf_mText_data *data,
                                const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_text(dxf_writer_t         *w,
                               const dxf_text_data  *data,
                               const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_attribute(dxf_writer_t             *w,
                                    const dxf_attribute_data *data,
                                    const dxf_attributes     *attr);
DXF_API dxf_I32 dxf_write_dim_style_overrides(dxf_writer_t             *w,
                                              const dxf_dimension_data *data);
DXF_API dxf_I32 dxf_write_dim_aligned(dxf_writer_t               *w,
                                      const dxf_dimension_data   *data,
                                      const dxf_dim_aligned_data *edata,
                                      const dxf_attributes       *attr);
DXF_API dxf_I32 dxf_write_dim_linear(dxf_writer_t         *w,
                                     dxf_dimension_data   *data,
                                     dxf_dim_linear_data  *edata,
                                     const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_dim_radial(dxf_writer_t              *w,
                                     const dxf_dimension_data  *data,
                                     const dxf_dim_radial_data *edata,
                                     const dxf_attributes      *attr);
DXF_API dxf_I32 dxf_write_dim_diametric(dxf_writer_t                 *w,
                                        const dxf_dimension_data     *data,
                                        const dxf_dim_diametric_data *edata,
                                        const dxf_attributes         *attr);
DXF_API dxf_I32 dxf_write_dim_angular2L(dxf_writer_t                 *w,
                                        const dxf_dimension_data     *data,
                                        const dxf_dim_angular2L_data *edata,
                                        const dxf_attributes         *attr);
DXF_API dxf_I32 dxf_write_dim_angular3P(dxf_writer_t                 *w,
                                        const dxf_dimension_data     *data,
                                        const dxf_dim_angular3P_data *edata,
                                        const dxf_attributes         *attr);
DXF_API dxf_I32 dxf_write_dim_ordinate(dxf_writer_t                *w,
                                       const dxf_dimension_data    *data,
                                       const dxf_dim_ordinate_data *edata,
                                       const dxf_attributes        *attr);
DXF_API dxf_I32 dxf_write_leader(dxf_writer_t          *w,
                                 const dxf_leader_data *data,
                                 const dxf_attributes  *attr);
DXF_API dxf_I32 dxf_write_leader_vertex(dxf_writer_t                 *w,
                                        const dxf_leader_vertex_data *data);
DXF_API dxf_I32 dxf_write_leader_end(dxf_writer_t *w, const dxf_leader_data *data);
DXF_API dxf_I32 dxf_write_hatch1(dxf_writer_t         *w,
                                 const dxf_hatch_data *data,
                                 const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_hatch2(dxf_writer_t         *w,
                                 const dxf_hatch_data *data,
                                 const dxf_attributes *attr);
DXF_API dxf_I32 dxf_write_hatch_loop1(dxf_writer_t *w, const dxf_hatch_loop_data *data);
DXF_API dxf_I32 dxf_write_hatch_loop2(dxf_writer_t *w, const dxf_hatch_loop_data *data);
DXF_API dxf_I32 dxf_write_hatch_edge(dxf_writer_t *w, const dxf_hatch_edge_data *data);

DXF_API uint32_t dxf_write_image(dxf_writer_t         *w,
                                 const dxf_image_data *data,
                                 const dxf_attributes *attr);

DXF_API dxf_I32 dxf_write_image_def(dxf_writer_t         *w,
                                    const dxf_I32         handle,
                                    const dxf_image_data *data);

DXF_API dxf_I32 dxf_write_layer(dxf_writer_t         *w,
                                const dxf_layer_data *data,
                                const dxf_attributes *attr);

DXF_API dxf_I32 dxf_write_line_type(dxf_writer_t *w, const dxf_line_type_data *data);

DXF_API dxf_I32 dxf_write_appid(dxf_writer_t *w, const dxf_CHAR *name);

DXF_API dxf_I32 dxf_write_block(dxf_writer_t *w, const dxf_block_data *data);
DXF_API dxf_I32 dxf_write_end_block(dxf_writer_t *w, const dxf_CHAR *name);

DXF_API dxf_I32  dxf_write_view_port(dxf_writer_t *w);
DXF_API dxf_I32  dxf_write_style(dxf_writer_t *w, const dxf_style_data *style);
DXF_API dxf_I32  dxf_write_view(dxf_writer_t *w);
DXF_API dxf_I32  dxf_write_ucs(dxf_writer_t *w);
DXF_API dxf_I32  dxf_write_dim_style(dxf_writer_t *w,
                                     dxf_F64       dimasz,
                                     dxf_F64       dimexe,
                                     dxf_F64       dimexo,
                                     dxf_F64       dimgap,
                                     dxf_F64       dimtxt,
                                     dxf_I32       dimtad,
                                     dxf_BOOL      dimtih);
DXF_API dxf_I32  dxf_write_block_record(dxf_writer_t *w, const dxf_CHAR *name);
DXF_API dxf_I32  dxf_write_objects(dxf_writer_t *w, const dxf_CHAR *appDictionaryName);
DXF_API dxf_I32  dxf_write_app_dictionary(dxf_writer_t *w);
DXF_API uint32_t dxf_write_dictionary_entry(dxf_writer_t *w, const dxf_CHAR *name);
DXF_API dxf_I32  dxf_write_x_record_int(dxf_writer_t *w, dxf_I32 handle, dxf_I32 value);
DXF_API dxf_I32 dxf_write_x_record_double(dxf_writer_t *w, dxf_I32 handle, dxf_F64 value);
DXF_API dxf_I32 dxf_write_x_record_BOOLean(dxf_writer_t *w,
                                           dxf_I32       handle,
                                           dxf_BOOL      value);
DXF_API dxf_I32 dxf_write_x_record_string(dxf_writer_t   *w,
                                          dxf_I32         handle,
                                          const dxf_CHAR *value);
DXF_API dxf_I32 dxf_write_objects_end(dxf_writer_t *w);

DXF_API dxf_I32 dxf_write_comment(dxf_writer_t *w, const dxf_CHAR *comment);

/* ------------------------------------------------------------------------------------ */
/*                                      Dxf Reader                                      */
/* ------------------------------------------------------------------------------------ */

typedef struct dxf_reader_t dxf_reader_t;

/* Reader callback. */
typedef struct dxf_reader_callback_t {
    void (*end_section)();
    void (*add_layer)(dxf_layer_data *);
    void (*add_line_type)(dxf_line_type_data *);
    void (*add_line_type_dash)(dxf_F64);
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
    void (*add_mText_chunk)(const dxf_CHAR *);
    void (*add_text)(dxf_text_data *);
    void (*add_arc_aligned_text)(dxf_arc_aligned_text_data *);
    void (*add_attribute)(dxf_attribute_data *);

    void (*add_dim_align)(dxf_dimension_data *, const dxf_dim_aligned_data *);
    void (*add_dim_linear)(dxf_dimension_data *, const dxf_dim_linear_data *);
    void (*add_dim_radial)(dxf_dimension_data *, const dxf_dim_radial_data *);
    void (*add_dim_diametric)(dxf_dimension_data *, const dxf_dim_diametric_data *);
    void (*add_dim_angular)(dxf_dimension_data *, const dxf_dim_angular2L_data *);
    void (*add_dim_angular3P)(dxf_dimension_data *, const dxf_dim_angular3P_data *);
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

    void (*add_x_record)(const dxf_CHAR *);
    void (*add_x_record_string)(dxf_I32, const dxf_CHAR *);
    void (*add_x_record_real)(dxf_I32, dxf_F64);
    void (*add_x_record_int)(dxf_I32, dxf_I32);
    void (*add_x_record_BOOL)(dxf_I32, dxf_BOOL);

    void (*add_x_data_app)(const dxf_CHAR *);
    void (*add_x_data_string)(dxf_I32, const dxf_CHAR *);
    void (*add_x_data_real)(dxf_I32, dxf_F64);
    void (*add_x_data_int)(dxf_I32, dxf_I32);

    void (*add_dictionary)(dxf_dictionary_data *);
    void (*add_dictionary_entry)(dxf_dictionary_entry_data *);

    void (*end_entity)();

    void (*add_comment)(const dxf_CHAR *);

    void (*set_variable_vector)(const dxf_CHAR *, dxf_F64, dxf_F64, dxf_F64, dxf_I32);
    void (*set_variable_string)(const dxf_CHAR *, const dxf_CHAR *, dxf_I32);
    void (*set_variable_int)(const dxf_CHAR *, dxf_I32, dxf_I32);
    void (*set_variable_double)(const dxf_CHAR *, dxf_F64, dxf_I32);

    void (*end_sequence)();
} dxf_reader_callback_t;

DXF_API dxf_I32 dxf_create_reader(dxf_reader_t **,
                                  const dxf_CHAR *file,
                                  dxf_reader_callback_t *);
DXF_API dxf_I32 dxf_destroy_reader(dxf_reader_t *);

DXF_API dxf_I32 dxf_read(dxf_reader_t *);

#ifdef __cplusplus
}
#endif

#endif // DXF_H
