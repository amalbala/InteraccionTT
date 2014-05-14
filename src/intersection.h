
#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "p3Df.h"
#include "geometry.h"

using namespace std;

int intersect_Ray(p3Df r1, p3Df r2, trian T, float* alpha);
int intersect_RayTriangle(p3Df r1, p3Df r2, trian T, p3Df* I);
int SegmentTriangleIntersection(trian tri, p3Df l1, p3Df l2, p3Df *info, p3Df *inters);
int SegmentSegmentIntersection(p3Df p0, p3Df d0, p3Df p1, p3Df d1, p3Df *i);
int calculateIntersectionLinePlane(plane *p, p3Df *p1, p3Df *p2, p3Df *intersec);

#endif