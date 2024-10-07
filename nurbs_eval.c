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
#include <assert.h>
#include <stdlib.h>

void nurbs__evalHomogenize1d(nurbs_PointArray *pa, double *weights)
{
    assert(pa);
    assert(pa->points);

    if (weights == NULL) {
        weights = (double *)malloc(pa->npoints * sizeof(double));
        if (weights == NULL) {
            return;
        }
        for (size_t i = 0; i < pa->npoints; i++) {
            weights[i] = 1.0;
        }
    }

    for (size_t i = 0; i < pa->npoints; i++) {
        pa->points[i].x = pa->points[i].x * weights[i];
        pa->points[i].y = pa->points[i].y * weights[i];
        pa->points[i].z = pa->points[i].z * weights[i];
    }
    pa->weights = weights;
}