/**
 * Copyright (c) 2023-present Merlot.Rain
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef LIBCADSHAPE_H
#define LIBCADSHAPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CAD_TRUE         1
#define CAD_FALSE        0

#define SHAPE_POINT      1
#define SHAPE_LINE       2
#define SHAPE_ARC        3
#define SHAPE_CIRCLE     4
#define SHAPE_ELLIPSE    5
#define SHAPE_POLYLINE   6
#define SHAPE_SPLINE     7
#define SHAPE_TRIANGLE   8
#define SHAPE_XLINE      9
#define SHAPE_RAY        10
#define SHAPE_COLLECTION 11

// algorithm, nurbs

typedef struct {
    double x;
    double y;
    double z;
} POINT3D;

typedef struct {
    uint32_t npoints;
    POINT3D *pointlist;
} POINTARRAY;

typedef struct {
    POINT3D min;
    POINT3D max;
} CADBOX;

typedef struct {
    uint8_t type;
    void *data;
} CADSHAPE;

typedef struct {
    uint8_t type;
    POINTARRAY *points;
    double radius;
    double beginAngle;
    double endAngle;
} CADARC;

typedef struct {
    uint8_t type;
    POINTARRAY *points;
} CADLINE;

typedef struct {
    uint8_t type;
    POINTARRAY *points;
    double radius;
} CADCIRCLE;

typedef struct {
    uint8_t type;
    POINTARRAY *points;
    double ratio;
    double start;
    double end;
    int reversed;
} CADELLIPSE;

typedef struct {
    uint8_t type;
    POINTARRAY *points;
} CADPOINT;

typedef struct {
    uint8_t type;
    POINTARRAY *points;
    double *bulges;
    int closed;
} CADPOLYLINE;

typedef struct {
    uint8_t type;
    POINTARRAY *points;
} CADRAY, CADXLINE;

typedef struct {
    uint8_t type;
    POINTARRAY *points;
} CADTRIANGLE;

typedef struct {
    uint8_t type;
    CADSHAPE **shapes;
    uint32_t nshapes;
} CADCOLLECTION;

extern CADSHAPE *cadarc_as_cadshape(const CADARC *obj);
extern CADSHAPE *cadcircle_as_cadshape(const CADCIRCLE *obj);
extern CADSHAPE *cadellipse_as_cadshape(const CADELLIPSE *obj);
extern CADSHAPE *cadline_as_cadshape(const CADLINE *obj);
extern CADSHAPE *cadpoint_as_cadshape(const CADPOINT *obj);
extern CADSHAPE *cadpolyline_as_cadshape(const CADPOLYLINE *obj);
extern CADSHAPE *cadray_as_cadshape(const CADRAY *obj);
extern CADSHAPE *cadxline_as_cadshape(const CADXLINE *obj);
extern CADSHAPE *cadtriangle_as_cadshape(const CADTRIANGLE *obj);
extern CADSHAPE *cadcollection_as_cadshape(const CADCOLLECTION *obj);

extern CADARC *cadshape_as_cadarc(const CADSHAPE *obj);
extern CADCIRCLE *cadshape_as_cadcircle(const CADSHAPE *obj);
extern CADELLIPSE *cadshape_as_cadellipse(const CADSHAPE *obj);
extern CADLINE *cadshape_as_cadline(const CADSHAPE *obj);
extern CADPOINT *cadshape_as_cadpoint(const CADSHAPE *obj);
extern CADPOLYLINE *cadshape_as_cadpolyline(const CADSHAPE *obj);
extern CADRAY *cadshape_as_cadray(const CADSHAPE *obj);
extern CADXLINE *cadshape_as_cadxline(const CADSHAPE *obj);
extern CADTRIANGLE *cadshape_as_cadtriangle(const CADSHAPE *obj);
extern CADCOLLECTION *cadshape_as_cadcollection(const CADSHAPE *obj);

extern void cadshape_free(CADSHAPE *obj);

extern CADBOX cadshape_bbox(const CADSHAPE *obj);
extern double cadshape_length(const CADSHAPE *obj);
extern int cadshape_equal(const CADSHAPE *obj1, const CADSHAPE *obj2,
                          double tol);
extern POINT3D cadshape_to(const CADSHAPE *obj, const POINT3D point,
                           int limited, double strict_range);
extern double distance_to(const CADSHAPE *obj, const POINT3D point, int limited,
                          double strict_range);
extern double max_distance_to(const CADSHAPE *obj, const POINT3D point,
                              int npoints, int limited, double strict_range);
extern int cad_on_shape(const CADSHAPE *obj, const POINT3D point, int limited,
                        double tol);
extern int cadshape_endpoints(const CADSHAPE *obj, POINT3D **points, int *n);
extern int cadshape_middlepoints(const CADSHAPE *obj, POINT3D **points, int *n);
extern int cadshape_centerpoints(const CADSHAPE *obj, POINT3D **points, int *n);
extern int cadshape_move(CADSHAPE *obj, const POINT3D offset);
extern int cadshape_rotate(CADSHAPE *obj, double rotation,
                           const POINT3D center);
extern int cadshape_scale(CADSHAPE *obj, double factor, const POINT3D center);
extern int cadshape_mirror(CADSHAPE *obj, const CADLINE line);
extern int cadshape_intersectionpoints(CADSHAPE *obj1, const CADSHAPE *obj2);

extern CADARC *cadarc_make3p(const POINT3D *points);
extern CADARC *cadarc_make2pbulge(const POINT3D *point, double bulge);
extern CADARC *cadarc_create_biarc(const POINT3D *start, double start_direction,
                                   const POINT3D *end, double end_direction);
extern CADELLIPSE *cadellipse_create_4points(const POINT3D *points);

#ifdef __cplusplus
}
#endif

#endif /* LIBCADSHAPE_H */