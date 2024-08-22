#ifndef TC_H
#define TC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _tcSHAPETYPE{
    Point,
    Line,
    Arc,
    Circle,
    Ellipse,
    Polyline,
    Spline,
    Triangle,
    XLine,
    Ray
} tcSHAPETYPE;


typedef struct _tcPOINT {
    double x;
    double y;
} tcPOINT;

typedef struct _tcARC {
    tcPOINT center;
    double radius;
    double begin_angle;
    double end_angle;
} tcARC;

typedef struct _tcCIRCLE {
    tcPOINT center;
    double radius;
}tcCIRCLE;

typedef struct _tcELLIPSE {
    tcPOINT center;
    tcPOINT major;
    double ratio;
} tcELLIPSE;

typedef struct _tcELLIPTICALARC {
    tcPOINT center;
    tcPOINT major;
    double ratio;
    double begin_angle;
    double end_angle;
} tcELLIPTICALARC;

typedef struct _tcLINE {
    tcPOINT begin;
    tcPOINT end;
} tcLINE;

typedef struct _tcRAY {
    tcPOINT base;
    tcPOINT direction;
} tcRAY, tcXLINE;

typedef struct _tcPOLYLINE {
    int pn;
    double *bulge;
    tcPOINT *points;
};

typedef struct _tcSPLINE {
    int pn;
} tcSPLINE;

void tc_tolerance(double tol);

bool tc_intersects(void* s1, void* s2, int *t);

bool tc_intersection(void* s1, void* s2, int *t, _tcPOINT** p, int* pn);

double tc_length(void* s, int t);

bool tc_order(void** s, int* t, int n);

void tc_trim();

void tc_round_corners();

void tc_round_shapes();

#ifdef __cplusplus
}
#endif

#endif