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

double nurbs__vecNorm_(const double *v)
{
    double norm2 = nurbs__vecNormSquared_(v);
    return norm2 != 0.0 ? sqrt(norm2) : norm2;
}

double nurbs__vecNormSquared_(const double *a)
{
    return pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2);
}

double *nurbs__vecAdd_(const double *v1, const double *v2)
{
    double res[3] = {0};
    res[0] = v1[0] + v2[0];
    res[1] = v1[1] + v2[1];
    res[2] = v1[2] + v2[2];
    return res;
}

double *nurbs__vecMul_(const double *v, double a)
{
    double res[3] = {0};
    res[0] = v[0] * a;
    res[1] = v[1] * a;
    res[2] = v[2] * a;
    return res;
}

double *nurbs__vecDiv_(const double *v, double a)
{
    double res[3] = {0};
    res[0] = v[0] / a;
    res[1] = v[1] / a;
    res[2] = v[2] / a;
    return res;
}

double *nurbs__vecSub_(const double *v1, const double *v2)
{
    double res[3] = {0};
    res[0] = v1[0] - v2[0];
    res[1] = v1[1] - v2[1];
    res[2] = v1[2] - v2[2];
    return res;
}

int nurbs__vecIsZero_(const double *v)
{
    if (v[0] > NURBS__TOLERANCE || v[1] > NURBS__TOLERANCE ||
        v[2] > NURBS__TOLERANCE)
        return NURBS_FALSE;
    return NURBS_TRUE;
}

double *nurbs__vecNormalized_(const double *v)
{
    return nurbs__vecDiv_(v, nurbs__vecNorm_(v));
}

double nurbs__vecDot_(const double *v1, const double *v2)
{
    double sum = 0;
    sum += v1[0] * v2[0];
    sum += v1[1] * v2[1];
    sum += v1[2] * v2[2];
    return sum;
}

double *nurbs__vecOnRay_(const double *origin, const double *dir, double u)
{
    return nurbs__vecAdd_(origin, nurbs__vecMul_(dir, u));
}
