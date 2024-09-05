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

double nurbs__vecNorm(nurbs_Vector a)
{
    double norm2 = nurbs__vecNormSquared(a);
    return norm2 != 0.0 ? sqrt(norm2) : norm2;
}

double nurbs__vecNormSquared(nurbs_Vector a)
{
    return pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2);
}

nurbs_Vector nurbs__vecAdd(const nurbs_Vector v1, const nurbs_Vector v2)
{
    nurbs_Vector res;
    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    return res;
}

nurbs_Vector nurbs__vecMul(const nurbs_Vector v, double a)
{
    nurbs_Vector res;
    res.x = v.x * a;
    res.y = v.y * a;
    res.z = v.z * a;
    return res;
}

nurbs_Vector nurbs__vecDiv(const nurbs_Vector v, double a)
{
    nurbs_Vector res;
    res.x = v.x / a;
    res.y = v.y / a;
    res.z = v.z / a;
    return res;
}

nurbs_Vector nurbs__vecSub(const nurbs_Vector v1, const nurbs_Vector v2)
{
    nurbs_Vector res;
    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    return res;
}

int nurbs__vecIsZero(nurbs_Vector v)
{
    if (v.x > 1e-6 || v.y > 1e-6 || v.z > 1e-6) return NURBS_FALSE;
    return NURBS_TRUE;
}

nurbs_Vector nurbs__vecNormalized(const nurbs_Vector v)
{
    return nurbs__vecDiv(v, nurbs__vecNorm(v));
}