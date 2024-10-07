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

#ifndef NURBS_INTERNAL_H
#define NURBS_INTERNAL_H

#include "nurbs_api.h"
#include <stddef.h>

#define NURBS__EPSILON   (1e-10)
#define NURBS__TOLERANCE (1e-6)

typedef struct {
    nurbs_Point point0;
    nurbs_Point point1;
    double u0;
    double u1;
} nurbs__CurveCurveIntersection;

/* ---------------------------------- Make ---------------------------------- */

nurbs_CurveData *nurbs__makeEllipseArc(const nurbs_Point *center,
                                       const nurbs_Vector *xaxis,
                                       const nurbs_Vector *yaxis,
                                       double minAngle, double maxAngle);

nurbs_CurveData *nurbs__makeArc(const nurbs_Point *center,
                                const nurbs_Vector *xaxis,
                                const nurbs_Vector *yaxis, double radius,
                                double minAngle, double maxAngle);

nurbs_CurveData *nurbs__makePolyline(const nurbs_Point *points, size_t np);

nurbs_CurveData *nurbs__makeRationalBezier(const nurbs_Point *points, size_t np,
                                           double *weights, size_t nw);

/* ---------------------------------- Vec ----------------------------------- */

double nurbs__vecNorm_(const double *v);
double nurbs__vecNormSquared_(const double *a);
double *nurbs__vecAdd_(const double *v1, const double *v2);
double *nurbs__vecMul_(const double *v, double a);
double *nurbs__vecDiv_(const double *v, double a);
double *nurbs__vecSub_(const double *v1, const double *v2);
int nurbs__vecIsZero_(const double *v);
double *nurbs__vecNormalized_(const double *v);
double nurbs__vecDot_(const double *v1, const double *v2);
double *nurbs__vecOnRay_(const double *origin, const double *dir, double u);

#define nurbs__vecNorm(v)        (nurbs__vecNorm_((const double *)(v)))

#define nurbs__vecNormSquared(v) (nurbs__vecNormalized_((const double *)(v)))

#define nurbs__vecAdd(v1, v2) \
    (nurbs__vecAdd_((const double *)(v1), (const double *)(v2)))

#define nurbs__vecMul(v, a) (nurbs__vecMul_((const double *)(v), a))

#define nurbs__vecDiv(v, a) (nurbs__vecDiv_((const double *)(v), a))

#define nurbs__vecSub(v1, v2) \
    (nurbs__vecSub_((const double *)(v1), (const double *)(v2)))

#define nurbs__vecIsZero(v)     (nurbs__vecIsZero_((const double *)(v)))

#define nurbs__vecNormalized(v) (nurbs__vecNormalized_((const double *)(v)))

#define nurbs__vecDot(v1, v2) \
    (nurbs__vecDot_((const double *)(v1), (const double *)(v2)))

#define nurbs__vecOnRay(origin, dir, u) \
    (nurbs__vecOnRay_((const double *)(origin), (const double *)(dir), u))

/* -------------------------------- Intersect ------------------------------- */

int nurbs__intersecectRay(const nurbs_Point *a0, const nurbs_Point *a,
                          const nurbs_Point *b0, const nurbs_Point *b,
                          nurbs__CurveCurveIntersection *intersection);

/* ---------------------------------- Eval ---------------------------------- */

/**
 * \brief Transform a 1d array of points into their homogeneous equivalents
 *
 * \param pa The array of points
 * \param weights The array of weights
 * \return void
 */
void nurbs__evalHomogenize1d(nurbs_PointArray *pa, double *weights);

/* ---------------------------------- Array --------------------------------- */

typedef void (*array_free)(void *);

typedef struct {
    uint8_t *elts;
    size_t size;
    size_t nalloc;
    size_t nelts;
    array_free free;
} nurbs_array_t;

#define nurbs_array_elts(arr)  ((arr)->elts)
#define nurbs_array_nelts(arr) ((arr)->nelts)

int nurbs_array_init(nurbs_array_t *arr, array_free free, size_t size,
                     size_t nalloc);
nurbs_array_t *nurbs_array_new(array_free free, size_t size, size_t nalloc);
void nurbs_array_destroy(nurbs_array_t *arr);
void nurbs_array_free(nurbs_array_t *arr);
void nurbs_array_reset(nurbs_array_t *arr);
void *nurbs_array_push(nurbs_array_t *arr);
void *nurbs_array_pushn(nurbs_array_t *arr, size_t n);
void nurbs_array_pop(nurbs_array_t *arr);

#endif /* NURBS_INTERNAL_H */