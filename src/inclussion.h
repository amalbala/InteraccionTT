
#ifndef _INCLUSSION_H_
#define _INCLUSSION_H_

#include "p3Df.h"
#include "geometry.h"
#include "intersection.h"

using namespace std;

int jimenezOpt(p3Df * q1, p3Df * q2,trian_ext *tt, float *alpha);
int jimenezOptmin(p3Df * q1, p3Df * q2,trian_ext *tt, float *alpha);
int jimenezOptNew(p3Df * q1, p3Df * q2,trian_ext *tt,p3Df a,p3Df b,p3Df c, p3Df w1, float w, float *alpha);
int inclusionPoint(p3Df p, mesh* m, int interType);
int JordanCurve(p3Df p, mesh* m, int interType);
int Feito(p3Df p,mesh* m);


#endif