#ifndef _SPLITTING_TRIANGLES_H
#define _SPLITTING_TRIANGLES_H

#include "p3Df.h"
#include "geometry.h"

using namespace std;

int sortPointsSide(int *p1, int *p2, int ptoinilado, mesh * malla);
int splitpattern_case11(int id_t, mesh *m, p3Df inters1,p3Df inters2,p3Df inters3,p3Df inters4, int ladodoble, vector<int> *newtottc);
int splitpattern_case7(int id_t, mesh *m, p3Df inters1,p3Df inters2, p3Df inters3,p3Df inters4, int lado1, int lado2, vector<int> *newtottc);
int splitpattern_case8(int id_t, mesh *m, p3Df inters1,p3Df inters2, p3Df ptointTT, int ptoint, vector<int> *newtottc);
int splitpattern_case5(int id_t, mesh *m, p3Df pto_int1,p3Df pto_int2,p3Df pto_int3,p3Df pto_int4,p3Df pto_int5,p3Df pto_int6,int lado,vector<int> *newtottc);
int splitpattern_case4(int id_t, mesh *m, p3Df inters1,p3Df inters2, int lado1, int lado2, vector<int> *newtottc);
int splitpattern_case3(int id_t, mesh *m, p3Df inters1,p3Df inters2, int lado1, int lado2, vector<int> *newtottc);
int splitpattern_case2(int id_t, mesh *m, p3Df inters1,p3Df inters2, int lado1, vector<int> *newtottc);
int splitpattern_case1(int id_t, mesh *m, p3Df pto_int, p3Df inters1,p3Df inters2, int lado, vector<int> *newtottc);

#endif