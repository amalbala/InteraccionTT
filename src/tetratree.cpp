
#include <math.h>
#include "tetratree.h"


int contador = 0;
float dist_old;
int nt;
int nt_raros, nt_completos,nt_studio = 0;
int ndeg=0;
int nt_studio_old=0;
int ptosint[7];
int nlimits;
vector<int> tritoerase;//Lista de triangulos a eliminar
//int index_max = 0;
int nnewtri=0; //Numero de nuevos triangulos generados
//int flag_nseg = 0;
int cases_used[11];
clock_t tiempo1i, tiempo2i;
			double tiempoi = 0.0;

void proyectionTTonTriangle(p3Df centroid, tetracone* tt, trian ori, trian *proy){

		plane pl;
	
		calculatePlane(&ori.v0,&ori.v1,&ori.v2,&pl);
	//printf("plano: %.4f x + %.4f y + %.4f z + %.4f \n",pl.alpha, pl.beta, pl.gamma,pl.delta);
	
		p3Df i1, i2, i3;
	//printf("TTori: [(%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f)]\n",tt->v1.x,tt->v1.y,tt->v1.z,tt->v2.x,tt->v2.y,tt->v2.z,tt->v3.x,tt->v3.y,tt->v3.z );
		if(calculateIntersectionLinePlane(&pl, &centroid, &(tt->v1),&(proy->v0))==1) nt_raros++; /*printf("Error1\n");*/
		if(calculateIntersectionLinePlane(&pl, &centroid, &(tt->v2),&(proy->v1))==1) nt_raros++; /*printf("Error2\n");*/
		if(calculateIntersectionLinePlane(&pl, &centroid, &(tt->v3),&(proy->v2))==1) nt_raros++; /*printf("Error3\n");*/
	//printf("\n");
		
	/**/
	/**/
}


void tetraPointLimits(signcoordB* scbary){
	if((scbary->beta ==  LIM) && ((scbary->gamma == LIM)||(scbary->gamma == POS))
	    && ((scbary->delta == LIM)||(scbary->delta == POS)))
			scbary->beta = POS;	    
	if((scbary->beta ==  LIM) && ((scbary->gamma == LIM)||(scbary->gamma == NEG))
	    && ((scbary->delta == LIM)||(scbary->delta == NEG)))
			scbary->beta = NEG;
	if(scbary->beta ==  LIM) scbary->beta = NEG;
	if((scbary->gamma ==  LIM) && ((scbary->beta == LIM)||(scbary->beta == POS))
	    && ((scbary->delta == LIM)||(scbary->delta == POS)))
			scbary->gamma = POS;	    
	if((scbary->gamma ==  LIM) && ((scbary->beta == LIM)||(scbary->beta == NEG))
	    && ((scbary->delta == LIM)||(scbary->delta == NEG)))
			scbary->gamma = NEG;
	if(scbary->gamma ==  LIM) scbary->gamma = NEG;
	if((scbary->delta ==  LIM) && ((scbary->beta == LIM)||(scbary->beta == POS))
	    && ((scbary->gamma == LIM)||(scbary->gamma == POS)))
			scbary->delta = POS;	    
	if((scbary->delta ==  LIM) && ((scbary->beta == LIM)||(scbary->beta == NEG))
	    && ((scbary->gamma == LIM)||(scbary->gamma == NEG)))
			scbary->delta = NEG;		
	if(scbary->delta ==  LIM) scbary->delta = NEG;
}
/*---------------------------------------------------------------------------*/
int tetraPoint(p3Df v0, p3Df v1, p3Df v2, p3Df v3, p3Df p,int signT){       
	//Calculamos los signos coordenadas baricentricas.
     signcoordB scbary;	
     signcoordBary(v0,v1,v2,v3,p,signT,&scbary);		
     //Estudiamos los signos para saber si el punto esta o no contenido en l tetracono.
	//Casos límite
	if((scbary.beta ==  LIM) || (scbary.gamma == LIM) || (scbary.delta == LIM)){		
		nlimits++;
		tetraPointLimits(&scbary);
	}

	
    if((scbary.beta ==  POS) && (scbary.gamma == POS) && (scbary.delta == POS)){
		if(scbary.alpha == POS){
			return COLIS;			
		}
	    return IN;
	}
	return OUT;	 
}
/*---------------------------------------------------------------------------*/
///Función para estudiar la inclusion de un punto en un tetracono.
int testTetraPointLimit(p3Df v0, p3Df v1, p3Df v2, p3Df v3, p3Df p){
	//Calculamos los signos coordenadas baricentricas
     signcoordB scbary;	
	 int den =  SIGNO(DET4D(v0,v1,v2,v3));
     signcoordBary(v0,v1,v2,v3,p,den,&scbary);		
	if((scbary.beta ==  LIM) || (scbary.gamma == LIM) || (scbary.delta == LIM))
		return 0;
	return 1;	 
}

/*---------------------------------------------------------------------------*/
///Función para estudiar la inclusion de un punto en un tetracono.
int tetraPoint(p3Df v0, p3Df v1, p3Df v2, p3Df v3, p3Df p){
	//Calculamos los signos coordenadas baricentricas
     signcoordB scbary;	
	 int den =  SIGNO(DET4D(v0,v1,v2,v3));
     signcoordBary(v0,v1,v2,v3,p,den,&scbary);		
	if((scbary.beta ==  LIM) || (scbary.gamma == LIM) || (scbary.delta == LIM))
		tetraPointLimits(&scbary);
     //Estudiamos los signos para saber si el punto esta o no contenido en l tetracono.
    if((scbary.beta ==  POS) && (scbary.gamma == POS) && (scbary.delta == POS))
		      return IN;	
	return OUT;	 
}
/*---------------------------------------------------------------------------*/
///Funcion para estudiar si un segmento  intersecta a un tetracono
int tetraSeg(p3Df v0, p3Df v1,p3Df v2, p3Df p1, p3Df p2){
    /*
    coordB cb;
    //Calculamos las coordenadas baricentricas de p2 con respecto al tetraedro P1-V0-V1-V2
	coordBary(p1,v0,v1,v2,p2,&cb);
    if((cb.alpha >0) || (cb.gamma < 0) || (cb.delta < 0))
                 return OUT;
    */
	signcoordB scb;
	int den =  SIGNO(DET4D(p1,v0,v1,v2));
	signcoordBary(p1,v0,v1,v2,p2,den,&scb);
	
	if((scb.alpha == POS) || (scb.gamma == NEG) || (scb.delta ==  NEG))	
                 return OUT;
	return IN;    
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
int nearestIntersectingTriangleMoeller(nodeTT* t,p3Df p, p3Df centroid,mesh* m, int *idTrian){

	int nearestTriangle;
	float alpha, mAlpha = 1;
	p3Df ray,inter;
	trian orig;
	int i = -1;
	*idTrian = -1;
	//Estudio el triangulo mas cercano
	p3Df_resta(p,centroid, &ray);
	for(i=0; i < t->tetrac->triangInc.size(); i++){
		orig.v0 = m->points[m->faces[t->tetrac->triangInc[i]].v0];
		orig.v1 = m->points[m->faces[t->tetrac->triangInc[i]].v1];
		orig.v2 = m->points[m->faces[t->tetrac->triangInc[i]].v2];
		orig.norm = m->faces[t->tetrac->triangInc[i]].norm;
		orig.id = t->tetrac->triangInc[i];
		//tiempo1i = clock();
		if(intersect_Ray(p, centroid, orig, &alpha ) == 1){
			if(mAlpha > alpha){
				mAlpha = alpha;
				*idTrian = i;			
			}
		}
	}

	//Si no hay triangulos estoy dentro... realmente estoy donde esté el centroide
	if(*idTrian == -1) return INSIDE;
	if(SIGNO(PRODESCN(ray,m->faces[*idTrian].norm)) == POS){
//		tiempo2i = clock();
//		printf("Tiempo Interno: %.8f\n",tiempoi);
		return INSIDE;
		
	}
//	tiempo2i = clock();
//	printf("Tiempo Interno: %.8f\n",tiempoi);
	return OUTSIDE;	
}

/*---------------------------------------------------------------------------*/
int nearestIntersectingTriangleJim(nodeTT* t,p3Df p, p3Df centroid,mesh* m, int *idTrian){

	
	int nearestTriangle;
	float alpha, mAlpha = 1;
	trian_ext orig,near;
	int i = -1;

	*idTrian = -1;
	//Estudio el triangulo mas cercano
	for(i=0; i < t->tetrac->triangInc.size(); i++){
		orig.v0 = m->points[m->faces[t->tetrac->triangInc[i]].v0];
		orig.v1 = m->points[m->faces[t->tetrac->triangInc[i]].v1];
		orig.v2 = m->points[m->faces[t->tetrac->triangInc[i]].v2];
		orig.norm = m->faces[t->tetrac->triangInc[i]].norm;
		orig.id = t->tetrac->triangInc[i];
		//if(intersect_RayTriangle(p, centroid, orig, &alpha ) == 1){
		/*printf("Punto1: %.2f,%.2f,%.2f, Punto2: %.2f,%.2f,%.2f Triangulo ((%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f))\n",
	    p.x,p.y,p.z,centroid.x,centroid.y,centroid.z,
	    orig.v0.x,orig.v0.y,orig.v0.z,
	    orig.v1.x,orig.v1.y,orig.v1.z,
	    orig.v2.x,orig.v2.y,orig.v2.z);
		 */
		//tiempo1i = clock();
		int res = jimenezOpt(&centroid,&p,&orig,&alpha);
		//tiempo2i = clock();
		//tiempoi +=(tiempo2i-tiempo1i)/(double)CLOCKS_PER_SEC; 
		if (res == 5){		
			if((mAlpha > alpha) && (alpha > EPSILON)){
				//printf("Aqui, %.8f\n",alpha);
				mAlpha = alpha;
				*idTrian = orig.id;
				near = orig;
			}
		}
	}
	//printf("Tiempo Interno: %.8f\n",tiempoi);
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
int nearestIntersectingTriangleJimNew(nodeTT* t,p3Df p, p3Df centroid,mesh* m, int *idTrian){

	
	int nearestTriangle;
	float alpha, mAlpha = 1;
	trian_ext orig, near;
	int i = -1;
	
	*idTrian = -1;
	//Estudio el triangulo mas cercano
	for(i=0; i < t->tetrac->triangInc.size(); i++){
		orig.v0 = m->points[m->faces[t->tetrac->triangInc[i]].v0];
		orig.v1 = m->points[m->faces[t->tetrac->triangInc[i]].v1];
		orig.v2 = m->points[m->faces[t->tetrac->triangInc[i]].v2];
		orig.norm = m->faces[t->tetrac->triangInc[i]].norm;
		orig.id = t->tetrac->triangInc[i];
		//if(intersect_RayTriangle(p, centroid, orig, &alpha ) == 1){
		/*printf("Punto1: %.2f,%.2f,%.2f, Punto2: %.2f,%.2f,%.2f Triangulo ((%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f))\n",
	    p.x,p.y,p.z,centroid.x,centroid.y,centroid.z,
	    orig.v0.x,orig.v0.y,orig.v0.z,
	    orig.v1.x,orig.v1.y,orig.v1.z,
	    orig.v2.x,orig.v2.y,orig.v2.z);
		 */		
		int res = jimenezOptNew(&centroid,&p,&orig,t->tetrac->b,t->tetrac->b,t->tetrac->c,t->tetrac->w1,t->tetrac->w,&alpha);
		if (res == 5){		
			if((mAlpha > alpha) && (alpha > EPSILON)){
				//printf("Aqui, %.8f\n",alpha);
				mAlpha = alpha;
				*idTrian = orig.id;
				near = orig;			
			}
		}
	}
	//printf("Tiempo Interno: %.8f\n",tiempoi);
	//printf("el triangulo más cercano es: %d con alpha: %f\n",(*idTrian),mAlpha);
	//si no hay triangulos estoy dentro...
	if(mAlpha == 1) return INSIDE;
	//printf("No esta totalmente dentro\n");
	if(near.w > 0) return OUTSIDE;
		//si el volumen negativo esta dentro
		return INSIDE;		
}

/*---------------------------------------------------------------------------*/
///Funcion para clasificar triangulos en el tetracono
void clasifyTriang(tetracone* ttc, int iTrian, mesh *mMesh, p3Df centroid){
	//Si es un traingulo virtualmente no existente
	if(mMesh->faces[iTrian].itype == -1 ) return;
	//Comparar vertices del triangulo con el tetracono
	//Utilizamos los signos de los tetraconos precalculados para acelerar cálculos.
	triangle vTrian;
	vTrian.v0 = mMesh->faces[iTrian].v0; 
  	vTrian.v1 = mMesh->faces[iTrian].v1; 
	vTrian.v2 = mMesh->faces[iTrian].v2; 
	//vTrian.itype = TOSTUDY;
	if(tetraPoint(centroid,ttc->v1, ttc->v2,ttc->v3,mMesh->points[vTrian.v0],ttc->sign)!=OUT){
		  ttc->triangInc.push_back(iTrian);
		  return;                     
    }
	vTrian.itype = TOSPLIT;
	if(tetraPoint(centroid,ttc->v1, ttc->v2,ttc->v3,mMesh->points[vTrian.v1],ttc->sign)!=OUT){
				  ttc->triangInc.push_back(iTrian);
		  return;                     
	}
	if(tetraPoint(centroid,ttc->v1, ttc->v2,ttc->v3,mMesh->points[vTrian.v2],ttc->sign)!=OUT){
			  ttc->triangInc.push_back(iTrian);
		  return;                     
	}

     //Comparar los vertices del tetracono con el triangulo
    if(tetraPoint(centroid,mMesh->points[vTrian.v0],mMesh->points[vTrian.v1],mMesh->points[vTrian.v2], ttc->v1)!=OUT){
				  ttc->triangInc.push_back(iTrian);
		  return;                     
	}             

 	if(tetraPoint(centroid,mMesh->points[vTrian.v0],mMesh->points[vTrian.v1],mMesh->points[vTrian.v2], ttc->v2)!=OUT){
		 		  ttc->triangInc.push_back(iTrian);
		  return;                     
    }
	if(tetraPoint(centroid,mMesh->points[vTrian.v0],mMesh->points[vTrian.v1],mMesh->points[vTrian.v2],ttc->v3)!=OUT){
				  ttc->triangInc.push_back(iTrian);
		  return;                     
	}
    //Comparar los segmentos del triangulo con el tetracono
    //Segmento v0-v1
     if (tetraSeg( centroid, ttc->v1, ttc->v2, mMesh->points[vTrian.v0],
        mMesh->points[vTrian.v1])== IN ) {
					  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	}
	if ( tetraSeg( centroid, ttc->v2, ttc->v3, mMesh->points[vTrian.v0], 
       mMesh->points[vTrian.v1]) == IN ) {
		   		  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	   }
	if ( tetraSeg( centroid, ttc->v3, ttc->v1, mMesh->points[vTrian.v0],
       mMesh->points[vTrian.v1]) == IN ) {
		   		  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	}
	
	//Segmento v1-v2
	
	if(tetraSeg( centroid, ttc->v1, ttc->v2, mMesh->points[vTrian.v1], 
       mMesh->points[vTrian.v2]) == IN ) {
		   		  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	}
	
	if(tetraSeg( centroid, ttc->v2, ttc->v3, mMesh->points[vTrian.v1],
       mMesh->points[vTrian.v2]) == IN ) {
		   		  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	}
	
	if(tetraSeg( centroid, ttc->v3, ttc->v1, mMesh->points[vTrian.v1], 
       mMesh->points[vTrian.v2]) == IN ) {
		   		  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	}        
	
	//Segmento v0  -v2
    
    if(tetraSeg( centroid, ttc->v1, ttc->v2, mMesh->points[vTrian.v0], 
       mMesh->points[vTrian.v2]) == IN ) {
		   		  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	}
	
	if(tetraSeg( centroid, ttc->v2, ttc->v3, mMesh->points[vTrian.v0],
       mMesh->points[vTrian.v2]) == IN ) {
		   		  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	}
	
	if(tetraSeg( centroid, ttc->v3, ttc->v1, mMesh->points[vTrian.v0], 
       mMesh->points[vTrian.v2]) == IN ) {
		   		  ttc->triangInc.push_back(iTrian);
			  return;                     
		
	}
	
}
/*---------------------------------------------------------------------------*/
//Funcion recursiva para generar el Tetratree
void generateTetraTree(unsigned int deep,unsigned int maxTri, vector<int> triang, nodeTT* tt, mesh *mMesh, p3Df centroid){
          //Clasificar triangulos.
			if(tt->tetrac->triangInc.size()!= 0) tt->tetrac->triangInc.clear();
		  	 for(unsigned int i = 0; i<triang.size(); i++)
	            clasifyTriang(tt->tetrac,triang[i],mMesh,centroid);			       
           	//criterio de parada			
           if(deep == 0 || tt->tetrac->triangInc.size() < maxTri) return;
            p3Df v12,v23,v31;
			
            
            //Nuevas coordenadas
            p3Df_suma(tt->tetrac->v1, tt->tetrac->v2,(&v12));
            p3Df_div(v12,2.0,(&v12));
            p3Df_suma(tt->tetrac->v3, tt->tetrac->v2,(&v23));
            p3Df_div(v23,2.0,(&v23));
            p3Df_suma(tt->tetrac->v1, tt->tetrac->v3,(&v31));
            p3Df_div(v31,2.0,(&v31));

			//Inicalizammos los hijos.
            tt->children = new nodeTT[4];
			nt+=3;
            
            for(int i=0; i<4; i++){
                     tt->children[i].children = NULL;
                     tt->children[i].tetrac = new (tetracone);
            }
                        
            //Primer hijo
            tt->children[0].tetrac = new tetracone;
            p3Df_set(tt->tetrac->v1,(&(tt->children[0].tetrac->v1)));
            p3Df_set(v12, (&(tt->children[0].tetrac->v2)));
            p3Df_set(v31, (&(tt->children[0].tetrac->v3)));
			tt->children[0].tetrac->sign = SIGNO(DET4D(centroid,tt->children[0].tetrac->v1,tt->children[0].tetrac->v2,tt->children[0].tetrac->v3));
            
            //Segundo hijo
            tt->children[1].tetrac = new tetracone;
            p3Df_set(v12,(&(tt->children[1].tetrac->v1)));
            p3Df_set(tt->tetrac->v2,(&(tt->children[1].tetrac->v2)));
            p3Df_set(v23,(&(tt->children[1].tetrac->v3)));
			tt->children[1].tetrac->sign = SIGNO(DET4D(centroid,tt->children[1].tetrac->v1,tt->children[1].tetrac->v2,tt->children[1].tetrac->v3));

            //Tercer hijo
            tt->children[2].tetrac = new tetracone;
            p3Df_set(v31,(&(tt->children[2].tetrac->v1)));
            p3Df_set(v23,(&(tt->children[2].tetrac->v2)));
            p3Df_set(tt->tetrac->v3,(&(tt->children[2].tetrac->v3)));
            tt->children[2].tetrac->sign = SIGNO(DET4D(centroid,tt->children[2].tetrac->v1,tt->children[2].tetrac->v2,tt->children[2].tetrac->v3));
            //Cuarto hijo
            tt->children[3].tetrac = new tetracone;
            p3Df_set(v12,(&(tt->children[3].tetrac->v1)));
            p3Df_set(v23,(&(tt->children[3].tetrac->v2)));
            p3Df_set(v31,(&(tt->children[3].tetrac->v3)));
			tt->children[3].tetrac->sign = SIGNO(DET4D(centroid,tt->children[3].tetrac->v1,tt->children[3].tetrac->v2,tt->children[3].tetrac->v3));

			
           //Generacion recursiva del tetratree                     
            for(int i=0; i<4; i++) 
                    generateTetraTree(deep-1,maxTri,tt->tetrac->triangInc,&(tt->children[i]),mMesh,centroid);                                
}
/*---------------------------------------------------------------------------*/
///Función para generar un tetre-tree asociado a una malla.
void generateTetraTree(unsigned int deep,unsigned int maxTri, tetratree* ttree, mesh *mMesh){
    
	//Cargamos la malla.
   ttree->mMeshTT = mMesh;
	
	//Inicializamos valores del tetracono
   double xc,yc,zc;
	xc= mMesh->points[0].x;
	yc= mMesh->points[0].y;
	zc= mMesh->points[0].z;
	
	//Calculo del centroide de la malla.
   for(unsigned int n=1; n<mMesh->points.size(); n++){
           xc += mMesh->points[n].x;           
           yc += mMesh->points[n].y;           
           zc += mMesh->points[n].z;
           
   }
   xc /= mMesh->points.size();
   yc /= mMesh->points.size();
   zc /= mMesh->points.size();   
   p3Df_sete((&(ttree->centroid)),xc,yc,zc);
	
   //Tamaño inicial del tetratree
   
   double sizeTT = 200.0;
   
	//Las 6 Coordenadas del tetracono 
   p3Df points[6];
   p3Df_sete(&(points[0]),xc,yc,zc+sizeTT);
   p3Df_sete(&(points[1]),xc,yc,zc-sizeTT);
   p3Df_sete(&(points[2]),xc,yc+sizeTT,zc);
   p3Df_sete(&(points[3]),xc,yc-sizeTT,zc);
   p3Df_sete(&(points[4]),xc+sizeTT,yc,zc);
   p3Df_sete(&(points[5]),xc-sizeTT,yc,zc);
   
	//Inicalizamos el nivel 1 de tetraconos
   for(int i=0; i<8; i++){
            ttree->children[i].tetrac = new (tetracone);
   			ttree->children[i].children = NULL;
   }	   
   
	//Insertamos coordenadas y signo del volumen.
   p3Df_set(points[0],&(ttree->children[0].tetrac->v1));
   p3Df_set(points[4],&(ttree->children[0].tetrac->v2));
   p3Df_set(points[2],&(ttree->children[0].tetrac->v3));   
   ttree->children[0].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[0].tetrac->v1,ttree->children[0].tetrac->v2,ttree->children[0].tetrac->v3));
   
   p3Df_set(points[0],&(ttree->children[1].tetrac->v1));
   p3Df_set(points[3],&(ttree->children[1].tetrac->v2));
   p3Df_set(points[4],&(ttree->children[1].tetrac->v3));   
   ttree->children[1].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[1].tetrac->v1,ttree->children[1].tetrac->v2,ttree->children[1].tetrac->v3));
   
   p3Df_set(points[0],&(ttree->children[2].tetrac->v1));
   p3Df_set(points[5],&(ttree->children[2].tetrac->v2));
   p3Df_set(points[3],&(ttree->children[2].tetrac->v3));   
   ttree->children[2].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[2].tetrac->v1,ttree->children[2].tetrac->v2,ttree->children[2].tetrac->v3));
   
   p3Df_set(points[0],&(ttree->children[3].tetrac->v1));
   p3Df_set(points[2],&(ttree->children[3].tetrac->v2));
   p3Df_set(points[5],&(ttree->children[3].tetrac->v3));   
	ttree->children[3].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[3].tetrac->v1,ttree->children[3].tetrac->v2,ttree->children[3].tetrac->v3));
   
   p3Df_set(points[1],&(ttree->children[4].tetrac->v1));
   p3Df_set(points[2],&(ttree->children[4].tetrac->v2));
   p3Df_set(points[4],&(ttree->children[4].tetrac->v3));
   ttree->children[4].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[4].tetrac->v1,ttree->children[4].tetrac->v2,ttree->children[4].tetrac->v3));
	
   p3Df_set(points[1],&(ttree->children[5].tetrac->v1));
   p3Df_set(points[4],&(ttree->children[5].tetrac->v2));
   p3Df_set(points[3],&(ttree->children[5].tetrac->v3));
   ttree->children[5].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[5].tetrac->v1,ttree->children[5].tetrac->v2,ttree->children[5].tetrac->v3));
	
   p3Df_set(points[1],&(ttree->children[6].tetrac->v1));
   p3Df_set(points[3],&(ttree->children[6].tetrac->v2));
   p3Df_set(points[5],&(ttree->children[6].tetrac->v3));
   ttree->children[6].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[6].tetrac->v1,ttree->children[6].tetrac->v2,ttree->children[6].tetrac->v3));

   p3Df_set(points[1],&(ttree->children[7].tetrac->v1));
   p3Df_set(points[5],&(ttree->children[7].tetrac->v2));
   p3Df_set(points[2],&(ttree->children[7].tetrac->v3));
   ttree->children[7].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[7].tetrac->v1,ttree->children[7].tetrac->v2,ttree->children[7].tetrac->v3));
	nt = 0;
	//Inicializamos el proceso recursivo de construcción del tetra-tree.
	//Generamos el vector de referencias a triangulos
			vector<int> vtrian;
			for(int n=0; n<ttree->mMeshTT->faces.size(); n++)
				vtrian.push_back(n);

	
   for(int i=0; i<8; i++){
	   	//printf("Generacion de hijos\t prof= %d\tmax= %d\n",deep,maxtri);
            generateTetraTree(deep-1, maxTri-1,vtrian,&ttree->children[i],ttree->mMeshTT,ttree->centroid);
    }      
	ttree->ntet = nt;
	
	//Ajuste del tetratree a tetratree envolvente
	//wrapTetratree(ttree);
}
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
//Funcion recursiva para generar el Tetratree
void generateTetraTreeInclussion(unsigned int deep,unsigned int maxTri, vector<int> triang, nodeTT* tt, mesh *mMesh, p3Df centroid){
          //Clasificar triangulos.
			if(tt->tetrac->triangInc.size()!= 0) tt->tetrac->triangInc.clear();
		  	 for(unsigned int i = 0; i<triang.size(); i++)
	            clasifyTriang(tt->tetrac,triang[i],mMesh,centroid);			       
           	//criterio de parada			
           if(deep == 0 || tt->tetrac->triangInc.size() < maxTri) return;
            p3Df v12,v23,v31;
			
            
            //Nuevas coordenadas
            p3Df_suma(tt->tetrac->v1, tt->tetrac->v2,(&v12));
            p3Df_div(v12,2.0,(&v12));
            p3Df_suma(tt->tetrac->v3, tt->tetrac->v2,(&v23));
            p3Df_div(v23,2.0,(&v23));
            p3Df_suma(tt->tetrac->v1, tt->tetrac->v3,(&v31));
            p3Df_div(v31,2.0,(&v31));

			//Inicalizammos los hijos.
            tt->children = new nodeTT[4];
			nt+=3;
            
            for(int i=0; i<4; i++){
                     tt->children[i].children = NULL;
                     tt->children[i].tetrac = new (tetracone);
            }
                        
            //Primer hijo
			
            tt->children[0].tetrac = new tetracone;
            p3Df_set(tt->tetrac->v1,(&(tt->children[0].tetrac->v1)));
            p3Df_set(v12, (&(tt->children[0].tetrac->v2)));
            p3Df_set(v31, (&(tt->children[0].tetrac->v3)));
			tt->children[0].tetrac->sign = SIGNO(DET4D(centroid,tt->children[0].tetrac->v1,tt->children[0].tetrac->v2,tt->children[0].tetrac->v3));
			p3Df_resta(centroid,tt->children[0].tetrac->v3,&(tt->children[0].tetrac->a));
			p3Df_resta(tt->children[0].tetrac->v1,tt->children[0].tetrac->v3,&(tt->children[0].tetrac->b));
			p3Df_resta(tt->children[0].tetrac->v2,tt->children[0].tetrac->v3,&(tt->children[0].tetrac->c));
			p3Df_cross(tt->children[0].tetrac->b,tt->children[0].tetrac->c,&(tt->children[0].tetrac->w1)); 
			tt->children[0].tetrac->w = DOT(tt->children[0].tetrac->a,tt->children[0].tetrac->w1);
            
            //Segundo hijo
            tt->children[1].tetrac = new tetracone;
            p3Df_set(v12,(&(tt->children[1].tetrac->v1)));
            p3Df_set(tt->tetrac->v2,(&(tt->children[1].tetrac->v2)));
            p3Df_set(v23,(&(tt->children[1].tetrac->v3)));
			tt->children[1].tetrac->sign = SIGNO(DET4D(centroid,tt->children[1].tetrac->v1,tt->children[1].tetrac->v2,tt->children[1].tetrac->v3));
			p3Df_resta(centroid,tt->children[1].tetrac->v3,&(tt->children[1].tetrac->a));
			p3Df_resta(tt->children[1].tetrac->v1,tt->children[1].tetrac->v3,&(tt->children[1].tetrac->b));
			p3Df_resta(tt->children[1].tetrac->v2,tt->children[1].tetrac->v3,&(tt->children[1].tetrac->c));
			p3Df_cross(tt->children[1].tetrac->b,tt->children[1].tetrac->c,&(tt->children[1].tetrac->w1)); 
			tt->children[1].tetrac->w = DOT(tt->children[1].tetrac->a,tt->children[1].tetrac->w1);

            //Tercer hijo
            tt->children[2].tetrac = new tetracone;
            p3Df_set(v31,(&(tt->children[2].tetrac->v1)));
            p3Df_set(v23,(&(tt->children[2].tetrac->v2)));
            p3Df_set(tt->tetrac->v3,(&(tt->children[2].tetrac->v3)));
            tt->children[2].tetrac->sign = SIGNO(DET4D(centroid,tt->children[2].tetrac->v1,tt->children[2].tetrac->v2,tt->children[2].tetrac->v3));
			p3Df_resta(centroid,tt->children[2].tetrac->v3,&(tt->children[2].tetrac->a));
			p3Df_resta(tt->children[2].tetrac->v1,tt->children[2].tetrac->v3,&(tt->children[2].tetrac->b));
			p3Df_resta(tt->children[2].tetrac->v2,tt->children[2].tetrac->v3,&(tt->children[2].tetrac->c));
			p3Df_cross(tt->children[2].tetrac->b,tt->children[2].tetrac->c,&(tt->children[2].tetrac->w1)); 
			tt->children[2].tetrac->w = DOT(tt->children[2].tetrac->a,tt->children[2].tetrac->w1);
	
            //Cuarto hijo
            tt->children[3].tetrac = new tetracone;
            p3Df_set(v12,(&(tt->children[3].tetrac->v1)));
            p3Df_set(v23,(&(tt->children[3].tetrac->v2)));
            p3Df_set(v31,(&(tt->children[3].tetrac->v3)));
			tt->children[3].tetrac->sign = SIGNO(DET4D(centroid,tt->children[3].tetrac->v1,tt->children[3].tetrac->v2,tt->children[3].tetrac->v3));
			p3Df_resta(centroid,tt->children[3].tetrac->v3,&(tt->children[3].tetrac->a));
			p3Df_resta(tt->children[3].tetrac->v1,tt->children[3].tetrac->v3,&(tt->children[3].tetrac->b));
			p3Df_resta(tt->children[3].tetrac->v2,tt->children[3].tetrac->v3,&(tt->children[3].tetrac->c));
			p3Df_cross(tt->children[3].tetrac->b,tt->children[3].tetrac->c,&(tt->children[3].tetrac->w1)); 
			tt->children[3].tetrac->w = DOT(tt->children[3].tetrac->a,tt->children[3].tetrac->w1);

			
           //Generacion recursiva del tetratree                     
            for(int i=0; i<4; i++) 
                    generateTetraTreeInclussion(deep-1,maxTri,tt->tetrac->triangInc,&(tt->children[i]),mMesh,centroid);                                
}
/*---------------------------------------------------------------------------*/
///Función para generar un tetre-tree asociado a una malla.
void generateTetraTreeInclussion(unsigned int deep,unsigned int maxTri, tetratree* ttree, mesh *mMesh){
    
	//Cargamos la malla.
   ttree->mMeshTT = mMesh;
	
	//Inicializamos valores del tetracono
   double xc,yc,zc;
	xc= mMesh->points[0].x;
	yc= mMesh->points[0].y;
	zc= mMesh->points[0].z;
	
	//Calculo del centroide de la malla.
   for(unsigned int n=1; n<mMesh->points.size(); n++){
           xc += mMesh->points[n].x;           
           yc += mMesh->points[n].y;           
           zc += mMesh->points[n].z;
           
   }
   xc /= mMesh->points.size();
   yc /= mMesh->points.size();
   zc /= mMesh->points.size();   
   p3Df_sete((&(ttree->centroid)),xc,yc,zc);
	
   //Tamaño inicial del tetratree
   
   double sizeTT = 200.0;
   
	//Las 6 Coordenadas del tetracono 
   p3Df points[6];
   p3Df_sete(&(points[0]),xc,yc,zc+sizeTT);
   p3Df_sete(&(points[1]),xc,yc,zc-sizeTT);
   p3Df_sete(&(points[2]),xc,yc+sizeTT,zc);
   p3Df_sete(&(points[3]),xc,yc-sizeTT,zc);
   p3Df_sete(&(points[4]),xc+sizeTT,yc,zc);
   p3Df_sete(&(points[5]),xc-sizeTT,yc,zc);
   
	//Inicalizamos el nivel 1 de tetraconos
   for(int i=0; i<8; i++){
            ttree->children[i].tetrac = new (tetracone);
   			ttree->children[i].children = NULL;
   }	   


	//Insertamos coordenadas y signo del volumen.
   p3Df_set(points[0],&(ttree->children[0].tetrac->v1));
   p3Df_set(points[4],&(ttree->children[0].tetrac->v2));
   p3Df_set(points[2],&(ttree->children[0].tetrac->v3));   
   ttree->children[0].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[0].tetrac->v1,ttree->children[0].tetrac->v2,ttree->children[0].tetrac->v3));
	p3Df_resta(ttree->centroid,ttree->children[0].tetrac->v3,&(ttree->children[0].tetrac->a));
	p3Df_resta(ttree->children[0].tetrac->v1,ttree->children[0].tetrac->v3,&(ttree->children[0].tetrac->b));
	p3Df_resta(ttree->children[0].tetrac->v2,ttree->children[0].tetrac->v3,&(ttree->children[0].tetrac->c));
	p3Df_cross(ttree->children[0].tetrac->b,ttree->children[0].tetrac->c,&(ttree->children[0].tetrac->w1)); 
	ttree->children[0].tetrac->w = DOT(ttree->children[0].tetrac->a,ttree->children[0].tetrac->w1);
   
   p3Df_set(points[0],&(ttree->children[1].tetrac->v1));
   p3Df_set(points[3],&(ttree->children[1].tetrac->v2));
   p3Df_set(points[4],&(ttree->children[1].tetrac->v3));   
   ttree->children[1].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[1].tetrac->v1,ttree->children[1].tetrac->v2,ttree->children[1].tetrac->v3));
	p3Df_resta(ttree->centroid,ttree->children[1].tetrac->v3,&(ttree->children[1].tetrac->a));
	p3Df_resta(ttree->children[1].tetrac->v1,ttree->children[1].tetrac->v3,&(ttree->children[1].tetrac->b));
	p3Df_resta(ttree->children[1].tetrac->v2,ttree->children[1].tetrac->v3,&(ttree->children[1].tetrac->c));
	p3Df_cross(ttree->children[1].tetrac->b,ttree->children[1].tetrac->c,&(ttree->children[1].tetrac->w1)); 
	ttree->children[1].tetrac->w = DOT(ttree->children[1].tetrac->a,ttree->children[1].tetrac->w1);
   
   p3Df_set(points[0],&(ttree->children[2].tetrac->v1));
   p3Df_set(points[5],&(ttree->children[2].tetrac->v2));
   p3Df_set(points[3],&(ttree->children[2].tetrac->v3));   
   ttree->children[2].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[2].tetrac->v1,ttree->children[2].tetrac->v2,ttree->children[2].tetrac->v3));
	p3Df_resta(ttree->centroid,ttree->children[2].tetrac->v3,&(ttree->children[2].tetrac->a));
	p3Df_resta(ttree->children[2].tetrac->v1,ttree->children[2].tetrac->v3,&(ttree->children[2].tetrac->b));
	p3Df_resta(ttree->children[2].tetrac->v2,ttree->children[2].tetrac->v3,&(ttree->children[2].tetrac->c));
	p3Df_cross(ttree->children[2].tetrac->b,ttree->children[2].tetrac->c,&(ttree->children[2].tetrac->w1)); 
	ttree->children[2].tetrac->w = DOT(ttree->children[2].tetrac->a,ttree->children[2].tetrac->w1);
   
   p3Df_set(points[0],&(ttree->children[3].tetrac->v1));
   p3Df_set(points[2],&(ttree->children[3].tetrac->v2));
   p3Df_set(points[5],&(ttree->children[3].tetrac->v3));   
	ttree->children[3].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[3].tetrac->v1,ttree->children[3].tetrac->v2,ttree->children[3].tetrac->v3));
	p3Df_resta(ttree->centroid,ttree->children[3].tetrac->v3,&(ttree->children[3].tetrac->a));
	p3Df_resta(ttree->children[3].tetrac->v1,ttree->children[3].tetrac->v3,&(ttree->children[3].tetrac->b));
	p3Df_resta(ttree->children[3].tetrac->v2,ttree->children[3].tetrac->v3,&(ttree->children[3].tetrac->c));
	p3Df_cross(ttree->children[3].tetrac->b,ttree->children[3].tetrac->c,&(ttree->children[3].tetrac->w1)); 
	ttree->children[3].tetrac->w = DOT(ttree->children[3].tetrac->a,ttree->children[3].tetrac->w1);
   
   p3Df_set(points[1],&(ttree->children[4].tetrac->v1));
   p3Df_set(points[2],&(ttree->children[4].tetrac->v2));
   p3Df_set(points[4],&(ttree->children[4].tetrac->v3));
   ttree->children[4].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[4].tetrac->v1,ttree->children[4].tetrac->v2,ttree->children[4].tetrac->v3));
	p3Df_resta(ttree->centroid,ttree->children[4].tetrac->v3,&(ttree->children[4].tetrac->a));
	p3Df_resta(ttree->children[4].tetrac->v1,ttree->children[4].tetrac->v3,&(ttree->children[4].tetrac->b));
	p3Df_resta(ttree->children[4].tetrac->v2,ttree->children[4].tetrac->v3,&(ttree->children[4].tetrac->c));
	p3Df_cross(ttree->children[4].tetrac->b,ttree->children[4].tetrac->c,&(ttree->children[4].tetrac->w1)); 
	ttree->children[4].tetrac->w = DOT(ttree->children[4].tetrac->a,ttree->children[4].tetrac->w1);
	
   p3Df_set(points[1],&(ttree->children[5].tetrac->v1));
   p3Df_set(points[4],&(ttree->children[5].tetrac->v2));
   p3Df_set(points[3],&(ttree->children[5].tetrac->v3));
   ttree->children[5].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[5].tetrac->v1,ttree->children[5].tetrac->v2,ttree->children[5].tetrac->v3));
	p3Df_resta(ttree->centroid,ttree->children[5].tetrac->v3,&(ttree->children[5].tetrac->a));
	p3Df_resta(ttree->children[5].tetrac->v1,ttree->children[5].tetrac->v3,&(ttree->children[5].tetrac->b));
	p3Df_resta(ttree->children[5].tetrac->v2,ttree->children[5].tetrac->v3,&(ttree->children[5].tetrac->c));
	p3Df_cross(ttree->children[5].tetrac->b,ttree->children[5].tetrac->c,&(ttree->children[5].tetrac->w1)); 
	ttree->children[5].tetrac->w = DOT(ttree->children[5].tetrac->a,ttree->children[5].tetrac->w1);
	
   p3Df_set(points[1],&(ttree->children[6].tetrac->v1));
   p3Df_set(points[3],&(ttree->children[6].tetrac->v2));
   p3Df_set(points[5],&(ttree->children[6].tetrac->v3));
   ttree->children[6].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[6].tetrac->v1,ttree->children[6].tetrac->v2,ttree->children[6].tetrac->v3));
	p3Df_resta(ttree->centroid,ttree->children[6].tetrac->v3,&(ttree->children[6].tetrac->a));
	p3Df_resta(ttree->children[6].tetrac->v1,ttree->children[6].tetrac->v3,&(ttree->children[6].tetrac->b));
	p3Df_resta(ttree->children[6].tetrac->v2,ttree->children[6].tetrac->v3,&(ttree->children[6].tetrac->c));
	p3Df_cross(ttree->children[6].tetrac->b,ttree->children[6].tetrac->c,&(ttree->children[6].tetrac->w1)); 
	ttree->children[6].tetrac->w = DOT(ttree->children[6].tetrac->a,ttree->children[6].tetrac->w1);

   p3Df_set(points[1],&(ttree->children[7].tetrac->v1));
   p3Df_set(points[5],&(ttree->children[7].tetrac->v2));
   p3Df_set(points[2],&(ttree->children[7].tetrac->v3));
   ttree->children[7].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[7].tetrac->v1,ttree->children[7].tetrac->v2,ttree->children[7].tetrac->v3));
	p3Df_resta(ttree->centroid,ttree->children[7].tetrac->v3,&(ttree->children[7].tetrac->a));
	p3Df_resta(ttree->children[7].tetrac->v1,ttree->children[7].tetrac->v3,&(ttree->children[7].tetrac->b));
	p3Df_resta(ttree->children[7].tetrac->v2,ttree->children[7].tetrac->v3,&(ttree->children[7].tetrac->c));
	p3Df_cross(ttree->children[7].tetrac->b,ttree->children[7].tetrac->c,&(ttree->children[7].tetrac->w1)); 
	ttree->children[7].tetrac->w = DOT(ttree->children[7].tetrac->a,ttree->children[7].tetrac->w1);
	nt = 0;
	//Inicializamos el proceso recursivo de construcción del tetra-tree.
	//Generamos el vector de referencias a triangulos
			vector<int> vtrian;
			for(int n=0; n<ttree->mMeshTT->faces.size(); n++)
				vtrian.push_back(n);

	
   for(int i=0; i<8; i++){
	   	//printf("Generacion de hijos\t prof= %d\tmax= %d\n",deep,maxtri);
            generateTetraTreeInclussion(deep-1, maxTri-1,vtrian,&ttree->children[i],ttree->mMeshTT,ttree->centroid);
    }      
	ttree->ntet = nt;
	
	//Ajuste del tetratree a tetratree envolvente
	//wrapTetratree(ttree);
}
/*---------------------------------------------------------------------------*/

int saveNTTMesh(tetratree *tte, nodeTT *tt, mesh *malla,p3Df centroid){
                  triangle tri;
           if(tt->children == NULL){
			  malla->points.push_back(centroid);
              malla->points.push_back(tt->tetrac->v1);
              malla->points.push_back(tt->tetrac->v2);
              malla->points.push_back(tt->tetrac->v3);
              tri.v0 = malla->points.size() - 3;
              tri.v1 = malla->points.size() - 2;
              tri.v2 = malla->points.size() - 1;
              malla->faces.push_back(tri);
			  tri.v0 = malla->points.size() - 4;
              tri.v1 = malla->points.size() - 3;
              tri.v2 = malla->points.size() - 2;
              malla->faces.push_back(tri);
			  tri.v0 = malla->points.size() - 4;
              tri.v1 = malla->points.size() - 2;
              tri.v2 = malla->points.size() - 1;
              malla->faces.push_back(tri);
			  tri.v0 = malla->points.size() - 4;
              tri.v1 = malla->points.size() - 1;
              tri.v2 = malla->points.size() - 3;
              malla->faces.push_back(tri);
			  /*
			  for(j=0; j<tt->tetrac->triangInc.size(); j++){
                      malla->faces.push_back(tt->tetrac->triangInc[j]);
				 }
			  char name[40];
              sprintf(name,"Tetracono%d.obj",contador);
			  */
			  
           }else{
                 for(int i=0; i<4; i++)
                     saveNTTMesh(tte,&(tt->children[i]),&(*malla),centroid);
			 }		 
}
/*---------------------------------------------------------------------------*/
void saveTTMesh(tetratree *tt,mesh *malla){
	int j;
	for(j=0; j<tt->mMeshTT->points.size(); j++)
                       malla->points.push_back(tt->mMeshTT->points[j]);   
	for(j=0; j<tt->mMeshTT->faces.size(); j++)
			if(tt->mMeshTT->faces[j].itype != -1)
                       malla->faces.push_back(tt->mMeshTT->faces[j]);   
     for(unsigned int i=0; i<8; i++){
             saveNTTMesh(tt,&(tt->children[i]),&(*malla),tt->centroid);
     }         
	 saveOBJ(malla, "Tetratreecompleto.obj");                    
}
/*---------------------------------------------------------------------------*/
void saveTTMesh(tetratree *tt){
     unsigned int i,j;
     triangle tri;
     for(i=0; i<8; i++){     
              mesh* malla;
              malla = new (mesh);
              nodeTT *tte;
              tte = &(tt->children[i]);
              
              for(j=0; j<tt->mMeshTT->points.size(); j++){
                       malla->points.push_back(tt->mMeshTT->points[j]);              
			  }
		      
		 	  malla->points.push_back(tt->centroid);
              malla->points.push_back(tte->tetrac->v1);
              malla->points.push_back(tte->tetrac->v2);
              malla->points.push_back(tte->tetrac->v3);
              tri.v0 = malla->points.size() - 3;
              tri.v1 = malla->points.size() - 2;
              tri.v2 = malla->points.size() - 1;
              malla->faces.push_back(tri);
			  tri.v0 = malla->points.size() - 4;
              tri.v1 = malla->points.size() - 3;
              tri.v2 = malla->points.size() - 2;
              malla->faces.push_back(tri);
			  tri.v0 = malla->points.size() - 4;
              tri.v1 = malla->points.size() - 3;
              tri.v2 = malla->points.size() - 1;
              malla->faces.push_back(tri);
			  tri.v0 = malla->points.size() - 4;
              tri.v1 = malla->points.size() - 1;
              tri.v2 = malla->points.size() - 3;
              malla->faces.push_back(tri);
			  
              for(j=0; j<tte->tetrac->triangInc.size(); j++){		
				  if(tt->mMeshTT->faces[tte->tetrac->triangInc[j]].itype != -1)
				  	malla->faces.push_back(tt->mMeshTT->faces[tte->tetrac->triangInc[j]]);				  
              }
		
			  
			  //printf("Numero de triangulos: %d\n",malla->faces.size());
              char name[40];			  
              sprintf(name,"Tetracono%d.obj",i);
			  saveOBJ(malla, name);                    
              
     }         
}


/*---------------------------------------------------------------------------*/
void wrapTetratree(nodeTT *tt, mesh *m, p3Df centroid){
	if(tt->children == NULL){
		float dist=0, dv1, dv2, dv3;
		p3Df cent,cenp1,cenp2,cenp3,cencen;
		p3Df_incentro(tt->tetrac->v1,tt->tetrac->v2,tt->tetrac->v3,&cent);
		for(int j=0; j< (tt->tetrac->triangInc.size()); j++){
			float da, db, dc;
			da = fabs(PROYECTION(m->points[m->faces[tt->tetrac->triangInc[j]].v0],cent,centroid));
			db = fabs(PROYECTION(m->points[m->faces[tt->tetrac->triangInc[j]].v1],cent,centroid));
			dc = fabs(PROYECTION(m->points[m->faces[tt->tetrac->triangInc[j]].v2],cent,centroid));
			
			if(da > dist) dist = da;
			if(db > dist) dist = db;
			if(dc > dist) dist = dc;
		}		
			
		dv1 = dist/(ANGLEV(cent,tt->tetrac->v1,centroid));
		p3Df_dist(dv1+1.0,&(tt->tetrac->v1),centroid);
		dv2 = dist /(ANGLEV(cent,tt->tetrac->v2,centroid));
		p3Df_dist(dv2+1.0,&(tt->tetrac->v2),centroid);
		dv3 = dist /(ANGLEV(cent,tt->tetrac->v3,centroid));
		p3Df_dist(dv3+1.0,&(tt->tetrac->v3),centroid);
		
	}else{
		for(int i=0; i<4; i++){
			wrapTetratree(&(tt->children[i]),m,centroid);
		}
	}
}

/*---------------------------------------------------------------------------*/
void wrapTetratree(tetratree *tt){
	
	for(int i=0; i<8; i++){
		wrapTetratree(&(tt->children[i]),tt->mMeshTT,tt->centroid);
	}	
	
}

/*---------------------------------------------------------------------------*/
void eraseTetratree(nodeTT *tt){
	int j,n,i;
	if(tt->children == NULL){
		tt->tetrac->triangInc.clear();		
	}else{
		for(i=0; i<4; i++){
			eraseTetratree(&(tt->children[i]));			
			delete(tt->children[i].tetrac);
		}
		delete(tt->children);
		tt->tetrac->triangInc.clear();				
	}
}

/*---------------------------------------------------------------------------*/
void eraseTetratree(tetratree *tt){
	for(int i=0; i<8; i++){
		eraseTetratree(&(tt->children[i]));		
	}	
	tt->mMeshTT->faces.clear();
	tt->mMeshTT->points.clear();
	tt->mMeshTT->normals.clear();
	tt->mMeshTT->textures.clear();
	delete(tt->mMeshTT);
	//delete(tt->children);
}

/*---------------------------------------------------------------------------*/
int updateTT(nodeTT* tt,int nnewtri, vector<int> tritoerase, mesh* m,p3Df cent){
	int j,n,i;
	if(tt->children == NULL){
		for(j=0; j< (tt->tetrac->triangInc.size()); j++){
			for(n=0; n< tritoerase.size(); n++){
				if(tt->tetrac->triangInc[j] == tritoerase[n])
					tt->tetrac->triangInc.erase(tt->tetrac->triangInc.begin() + j);
			}
		 }
		for(j=1; j<=nnewtri; j++){
			clasifyTriang(tt->tetrac,(m->faces.size()-j),m,cent);	
		}
	}else{
		for(i=0; i<4; i++){
			updateTT(&(tt->children[i]),nnewtri,tritoerase,m,cent);
		}
	}
}
/*---------------------------------------------------------------------------*/
int updateTT(tetratree* tt,int nnewtri, vector<int> tritoerase){
	for(int i=0; i<8; i++){
		updateTT(&(tt->children[i]),nnewtri,tritoerase,tt->mMeshTT,tt->centroid);
	}	
}
/*---------------------------------------------------------------------------*/
void splitTetracone(nodeTT *tt, mesh *m, p3Df centroid){
	// printf("Otro tetracono...%d inc\n",tt->tetrac->triangInc.size());
		vector<int> newtriangtt;
		int n;
		//Nodo hoja del tetratree
		for(int j=0; j< (tt->tetrac->triangInc.size()); j++){
			int pinc[3];//En esta varible almancenamos cuantos puntos del triangulo están dentro del tetracono
			for(n=0; n<3; n++) pinc[n] = 0;
			//Para cada triangulo seleccionado
			if(tetraPoint(centroid,tt->tetrac->v1, tt->tetrac->v2,tt->tetrac->v3,m->points[m->faces[tt->tetrac->triangInc[j]].v0],tt->tetrac->sign)==OUT)
					pinc[0] = 1;					
			if(tetraPoint(centroid,tt->tetrac->v1, tt->tetrac->v2,tt->tetrac->v3,m->points[m->faces[tt->tetrac->triangInc[j]].v1],tt->tetrac->sign)==OUT)
					pinc[1] = 1;
			if(tetraPoint(centroid,tt->tetrac->v1, tt->tetrac->v2,tt->tetrac->v3,m->points[m->faces[tt->tetrac->triangInc[j]].v2],tt->tetrac->sign)==OUT)
					pinc[2] = 1;
			if( ((pinc[0]==1)&&(pinc[1]==1)&&(pinc[2]==1)) || 
			    ((pinc[0]==0)&&(pinc[1]==0)&&(pinc[2]==0)) ||
			    (m->faces[tt->tetrac->triangInc[j]].itype == ERASED)){
					// printf("Triangulo %d totalmente contenido\n",j);		
					nt_completos++;
			}else{	
				m->faces[tt->tetrac->triangInc[j]].itype = ERASED;
				int ptinc[3];//En esta varible almancenamos cuantos puntos del triangulo están dentro del tetracono
				int pladostt[3];//numero de latos del triangulo interesectados
				int pladosint[3];//Almacenamos que lados del tetracono son intersectados
				int nplti=0;//numero de planos intersectados del 	
				for(n=0; n<3; n++) ptinc[n] = pladostt[n] = pladosint[n] = 0;

				//Si no esta totalmente contenido hay que trocear
				//Almacenamos el triangulo para eliminar
				//tritoerase.push_back(j);
				p3Df inters[9];
				p3Df ptdentrotri[3];
				for(n=0; n<9; n++){ inters[n].x = 0.0;inters[n].y = 0.0;inters[n].z = 0.0;}
				for(n=0; n<3; n++){ ptdentrotri[n].x = 0.0;ptdentrotri[n].y = 0.0;ptdentrotri[n].z = 0.0;}
				trian orig,proy;
				int n_int = 0;
				int climit = 0;
			
				p3Df o01, o12, o20, py01, py12, py20;
				//extraemos las coordenadas del triangulo de la malla
				orig.v0 = m->points[m->faces[tt->tetrac->triangInc[j]].v0];
				orig.v1 = m->points[m->faces[tt->tetrac->triangInc[j]].v1];
				orig.v2 = m->points[m->faces[tt->tetrac->triangInc[j]].v2];

				//Caso limite de un punto de intersection en una arista lateral del tetracono
				if((testTetraPointLimit(centroid, orig.v0, orig.v1, orig.v2,tt->tetrac->v1) == 0)||
				    (testTetraPointLimit(centroid, orig.v0, orig.v1, orig.v2,tt->tetrac->v2) == 0)||
				    (testTetraPointLimit(centroid, orig.v0, orig.v1, orig.v2,tt->tetrac->v3) == 0))
						climit = 1;
					
				
				    

				
			//Estudiamos que vertices del tetracono estan dentro del triangulo
				if(intersect_RayTriangle(centroid,tt->tetrac->v1,orig, &(ptdentrotri[0]))==1)
					  ptinc[0] = 1;
				if(intersect_RayTriangle(centroid,tt->tetrac->v2,orig, &(ptdentrotri[1]))==1)
					  ptinc[1] = 1;
				if(intersect_RayTriangle(centroid,tt->tetrac->v3,orig, &(ptdentrotri[2]))==1)
					  ptinc[2] = 1;
				//Para estudiar la intersecacion vamos a comparar cada segmento
				//del triangulo con las caras laterales del tetracono
				p3Df inf;
				trian ttcono;
				//Cara c,v1,c2
				ttcono.v0 = centroid;
				ttcono.v1 = tt->tetrac->v1;
				ttcono.v2 = tt->tetrac->v2;
				
			 	if(intersect_RayTriangle(orig.v0, orig.v1,ttcono, &(inters[0]))==1)
					n_int++;
				if(intersect_RayTriangle(orig.v1, orig.v2,ttcono, &(inters[1]))==1)
					n_int++;
				if(intersect_RayTriangle(orig.v2, orig.v0,ttcono, &(inters[2]))==1)
					n_int++;
				int parc1 = n_int;
				if(parc1 != 0){ 
					pladosint[0] = n_int;//El plano c,v1,v2 es intersectado n veces
					nplti++;
				}
				//Cara c,v2,c3
				ttcono.v1 = tt->tetrac->v2;
				ttcono.v2 = tt->tetrac->v3;
				if(intersect_RayTriangle(orig.v0, orig.v1,ttcono, &(inters[3]))==1)
					n_int++;
				if(intersect_RayTriangle(orig.v1, orig.v2,ttcono, &(inters[4]))==1)
					n_int++;
				if(intersect_RayTriangle(orig.v2, orig.v0,ttcono, &(inters[5]))==1)
					n_int++;
				int parc2 = (n_int - parc1);
			    if((n_int - parc1) != 0){
					pladosint[1] = (n_int-parc1);//El plano c,v2,v3 es intersectado
					nplti++;
				}
				//Cara c,v3,c1
			    ttcono.v1 = tt->tetrac->v3;
				ttcono.v2 = tt->tetrac->v1;
				if(intersect_RayTriangle(orig.v0, orig.v1,ttcono, &(inters[6]))==1)
					n_int++;
				if(intersect_RayTriangle(orig.v1, orig.v2,ttcono, &(inters[7]))==1)
					n_int++;
				if(intersect_RayTriangle(orig.v2, orig.v0,ttcono, &(inters[8]))==1)
					n_int++;
				if((n_int - parc1 -parc2) != 0){
					pladosint[2] = (n_int - parc1 -parc2);//El plano c,v3,v1 es intersectado
					nplti++;
				}
				ptosint[n_int]++;
				//Hemos determinado:
				    //1. numero de puntos del triangulo dentro del tetracono
				    //2. numero de puntos de interseccion.
				    //3. numero de puntos del tetracono dentro del triangulo
				    //4. planos laterales del tetracono intersectados
				//Ahora vamos a estudiar a que caso pertenecen
			
				int n_pinc = pinc[0] + pinc[1] + pinc[2];
				int n_ptinc = ptinc[0] + ptinc[1] + ptinc[2]; 
				int caso = 0;
				p3Df interstemp[6];
				int c=0;
				int sid;
				switch (n_pinc){
					case 0: 
							switch(n_ptinc){
								case 0:
									switch(nplti){
										case 2: caso = 7; break;
										case 3: caso = 5; break;
										default: printf(" Error 0 - 0 - %d) %d\n",nplti,climit);
											break;
									}
				    				break;
								case 1:
					    			switch(nplti){
										case 2: caso = 1; break;
										case 3: caso = 6; break;
										default: printf(" Error 0 - 1 - X\n)"); 
											break;
									}
				    				break;
								case 2:
										if(nplti == 2) caso = 2; else printf(" Error 0 - 2 - X\n)");
										break;
								default: printf(" Error 0 - X - X\n)"); 
											break;
							}
							break;
					case 1:
							switch(n_ptinc){
								case 0: 
									switch(nplti){
										case 1: caso = 3; break;
										case 2: caso = 11; break;
										default: printf(" Error 1 - 0 - X\n)");
											break;
									}
				    				break;
								case 1: 
										if(nplti == 2)  caso = 8; else printf(" Error 1 - 1 - %d\n)",nplti);
										break;
								case 2:
										if(nplti == 2) caso = 9; else printf(" Error 1 - 2 - %d\n)",nplti);
										break;
								default: printf("Error 1 - X - X\n"); 
											break;
							}
							break;
					case 2:
							if((n_ptinc == 0)&&(nplti == 1)){ caso = 4;
							}else{
								if((n_ptinc == 1)&&(nplti == 2)){ caso = 10;
								}else{
									//printf("Error 2 - X - X\t (%d,%d,%d)\t (%d,%d,%d)\n",2,n_ptinc,nplti,pladosint[0],pladosint[1],pladosint[2]); 
									break;
								}
							}
							break;
					default: printf("Error X - X - X\n"); break;
				}
				//printf("Caso %d\n",caso);

				
				if((p3Df_testnulo(inters[0]) != 0) || (p3Df_testnulo(inters[3]) != 0) || (p3Df_testnulo(inters[6]) != 0))
					pladostt[0] = 1;
				if((p3Df_testnulo(inters[1]) != 0) || (p3Df_testnulo(inters[4]) != 0) || (p3Df_testnulo(inters[7]) != 0))
					pladostt[1] = 1;
				if((p3Df_testnulo(inters[2]) != 0) || (p3Df_testnulo(inters[5]) != 0) || (p3Df_testnulo(inters[8]) != 0))
					pladostt[2] = 1;
				

				p3Df pinterno, inter1, inter2, inter3, inter4, inter5, inter6;
				int ladot,lado1, lado2,pintTT;
				int enc = 0;
				cases_used[caso-1]++;
				switch(caso){
					case 1:
						
						for(n=0; n<9; n++){
							if(enc == 0){
								if(p3Df_testnulo(inters[n]) != 0){
									inter1 = inters[n];
									enc = 1;
									n++;
								}
							}else{
								if(p3Df_testnulo(inters[n]) != 0){
									inter2 = inters[n];
									n++;
								}
							}									
						}
											
						if(pladostt[0]==1) ladot = 1;
						if(pladostt[1]==1) ladot = 2;
						if(pladostt[2]==1) ladot = 3;
						for(n=0; n<3; n++){
							if(p3Df_testnulo(ptdentrotri[n])!= 0){
								pinterno = ptdentrotri[n];
							}
						}
						//Cortamos
						tritoerase.push_back(j);
						splitpattern_case1( tt->tetrac->triangInc[j],m, 
						    pinterno,inter1,inter2, ladot, &(newtriangtt));	
						nnewtri += 5;							
						break;
					case 3:
						
						for(n=0; n<9; n++){
							if(enc == 0){
								if(p3Df_testnulo(inters[n]) != 0){
									inter1 = inters[n];
									lado1 = (n%3)+1;
									enc = 1;										
								}
							}else{
								if(p3Df_testnulo(inters[n]) != 0){
									inter2 = inters[n];										
									lado2 = (n%3)+1;
								}
							}									
						}
						tritoerase.push_back(j);
						splitpattern_case3(tt->tetrac->triangInc[j],m,inter1,inter2, lado1,lado2,&newtriangtt);
						nnewtri += 3;
						break;
						 
					case 4:
						for(n=0; n<9; n++){
							if(enc == 0){
								if(p3Df_testnulo(inters[n]) != 0){
									inter1 = inters[n];
									lado1 = (n%3)+1;
									enc = 1;										
								}
							}else{
								if(p3Df_testnulo(inters[n]) != 0){
									inter2 = inters[n];										
									lado2 = (n%3)+1;
								}
							}									
						}
						//if((lado1==1)&&(lado2==1)) printf("Error lado1 = 1, lado2 = 1\n");
						//if((lado1==2)&&(lado2!=3)) printf("Error lado1 = 2, lado2 = %d\n",lado2);
						//if(lado1 == 3) printf("Error lado1 = 3\n");
						tritoerase.push_back(j);
						splitpattern_case4(tt->tetrac->triangInc[j],m,inter1,inter2, lado1,lado2,&newtriangtt);
						nnewtri += 3;
						break;	
					case 5:
						
						for(n=0; n<9; n=n+3){
							if(p3Df_testnulo(inters[n+1]) == 0){
								interstemp[c] = inters[n+2];
								c++;
								interstemp[c] = inters[n];
								c++;
								if(n == 0) sid = 1;
								if(n == 3) sid = 3;
								if(n == 6) sid = 2;
								
							}else{
								if(p3Df_testnulo(inters[n]) == 0){
									interstemp[c] = inters[n+1];
									c++;
									interstemp[c] = inters[n+2];
									c++;
								}else{
									interstemp[c] = inters[n];
									c++;
									interstemp[c] = inters[n+1];
									c++;
								}
							}
						}
						
						splitpattern_case5(tt->tetrac->triangInc[j],m, interstemp[0],
						                   interstemp[1],interstemp[2],
						                   interstemp[3],interstemp[4],
						                   interstemp[5],sid,&newtriangtt);
						nnewtri += 7;
						break;					
						
							
					case 7:
						for(n=0; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){
								if(p3Df_testnulo(inter1) == 0){
									inter1 = inters[n];
								}else{
									inter2 = inters[n];
									lado1 = 1;										
								}
							}													
						}
						for(n=1; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){
								if(lado1 != 0){
									if(p3Df_testnulo(inter3) == 0){
										inter3 = inters[n];
									}else{
										inter4 = inters[n];
										lado2 = 2;											
									}									
								}else{
									if(p3Df_testnulo(inter1) == 0){
										inter1 = inters[n];
									}else{
										inter2 = inters[n];
										lado1 = 2;										
									}
								}										
							}													
						}
						for(n=2; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){
								if(p3Df_testnulo(inter3) == 0){
									inter3 = inters[n];
								}else{
									inter4 = inters[n];
									lado2 = 3;											
								}																			
							}													
						}
						splitpattern_case7(tt->tetrac->triangInc[j],m,inter1,inter2, inter3,inter4, lado1, lado2, &newtriangtt);
						nnewtri += 5;
						break;
					case 8: 
						for(n=0; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){
								inter1 = inters[n];
								lado1 = 1;										
								
							}													
						}
						for(n=1; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){
								if(lado1 != 0){
									inter2 = inters[n];
									lado2 = 2;
								}else{
									inter1 = inters[n];
									lado1 = 2;											
								}									
							}													
						}
						for(n=2; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){									
									inter2 = inters[n];
									lado2 = 3;											
																											
							}													
						}
						for(n=0; n<3; n++){
							if(p3Df_testnulo(ptdentrotri[n])!= 0){
								pinterno = ptdentrotri[n];
							}
						}
						if((lado1 == 1)&&(lado2 == 2)) pintTT = 1;
						if((lado1 == 2)&&(lado2 == 3)) pintTT = 2;
						if((lado1 == 1)&&(lado2 == 3)) pintTT = 3;
						splitpattern_case8(tt->tetrac->triangInc[j],m,inter1,inter2, pinterno, pintTT,&newtriangtt);
						nnewtri += 5;
						break;
					case 11:
						for(n=0; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){
								if(p3Df_testnulo(inter1) == 0){
									inter1 = inters[n];
								}else{
									inter2 = inters[n];
									lado1 = 1;
									enc = 1;
								}
							}													
						}
						for(n=1; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){
								if(enc == 1){
									inter3 = inters[n];
								}else{
									if(p3Df_testnulo(inter2) == 0){
										inter2 = inters[n];
									}else{
										inter3 = inters[n];
										lado1 = 2;
										enc = 1;
									}
								}
							}													
						}
						for(n=2; n<9; n=n+3){
							if(p3Df_testnulo(inters[n]) != 0){
								if(enc == 1){
									inter4 = inters[n];
								}else{
									if(p3Df_testnulo(inter3) == 0){
										inter3 = inters[n];
									}else{
										inter4 = inters[n];
										lado1 = 3;
										enc = 1;
									}
								}
							}													
						}
						
						tritoerase.push_back(j);
						splitpattern_case11(tt->tetrac->triangInc[j],m,inter1,inter2,inter3,inter4,lado1,&newtriangtt);
						nnewtri += 5;
						break;
				
				}
					
			}			
			
		}				
	if(nnewtri>0){
			//printf("Adding... %d-%d\n",nnewtri,newtriangtt.size());
			for(int nv=0; nv<newtriangtt.size(); nv++){
				trian tr;
				tr.v0 = m->points[m->faces[newtriangtt[nv]].v0];
				tr.v1 = m->points[m->faces[newtriangtt[nv]].v1];
				tr.v2 = m->points[m->faces[newtriangtt[nv]].v2];
				if(testDegenerateTriangle(tr)==0)
					ndeg++;
				else
					tt->tetrac->triangInc.push_back(newtriangtt[nv]);
			}
			newtriangtt.clear();
				
		}				
				
	
}
/*---------------------------------------------------------------------------*/
void splitTT(tetratree* ttree ,nodeTT *tt, mesh *m, p3Df centroid){

	//Para localizar los triangulos a trocear, primero descartamos aquellos que estan
	//totalmente contenidos en el tetracono
	
	
	
	if(tt->children == NULL){
		splitTetracone(tt,m,centroid);
	}else{
		for(int i=0; i<4; i++){
			splitTT(ttree,&(tt->children[i]),m,centroid);
		}
	}
	
}

/*---------------------------------------------------------------------------*/
int inclusionPointTT(p3Df p, nodeTT *t, p3Df centroid, mesh* m, int interType){	
	int pos = tetraPoint(centroid,t->tetrac->v1,t->tetrac->v2,t->tetrac->v3,p,t->tetrac->sign);
	if(pos==IN || pos==COLIS){
		if(t->children == NULL){	
			int idTrian, res;
				if(interType == JIMENEZ){
					res = nearestIntersectingTriangleJim(t,p,centroid,m,&idTrian);	
				}
				if(interType == JIMENEZOPT){
					res = nearestIntersectingTriangleJimNew(t,p,centroid,m,&idTrian);
				}				
				if(interType == MOLLER){
					
					res = nearestIntersectingTriangleMoeller(t,p,centroid,m,&idTrian);
				}
				
				
				
			
			
			//int res = nearestIntersectingTriangleJim(t,p,centroid,m,&idTrian);	
			//int res = nearestIntersectingTriangleMoeller(t,p,centroid,m,&idTrian);
			//int res = nearestIntersectingTriangleJimNew(t,p,centroid,m,&idTrian);
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
			
		}else{
			for(int i=0; i<4; i++)
				inclusionPointTT(p,&(t->children[i]),centroid,m,interType);								
		}		
	}
}

/*---------------------------------------------------------------------------*/
int inclusionPointTT(p3Df p, tetratree *tt,int interType){
	for(int i=0; i<8; i++){
		//printf("Empezando tetracono %d\n",i);
		inclusionPointTT(p, &(tt->children[i]), tt->centroid, tt->mMeshTT,interType);
		//printf("Terminado tetracono %d\n",i);
	}		
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
//Funcion recursiva para generar el Tetratree
void generateTetraTreeExt(unsigned int deep,unsigned int maxTri, vector<int> triang, nodeTT* tt, mesh *mMesh, p3Df centroid){
          //Clasificar triangulos.
			if(tt->tetrac->triangInc.size()!= 0) tt->tetrac->triangInc.clear();
		  	 for(unsigned int i = 0; i<triang.size(); i++)
	            clasifyTriang(tt->tetrac,triang[i],mMesh,centroid);	
			//printf("Casos Limite: %d\n",nlimits);
			nlimits = 0;
			splitTetracone(tt,mMesh,centroid);				
			//removeMarkedTriangles(mMesh, -1);		
           	//criterio de parada	
		//printf("Prof = %d\n",deep);
           if(deep == 0 || tt->tetrac->triangInc.size() < maxTri) return;
            p3Df v12,v23,v31;
			
            
            //Nuevas coordenadas
            p3Df_suma(tt->tetrac->v1, tt->tetrac->v2,(&v12));
            p3Df_div(v12,2.0,(&v12));
            p3Df_suma(tt->tetrac->v3, tt->tetrac->v2,(&v23));
            p3Df_div(v23,2.0,(&v23));
            p3Df_suma(tt->tetrac->v1, tt->tetrac->v3,(&v31));
            p3Df_div(v31,2.0,(&v31));

			//Inicalizammos los hijos.
            tt->children = new nodeTT[4];
			nt+=3;
            for(int i=0; i<4; i++){
                     tt->children[i].children = NULL;
                     tt->children[i].tetrac = new (tetracone);
					 				
            }
		
                        
            //Primer hijo
            tt->children[0].tetrac = new tetracone;
            p3Df_set(tt->tetrac->v1,(&(tt->children[0].tetrac->v1)));
            p3Df_set(v12, (&(tt->children[0].tetrac->v2)));
            p3Df_set(v31, (&(tt->children[0].tetrac->v3)));
			tt->children[0].tetrac->sign = SIGNO(DET4D(centroid,tt->children[0].tetrac->v1,tt->children[0].tetrac->v2,tt->children[0].tetrac->v3));
            
            //Segundo hijo
            tt->children[1].tetrac = new tetracone;
            p3Df_set(v12,(&(tt->children[1].tetrac->v1)));
            p3Df_set(tt->tetrac->v2,(&(tt->children[1].tetrac->v2)));
            p3Df_set(v23,(&(tt->children[1].tetrac->v3)));
			tt->children[1].tetrac->sign = SIGNO(DET4D(centroid,tt->children[1].tetrac->v1,tt->children[1].tetrac->v2,tt->children[1].tetrac->v3));

            //Tercer hijo
            tt->children[2].tetrac = new tetracone;
            p3Df_set(v31,(&(tt->children[2].tetrac->v1)));
            p3Df_set(v23,(&(tt->children[2].tetrac->v2)));
            p3Df_set(tt->tetrac->v3,(&(tt->children[2].tetrac->v3)));
            tt->children[2].tetrac->sign = SIGNO(DET4D(centroid,tt->children[2].tetrac->v1,tt->children[2].tetrac->v2,tt->children[2].tetrac->v3));
            //Cuarto hijo
            tt->children[3].tetrac = new tetracone;
            p3Df_set(v12,(&(tt->children[3].tetrac->v1)));
            p3Df_set(v23,(&(tt->children[3].tetrac->v2)));
            p3Df_set(v31,(&(tt->children[3].tetrac->v3)));
			tt->children[3].tetrac->sign = SIGNO(DET4D(centroid,tt->children[3].tetrac->v1,tt->children[3].tetrac->v2,tt->children[3].tetrac->v3));
           //Generacion recursiva del tetratree                     
            for(int i=0; i<4; i++) 
					//generateTetraTree(deep-1,maxTri,tt->tetrac->triangInc,&(tt->children[i]),mMesh,centroid);
                    generateTetraTreeExt(deep-1,maxTri,tt->tetrac->triangInc,&(tt->children[i]),mMesh,centroid);                                
}
/*---------------------------------------------------------------------------*/
///Función para generar un tetre-tree asociado a una malla.
void generateTetraTreeExt(unsigned int deep,unsigned int maxTri, tetratree* ttree, mesh *mMesh){
    
	//Cargamos la malla.
   ttree->mMeshTT = mMesh;
	
	//Inicializamos valores del tetracono
   double xc,yc,zc;
	xc= mMesh->points[0].x;
	yc= mMesh->points[0].y;
	zc= mMesh->points[0].z;
	
	//Calculo del centroide de la malla.
   for(unsigned int n=1; n<mMesh->points.size(); n++){
           xc += mMesh->points[n].x;           
           yc += mMesh->points[n].y;           
           zc += mMesh->points[n].z;
           
   }
   xc /= mMesh->points.size();
   yc /= mMesh->points.size();
   zc /= mMesh->points.size();   
   p3Df_sete((&(ttree->centroid)),xc,yc,zc);
	
   //Tamaño inicial del tetratree
   
   double sizeTT = 200.0;
   
	//Las 6 Coordenadas del tetracono 
   p3Df points[6];
   p3Df_sete(&(points[0]),xc,yc,zc+sizeTT);
   p3Df_sete(&(points[1]),xc,yc,zc-sizeTT);
   p3Df_sete(&(points[2]),xc,yc+sizeTT,zc);
   p3Df_sete(&(points[3]),xc,yc-sizeTT,zc);
   p3Df_sete(&(points[4]),xc+sizeTT,yc,zc);
   p3Df_sete(&(points[5]),xc-sizeTT,yc,zc);
   
	//Inicalizamos el nivel 1 de tetraconos
   for(int i=0; i<8; i++){
            ttree->children[i].tetrac = new (tetracone);
   			ttree->children[i].children = NULL;
   }	   
   
	//Insertamos coordenadas y signo del volumen.
   p3Df_set(points[0],&(ttree->children[0].tetrac->v1));
   p3Df_set(points[4],&(ttree->children[0].tetrac->v2));
   p3Df_set(points[2],&(ttree->children[0].tetrac->v3));   
   ttree->children[0].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[0].tetrac->v1,ttree->children[0].tetrac->v2,ttree->children[0].tetrac->v3));
   
   p3Df_set(points[0],&(ttree->children[1].tetrac->v1));
   p3Df_set(points[3],&(ttree->children[1].tetrac->v2));
   p3Df_set(points[4],&(ttree->children[1].tetrac->v3));   
   ttree->children[1].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[1].tetrac->v1,ttree->children[1].tetrac->v2,ttree->children[1].tetrac->v3));
   
   p3Df_set(points[0],&(ttree->children[2].tetrac->v1));
   p3Df_set(points[5],&(ttree->children[2].tetrac->v2));
   p3Df_set(points[3],&(ttree->children[2].tetrac->v3));   
   ttree->children[2].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[2].tetrac->v1,ttree->children[2].tetrac->v2,ttree->children[2].tetrac->v3));
   
   p3Df_set(points[0],&(ttree->children[3].tetrac->v1));
   p3Df_set(points[2],&(ttree->children[3].tetrac->v2));
   p3Df_set(points[5],&(ttree->children[3].tetrac->v3));   
	ttree->children[3].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[3].tetrac->v1,ttree->children[3].tetrac->v2,ttree->children[3].tetrac->v3));
   
   p3Df_set(points[1],&(ttree->children[4].tetrac->v1));
   p3Df_set(points[2],&(ttree->children[4].tetrac->v2));
   p3Df_set(points[4],&(ttree->children[4].tetrac->v3));
   ttree->children[4].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[4].tetrac->v1,ttree->children[4].tetrac->v2,ttree->children[4].tetrac->v3));
	
   p3Df_set(points[1],&(ttree->children[5].tetrac->v1));
   p3Df_set(points[4],&(ttree->children[5].tetrac->v2));
   p3Df_set(points[3],&(ttree->children[5].tetrac->v3));
   ttree->children[5].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[5].tetrac->v1,ttree->children[5].tetrac->v2,ttree->children[5].tetrac->v3));
	
   p3Df_set(points[1],&(ttree->children[6].tetrac->v1));
   p3Df_set(points[3],&(ttree->children[6].tetrac->v2));
   p3Df_set(points[5],&(ttree->children[6].tetrac->v3));
   ttree->children[6].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[6].tetrac->v1,ttree->children[6].tetrac->v2,ttree->children[6].tetrac->v3));

   p3Df_set(points[1],&(ttree->children[7].tetrac->v1));
   p3Df_set(points[5],&(ttree->children[7].tetrac->v2));
   p3Df_set(points[2],&(ttree->children[7].tetrac->v3));
   ttree->children[7].tetrac->sign = SIGNO(DET4D(ttree->centroid,ttree->children[7].tetrac->v1,ttree->children[7].tetrac->v2,ttree->children[7].tetrac->v3));
	nt = 0;
	//Inicializamos el proceso recursivo de construcción del tetra-tree.
	//Generamos el vector de referencias a triangulos
			vector<int> vtrian;
			for(int n=0; n<ttree->mMeshTT->faces.size(); n++)
				vtrian.push_back(n);
/*
	for(int i=0; i<8; i++){
		splitTetracone(&ttree->children[i],ttree->mMeshTT, ttree->centroid);
		removeMarkedTriangles(ttree->mMeshTT, -1);		
	}
*/

	//index_max = ttree->mMeshTT->points.size();
	//int max=0;
	//int valorparada;
	//for(int kil=0; kil<11; kil++) cases_used[kil] = 0;
	//nt_raros = 0;
	//nt_completos = 0;
	//nt_studio = 0;
	//printf("Index Max: %d\t Index.actual%d\n",index_max,ttree->mMeshTT->points.size());
	//int i;
	//for(i=0; i<7; i++) ptosint[i] = 0;
		    
   for(int i=0; i<8; i++){
	   	//printf("Generacion de hijos\t prof= %d\tmax= %d\n",deep,maxtri);
            generateTetraTreeExt(deep-1, maxTri-1,vtrian,&ttree->children[i],ttree->mMeshTT,ttree->centroid);
    }      

	ttree->ntet = nt;
	printf("Triangulos degenerados: %d\n",ndeg);
/*	printf("Numero de casos no solucionados: %d\n",nt_raros);
	for(i=0; i<7; i++){
		printf("Triangulos con %d puntos interseccion: %d\n",i,ptosint[i]);
		nt_studio+=ptosint[i];
	}
	printf("Numero de casos completos: %d\n", nt_completos);
	printf("Generados %d triangulos nuevos.\n",nnewtri);
	valorparada = nt_studio - nt_studio_old;
	
	int nft = 0;	 
	for(int n=0; n<ttree->mMeshTT->faces.size(); n++)
		if(ttree->mMeshTT->faces[n].itype != -1) nft++;
	printf("Malla Troceada: %d Triangulos - %d Puntos\n",nft,ttree->mMeshTT->points.size());
	 */
	/*
	tritoerase.clear();
	max++;
	for(int paso =0; paso < 11; paso++) printf("Caso %d: %d veces.\n",paso+1, cases_used[paso]);
	flag_nseg = 1;
	 */
	//saveOBJ(ttree->mMeshTT, "mallatroceada.obj");
	//saveTTMesh(ttree);	
	//Ajuste del tetratree a tetratree envolvente
	//wrapTetratree(ttree);
}
/*---------------------------------------------------------------------------*/
