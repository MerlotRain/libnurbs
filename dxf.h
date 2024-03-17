#ifndef DXF_H
#define DXF_H

#include <dxf_config.h>

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

#if defined(WIN32)
#    define STRCASECMP(a, b)     (_stricmp(a, b))
#    define STRNCASECMP(a, b, n) (_strnicmp(a, b, n))
#    define STRCMP(a, b)         (_strcmp(a, b))
#    define STRNCMP(a, b, n)     (_strncmp(a, b, n))
#else
/** Alias for strcasecmp() */
#    define STRCASECMP(a, b)     (strcasecmp(a, b))
/** Alias for strncasecmp() */
#    define STRNCASECMP(a, b, n) (strncasecmp(a, b, n))
#endif
/** Alias for strncasecmp() == 0 */
#define EQUALN(a, b, n) (STRNCASECMP(a, b, n) == 0)
/** Alias for strcasecmp() == 0 */
#define EQUAL(a, b) (STRCASECMP(a, b) == 0)

#define FALSE       0
#define TRUE        1
#define DXF_FAILURE -1
#define DXF_SUCCESS 1

#define DL_DXF_MAX_STRING     1024
#define DL_DXF_MAX_LINE       1024
#define DL_DXF_MAX_GROUP_CODE 1100

/* ------------------------------------------------------------------------------------ */
/*                                   dxf kernel codes                                   */
/* ------------------------------------------------------------------------------------ */

typedef enum {
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
} Color;

/* Version numbers for the DXF Format. */
typedef enum {
    AC1006, /*!< R10. */
    AC1009, /*!< R11 & R12. */
    AC1012, /*!< R13. */
    AC1014, /*!< R14. */
    AC1015, /*!< ACAD 2000. */
    AC1018, /*!< ACAD 2004. */
    AC1021, /*!< ACAD 2007. */
    AC1024, /*!< ACAD 2010. */
    AC1027  /*!< ACAD 2013. */
} Version;

typedef enum {
    ERR_NONE,             /*!< No error. */
    ERR_UNKNOWN,          /*!< UNKNOWN. */
    ERR_OPEN,             /*!< error opening file. */
    ERR_VERSION,          /*!< unsupported version. */
    ERR_READ_METADATA,    /*!< error reading mata data. */
    ERR_READ_FILE_HEADER, /*!< error in file header read process. */
    ERR_READ_HEADER,      /*!< error in header vars read process. */
    ERR_READ_HANDLES,     /*!< error in object map read process. */
    ERR_READ_CLASSES,     /*!< error in classes read process. */
    ERR_READ_TABLES,      /*!< error in tables read process. */
    ERR_READ_BLOCKS,      /*!< error in block read process. */
    ERR_READ_ENTITIES,    /*!< error in entities read process. */
    ERR_READ_OBJECTS      /*!< error in objects read process. */
} ErrorCode;

typedef enum {
    width00      = 0,  /* 0.00mm (dxf 0)*/
    width01      = 1,  /* 0.05mm (dxf 5)*/
    width02      = 2,  /* 0.09mm (dxf 9)*/
    width03      = 3,  /* 0.13mm (dxf 13)*/
    width04      = 4,  /* 0.15mm (dxf 15)*/
    width05      = 5,  /* 0.18mm (dxf 18)*/
    width06      = 6,  /* 0.20mm (dxf 20)*/
    width07      = 7,  /* 0.25mm (dxf 25)*/
    width08      = 8,  /* 0.30mm (dxf 30)*/
    width09      = 9,  /* 0.35mm (dxf 35)*/
    width10      = 10, /* 0.40mm (dxf 40)*/
    width11      = 11, /* 0.50mm (dxf 50)*/
    width12      = 12, /* 0.53mm (dxf 53)*/
    width13      = 13, /* 0.60mm (dxf 60)*/
    width14      = 14, /* 0.70mm (dxf 70)*/
    width15      = 15, /* 0.80mm (dxf 80)*/
    width16      = 16, /* 0.90mm (dxf 90)*/
    width17      = 17, /* 1.00mm (dxf 100)*/
    width18      = 18, /* 1.06mm (dxf 106)*/
    width19      = 19, /* 1.20mm (dxf 120)*/
    width20      = 20, /* 1.40mm (dxf 140)*/
    width21      = 21, /* 1.58mm (dxf 158)*/
    width22      = 22, /* 2.00mm (dxf 200)*/
    width23      = 23, /* 2.11mm (dxf 211)*/
    widthByLayer = 29, /* by layer (dxf -1) */
    widthByBlock = 30, /* by block (dxf -2) */
    widthDefault = 31  /* by default (dxf -3) */
} LineWidth;

typedef enum { ModelSpace = 0, PaperSpace = 1 } Space;

typedef enum {
    CastAndReceiveShadows = 0,
    CastShadows           = 1,
    ReceiveShadows        = 2,
    IgnoreShadows         = 3
} ShadowMode;

// Extended color palette:
// The first entry is only for direct indexing starting with [1]
// Color 1 is red (1,0,0)
static const dxf_F64 dxfColors[][3] = {
#include "dxf_color.inl"
};

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

/* Layer Data. */
typedef struct dxf_layer_data {
    dxf_CHAR name[512]; /* Layer name. */
    dxf_I32  flags;     /* Layer flags. (1 = frozen, 2 = frozen by default, 4 =
                           locked) */
    dxf_BOOL off;       /* Layer is off */
} dxf_layer_data;

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

/* Block attribute data. */
typedef struct dxf_attribute_data {
    dxf_text_data text;
    dxf_CHAR      tag[512]; /* Tag. */
} dxf_attribute_data;

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
/*                                 dxf Entity Structure                                 */
/* ------------------------------------------------------------------------------------ */

typedef enum {
    UNKNOWN,
    E3DFACE,
    // E3DSOLID,
    // ACAD_PROXY_ENTITY,
    ARC,
    // ATTDEF,
    // ATTRIB,
    BLOCK,
    CIRCLE,
    // BODY,
    DIMENSION,
    DIM_ALIGNED,
    DIM_LINEAR,
    DIM_RADIAL,
    DIM_DIAMETRIC,
    DIM_ANGULAR2L,
    DIM_ANGULAR3P,
    DIM_ORDINATE,
    ELLIPSE,
    HATCH,
    // HELIX,
    IMAGE,
    INSERT,
    LEADER,
    // LIGHT,
    LINE,
    LWPOLYLINE,
    // MESH,
    // MLINE,
    // MLEADERSTYLE,
    // MLEADER,
    MTEXT,
    // OLEFRAME,
    // OLE2FRAME,
    POINT,
    POLYLINE,
    RAY,
    // REGION,
    // SECTION,
    // SEQEND,
    // SHAPE,
    SOLID,
    SPLINE,
    // SUN,
    // SURFACE,
    // TABLE,
    TEXT,
    // TOLERANCE,
    TRACE,
    UNDERLAY,
    VERTEX,
    VIEWPORT,
    // WIPEOUT,
    // WIPEOUTVARIABLE,
    XLINE,
} EntityType;
/* dxf 3d point */
typedef struct dxf_coord {
    dxf_F64 x;
    dxf_F64 y;
    dxf_F64 z;
} dxf_coord;

/* dxf entity attribute data. */
typedef struct dxf_entity_attr {
    dxf_U32 handle;        /* entity identifier, code 5 */
    dxf_U32 parentHandle;  /* Soft-pointer ID/handle to owner BLOCK_RECORD object, code
                              330 */
    Space      space;      /* space indicator, code 67 */
    dxf_CHAR   layer[512]; /* layer name, code 8 */
    dxf_CHAR   line_type[512];  /* line type, code 6 */
    dxf_U32    material;        /* hard pointer id to material object, code 347 */
    dxf_I32    color;           /* entity color, code 62 */
    LineWidth  lWeight;         /* entity line weight, code 370 */
    dxf_F64    ltype_scale;     /* linetype scale, code 48 */
    dxf_BOOL   visible;         /* entity visibility, code 60 */
    dxf_I32    num_proxy_graph; /* Number of bytes in proxy graphics, code 92 */
    dxf_CHAR   proxy_graphics;  /* proxy graphics bytes, code 310 */
    dxf_I32    color24;         /* 24-bit color, code 420 */
    dxf_CHAR   color_name[64];  /* color name, code 430 */
    dxf_I32    transparency;    /* transparency, code 440 */
    dxf_I32    plot_style;      /* hard pointer id to plot style object, code 390 */
    ShadowMode shadow;          /* shadow mode, code 284 */
    dxf_BOOL   have_extrusion;  /* set to true if the entity have extrusion */
} dxf_entity_attr;

/* Point Data. */
typedef struct dxf_point_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
} dxf_point_data;

/* Line Data. */
typedef struct dxf_line_data {
    dxf_coord begin_point;     /* start point, code 10, 20 & 30 */
    dxf_coord end_point;       /* end point, code 11, 21 & 31 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
} dxf_line_data;

/* Ray Data. */
typedef struct dxf_ray_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30 */
    dxf_coord direction_point; /* direction point, code 11, 21 & 31 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
} dxf_ray_data;

/* XLine Data. */
typedef struct dxf_xline_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30 */
    dxf_coord direction_point; /* direction point, code 11, 21 & 31 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
} dxf_xline_data;

/* Circle Data. */
typedef struct dxf_circle_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_F64   radius;          /* radius of arc, code 40 */
} dxf_circle_data;

/* Arc Data. */
typedef struct dxf_arc_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_F64   radius;          /* radius of arc, code 40 */
    dxf_F64   start_angle;     /* start angle, code 50 in radians */
    dxf_F64   end_angle;       /* end angle, code 51 in radians */
    dxf_I32   ccw; /* is counter clockwise arc?, only used in hatch, code 73 */
} dxf_arc_data;

/* Ellipse Data */
typedef struct dxf_ellipse_data {
    dxf_coord center;      /* Center point of circle, code 10, 20 & 30 */
    dxf_coord major_axis;  /* Endpoint of major axis, relative to the dxf.center (Vec3),
                                code 11, 21 & 31  default value is (1, 0, 0).  */
    dxf_F64   ratio;       /* ratio, code 40 */
    dxf_F64   start_param; /* start parameter, code 41, 0.0 for full ellipse*/
    dxf_F64   end_param;   /* end parameter, code 42, 2*PI for full ellipse */
    dxf_coord extrusion;   /* is counter clockwise arc?, only used in hatch, code 73 */
} dxf_ellipse_data;

/* Trace Data */
typedef struct dxf_trace_data {
    dxf_coord vtx0;            /* Location of 1. vertex code 10, 20 & 30 */
    dxf_coord vtx1;            /* Location of 2. vertex code 11, 21 & 31 */
    dxf_coord vtx2;            /* Location of 3. vertex code 12, 22 & 32 */
    dxf_coord vtx3;            /* Location of 4. vertex code 13, 23 & 33 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
} dxf_trace_data;

/* solid data */
typedef struct dxf_solid_data {
    dxf_coord vtx0;            /* Location of 1. vertex code 10, 20 & 30 */
    dxf_coord vtx1;            /* Location of 2. vertex code 11, 21 & 31 */
    dxf_coord vtx2;            /* Location of 3. vertex code 12, 22 & 32 */
    dxf_coord vtx3;            /* Location of 4. vertex code 13, 23 & 33 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230 */
} dxf_solid_data;

/* 3d face data. */
typedef struct dxf_3d_face_data {
    dxf_coord vtx0;            /* Location of 1. vertex code 10, 20 & 30 */
    dxf_coord vtx1;            /* Location of 2. vertex code 11, 21 & 31 */
    dxf_coord vtx2;            /* Location of 3. vertex code 12, 22 & 32 */
    dxf_coord vtx3;            /* Location of 4. vertex code 13, 23 & 33 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230 */
    dxf_I32   invisible_edges; /* Invisible edge flags, code 70, default=0 */
                               /* 1 first edge is invisible */
                               /* 2 second edge is invisible */
                               /* 4 third edge is invisible */
                               /* 8 fourth edge is invisible */
} dxf_3d_face_data;

/* Block Data. */
typedef struct dxf_block_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_CHAR  name[512];       /* Block name, code 2 */
    dxf_I32   flags;           /* Block flags. (not used currently), code 70 */
} dxf_block_data;

/* Insert Data. */
typedef struct dxf_insert_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_CHAR  name[512];       /* Name of the referred block. code 2 */
    dxf_F64   xScale;          /* x scale factor, code 41 */
    dxf_F64   yScale;          /* y scale factor, code 42 */
    dxf_F64   zScale;          /* z scale factor, code 43 */
    dxf_F64   angle;           /* rotation angle in radians, code 50 */
    dxf_I32   col_count;       /* column count, code 70 */
    dxf_I32   row_count;       /* row count, code 71 */
    dxf_F64   col_space;       /* column space, code 44 */
    dxf_F64   row_space;       /* row space, code 45 */
} dxf_insert_data;

/* Class to handle vertex for lwpolyline entity */
typedef struct dxf_point2d {
    double x;           /*!< x coordinate, code 10 */
    double y;           /*!< y coordinate, code 20 */
    double start_width; /*!< Start width, code 40 */
    double end_width;   /*!< End width, code 41 */
    double bulge;       /*!< bulge, code 42 */
} dxf_point2d;

/* Lwpolyline Data. */
typedef struct dxf_lwpolyline_data {
    dxf_I32      vertex_num;      /* number of vertex, code 90 */
    dxf_I32      flags;           /* polyline flag, code 70, default 0 */
    dxf_F64      width;           /* constant width, code 43 */
    dxf_F64      elevation;       /* elevation, code 38 */
    dxf_F64      thickness;       /* thickness, code 39 */
    dxf_coord    extrusion_point; /*  Dir extrusion normal vector, code 210, 220 & 230 */
    dxf_point2d  vertex;          /* current vertex to add data */
    dxf_point2d *vertex_list;     /* vertex list */
} dxf_lwpolyline_data;

/* Text Data. */
typedef struct dxf_text_data {
    dxf_coord insertion_point; /* insertion point, code 10, 20 & 30 */
    dxf_coord alignment_point; /* alignment point, code 11, 21 & 31 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_F64   height;          /* height text, code 40 */
    dxf_CHAR  text[512];       /* text string, code 1 */
    dxf_F64   angle;           /* rotation angle in degrees (360), code 50 */
    dxf_F64   widthScale;      /* width factor, code 41 */
    dxf_F64   oblique;         /* oblique angle, code 51 */
    dxf_CHAR  style[512];      /* style name, code 7 */
    dxf_I32   text_generation; /* text generation, code 71 */
                               /* default = 0 */
                               /* 2 = Text is backward (mirrored in X) */
                               /* 4 = Text is upside down (mirrored in Y) */
    dxf_I32 alignH;            /* horizontal align, code 72 */
                               /* Top = 0 */
                               /* Bottom = 1 */
                               /* Middle = 2 */
                               /* Top = 3 */
    dxf_I32 alignV;            /* vertical align, code 73 */
                               /* Left = 0 */
                               /* Centered = 1 */
                               /* Right = 2 */
                               /* Aligned = 3 (if VAlign==0) */
                               /* middle = 4 (if VAlign==0) */
                               /* fit into point = 5 (if VAlign==0) */
    // dwgHandle   styleH;       /* handle for text style */
} dxf_text_data;

/* MText Data. */
typedef struct dxf_mText_data {
    dxf_coord insertion_point; /* insertion point, code 10, 20 & 30 */
    dxf_coord alignment_point; /* alignment point, code 11, 21 & 31 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_F64   height;          /* height text, code 40 */
    dxf_CHAR  text[512];       /* text string, code 1 */
    dxf_F64   angle;           /* rotation angle in degrees (360), code 50 */
    dxf_F64   widthScale;      /* width factor, code 41 */
    dxf_F64   oblique;         /* oblique angle, code 51 */
    dxf_CHAR  style[512];      /* style name, code 7 */
    dxf_I32   text_generation; /* text generation, code 71 */
                               /* default = 0 */
                               /* 2 = Text is backward (mirrored in X) */
                               /* 4 = Text is upside down (mirrored in Y) */
    dxf_I32 alignH;            /* horizontal align, code 72 */
                               /* Top = 0 */
                               /* Bottom = 1 */
                               /* Middle = 2 */
                               /* Top = 3 */
    dxf_I32 alignV;            /* vertical align, code 73 */
                               /* TopLeft = 1 */
                               /* TopCenter = 2 */
                               /* TopRight = 3 */
                               /* MiddleLeft = 4 */
                               /* MiddleCenter = 5 */
                               /* MiddleRight = 6 */
                               /* BottomLeft = 7 */
                               /* BottomCenter = 8 */
                               /* BottomRight  = 9 */
    dxf_F64 inter_lin;         /* width factor, code 44 */
} dxf_mText_data;

/* Vertex Data. */
typedef struct dxf_vertex_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_F64   start_width;     /* Start width, code 40 */
    dxf_F64   end_width;       /* End width, code 41 */
    dxf_F64   bulge;           /* bulge, code 42 */
    dxf_I32   flags;           /* vertex flag, code 70, default 0 */
    dxf_F64   tan_direction;   /* curve fit tangent direction, code 50 */
    dxf_I32   vtx1;            /* polyface mesh vertex index, code 71, default 0 */
    dxf_I32   vtx2;            /* polyface mesh vertex index, code 72, default 0 */
    dxf_I32   vtx3;            /* polyface mesh vertex index, code 73, default 0 */
    dxf_I32   vtx4;            /* polyface mesh vertex index, code 74, default 0 */
    dxf_I32   identifier;      /* vertex identifier, code 91, default 0 */
} dxf_vertex_data;

/* Polyline Data. */
typedef struct dxf_polyline_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_F64   elevation;       /* elevation of the polyline. */
    dxf_I32   flags;           /* polyline flag, code 70, default 0 */
    dxf_F64   start_width;     /* Start width, code 40, default 0 */
    dxf_F64   end_width;       /* End width, code 41, default 0 */
    dxf_I32   num_m; /* polygon mesh M vertex or polyface vtx num, code 71, default 0 */
    dxf_I32   num_n; /* polygon mesh N vertex or polyface face num, code 72, default 0 */
    dxf_I32   smoothM;    /* smooth surface M density, code 73, default 0 */
    dxf_I32   smoothN;    /* smooth surface M density, code 74, default 0 */
    dxf_I32   curve_type; /* curves & smooth surface type, code 75, default 0 */
                          /* 0 = No smooth surface fitted */
                          /* 5 = Quadratic B-spline surface */
                          /* 6 = Cubic B-spline surface */
                          /* 8 = Bezier surface */
} dxf_polyline_data;

/* Spline Data. */
typedef struct dxf_spline_data {
    dxf_coord  normalVec;    /* normal vector, code 210, 220, 230 */
    dxf_coord  tgStart;      /* start tangent, code 12, 22, 32 */
    dxf_coord  tgEnd;        /* end tangent, code 13, 23, 33 */
    dxf_I32    flags;        /* spline flag, code 70 */
    dxf_I32    degree;       /* degree of the spline, code 71 */
    dxf_U32    num_knots;    /* number of knots, code 72, default 0 */
    dxf_U32    num_control;  /* number of control points, code 73, default 0 */
    dxf_U32    num_fit;      /* number of fit points, code 74, default 0 */
    dxf_F64    tol_knot;     /* knot tolerance, code 42, default 0.0000001 */
    dxf_F64    tol_control;  /* control point tolerance, code 43, default 0.0000001 */
    dxf_F64    tol_fit;      /* fit point tolerance, code 44, default 0.0000001 */
    dxf_F64   *knots_list;   /* knots list, code 40 */
    dxf_coord *control_list; /* control points list, code 10, 20 & 30 */
    dxf_coord *fit_list;     /* fit points list, code 11, 21 & 31 */
} dxf_spline_data;

/* Hatch edge data. */
typedef struct dxf_hatch_edge_data {
    dxf_I32 type; /* Edge type. 1=line, 2=arc, 3=elliptic arc, 4=spline. */
    union {
        dxf_line_data    *line;
        dxf_arc_data     *arc;
        dxf_ellipse_data *ellipse;
        dxf_spline_data  *spline;
    } ito;
} dxf_hatch_edge_data;

/* Hatch boundary path (loop) data. */
typedef struct dxf_hatch_loop_data {
    dxf_I32              type; /* boundary path type, code 92, polyline=2, default=0 */
    dxf_I32              num_edges; /* number of edges (if not a polyline), code 93 */
    dxf_hatch_edge_data *edges;
} dxf_hatch_loop_data;

/* Hatch data. */
typedef struct dxf_hatch_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_CHAR  name[512];       /* hatch pattern name, code 2 */
    dxf_I32   solid;           /* solid fill flag, code 70, solid=1, pattern=0 */
    dxf_I32   associative;     /* associativity,code 71, associatve=1, non-assoc.=0 */
    dxf_I32   style;           /* hatch style, code 75 */
    dxf_I32   pattern;         /* hatch pattern type, code 76 */
    dxf_I32   double_flag;     /* hatch pattern double flag, code 77 */
    dxf_I32   loop_num;        /* number of boundary paths (loops), code 91 */
    dxf_F64   angle;           /* hatch pattern angle, code 52 */
    dxf_F64   scale;           /* hatch pattern scale, code 41 */
    dxf_I32   def_lines;       /* number of pattern definition lines, code 78 */
} dxf_hatch_data;

/* Image Data. */
typedef struct dxf_image_data {
    dxf_coord begin_point;     /* start point, code 10, 20 & 30 */
    dxf_coord end_point;       /* end point, code 11, 21 & 31 */
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    dxf_U32   ref;             /* Hard reference to imagedef object, code 340 */
    double    size_u;          /* image size in pixels, U value, code 13 */
    double    size_v;          /* image size in pixels, V value, code 23 */
    double    dz;              /* z coordinate, code 33 */
    int       clip;            /* Clipping state, code 280, 0=off 1=on */
    int       brightness;      /* Brightness value, code 281, (0-100) default 50 */
    int       contrast;        /* Brightness value, code 282, (0-100) default 50 */
    int       fade;            /* Brightness value, code 283, (0-100) default 0 */
    dxf_coord vVector; /* V-vector of a single pixel, x coordinate, code 12, 22 & 32 */
} dxf_image_data;

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
    dxf_CHAR  style[512]; /* Dimension style name, code 3 */
    dxf_I32   arrow;      /* Arrowhead flag, code 71, 0=Disabled; 1=Enabled */
    dxf_I32   leader; /* Leader path type, code 72, 0=Straight line segments; 1=Spline */
    dxf_I32   flag;   /* Leader creation flag, code 73, default 3 */
    dxf_I32   hookline;       /* Hook line direction flag, code 74, default 1 */
    dxf_I32   hook_flag;      /* Hook line flag, code 75 */
    dxf_F64   text_height;    /* Text annotation height, code 40 */
    dxf_F64   text_width;     /* Text annotation width, code 41 */
    dxf_I32   vert_num;       /* Number of vertices, code 76 */
    dxf_I32   color_use;      /* Color to use if leader's DIMCLRD = BYBLOCK, code 77 */
    dxf_U32   annotHandle;    /* Hard reference to associated annotation, code 340 */
    dxf_coord extrusionPoint; /* Normal vector, code 210, 220 & 230 */
    dxf_coord hor_dir;        /* Horizontal direction for leader, code 211, 221 & 231 */
    dxf_coord
        offset_block; /* Offset of last leader vertex from block, code 212, 222 & 232 */
    dxf_coord offset_text;  /* Offset of last leader vertex from annotation, code 213,
                              223 & 233 */
    dxf_coord *vertex_list; /* vertex points list, code 10, 20 & 30 */
} dxf_leader_data;

/* Viewport Data. */
typedef struct dxf_viewport_data {
    dxf_coord base_point;      /* base point, code 10, 20 & 30*/
    dxf_F64   thickness;       /* thickness, code 39 */
    dxf_coord extrusion_point; /* dir extrusion normal vector, code 210, 220 & 230  */
    double    ps_width;        /* Width in paper space units, code 40 */
    double    ps_height;       /* Height in paper space units, code 41 */
    int       vp_status;       /* Viewport status, code 68 */
    int       vp_id;           /* Viewport ID, code 69 */
    double    center_x;        /* view center point X, code 12 */
    double    center_y;        /* view center point Y, code 22 */
    double    snap_point_x;    /* Snap base point X, code 13 */
    double    snap_point_y;    /* Snap base point Y, code 23 */
    double    snap_spacing_x;  /* Snap spacing X, code 14 */
    double    snap_spacing_y;  /* Snap spacing Y, code 24 */
    dxf_coord view_dir;        /* View direction vector, code 16, 26 & 36 */
    dxf_coord view_target;     /* View target point, code 17, 27, 37 */
    double    view_length;     /* Perspective lens length, code 42 */
    double    front_clip;      /* Front clip plane Z value, code 43 */
    double    back_clip;       /* Back clip plane Z value, code 44 */
    double    view_height;     /* View height in model space units, code 45 */
    double    snap_angle;      /* Snap angle, code 50 */
    double    twist_angle;     /* view twist angle, code 51 */
} dxf_viewport_data;

/* ------------------------------------------------------------------------------------ */
/*                                      dxf Writer                                      */
/* ------------------------------------------------------------------------------------ */

typedef struct dxf_writer_t dxf_writer_t;

DXF_API dxf_I32 dxf_create_writer(dxf_writer_t  **w,
                                  const dxf_CHAR *filename,
                                  Version         version);
DXF_API dxf_I32 dxf_destroy_writer(dxf_writer_t *w);

/* Must be overwritten by the implementing class to write a real value to the file. */
DXF_API dxf_I32 dxf_write_real(dxf_writer_t *w, dxf_I32 gc, dxf_F64 value);

/* Must be overwritten by the implementing class to write an int value to the file. */
DXF_API dxf_I32 dxf_write_int(dxf_writer_t *w, dxf_I32 gc, dxf_I32 value);

/* Can be overwritten by the implementing class to write a bool value to the file. */
DXF_API dxf_I32 dxf_write_boolean(dxf_writer_t *w, dxf_I32 gc, dxf_BOOL value);

/* Must be overwritten by the implementing class to write an int value (hex) to the file.
 */
DXF_API dxf_I32 dxf_write_hex(dxf_writer_t *w, dxf_I32 gc, dxf_I32 value);

/* Must be overwritten by the implementing class to write a string to the file. */
DXF_API dxf_I32 dxf_write_string(dxf_writer_t *w, dxf_I32 gc, const dxf_CHAR *value);

/* Generic section for section 'name'. */
DXF_API dxf_I32 dxf_section(dxf_writer_t *w, const dxf_CHAR *name);

/* Section HEADER 0. */
DXF_API dxf_I32 dxf_section_header(dxf_writer_t *w);

/* Section TABLES */
DXF_API dxf_I32 dxf_section_tables(dxf_writer_t *w);

/* Section BLOCKS */
DXF_API dxf_I32 dxf_section_blocks(dxf_writer_t *w);

/* Section ENTITIES */
DXF_API dxf_I32 dxf_section_entities(dxf_writer_t *w);

/* Section CLASSES */
DXF_API dxf_I32 dxf_section_classes(dxf_writer_t *w);

/* Section OBJECTS */
DXF_API dxf_I32 dxf_section_object(dxf_writer_t *w);

/* End of a section. */
DXF_API dxf_I32 dxf_section_end(dxf_writer_t *w);

/* Table for layers. */
DXF_API dxf_I32 dxf_table_layers(dxf_writer_t *w, dxf_I32 num);

/* Table for line types. */
DXF_API dxf_I32 dxf_table_line_types(dxf_writer_t *w, dxf_I32 num);

/* Table for application id. */
DXF_API dxf_I32 dxf_table_appid(dxf_writer_t *w, dxf_I32 num);

/* Table for text style. */
DXF_API dxf_I32 dxf_table_style(dxf_writer_t *w, dxf_I32 num);

/* End of a table. */
DXF_API dxf_I32 dxf_table_end(dxf_writer_t *w);

/* End of the DXF file. */
DXF_API dxf_I32 dxf_EOF(dxf_writer_t *w);

/* Entity. */
DXF_API dxf_I32 dxf_write_entity(dxf_writer_t *w, const dxf_CHAR *text);

/* Attributes of an entity. */
DXF_API dxf_I32 dxf_entity_attributes(dxf_writer_t *w, const dxf_entity_attr *attr);

/* Writes a DXF header to the file currently opened by the given DXF writer object.*/
DXF_API dxf_I32 dxf_write_header(dxf_writer_t *w);

/*  Writes a point entity to the file. */
DXF_API dxf_I32 dxf_write_point(dxf_writer_t          *w,
                                const dxf_point_data  *data,
                                const dxf_entity_attr *attr);

/* Writes a line entity to the file. */
DXF_API dxf_I32 dxf_write_line(dxf_writer_t          *w,
                               const dxf_line_data   *data,
                               const dxf_entity_attr *attr);

/* Writes an x line entity to the file. */
DXF_API dxf_I32 dxf_write_xline(dxf_writer_t          *w,
                                const dxf_xline_data  *data,
                                const dxf_entity_attr *attr);

/* Writes a ray entity to the file. */
DXF_API dxf_I32 dxf_write_ray(dxf_writer_t          *w,
                              const dxf_ray_data    *data,
                              const dxf_entity_attr *attr);

/* Writes a polyline entity to the file. */
DXF_API dxf_I32 dxf_write_polyline(dxf_writer_t            *w,
                                   const dxf_polyline_data *data,
                                   const dxf_entity_attr   *attr);

/* Writes a single vertex of a polyline to the file. */
DXF_API dxf_I32 dxf_write_vertex(dxf_writer_t *w, const dxf_vertex_data *data);

/* Writes the polyline end. Only needed for DXF R12. */
DXF_API dxf_I32 dxf_write_polyline_end(dxf_writer_t *w);

/* Writes a spline entity to the file. */
DXF_API dxf_I32 dxf_write_spline(dxf_writer_t          *w,
                                 const dxf_spline_data *data,
                                 const dxf_entity_attr *attr);

/* Writes a circle entity to the file. */
DXF_API dxf_I32 dxf_write_circle(dxf_writer_t          *w,
                                 const dxf_circle_data *data,
                                 const dxf_entity_attr *attr);

/* Writes an arc entity to the file. */
DXF_API dxf_I32 dxf_write_arc(dxf_writer_t          *w,
                              const dxf_arc_data    *data,
                              const dxf_entity_attr *attr);

/* Writes an ellipse entity to the file. */
DXF_API dxf_I32 dxf_write_ellipse(dxf_writer_t           *w,
                                  const dxf_ellipse_data *data,
                                  const dxf_entity_attr  *attr);

/* Writes a solid entity to the file. */
DXF_API dxf_I32 dxf_write_solid(dxf_writer_t          *w,
                                const dxf_solid_data  *data,
                                const dxf_entity_attr *attr);

/* Writes a trace entity to the file. */
DXF_API dxf_I32 dxf_write_trace(dxf_writer_t          *w,
                                const dxf_trace_data  *data,
                                const dxf_entity_attr *attr);

/* Writes a 3d face entity to the file. */
DXF_API dxf_I32 dxf_write_3dFace(dxf_writer_t           *w,
                                 const dxf_3d_face_data *data,
                                 const dxf_entity_attr  *attr);

/* Writes an insert to the file. */
DXF_API dxf_I32 dxf_write_insert(dxf_writer_t          *w,
                                 const dxf_insert_data *data,
                                 const dxf_entity_attr *attr);

/* Writes a multi text entity to the file. */
DXF_API dxf_I32 dxf_write_mText(dxf_writer_t          *w,
                                const dxf_mText_data  *data,
                                const dxf_entity_attr *attr);

/* Writes a text entity to the file. */
DXF_API dxf_I32 dxf_write_text(dxf_writer_t          *w,
                               const dxf_text_data   *data,
                               const dxf_entity_attr *attr);

/* Writes a attribute entity to the file. */
DXF_API dxf_I32 dxf_write_attribute(dxf_writer_t             *w,
                                    const dxf_attribute_data *data,
                                    const dxf_entity_attr    *attr);

DXF_API dxf_I32 dxf_write_dim_style_overrides(dxf_writer_t             *w,
                                              const dxf_dimension_data *data);

/* Writes an aligned dimension entity to the file. */
DXF_API dxf_I32 dxf_write_dim_aligned(dxf_writer_t               *w,
                                      const dxf_dimension_data   *data,
                                      const dxf_dim_aligned_data *edata,
                                      const dxf_entity_attr      *attr);

/* Writes a linear dimension entity to the file. */
DXF_API dxf_I32 dxf_write_dim_linear(dxf_writer_t          *w,
                                     dxf_dimension_data    *data,
                                     dxf_dim_linear_data   *edata,
                                     const dxf_entity_attr *attr);

/* Writes a radial dimension entity to the file. */
DXF_API dxf_I32 dxf_write_dim_radial(dxf_writer_t              *w,
                                     const dxf_dimension_data  *data,
                                     const dxf_dim_radial_data *edata,
                                     const dxf_entity_attr     *attr);

/* Writes a diametric dimension entity to the file. */
DXF_API dxf_I32 dxf_write_dim_diametric(dxf_writer_t                 *w,
                                        const dxf_dimension_data     *data,
                                        const dxf_dim_diametric_data *edata,
                                        const dxf_entity_attr        *attr);

/* Writes an angular dimension entity to the file. */
DXF_API dxf_I32 dxf_write_dim_angular2L(dxf_writer_t                 *w,
                                        const dxf_dimension_data     *data,
                                        const dxf_dim_angular2L_data *edata,
                                        const dxf_entity_attr        *attr);

/* Writes an angular dimension entity (3 points version) to the file. */
DXF_API dxf_I32 dxf_write_dim_angular3P(dxf_writer_t                 *w,
                                        const dxf_dimension_data     *data,
                                        const dxf_dim_angular3P_data *edata,
                                        const dxf_entity_attr        *attr);

/* Writes an ordinate dimension entity to the file. */
DXF_API dxf_I32 dxf_write_dim_ordinate(dxf_writer_t                *w,
                                       const dxf_dimension_data    *data,
                                       const dxf_dim_ordinate_data *edata,
                                       const dxf_entity_attr       *attr);

/* Writes a leader entity to the file. */
DXF_API dxf_I32 dxf_write_leader(dxf_writer_t          *w,
                                 const dxf_leader_data *data,
                                 const dxf_entity_attr *attr);

/* Writes leader end to the file. */
DXF_API dxf_I32 dxf_write_leader_end(dxf_writer_t *w, const dxf_leader_data *data);

/* Writes the beginning of a hatch entity to the file. This must be followed by one or
 * more writeHatchLoop() calls and a writeHatch2() call.*/
DXF_API dxf_I32 dxf_write_hatch1(dxf_writer_t          *w,
                                 const dxf_hatch_data  *data,
                                 const dxf_entity_attr *attr);

/* Writes the end of a hatch entity to the file. */
DXF_API dxf_I32 dxf_write_hatch2(dxf_writer_t          *w,
                                 const dxf_hatch_data  *data,
                                 const dxf_entity_attr *attr);

/* Writes the beginning of a hatch loop to the file. This must happen after writing the
 * beginning of a hatch entity.*/
DXF_API dxf_I32 dxf_write_hatch_loop1(dxf_writer_t *w, const dxf_hatch_loop_data *data);

/* Writes the end of a hatch loop to the file. */
DXF_API dxf_I32 dxf_write_hatch_loop2(dxf_writer_t *w, const dxf_hatch_loop_data *data);

/* Writes the beginning of a hatch entity to the file. */
DXF_API dxf_I32 dxf_write_hatch_edge(dxf_writer_t *w, const dxf_hatch_edge_data *data);

/* Writes an image entity.*/
DXF_API dxf_U32 dxf_write_image(dxf_writer_t          *w,
                                const dxf_image_data  *data,
                                const dxf_entity_attr *attr);

/* Writes an image definition entity. */
DXF_API dxf_I32 dxf_write_image_def(dxf_writer_t         *w,
                                    const dxf_I32         handle,
                                    const dxf_image_data *data);

/* Writes a layer to the file. Layers are stored in the tables section of a DXF file.*/
DXF_API dxf_I32 dxf_write_layer(dxf_writer_t          *w,
                                const dxf_layer_data  *data,
                                const dxf_entity_attr *attr);

/* Writes a line type to the file. Line types are stored in the tables section of a DXF
 * file.*/
DXF_API dxf_I32 dxf_write_line_type(dxf_writer_t *w, const dxf_line_type_data *data);

/* Writes the APPID section to the DXF file. */
DXF_API dxf_I32 dxf_write_appid(dxf_writer_t *w, const dxf_CHAR *name);

/* Writes a block's definition (no entities) to the DXF file. */
DXF_API dxf_I32 dxf_write_block(dxf_writer_t *w, const dxf_block_data *data);

/* Writes a block end. */
DXF_API dxf_I32 dxf_write_end_block(dxf_writer_t *w, const dxf_CHAR *name);

/* Writes a viewport section. This section is needed in DL_VERSION_R13. Note that this
 * method currently only writes a faked VPORT section to make the file readable by
 * Aut*cad.*/
DXF_API dxf_I32 dxf_write_view_port(dxf_writer_t *w);

/* Writes a style section. This section is needed in DL_VERSION_R13. */
DXF_API dxf_I32 dxf_write_style(dxf_writer_t *w, const dxf_style_data *style);

/* Writes a view section. This section is needed in DL_VERSION_R13. Note that this method
 * currently only writes a faked VIEW section to make the file readable by Aut*cad.*/
DXF_API dxf_I32 dxf_write_view(dxf_writer_t *w);

/* Writes a ucs section. This section is needed in DL_VERSION_R13. Note that this method
 * currently only writes a faked UCS section to make the file readable by Aut*cad.*/
DXF_API dxf_I32 dxf_write_ucs(dxf_writer_t *w);

/* Writes a dimstyle section. This section is needed in DL_VERSION_R13. Note that this
 * method currently only writes a faked DIMSTYLE section to make the file readable by
 * Aut*cad.*/
DXF_API dxf_I32 dxf_write_dim_style(dxf_writer_t *w,
                                    dxf_F64       dimasz,
                                    dxf_F64       dimexe,
                                    dxf_F64       dimexo,
                                    dxf_F64       dimgap,
                                    dxf_F64       dimtxt,
                                    dxf_I32       dimtad,
                                    dxf_BOOL      dimtih);

/* Writes a blockrecord section. This section is needed in DL_VERSION_R13. Note that this
 * method currently only writes a faked BLOCKRECORD section to make the file readable by
 * Aut*cad.*/
DXF_API dxf_I32 dxf_write_block_record(dxf_writer_t *w, const dxf_CHAR *name);

/* Writes a objects section. This section is needed in DL_VERSION_R13. Note that this
 * method currently only writes a faked OBJECTS section to make the file readable by
 * Aut*cad.*/

DXF_API dxf_I32 dxf_write_objects(dxf_writer_t *w, const dxf_CHAR *appDictionaryName);

DXF_API dxf_I32 dxf_write_app_dictionary(dxf_writer_t *w);

DXF_API dxf_U32 dxf_write_dictionary_entry(dxf_writer_t *w, const dxf_CHAR *name);

DXF_API dxf_I32 dxf_write_x_record_int(dxf_writer_t *w, dxf_I32 handle, dxf_I32 value);

DXF_API dxf_I32 dxf_write_x_record_double(dxf_writer_t *w, dxf_I32 handle, dxf_F64 value);

DXF_API dxf_I32 dxf_write_x_record_BOOLean(dxf_writer_t *w,
                                           dxf_I32       handle,
                                           dxf_BOOL      value);

DXF_API dxf_I32 dxf_write_x_record_string(dxf_writer_t   *w,
                                          dxf_I32         handle,
                                          const dxf_CHAR *value);

/* Writes the end of the objects section. This section is needed in DL_VERSION_R13. Note
 * that this method currently only writes a faked OBJECTS section to make the file
 * readable by Aut*cad.*/
DXF_API dxf_I32 dxf_write_objects_end(dxf_writer_t *w);

/* Writes a comment to the DXF file. */
DXF_API dxf_I32 dxf_write_comment(dxf_writer_t *w, const dxf_CHAR *comment);

/* ------------------------------------------------------------------------------------ */
/*                                      dxf Reader                                      */
/* ------------------------------------------------------------------------------------ */

typedef struct dxf_document_t {
    Version version;

    dxf_CHAR polylineLayer[512];
    dxf_F64 *vertices;
    dxf_I32  maxVertices;
    dxf_I32  vertexIndex;

    dxf_F64 *knots;
    dxf_I32  maxKnots;
    dxf_I32  knotIndex;

    dxf_F64 *weights;
    dxf_I32  weightIndex;

    dxf_F64 *controlPoints;
    dxf_I32  maxControlPoints;
    dxf_I32  controlPointIndex;

    dxf_F64 *fitPoints;
    dxf_I32  maxFitPoints;
    dxf_I32  fitPointIndex;

    dxf_F64 *leaderVertices;
    dxf_I32  maxLeaderVertices;
    dxf_I32  leaderVertexIndex;

    dxf_BOOL            firstHatchLoop;
    dxf_hatch_edge_data hatchEdge;
    struct link_list  **hatchEdges; /* dxf_hatch_edge_data second rank pointer */

    dxf_BOOL xRecordValues;

    /* ...same as integer */
    dxf_U32 groupCode;
    /* Only the useful part of the group value */
    dxf_CHAR groupValue[DL_DXF_MAX_LINE];
    /* Current entity type */
    dxf_I32 currentObjectType;
    /* Value of the current setting */
    dxf_CHAR settingValue[DL_DXF_MAX_LINE + 1];
    /* Key of the current setting */
    dxf_CHAR settingKey[DL_DXF_MAX_LINE];
    /* Stores the group codes */
    struct hash_table *values;
    /* First call of this method. We initialize all group values in the first call. */
    dxf_BOOL firstCall;
    /* Attributes of the current entity (layer, color, width, line type) */
    dxf_entity_attr attrib;
    /* library version. hex: 0x20003001 = 2.0.3.1 */
    dxf_I32 libVersion;
    /* app specific dictionary handle: */
    dxf_U32 appDictionaryHandle;
    /* handle of standard text style, referenced by dim style: */
    dxf_U32 styleHandleStd;
} dxf_document_t;

#ifdef __cplusplus
}
#endif

#endif // DXF_H
