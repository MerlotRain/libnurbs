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

#ifndef NURBSAPI_H
#define NURBSAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nurbs.h"

/**
 * free nurbs curve
 * \p curve curve object
 */
void nurbs_free(nurbs_Curve *curve);

/**
 * construct a NurbsCurve by degree, knots, control points, weights
 * \p degree degree of curve
 * \p cv control vertex
 * \p ncv number of control vertex
 * \p knots nondecreasing knot values
 * \p nknots number of nondecreasing knot values
 * \p weights weights of control vertex
 * \p nweights number of weights
 * \return nurbs curve object
 */
nurbs_Curve *nurbs_new_curve_withKCW(uint8_t degree, const nurbs_Point *cv,
                                     uint32_t ncv, double *knots,
                                     uint32_t nknots, double *weights,
                                     uint32_t nweights);

/**
 * construct a NurbsCurve by interpolating a collection of points.  The
 * resultant curve will pass through all of the points.
 * \p cv control vertex
 * \p ncv number of control vertex
 * \p degree degree of curve
 * \return nurbs curve object
 */
nurbs_Curve *nurbs_new_curve_withP(const nurbs_Point *cv, uint32_t ncv,
                                   uint8_t degree);

/**
 * constructor for Arc
 * \p center Length center of the arc
 * \p xaxis xaxis
 * \p yaxis perpendicular yaxis
 * \p radius radius of the arc arc
 * \p minAngle start angle in radians
 * \p maxAngle end angle in radians
 * \return nurbs arc object
 */
nurbs_Arc *nurbs_new_arc(const nurbs_Point center, const nurbs_Vector xaxis,
                         const nurbs_Vector yaxis, double radius,
                         double minAngle, double maxAngle);

/**
 * create a bezier curve
 * \p points array of control points
 * \p npoints number of control points
 * \p weights array of control point weights (optional)
 * \p nw number of control point weights
 * \return nurbs bezier curve object
 */
nurbs_BezierCurve *nurbs_new_bezier(const nurbs_Point *points, uint32_t npoints,
                                    double *weights, int nw);

/**
 * create a circle
 * \p center center of the circle
 * \p xaxis the xaxis
 * \p yaxis the perpendicular yaxis
 * \p radius radius of the circle
 * \return nurbs circle object
 */
nurbs_Circle *nurbs_new_circle(const nurbs_Point center,
                               const nurbs_Vector xaxis,
                               const nurbs_Vector yaxis, double radius);

/**
 * create an EllipseArc
 * \p center the center of the arc
 * \p xaxis the xaxis
 * \p yaxis the perpendicular yaxis
 * \p minAngle minimum angle of the EllipseArc
 * \p maxAngle maximum angle of the EllipseArc
 * \return nurbs ellipse arc object
 */
nurbs_EllipseArc *nurbs_new_ellipsearc(const nurbs_Point center,
                                       const nurbs_Vector xaxis,
                                       const nurbs_Vector yaxis,
                                       double minAngle, double maxAngle);

/**
 * create an ellipse
 * \p center the center of the arc
 * \p xaxis the xaxis
 * \p yaxis the perpendicular yaxis
 * \return nurbs ellipse object
 */
nurbs_Ellipse *nurbs_new_ellipse(const nurbs_Point center,
                                 const nurbs_Vector xaxis,
                                 const nurbs_Vector yaxis);

/**
 * create a line
 * \p start the start point
 * \p end the end point
 * \return nurbs line object
 */
nurbs_Line *nurbs_new_line(const nurbs_Point start, const nurbs_Point end);

/**
 * everse the parameterization of the curve
 * \p curve origion curve
 * \return a reversed curve
 */
nurbs_Curve *nurbs_curve_reverse(const nurbs_Curve *curve);

/**
 * determine the valid domain of the curve
 * \p curve curve object
 * \p min domain min value
 * \p max domain max value
 */
void nurbs_curve_domain(const nurbs_Curve *curve, double *min, double *max);

/**
 * transform a curve with the given matrix.
 * \p curve origion curve
 * \p matrix 4x4 transformation matrix
 * \return
 */
nurbs_Curve *nurbs_curve_transform(const nurbs_Curve *curve,
                                   nurbs_Matrix matrix);

/**
 * sample a point at the given parameter
 * \p curve curve object
 * \p u parameter
 * \return
 */
nurbs_Point nurbs_curve_point(const nurbs_Curve *curve, double u);

/**
 * obtain the curve tangent at the given parameter.  This is the first
 * derivative and is not normalized
 * \p curve curve object
 * \p u parameter
 */
nurbs_Vector nurbs_curve_tangent(const nurbs_Curve *curve, double u);

/**
 * get derivatives at a given parameter
 * \param curve curve object
 * \param u parameter
 * \param nderives number of derivatives to obtain
 * \param v array of vectors to store the derivatives
 * \param nv number of vectors in the array
 */
int nurbs_curve_derivatives(const nurbs_Curve *curve, double u, int nderives,
                            nurbs_Vector **v, int *nv);
/**
 * determine the closest point on the curve to the given point
 * \p curve curve object
 * \p point point to find the closest point to
 * \return the closest point on the curve to the given point
 */
nurbs_Point nurbs_curve_closepoint(const nurbs_Curve *curve,
                                   const nurbs_Point point);

/**
 * determine the closest parameter on the curve to the given point
 * \p curve curve object
 * \p point point to find the closest parameter to
 * \return the closest parameter on the curve to the given point
 */
double nurbs_curve_closeparam(const nurbs_Curve *curve,
                              const nurbs_Point point);

/**
 * determine the length of the curve
 * \p curve curve object
 * \return the length of the curve
 */
double nurbs_curve_length(const nurbs_Curve *curve);

/**
 * determine the length of the curve at the given parameter
 * \p curve curve object
 * \p u parameter
 * \return the length of the curve at the given parameter
 */
double nurbs_curve_lengthAtParam(const nurbs_Curve *curve, double u);

/**
 * determine the parameter at the given length
 * \p curve curve object
 * \p len length
 * \return the parameter at the given length
 */
double nurbs_curve_paramAtLength(const nurbs_Curve *curve, double len);

/**
 * determine the parameters necessary to divide the curve into equal arc length
 * segments
 * \p curve curve object
 * \p divisions number of divisions
 * \p samples array of samples
 * \p ns number of samples
 * \return
 */
int nurbs_curve_divideByEqualArcLength(const nurbs_Curve *curve, int divisions,
                                       nurbs_CurveSample **samples, int *ns);

/**
 * given the distance to divide the curve, determine the parameters necessary to
 * divide the curve into equal arc length segments
 *
 * \p curve curve object
 * \p arclength arc length of each segment
 * \p samples array of samples
 * \p ns number of samples
 * \return
 */
int nurbs_curve_divideByArcLength(const nurbs_Curve *curve, double arclength,
                                  nurbs_CurveSample **samples, int *ns);

/**
 * split the curve at the given parameter
 * \p curve curve object
 * \p u parameter
 * \p curves array of curves
 * \p nc number of curves
 * \return
 */
int nurbs_curve_split(const nurbs_Curve *curve, double u, nurbs_Curve **curves,
                      int *nc);

/**
 * tessellate a curve at a given tolerance
 * \p curve curve object
 * \p tol tolerance
 * \p points array of points
 * \p np number of points
 * \return
 */
int nurbs_curve_tessellate(const nurbs_Curve *curve, double tol,
                           nurbs_Point **points, int *np);

#ifdef __cplusplus
}
#endif

#endif /* NURBSAPI_H */