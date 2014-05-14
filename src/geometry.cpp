
#include "geometry.h"
#include "constants.h"

//---------------------------------------------------------------------------
void calculatePlane(p3Df *p1, p3Df *p2, p3Df *p3,plane* pl){
	
	p3Df u,v;
	p3Df_resta((*p2),(*p1),(&u));
	p3Df_resta((*p3),(*p1), (&v));
	//printf("restas: ( %.2f,%.2f,%.2f) y ( %.2f,%.2f,%.2f)\n", u.x, u.y, u.z, v.x, v.y, v.z);
	
	pl->alpha = ((u.y * v.z)-(v.y * u.z));
	pl->beta = ((u.z * v.x)-(u.x *v.z));
	pl->gamma = ((u.x * v.y)-(v.x * u.y));
	pl->delta = ((v.y * u.z * p1->x) - (u.y * v.z * p1->x) + (u.x * v.z * p1->y) 
	    - (u.z * v.x * p1->y) + (v.x * u.y * p1->z) - (u.x * v.y * p1->z));
}

/*---------------------------------------------------------------------------*/
///Calculo de los signos de las coordenadas baricentricas
void signcoordBary(p3Df v0, p3Df v1, p3Df v2, p3Df v3, p3Df p,int den,signcoordB* scb){

if (den == 0) 
		scb->beta = scb->gamma = scb->delta = scb->alpha = NEG;
	else {
		scb->beta =   SIGNO(DET4D(v0,p,v2,v3));
		scb->gamma =  SIGNO(DET4D(v0,v1,p,v3));
		scb->delta =  SIGNO(DET4D(v0,v1,v2,p));
		scb->alpha =  SIGNO(DET4D(p,v1,v2,v3));      
		if(den == NEG){
			scb->beta *= -1;		
			scb->gamma *= -1;
			scb->delta *= -1;
			scb->alpha *= -1;
	   }
   }
} 
/*---------------------------------------------------------------------------*/
///Calculo de coordenadas baricentricas.
void coordBary(p3Df v0, p3Df v1, p3Df v2, p3Df v3, p3Df p, coordB* cb){
	 float den =  DET4D(v0,v1,v2,v3);
	
	if (den == 0) 
		cb->beta = cb->gamma = cb->delta = -1;
	else {
	
     cb->beta =  (DET4D(v0,p,v2,v3))/den;
     cb->gamma = (DET4D(v0,v1,p,v3))/den;
     cb->delta = (DET4D(v0,v1,v2,p))/den;
	 cb->alpha = 1.0 -(cb->delta + cb->gamma + cb->beta);      
	}
}
/*---------------------------------------------------------------------------*/
void boundingBox(mesh* m, p3Df *p1, p3Df *p2){
	//Calculo del centroide de la malla.
	p1->x = p1->y = p1->z = p2->x = p2->y = p2->z =0.0;
	
   for(unsigned int i=1; i<m->points.size(); i++){
	   if(m->points[i].x > p1->x) p1->x = m->points[i].x;
	   if(m->points[i].y > p1->y) p1->y = m->points[i].y;
	   if(m->points[i].z > p1->z) p1->z = m->points[i].z;
	   
	   if(m->points[i].x < p2->x) p2->x = m->points[i].x;
	   if(m->points[i].y < p2->y) p2->y = m->points[i].y;
	   if(m->points[i].z < p2->z) p2->z = m->points[i].z;
   }	
}
/*---------------------------------------------------------------------------*/
void removeMarkedTriangles(mesh *m,int flag){
	for(int n=0; n< m->faces.size(); n++){
				if(m->faces[n].itype == flag)
					m->faces.erase(m->faces.begin() + n);				
			}
}
/*---------------------------------------------------------------------------*/
int testDegenerateTriangle(trian t){

	double v1[3],v2[3],v3[3],s1[3],s2[3],pv[3];
	
	STORE(v1,t.v0);
	STORE(v2,t.v1);
	STORE(v3,t.v2);
	SUB(s1,v2,v1);
	SUB(s2,v3,v1);
	CROSS(pv,s1,s2);
	if((SIGNO(pv[0] == LIM)) &&(SIGNO(pv[1] == LIM)) &&(SIGNO(pv[2] == LIM)))
	    return 0;
   return 1;
	
}
