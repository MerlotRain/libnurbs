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

#include "nurbs_internal.h"
#include <math.h>

int nurbs__intersecectRay(const nurbs_Point *a0, const nurbs_Point *a,
                          const nurbs_Point *b0, const nurbs_Point *b,
                          nurbs__CurveCurveIntersection *intersection)
{

    double dab = nurbs__vecDot(a, b);
    double dab0 = nurbs__vecDot(a, b0);
    double daa0 = nurbs__vecDot(a, a0);
    double dbb0 = nurbs__vecDot(b, b0);
    double dba0 = nurbs__vecDot(b, a0);
    double daa = nurbs__vecDot(a, a);
    double dbb = nurbs__vecDot(b, b);
    double div = daa * dbb - dab * dab;

    if (fabs(div) < NURBS__EPSILON) {
        return NURBS_FALSE;
    }

    double num = dab * (dab0 - daa0) - daa * (dbb0 - dba0);
    double w = num / div;
    double t = (dab0 - daa0 + w * dab) / daa;

    nurbs_Point *p0 = (nurbs_Point *)nurbs__vecOnRay(a0, a, t);
    nurbs_Point *p1 = (nurbs_Point *)nurbs__vecOnRay(b0, b, w);
    intersection->point0 = *p0;
    intersection->point1 = *p1;
    intersection->u0 = t;
    intersection->u1 = w;

    return NURBS_TRUE;
}
