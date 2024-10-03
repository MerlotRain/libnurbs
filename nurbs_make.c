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

nurbs_CurveData *nurbs__makeEllipseArc(const nurbs_Point *center,
                                       const nurbs_Vector *xaxis,
                                       const nurbs_Vector *yaxis,
                                       double minAngle, double maxAngle)
{
    double xradius = nurbs__vecNorm((const double *)xaxis);
    double yradius = nurbs__vecNorm((const double *)yaxis);

    nurbs_Vector *lxaxis = (nurbs_Vector *)nurbs__vecNormalized(xaxis);
    nurbs_Vector *lyaxis = (nurbs_Vector *)nurbs__vecNormalized(yaxis);

    // if the end angle is less than the start angle, do a circle.
    if (maxAngle < minAngle)
        maxAngle = 2.0 * M_PI + minAngle;

    double theta = maxAngle - minAngle;
    size_t numArcs = 0;
    // how many arcs?
    if (theta < M_PI_2)
        numArcs = 1;
    else {
        if (theta <= M_PI)
            numArcs = 2;
        else if (theta <= 3.0 * M_PI_2)
            numArcs = 3;
        else
            numArcs = 4;
    }

    double dtheta = theta / numArcs;
    size_t n = 2 * numArcs;
    double w1 = cos(dtheta / 2);
    nurbs_Point *P0 = (nurbs_Point *)nurbs__vecAdd(
        center, nurbs__vecAdd(nurbs__vecMul(lxaxis, xradius * cos(minAngle)),
                              nurbs__vecMul(lyaxis, yradius * sin(minAngle))));
    nurbs_Vector *T0 =
        (nurbs_Vector *)nurbs__vecSub(nurbs__vecMul(lyaxis, cos(minAngle)),
                                      nurbs__vecMul(lxaxis, sin(minAngle)));
    double *knots = (double *)calloc(2 * numArcs + 3, sizeof(double));
    assert(knots);
    size_t index = 0;
    double angle = minAngle;
    double *weights = (double *)calloc(numArcs * 2, sizeof(double));
    assert(weights);
    nurbs_PointArray *points =
        (nurbs_PointArray *)malloc(sizeof(nurbs_PointArray));
    assert(points);
    points->npoints = numArcs * 2 + 1;
    points->points =
        (nurbs_Point *)malloc(sizeof(nurbs_Point) * (numArcs * 2 + 1));
    points->weights = (double *)malloc(sizeof(double) * (numArcs * 2 + 1));
    assert(points->points);
    assert(points->weights);
    points->npoints = numArcs * 2 + 1;
    points->points[0] = *P0;

    for (size_t i = 1; i < numArcs + 1; i++) {
        angle += dtheta;
        nurbs_Point *P2 = (nurbs_Point *)nurbs__vecAdd(
            center, nurbs__vecAdd(nurbs__vecMul(lxaxis, xradius * cos(angle)),
                                  nurbs__vecMul(lyaxis, yradius * sin(angle))));
        weights[index + 2] = 1;
        points->points[index + 2] = *P2;

        nurbs_Vector *T2 =
            (nurbs_Vector *)nurbs__vecSub(nurbs__vecMul(lyaxis, cos(angle)),
                                          nurbs__vecMul(lxaxis, sin(angle)));
        nurbs__CurveCurveIntersection inters;
        nurbs__intersecectRay(
            P0,
            (const nurbs_Point *)(nurbs__vecMul(T0, 1 / nurbs__vecNorm(T0))),
            P2,
            (const nurbs_Point *)(nurbs__vecMul(T2, 1 / nurbs__vecNorm(T2))),
            &inters);

        nurbs_Point *T1 =
            (nurbs_Point *)nurbs__vecAdd(P0, nurbs__vecMul(T0, inters.u0));

        weights[index + 1] = w1;
        points->points[index + 1] = *T1;

        index += 2;
        if (i < numArcs) {
            P0 = P2;
            T0 = T2;
        }
    }

    size_t j = 2 * numArcs + 1;

    for (size_t i = 0; i < 3; ++i) {
        knots[i] = 0;
        knots[i + j] = 1.0;
    }

    switch (numArcs) {
    case 2:
        knots[3] = knots[4] = 0.5;
        break;
    case 3:
        knots[3] = knots[4] = 1.0 / 3.0;
        knots[5] = knots[6] = 2.0 / 3.0;
        break;
    case 4:
        knots[3] = knots[4] = 0.25;
        knots[5] = knots[6] = 0.5;
        knots[7] = knots[8] = 0.75;
        break;
    default:
        break;
    }

    nurbs_CurveData *curve_data =
        (nurbs_CurveData *)malloc(sizeof(nurbs_CurveData));
    curve_data->degree = 2;
    curve_data->knots = knots;
    curve_data->cv = points;
    return curve_data;
}

nurbs_CurveData *nurbs__makeArc(const nurbs_Point *center,
                                const nurbs_Vector *xaxis,
                                const nurbs_Vector *yaxis, double radius,
                                double minAngle, double maxAngle)
{
    return nurbs__makeEllipseArc(center,
                                 (const nurbs_Vector *)nurbs__vecMul(
                                     nurbs__vecNormalized(xaxis), radius),
                                 (const nurbs_Vector *)nurbs__vecMul(
                                     nurbs__vecNormalized(yaxis), radius),
                                 minAngle, maxAngle);
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
