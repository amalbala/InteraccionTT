#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "p3Df.h"


//Determina el Signo de un valor
#define SIGNO(x) \
	(((double) x<=EPSILON) ? (((double) x < -EPSILON) ? NEG : LIM) : POS)

//Determinante 3D
#define DET3D(p1,p2,p3) (((p1.x)*((p2.y)*(p3.z)-(p2.z)*(p3.y)) + \
   (p1.y)*((p2.z)*(p3.x)-(p2.x)*(p3.z))+(p1.z)*((p2.x)*(p3.y)-(p2.y)*(p3.x))))      

//Determinante 4D
#define DET4D(v0,v1,v2,v3) \
	((((v1.x - v0.x)*(v2.y - v0.y) - (v2.x - v0.x)*(v1.y - v0.y))*(v3.z - v0.z) +\
	((v1.y - v0.y)*(v3.x - v0.x) - (v3.y - v0.y)*(v1.x - v0.x))*(v2.z - v0.z) +\
	((v2.x - v0.x)*(v3.y - v0.y) - (v2.y - v0.y)*(v3.x - v0.x))*(v1.z - v0.z)))
	
//Distancia entre dos puntos
#define DIST3D(p1,p2) \
        (sqrt(((p1.x - p2.x) * (p1.x - p2.x))+((p1.y - p2.y) * (p1.y - p2.y))+((p1.z - p2.z) * (p1.z - p2.z))))

#define DISTPLANE(A,B,C,D,l1,l2) \
	(-(((A*l1.x) + (B*l1.y) + (C*l1.z) + D)/((A*l2.x) + (B*l2.y) +(C*l2.z)))) 

#define DOT(p1, p2) \
	((p1.x * p2.x)+(p1.y * p2.y)+(p1.z*p2.z))

#define STORE(dest,orig) dest[0]=(orig).x;dest[1]=(orig).y;dest[2]=(orig).z;
#define SUB(dest,ini,fin) dest[0]=ini[0]-fin[0];dest[1]=ini[1]-fin[1];dest[2]=ini[2]-fin[2];
#define ADD(dest,ini,fin) dest[0]=ini[0]+fin[0];dest[1]=ini[1]+fin[1];dest[2]=ini[2]+fin[2];
#define CROSS(dest,ini,fin) dest[0]=ini[1]*fin[2]-ini[2]*fin[1];dest[1]=ini[2]*fin[0]-ini[0]*fin[2];dest[2]=ini[0]*fin[1]-ini[1]*fin[0];
#define DOT2(ini,fin) (ini[0]*fin[0]+ini[1]*fin[1]+ini[2]*fin[2])



///Triangulo
typedef struct{
        float alpha;
        float beta;
        float gamma;
        float delta;
} coordB;

typedef struct{
        int alpha;
        int beta;
        int gamma;
        int delta;
} signcoordB;

typedef struct{
        p3Df v0;
        p3Df v1;
        p3Df v2;
        p3Df norm;			
		float w;
		float s;
		int id;
} trian_ext;


typedef struct{
        p3Df v0;
        p3Df v1;
        p3Df v2;
        p3Df norm;	
		int id;
} trian;

///Triangulo
typedef struct{
        int v0;
        int v1;
        int v2;
        p3Df norm;		
		int itype;
} triangle;

///Malla
typedef struct{
        vector<p3Df> points;
        vector<p3Df> normals;
        vector<p3Df> textures;
        vector<triangle> faces;
}mesh;


typedef coordB plane;

void calculatePlane(p3Df *p1, p3Df *p2, p3Df *p3,plane* pl);

void signcoordBary(p3Df v0, p3Df v1, p3Df v2, p3Df v3, p3Df p,int den,signcoordB* scb);
void coordBary(p3Df v0, p3Df v1, p3Df v2, p3Df v3, p3Df p, coordB* cb);
void boundingBox(mesh* m, p3Df *p1, p3Df *p2);
void removeMarkedTriangles(mesh *m,int flag);
int testDegenerateTriangle(trian t);

#endif