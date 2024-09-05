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

#include "nurbs.h"
#include <stddef.h>

/* ---------------------------------- Make ---------------------------------- */

nurbs_CurveData *nurbs__makeEllipseArc(const nurbs_Point center,
                                       const nurbs_Vector xaxis,
                                       const nurbs_Vector yaxis,
                                       double minAngle, double maxAngle);

nurbs_CurveData *nurbs__makeArc(const nurbs_Point center,
                                const nurbs_Vector xaxis,
                                const nurbs_Vector yaxis, double radius,
                                double minAngle, double maxAngle);

nurbs_CurveData *nurbs__makePolyline(const nurbs_Point *points, size_t np);

nurbs_CurveData *nurbs__makeRationalBezier(const nurbs_Point *points, size_t np,
                                           double *weights, size_t nw);


/* ---------------------------------- Vec ----------------------------------- */

double nurbs__vecNorm(nurbs_Vector a);

double nurbs__vecNormSquared(nurbs_Vector a);

nurbs_Vector nurbs__vecAdd(const nurbs_Vector v1, const nurbs_Vector v2);

nurbs_Vector nurbs__vecMul(const nurbs_Vector v, double a);

nurbs_Vector nurbs__vecDiv(const nurbs_Vector v, double a);

nurbs_Vector nurbs__vecSub(const nurbs_Vector v1, const nurbs_Vector v2);

int nurbs__vecIsZero(nurbs_Vector v);

nurbs_Vector nurbs__vecNormalized(const nurbs_Vector v);

#endif /* NURBS_INTERNAL_H */