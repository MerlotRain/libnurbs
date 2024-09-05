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
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

nurbs_CurveData *nurbs__makeEllipseArc(const nurbs_Point center,
                                       const nurbs_Vector xaxis,
                                       const nurbs_Vector yaxis,
                                       double minAngle, double maxAngle)
{
    double xradius = nurbs__vecNorm(xaxis);
    double yradius = nurbs__vecNorm(yaxis);

    nurbs_Vector lcenter = {.x = center.x, .y = center.y, .z = center.z};
    nurbs_Vector lxaxis = nurbs__vecNormalized(xaxis);
    nurbs_Vector lyaxis = nurbs__vecNormalized(yaxis);

    if(maxAngle < minAngle) maxAngle = 2.0 * M_PI + minAngle;

    double theta = maxAngle - minAngle;
    size_t numArcs = 0;

    if(theta < M_PI_2)
        numArcs = 1;
    else
    {
        if(theta <= M_PI)
            numArcs = 2;
        else if(theta <= 3.0 * M_PI_2)
            numArcs = 3;
        else
            numArcs = 4;
    }

    double dtheta = theta / numArcs;
    size_t n = 2 * numArcs;
    double w1 = cos(dtheta / 2);
    nurbs_Vector P0 = nurbs__vecAdd(
        lcenter,
        nurbs__vecAdd(nurbs__vecMul(lxaxis, xradius * cos(minAngle)),
                      nurbs__vecMul(lyaxis, yradius * sin(minAngle))));
    nurbs_Vector T0 = nurbs__vecSub(nurbs__vecMul(lyaxis, cos(minAngle)),
                                    nurbs__vecMul(lxaxis, sin(minAngle)));
    double *knots = (double *)calloc(2 * numArcs + 3, sizeof(double));
    assert(knots);
    size_t index = 0;
    double angle = minAngle;
    double *weights = (double *)calloc(numArcs * 2, sizeof(double));
    assert(weights);
    return NULL;
}

nurbs_CurveData *nurbs__makeArc(const nurbs_Point center,
                                const nurbs_Vector xaxis,
                                const nurbs_Vector yaxis, double radius,
                                double minAngle, double maxAngle)
{
    return nurbs__makeEllipseArc(
            center, nurbs__vecMul(nurbs__vecNormalized(xaxis), radius),
            nurbs__vecMul(nurbs__vecNormalized(yaxis), radius), minAngle,
            maxAngle);
}

nurbs_CurveData *nurbs__makePolyline(const nurbs_Point *points, size_t np)
{
    return NULL;
}

nurbs_CurveData *nurbs__makeRationalBezier(const nurbs_Point *points, size_t np,
                                           double *weights, size_t nw)
{
    return NULL;
}
