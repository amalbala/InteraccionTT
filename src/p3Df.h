
#ifndef _P3DF_
#define _P3DF_


#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

using namespace std;

#define VECMOD(p1) (sqrt((p1.x * p1.x)+(p1.y * p1.y)+(p1.z * p1.z)))
#define LONGSEG(p1,p2) (sqrt(((p1.x-p2.x) * (p1.x-p2.x))+((p1.y-p2.y) * (p1.y-p2.y))+((p1.z-p2.z) * (p1.z-p2.z))))
#define PRODESC(p1, p2, c) ((((p1.x - c.x)* (p2.x - c.x))+((p1.y - c.y)*(p2.y - c.y))+((p1.z - c.z) + (p2.z - c.z)))\
							/(sqrt(((p1.x-c.x) * (p1.x-c.x))+((p1.y-c.y) * (p1.y-c.y))+((p1.z-c.z) * (p1.z-c.z)))))
#define PRODESCN(p1,p2)((p1.x * p2.x)+(p1.y*p2.y)+(p1.z*p2.z))
#define PROYECTION(p1,p2,c) ((((p1.x-c.x)*(p2.x-c.x))+((p1.y-c.y)*(p2.y-c.y))+((p1.z-c.z)*(p2.z-c.z)))\
							/(sqrt(((p2.x-c.x) * (p2.x-c.x))+((p2.y-c.y) * (p2.y-c.y))+((p2.z-c.z) * (p2.z-c.z)))))

#define ANGLEV(p1,p2,c) ( (((p1.x-c.x)*(p2.x-c.x))+((p1.y-c.y)*(p2.y-c.y))+((p1.z-c.z)*(p2.z-c.z)))\
							/(sqrt(((p2.x-c.x)*(p2.x-c.x))+((p2.y-c.y)*(p2.y-c.y))+((p2.z-c.z)*(p2.z-c.z)))*\
							 (sqrt(((p1.x-c.x)*(p1.x-c.x))+((p1.y-c.y)*(p1.y-c.y))+((p1.z-c.z)*(p1.z-c.z))))))
#define ANGLE(p1,p2) ( ((p1.x * p2.x) + (p1.y * p2.y) +(p1.z * p2.z))/(VECMOD(p1) * VECMOD(p2)))

#define INTERSECTION_PLANE_SEG(s1,ds,pn,pp,d) (-(pn.x * s1.x + pn.y * s1.y + pn.z * s1.z + d) / (pn.x * ds.x + pn.y * ds.y + pn.z * ds.z))

#define p3Df_suma(p1,p2,r) (r)->x = (p1).x + (p2).x;(r)->y = (p1).y + (p2).y;(r)->z = (p1).z + (p2).z;     

#define p3Df_resta(p1,p2,r) (r)->x = (p1).x - (p2).x;(r)->y = (p1).y - (p2).y;(r)->z = (p1).z - (p2).z;

#define p3Df_prod(p1,f,r) (r)->x = (p1).x * f;(r)->y = (p1).y * f;(r)->z = (p1).z * f;

#define p3Df_div(p1,f,r) (r)->x = (p1).x / f;(r)->y = (p1).y / f;(r)->z = (p1).z / f;

#define p3Df_set(p1,r) (r)->x = (p1).x;(r)->y = (p1).y;(r)->z = (p1).z;



#define p3Df_sete(r,a,b,c) (r)->x = a;(r)->y = b;(r)->z = c;

#define p3Df_norm(v1,v2,res) (res)->x = ((v1).y * (v2).z) - ((v1).z * (v2).y); (res)->y = -(((v1).x * (v2).z) - ((v1).z * (v2).x));(res)->z = ((v1).x * (v2).y) - ((v1).y * (v2).x);

#define p3Df_norm2(v1,v2,v3,res) (res)->x = (((v2).y - (v1).y) * ((v3).z - (v1).z)) - (((v2).z - (v1).z) * ((v3).y - (v1).y));\
(res)->y = -((((v2).x - (v1).x) * ((v3).z - (v1).z)) - (((v2).z - (v1).z) * ((v3).x - (v1).x)));\
(res)->z = (((v2).x - (v1).x) * ((v3).y - (v1).y)) - (((v2).y - (v1).y) * ((v3).x - (v1).x));

#define p3Df_cross(v1,v2,res) (res)->x = ((v1).y * (v2).z) - ((v2).y*(v1).z); (res)->y = ((v1).z*(v2).x) - ((v2).z*(v1).x);(res)->z = ((v1).x*(v2).y) - ((v2).x*(v1).y);



///Punto 2D
/**
*/
typedef struct{
	float x; 
    float y;
} p2Df;

///Punto 3D

typedef struct{
	 float x; 
	 float y;
	 float z;
	 int flag;
} p3Df;


void p3Df_dist(float dist, p3Df* res, p3Df centro);
void p3Df_incentro(p3Df p1,p3Df p2,p3Df p3, p3Df *centro);
int p3Df_testnulo(p3Df p1);
int intersec3D_seg_plane(p3Df s1, p3Df s2, p3Df p, p3Df norm,p3Df* inter);
float p3Df_angulo(p3Df v1, p3Df v2);
int p3Df_equal(p3Df p1, p3Df p2);



#endif
