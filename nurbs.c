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

void nurbs_free(nurbs_Curve* curve);

nurbs_Curve* nurbs_new_curve_withKCW(uint8_t degree, const nurbs_Point* cv, uint32_t ncv, double* knots, uint32_t nknots, double* weights, uint32_t nweights)
{
    return NULL;
}

nurbs_Curve* nurbs_new_curve_withP(const nurbs_Point* cv, uint32_t ncv, uint8_t degree)
{
    return NULL;
}

nurbs_Arc* nurbs_new_arc(const nurbs_Point center, const nurbs_Vector xaxis, const nurbs_Vector yaxis, double radius, double minAngle, double maxAngle)
{
    nurbs_Arc* arc = (nurbs_Arc*) malloc(sizeof(nurbs_Arc));
    if(arc == NULL)
        return NULL;
    
    arc->type = NURBS_GEOM_ARC;
    arc->_center = center;
    arc->_xaxis = xaxis;
    arc->_yaxis = yaxis;
    arc->_radius = radius;
    arc->_minAngle = minAngle;
    arc->_maxAngle = maxAngle;
    return arc;
}

nurbs_BezierCurve* nurbs_new_bezier(const nurbs_Point* points, uint32_t npoints, double* weights, int nw)
{
    return NULL;
}

nurbs_Circle* nurbs_new_circle(const nurbs_Point center, const nurbs_Vector xaxis, const nurbs_Vector yaxis, double radius)
{
    return NULL;
}

nurbs_EllipseArc* nurbs_new_ellipsearc(const nurbs_Point center, const nurbs_Vector xaxis, const nurbs_Vector yaxis, double minAngle, double maxAngle)
{
    return NULL;
}

nurbs_Ellipse* nurbs_new_ellipse(const nurbs_Point center, const nurbs_Vector xaxis, const nurbs_Vector yaxis)
{
    return NULL;
}

nurbs_Line* nurbs_new_line(const nurbs_Point start, const nurbs_Point end)
{
    return NULL;
}

void nurbs_curve_reverse(nurbs_Curve* curve)
{
}

void nurbs_curve_domain(const nurbs_Curve* curve, double* min, double* max)
{
}

void nurbs_curve_transform(nurbs_Curve* curve, void* mat)
{
}

nurbs_Point nurbs_curve_point(const nurbs_Curve* curve, double u)
{
    return nurbs_Point();
}

nurbs_Vector nurbs_curve_tangent(const nurbs_Curve* curve, double u)
{
    return nurbs_Vector();
}

int nurbs_curve_derivatives(const nurbs_Curve* curve, double u, int nderives, nurbs_Vector** v, int *nv)
{
    return 0;
}

nurbs_Point nurbs_curve_closepoint(const nurbs_Curve* curve, const nurbs_Point point)
{
    return nurbs_Point();
}

double nurbs_curve_closeparam(const nurbs_Curve* curve, const nurbs_Point point)
{
    return 0.0;
}

double nurbs_curve_length(const nurbs_Curve* curve)
{
    return 0.0;
}

double nurbs_curve_lengthAtParam(const nurbs_Curve* curve, double u)
{
    return 0.0;
}

double nurbs_curve_paramAtLength(const nurbs_Curve* curve, double len)
{
    return 0.0;
}

int nurbs_curve_divideByEqualArcLength(const nurbs_Curve* curve, int divisions, nurbs_CurveSample** samples, int *ns)
{
    return 0;
}

int nurbs_curve_divideByArcLength(const nurbs_Curve* curve, double arclength, nurbs_CurveSample** samples, int *ns)
{
    return 0;
}

int nurbs_curve_split(const nurbs_Curve* curve, double u, nurbs_Curve** curves, int *nc)
{
    return 0;
}

int nurbs_curve_tessellate(const nurbs_Curve* curve, double tol, nurbs_Point** points, int *np)
{
    return 0;
}
