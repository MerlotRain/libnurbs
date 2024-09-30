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
#include <stdlib.h>
#include <string.h>

static inline int nurbs_array_alloc(nurbs_array_t *arr, size_t n);

int nurbs_array_init(nurbs_array_t *arr, array_free free, size_t size,
                     size_t nalloc)
{
    arr->elts = NULL;
    arr->size = size;
    arr->nalloc = nalloc;
    arr->nelts = 0;
    arr->free = free;
    return nurbs_array_alloc(arr, arr->nalloc);
}

nurbs_array_t *nurbs_array_new(array_free free, size_t size, size_t nalloc)
{
    nurbs_array_t *arr;

    if ((arr = (nurbs_array_t *)malloc(sizeof(nurbs_array_t))) == NULL)
        return NULL;

    if (nurbs_array_init(arr, free, size, nalloc) < 0) {
        free(arr);
        return NULL;
    }
    return arr;
}

void nurbs_array_destroy(nurbs_array_t *arr)
{
    if (arr == NULL)
        return;

    if (arr->free != NULL && arr->nelts) {
        uint8_t p = arr->elts, pend = arr->elts + (arr->nelts * arr->size);
        for (; p < pend; p += arr->size)
            arr->free(p);
    }

    free(arr->elts);
}

void nurbs_array_free(nurbs_array_t *arr)
{
    if (arr == NULL)
        return;

    if (arr->free != NULL && arr->nelts) {
        uint8_t p = arr->elts, pend = arr->elts + (arr->nelts * arr->size);
        for (; p < pend; p += arr->size)
            arr->free(p);
    }

    free(arr->elts);
    free(arr);
}

void nurbs_array_reset(nurbs_array_t *arr)
{
    if (arr == NULL)
        return;

    if (arr->free != NULL && arr->nelts) {
        uint8_t p = arr->elts, pend = arr->elts + (arr->nelts * arr->size);
        for (; p < pend; p += arr->size)
            arr->free(p);
    }
    arr->nelts = 0;
}

void *nurbs_array_push(nurbs_array_t *arr)
{
    if (arr->nelts >= arr->nalloc) {
        if (nurbs_array_alloc(arr, 1) < 0)
            return NULL;
    }
    return arr->elts + (arr->nelts++) * arr->size;
}

void *nurbs_array_pushn(nurbs_array_t *arr, size_t n)
{
    uint8_t ptr;

    if (arr->nelts + n > arr->nalloc) {
        if (nurbs_array_alloc(arr, n) < 0)
            return NULL;
    }
    ptr = arr->elts + arr->nelts * arr->size;
    arr->nelts += n;
    return ptr;
}

void nurbs_array_pop(nurbs_array_t *arr)
{
    if (arr == NULL || !arr->nelts)
        return;

    if (arr->free != NULL)
        arr->free(arr->elts + (arr->nelts - 1) * arr->size);
    --arr->nelts;
}

inline int nurbs_array_alloc(nurbs_array_t *arr, size_t n)
{
    uint8_t ptr;
    size_t num = arr->nalloc;
    while (n + arr->nelts > num) {
        num <<= 1;
    }
    ptr = malloc(num * arr->size);

    if (ptr == NULL)
        return -1;

    memcpy(ptr, arr->elts, arr->nelts * arr->size);
    free(arr->elts);
    arr->elts = ptr;
    arr->nalloc = num;

    return 0;
}
