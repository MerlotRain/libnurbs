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

#ifndef NURBS_H
#define NURBS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#define NURBS_TRUE            1
#define NURBS_FALSE           0

#define NURBS_GEOM_ARC        1
#define NURBS_GEOM_BEZIER     2
#define NURBS_GEOM_CIRCLE     3
#define NURBS_GEOM_ELLIPSE    4
#define NURBS_GEOM_ELLIPSEARC 5
#define NURBS_GEOM_LINE       6

typedef struct {
    double x;
    double y;
    double z;
    double w; /* weight */
} nurbs_Point;

typedef struct {
    double x;
    double y;
    double z;
} nurbs_Vector;

typedef struct {
    size_t npoints;      /* number of control vertex */
    nurbs_Point *points; /* array of control vertex */
    double *weights;     /* array of weights */
} nurbs_PointArray;

typedef struct {
    nurbs_Vector normal;
    nurbs_Point origin;
} nurbs_Plane;

typedef struct {
    nurbs_Vector dir;
    nurbs_Point origin;
} nurbs_Ray;

typedef struct {
    uint8_t degree;       /* degree of curve */
    uint32_t nknots;      /* number of nondecreasing knot values */
    double *knots;        /* array of nondecreasing knot values */
    nurbs_PointArray *cv; /* control vertex */
} nurbs_CurveData;

typedef struct {
    uint8_t degreeU;       /* degree of surface in u direction */
    uint8_t degreeV;       /* degree of surface in v direction */
    double *knotsU;        /* array of nondecreasing knot values in u
                              direction */
    double *knotsV;        /* array of nondecreasing knot values in v
                              direction */
    uint32_t npointsU;     /* number of knot values in u direction */
    uint32_t npointsV;     /* number of knot values in v direction */
    nurbs_PointArray *cvs; /* 2d array of control points, the
                              vertical direction (u) increases from
                              top to bottom, the v direction from
                              left to right, and where each control
                              point is an array of length (dim)*/
    int ncvs;              /* number of cvs */
} nurbs_SurfaceData;

/*
 square matrix data array
 2 1 0 0 1
  |
  |-----
        [1 0]
        [0 1]
 3 1 0 0 0 1 0 0 0 1
  |
  |-----
        [1  0  0]
        [0  1  0]
        [0  0  1]
  The first tuple of the array represents the size of the matrix,
  so the size of the array is size * size + 1.
  and fill the entire matrix line by line with the remaining elements.
*/
typedef double *nurbs_Matrix;

typedef struct {
    double u;
    double len;
} nurbs_CurveSample;

/* Nurbs shapes */

#define GEOM_NURBS_DATA \
    int type;           \
    nurbs_CurveData *nurbs_data;

typedef struct {
    GEOM_NURBS_DATA
} nurbs_Curve;

typedef struct {
    GEOM_NURBS_DATA

    nurbs_Point _center;
    nurbs_Vector _xaxis;
    nurbs_Vector _yaxis;
    double _radius;
    double _minAngle;
    double _maxAngle;
} nurbs_Arc, nurbs_Circle;

typedef struct {
    GEOM_NURBS_DATA
} nurbs_BezierCurve;

typedef struct {
    GEOM_NURBS_DATA

    nurbs_Point _center;
    nurbs_Vector _xaxis;
    nurbs_Vector _yaxis;
    double _minAngle;
    double _maxAngle;
} nurbs_EllipseArc, nurbs_Ellipse;

typedef struct {
    GEOM_NURBS_DATA

    nurbs_Point _start;
    nurbs_Point _end;
} nurbs_Line;

#ifdef __cplusplus
}
#endif

#endif /* NURBS_H */