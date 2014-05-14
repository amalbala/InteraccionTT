
#include "inclussion.h"
#include "constants.h"

/*---------------------------------------------------------------------------*/
// Totalmente robusto, calcula la intersección cuando w=0 o s=0, si los dos son 0 sale.

int jimenezOpt(p3Df * q1, p3Df * q2,trian_ext *tt, float *alpha) {
	/*printf("Punto1: %.2f,%.2f,%.2f, Punto2: %.2f,%.2f,%.2f Triangulo ((%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f))\n",
	    q1->x,q1->y,q1->z,q2->x,q2->y,q2->z,
	    tt->v0.x,tt->v0.y,tt->v0.z,
	    tt->v1.x,tt->v1.y,tt->v1.z,
	    tt->v2.x,tt->v2.y,tt->v2.z);
	*/
	double Q1[3],Q2[3],V1[3],V2[3],V3[3];
	STORE(Q1,*q1);
	STORE(Q2,*q2);
	STORE(V1,tt->v0);
	STORE(V2,tt->v1);
	STORE(V3,tt->v2);
	double A[3],B[3],W1[3],C[3],D[3],W2[3];//double E[3],F[3],G[3];
	
	SUB(A,Q1,V3);
	SUB(B,V1,V3);
	SUB(C,V2,V3);
	CROSS(W1,B,C);
	double w = DOT2(A,W1);
	tt->w = w;

	SUB(D,Q2,V3);
	double s = DOT2(D,W1);
		tt->s = s;
	// La siguiente comparación puede llevarse al final.
	//if ( w>-EPSILON && w<EPSILON && s>-EPSILON && s<EPSILON) return 0; //segmento coplanario
	double t,u;
	//printf("W: %.4f\n",w);
	if ( w > EPSILON ) {
		
		if ( s > EPSILON ) return 1;
		CROSS(W2,A,D);
		t = DOT2(W2,C);
		if ( t < -EPSILON ) return 2;
		u = -DOT2(W2,B);	
		if ( u < -EPSILON ) return 3;		
		if ( w < s+t+u ) return 4;
	} else if ( w<-EPSILON ) {
		
		if ( s < -EPSILON ) return 1;
		CROSS(W2,A,D);
		t = DOT2(W2,C);
		if ( t > EPSILON ) return 2;
		u = -DOT2(W2,B);
		if ( u > EPSILON ) return 3;
		if ( w > s+t+u ) return 4;
	} else { // w=0, intercambio de Q1 y Q2
		if ( s > EPSILON ) {
			
			CROSS(W2,D,A);
			t = DOT2(W2,C);
			if ( t < -EPSILON ) return 2;
			u = -DOT2(W2,B);
			if ( u < -EPSILON ) return 3;
			if ( s < t+u ) return 4; // s < w+t+u, pero w=0
		} else if ( s < -EPSILON ) {
			
			CROSS(W2,D,A);
			t = DOT2(W2,C);
			if ( t > EPSILON ) return 2;
			u = -DOT2(W2,B);
			if ( u > EPSILON ) return 3;
			if ( s > t+u ) return 4; // s > w+t+u, pero w=0
		} else return 0; //segmento coplanario con el triangulo
	}// else if (s>-EPSILON && s<EPSILON) return 0;
	//if ( w>-EPSILON && w<EPSILON && s>-EPSILON && s<EPSILON) return 0; //segmento coplanario

	double t_param = 1.0 / (w - s); //en realidad t_param = w / (w - s);
	double alfa, beta;
	alfa = t_param * t;
	(*alpha) = alfa;
	beta = t_param * u;
	//double gamma=1-alfa-beta; gamma=t_param*(w-t-u-s);
	return 5;
}

/*---------------------------------------------------------------------------*/
int jimenezOptmin(p3Df * q1, p3Df * q2,trian_ext *tt, float *alpha) {
	double Q1[3],Q2[3],V1[3],V2[3],V3[3];
	STORE(Q1,*q1);
	STORE(Q2,*q2);
	STORE(V1,tt->v0);
	STORE(V2,tt->v1);
	STORE(V3,tt->v2);
	double A[3],B[3],W1[3],C[3],D[3],W2[3];//double E[3],F[3],G[3];
	
	SUB(A,Q1,V3);
	SUB(B,V1,V3);
	SUB(C,V2,V3);
	CROSS(W1,B,C);
	double w = DOT2(A,W1);
	SUB(D,Q2,V3);
	double s = DOT2(D,W1);
	tt->w = w;
	tt->s = s;
	double t_param = w / (w-s); //en realidad t_param = w / (w - s);
	*alpha = t_param;
	return 5;
}
/*---------------------------------------------------------------------------*/
int jimenezOptNew(p3Df * q1, p3Df * q2,trian_ext *tt,p3Df a,p3Df b,p3Df c, p3Df w1,float w, float *alpha) {
	double Q2[3],V3[3],B[3],C[3],W1[3];
	STORE(Q2,*q2);
	STORE(W1,w1);
	double A[3],D[3],W2[3];//double E[3],F[3],G[3];	
	STORE(V3,tt->v2);
	SUB(D,Q2,V3);
	double s = DOT2(D,W1);
	// La siguiente comparación puede llevarse al final.
	//if ( w>-EPSILON && w<EPSILON && s>-EPSILON && s<EPSILON) return 0; //segmento coplanario
	double t,u;
	//printf("W: %.4f\n",w);
	if ( w > EPSILON ) {		
		if ( s > EPSILON ) return 1;
		STORE(A,a);	
		CROSS(W2,A,D);
		STORE(C,c);
		t = DOT2(W2,C);
		if ( t < -EPSILON ) return 2;
		STORE(B,b);
		u = -DOT2(W2,B);	
		if ( u < -EPSILON ) return 3;		
		if ( w < s+t+u ) return 4;
	} else if ( w<-EPSILON ) {
		
		if ( s < -EPSILON ) return 1;
		STORE(A,a);	
		CROSS(W2,A,D);
		STORE(C,c);
		t = DOT2(W2,C);
		if ( t > EPSILON ) return 2;
		STORE(B,b);
		u = -DOT2(W2,B);
		if ( u > EPSILON ) return 3;
		if ( w > s+t+u ) return 4;
	} else { // w=0, intercambio de Q1 y Q2
		if ( s > EPSILON ) {
			STORE(A,a);	
			CROSS(W2,D,A);
			STORE(C,c);
			t = DOT2(W2,C);
			if ( t < -EPSILON ) return 2;
			STORE(B,b);
			u = -DOT2(W2,B);
			if ( u < -EPSILON ) return 3;
			if ( s < t+u ) return 4; // s < w+t+u, pero w=0
		} else if ( s < -EPSILON ) {
			STORE(A,a);	
			CROSS(W2,D,A);
			STORE(C,c);
			t = DOT2(W2,C);
			if ( t > EPSILON ) return 2;
			STORE(B,b);
			u = -DOT2(W2,B);
			if ( u > EPSILON ) return 3;
			if ( s > t+u ) return 4; // s > w+t+u, pero w=0
		} else return 0; //segmento coplanario con el triangulo
	}// else if (s>-EPSILON && s<EPSILON) return 0;
	//if ( w>-EPSILON && w<EPSILON && s>-EPSILON && s<EPSILON) return 0; //segmento coplanario

	double t_param = 1.0 / (w - s); //en realidad t_param = w / (w - s);
	double alfa, beta;
	alfa = t_param * t;
	(*alpha) = alfa;
	beta = t_param * u;
	tt->s = s;
	//double gamma=1-alfa-beta; gamma=t_param*(w-t-u-s);
	return 5;
}
/*---------------------------------------------------------------------------*/
int nearestIntersectingTriangleMoeller(p3Df p, p3Df centroid,mesh* m, int *idTrian){

	int nearestTriangle;
	float alpha, mAlpha = 1;
	p3Df ray;
	trian orig;
	int i = -1;
	*idTrian = -1;
	//Estudio el triangulo mas cercano
	p3Df_resta(p,centroid, &ray);
	for(i=0; i < m->faces.size(); i++){
		orig.v0 = m->points[m->faces[i].v0];
		orig.v1 = m->points[m->faces[i].v1];
		orig.v2 = m->points[m->faces[i].v2];
		orig.norm = m->faces[i].norm;
		orig.id = i;
		if(intersect_Ray(p, centroid, orig, &alpha ) == 1){
			if(mAlpha > alpha){
				mAlpha = alpha;
				*idTrian = i;			
			}
		}
	}

	//Si no hay triangulos estoy dentro... realmente estoy donde esté el centroide
	if(*idTrian == -1) return INSIDE;
	if(SIGNO(PRODESCN(ray,m->faces[*idTrian].norm)) == POS) return INSIDE;
	return OUTSIDE;	
}
/*---------------------------------------------------------------------------*/
int nearestIntersectingTriangleJim(p3Df p, p3Df centroid,mesh* m, int *idTrian){

	
	int nearestTriangle;
	float alpha, mAlpha = 1;
	trian_ext orig, near;
	vector<trian_ext> vt;
	int i = -1;
	*idTrian = -1;
	//Estudio el triangulo mas cercano
	for(i=0; i < m->faces.size(); i++){
		orig.v0 = m->points[m->faces[i].v0];
		orig.v1 = m->points[m->faces[i].v1];
		orig.v2 = m->points[m->faces[i].v2];
		orig.norm = m->faces[i].norm;
		orig.id = i;
		
		//printf("Hola\n");
		int res = jimenezOpt(&centroid,&p,&orig,&alpha);
		if (res == 5){	
			vt.push_back(orig);
			if((mAlpha > alpha) && (alpha > EPSILON)){
				//printf("Aqui, %.8f\n",alpha);
				mAlpha = alpha;
				near = orig;			
			}
		}
	}
	//printf("el triangulo más cercano es: %d con alpha: %f\n",(*idTrian),mAlpha);
	//si no hay triangulos estoy dentro...
	if(mAlpha == 1) return INSIDE;
	//printf("No esta totalmente dentro\n");
	if(near.w > 0) return OUTSIDE;
		//si el volumen negativo esta dentro
		return INSIDE;
		
		
/*	//Estudio si intersecta
	int intc = jimenezOpt(&centroid,&p,&(vt[*idTrian]));
	if(intc == 5){
		//si el volumen positivo esta fuera
		if(vt[*idTrian].w > 0) return OUTSIDE;
		//si el volumen negativo esta dentro
		return INSIDE;
	}else{
		//borro el triangulo ya estudiado
		vt.erase(vt.begin() + (*idTrian));
		*idTrian = -1;
		for(i=0; i <vt.size(); i++){
			orig.v0 = m->points[m->faces[vt[i].id].v0];
			orig.v1 = m->points[m->faces[vt[i].id].v1];
			orig.v2 = m->points[m->faces[vt[i].id].v2];
			orig.norm = m->faces[vt[i].id].norm;
			//if(intersect_RayTriangle(p, centroid, orig, &alpha ) == 1){
			jimenezOptmin(&centroid,&p,&orig,&alpha);
			vt.push_back(orig);
			if((mAlpha > alpha)&&(alpha > 0.0)){
				mAlpha = alpha;
				*idTrian = i;
				}
			}
		}
		//si no hay triangulos estoy dentro...
	if(*idTrian == -1) return INSIDE;
	//Estudio si intersecta
	if(jimenezOpt(&centroid,&p,&(vt[*idTrian])) == 5){
		//si el volumen positivo esta fuera
		if(vt[*idTrian].w > 0) return OUTSIDE;
		//si el volumen negativo esta dentro
		return INSIDE;
	}	
	*/
}
/*---------------------------------------------------------------------------*/
int inclusionPoint(p3Df p, mesh* m, int interType){

	p3Df centr;
	
	centr.x = centr.y = centr.z = 0.0;
	for(unsigned int n=1; n<m->points.size(); n++){
           centr.x += m->points[n].x;           
           centr.y += m->points[n].y;           
           centr.z += m->points[n].z;
           
   }
	centr.x /= m->points.size();
   	centr.y /= m->points.size();
   	centr.z /= m->points.size();  
	int idT,res;
	if(interType == MOLLER)
		res = nearestIntersectingTriangleMoeller(p,centr,m,&idT);
	if(interType == JIMENEZ)
		
		res = nearestIntersectingTriangleJim(p,centr,m,&idT);
	
	/*
			switch(res){
				case INSIDE: 
					printf("Esta DENTRO del sólido, triangulo: %d\n",idTrian);
					break;
				case OUTSIDE: 
					printf("Esta FUERA del sólido, triangulo: %d\n",idTrian);
					break;
		
			}
			*/
	
}

/*---------------------------------------------------------------------------*/
int JordanCurve(p3Df p, mesh* m, int interType){

	p3Df centr;
	trian orig;
	centr.x = centr.y = centr.z = 0.0;
	for(unsigned int n=1; n<m->points.size(); n++){
           centr.x += m->points[n].x;           
           centr.y += m->points[n].y;           
           centr.z += m->points[n].z;
           
   }
	centr.x /= m->points.size();
   	centr.y /= m->points.size();
   	centr.z /= m->points.size();  
	int idT,res;
	int ncross=0;
	float alfa;

	
	
	
	if(interType == MOLLER){
		for(int n = 0; n<m->faces.size(); n++){		
			orig.v0 = m->points[m->faces[n].v0];
			orig.v1 = m->points[m->faces[n].v1];
			orig.v2 = m->points[m->faces[n].v2];
			orig.norm = m->faces[n].norm;
			orig.id = n;
			if(intersect_Ray(p, centr, orig, &alfa)==1) ncross++;
		}
	}
	if ((ncross%2)==0) return INSIDE;
	return OUTSIDE;			
	
	/*
			switch(res){
				case INSIDE: 
					printf("Esta DENTRO del sólido, triangulo: %d\n",idTrian);
					break;
				case OUTSIDE: 
					printf("Esta FUERA del sólido, triangulo: %d\n",idTrian);
					break;
		
			}
			*/
	
}
/*---------------------------------------------------------------------------*/
int Feito(p3Df p,mesh* m){

	int sig=0;
	p3Df ori, a,b,c;
	ori.x = ori.y = ori.z = 0.0;

	
	
	for(int n = 0; n<m->faces.size(); n++){		
			a = m->points[m->faces[n].v0];
			b = m->points[m->faces[n].v1];
			c = m->points[m->faces[n].v2];
			sig += SIGNO(DET3D(a,b,p));
			if(sig>1)sig = 1;
			if(sig<-1)sig = -1;
			sig += -SIGNO(DET3D(a,c,p));
			if(sig>1)sig = 1;
			if(sig<-1)sig = -1;
			sig += SIGNO(DET3D(b,c,p));
			if(sig>1)sig = 1;
			if(sig<-1)sig = -1;

	}
	if(sig == 1)return INSIDE;
	return(OUTSIDE);
}
/*---------------------------------------------------------------------------*/