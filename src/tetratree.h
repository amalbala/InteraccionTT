
#ifndef _TETRATREE_H_
#define _TETRATREE_H_

#include <time.h>
#include "p3Df.h"
#include "geometry.h"
#include "intersection.h"
#include "inclussion.h"
#include "splittriangles.h"
#include "IOUtils.h"
#include "constants.h"


using namespace std;

//Opciones del WrapTethaedron
enum{FAREST_TRIAN, FAREST_POINT, AVERAGE_NORM};


///Tetracono
typedef struct{
        p3Df v1;
        p3Df v2;
        p3Df v3;
        vector<int> triangInc;    
		p3Df norm;
		int sign;
		double w;
		p3Df w1;
		p3Df c;
		p3Df b;
		p3Df a;
}tetracone;


///Nodo del tetratree
typedef struct node *nodeT;
typedef struct node{
        nodeT children;
        tetracone* tetrac;        
}nodeTT;



///Tetratree
typedef struct{
        nodeTT children[8];        
        p3Df centroid;
        mesh* mMeshTT;
		int ntet;	
}tetratree;

///Funcion para generar el tetratree
void generateTetraTree(unsigned int deep,unsigned int maxTri, tetratree* ttree, mesh *mMesh);
void generateTetraTreeInclussion(unsigned int deep,unsigned int maxTri, tetratree* ttree, mesh *mMesh);
void generateTetraTreeExt(unsigned int deep,unsigned int maxTri, tetratree* ttree, mesh *mMesh);
void eraseTetratree(tetratree *tt);

void visualization(nodeTT *tt,vector<triangle> malla,mesh* mallaori);
void saveTTMesh(tetratree *tt,mesh *malla);
void saveTTMesh(tetratree *tt);
void wrapTetraTree(tetratree *tt);

void saveSplitTriangleInfo(tetratree *tt);
int inclusionPointTT(p3Df p, tetratree *tt, int interType);


#endif