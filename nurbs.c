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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void nurbs_free(nurbs_Curve *curve)
{
}

nurbs_Curve *nurbs_new_curve_withKCW(uint8_t degree, const nurbs_Point *cv,
                                     uint32_t ncv, double *knots,
                                     uint32_t nknots, double *weights,
                                     uint32_t nweights)
{
    return NULL;
}

nurbs_Curve *nurbs_new_curve_withP(const nurbs_Point *cv, uint32_t ncv,
                                   uint8_t degree)
{
    return NULL;
}

nurbs_Arc *nurbs_new_arc(const nurbs_Point center, const nurbs_Vector xaxis,
                         const nurbs_Vector yaxis, double radius,
                         double minAngle, double maxAngle)
{
    nurbs_Arc *arc = (nurbs_Arc *)malloc(sizeof(nurbs_Arc));
    if (arc == NULL)
        return NULL;

    arc->type = NURBS_GEOM_ARC;
    arc->nurbs_data =
        nurbs__makeArc(center, xaxis, yaxis, radius, minAngle, maxAngle);
    if (arc->nurbs_data == NULL) {
        free(arc);
        return NULL;
    };
    arc->_center = center;
    arc->_xaxis = xaxis;
    arc->_yaxis = yaxis;
    arc->_radius = radius;
    arc->_minAngle = minAngle;
    arc->_maxAngle = maxAngle;
    return arc;
}

nurbs_BezierCurve *nurbs_new_bezier(const nurbs_Point *points, uint32_t npoints,
                                    double *weights, int nw)
{
    nurbs_BezierCurve *bezier =
        (nurbs_BezierCurve *)malloc(sizeof(nurbs_BezierCurve));
    if (bezier == NULL)
        return NULL;
    bezier->type = NURBS_GEOM_BEZIER;
    bezier->nurbs_data =
        nurbs__makeRationalBezier(points, npoints, weights, nw);
    if (bezier->nurbs_data == NULL) {
        free(bezier);
        return NULL;
    }
    return bezier;
}

nurbs_Circle *nurbs_new_circle(const nurbs_Point center,
                               const nurbs_Vector xaxis,
                               const nurbs_Vector yaxis, double radius)
{
    nurbs_Circle *circle = (nurbs_Circle *)malloc(sizeof(nurbs_Circle));
    if (circle == NULL)
        return NULL;
    circle->type = NURBS_GEOM_CIRCLE;
    circle->nurbs_data =
        nurbs__makeArc(center, xaxis, yaxis, radius, 0.0, 2.0 * M_PI);
    if (circle->nurbs_data == NULL) {
        free(circle);
        return NULL;
    }
    circle->_center = center;
    circle->_xaxis = xaxis;
    circle->_yaxis = yaxis;
    circle->_radius = radius;
    circle->_minAngle = 0.0;
    circle->_maxAngle = 2.0 * M_PI;
    return circle;
}

nurbs_EllipseArc *nurbs_new_ellipsearc(const nurbs_Point center,
                                       const nurbs_Vector xaxis,
                                       const nurbs_Vector yaxis,
                                       double minAngle, double maxAngle)
{
    nurbs_EllipseArc *arc =
        (nurbs_EllipseArc *)malloc(sizeof(nurbs_EllipseArc));
    if (arc == NULL)
        return NULL;
    arc->type = NURBS_GEOM_ELLIPSEARC;
    arc->nurbs_data =
        nurbs__makeEllipseArc(center, xaxis, yaxis, minAngle, maxAngle);
    if (arc->nurbs_data == NULL) {
        free(arc);
        return NULL;
    }
    arc->_center = center;
    arc->_xaxis = xaxis;
    arc->_yaxis = yaxis;
    arc->_minAngle = minAngle;
    arc->_maxAngle = maxAngle;
    return arc;
}

nurbs_Ellipse *nurbs_new_ellipse(const nurbs_Point center,
                                 const nurbs_Vector xaxis,
                                 const nurbs_Vector yaxis)
{
    nurbs_Ellipse *ellipse = (nurbs_Ellipse *)malloc(sizeof(nurbs_Ellipse));
    if (ellipse == NULL)
        return NULL;
    ellipse->type = NURBS_GEOM_ELLIPSE;
    ellipse->nurbs_data =
        nurbs__makeEllipseArc(center, xaxis, yaxis, 0.0, 2.0 * M_PI);
    if (ellipse->nurbs_data == NULL) {
        free(ellipse);
        return NULL;
    }
    ellipse->_center = center;
    ellipse->_xaxis = xaxis;
    ellipse->_yaxis = yaxis;
    ellipse->_minAngle = 0.0;
    ellipse->_maxAngle = 2.0 * M_PI;
    return ellipse;
}

nurbs_Line *nurbs_new_line(const nurbs_Point start, const nurbs_Point end)
{
    nurbs_Line *line = (nurbs_Line *)malloc(sizeof(nurbs_Line));
    if (line == NULL)
        return NULL;
    line->type = NURBS_GEOM_LINE;
    nurbs_Point points[2] = {start, end};
    line->nurbs_data = nurbs__makePolyline(points, 2);
    if (line->nurbs_data == NULL) {
        free(line);
        return NULL;
    }
    line->_start = start;
    line->_end = end;
    return line;
}

nurbs_Curve *nurbs_curve_reverse(const nurbs_Curve *curve)
{
    return NULL;
}

void nurbs_curve_domain(const nurbs_Curve *curve, double *min, double *max)
{
}

nurbs_Curve *nurbs_curve_transform(const nurbs_Curve *curve, nurbs_Matrix mat)
{
    return NULL;
}

nurbs_Point nurbs_curve_point(const nurbs_Curve *curve, double u)
{
    nurbs_Point p;
    return p;
}

nurbs_Vector nurbs_curve_tangent(const nurbs_Curve *curve, double u)
{
    nurbs_Vector p;
    return p;
}

int nurbs_curve_derivatives(const nurbs_Curve *curve, double u, int nderives,
                            nurbs_Vector **v, int *nv)
{
    return 0;
}

nurbs_Point nurbs_curve_closepoint(const nurbs_Curve *curve,
                                   const nurbs_Point point)
{
    nurbs_Point p;
    return p;
}

double nurbs_curve_closeparam(const nurbs_Curve *curve, const nurbs_Point point)
{
    return 0.0;
}

double nurbs_curve_length(const nurbs_Curve *curve)
{
    return 0.0;
}

double nurbs_curve_lengthAtParam(const nurbs_Curve *curve, double u)
{
    return 0.0;
}

double nurbs_curve_paramAtLength(const nurbs_Curve *curve, double len)
{
    return 0.0;
}

int nurbs_curve_divideByEqualArcLength(const nurbs_Curve *curve, int divisions,
                                       nurbs_CurveSample **samples, int *ns)
{
    return 0;
}

int nurbs_curve_divideByArcLength(const nurbs_Curve *curve, double arclength,
                                  nurbs_CurveSample **samples, int *ns)
{
    return 0;
}

int nurbs_curve_split(const nurbs_Curve *curve, double u, nurbs_Curve **curves,
                      int *nc)
{
    return 0;
}

int nurbs_curve_tessellate(const nurbs_Curve *curve, double tol,
                           nurbs_Point **points, int *np)
{
    return 0;
}
