
#include <math.h>
#include "splittriangles.h"

/*---------------------------------------------------------------------------*/
int sortPointsSide(int *p1, int *p2, int ptoinilado, mesh * malla){

	float da, db;
	int tmp;

	da = DIST3D(malla->points[(*p1)],malla->points[ptoinilado]);
	db = DIST3D(malla->points[(*p2)],malla->points[ptoinilado]);
	if(db < da){
		tmp = (*p2);
		(*p2) = (*p1);
		(*p1) = tmp;		
	}	
}
/*---------------------------------------------------------------------------*/
int splitpattern_case11(int id_t, mesh *m, p3Df inters1,p3Df inters2,p3Df inters3,p3Df inters4, int ladodoble, vector<int> *newtottc){

	int i1,i2,i3,i4,t1,t2,t3,newp,tmp;
	float da,db;
	triangle t;
	t.itype = 0;

	t1 = m->faces[id_t].v0;
	t2 = m->faces[id_t].v1;
	t3 = m->faces[id_t].v2;

	
	m->points.push_back(inters1);
	m->points.push_back(inters2);
	m->points.push_back(inters3);
	m->points.push_back(inters4);
	
	i1 = m->points.size()-4;
	i2 = m->points.size()-3;
	i3 = m->points.size()-2;
	i4 = m->points.size()-1;
	
	switch(ladodoble){
		case 1: 
			sortPointsSide(&i1, &i2, t1,m);
			t.v0 = t3;
			t.v1 = i4;
			t.v2 = i1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v1 = i1;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v1 = i2;
			t.v2 = i3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v0 = i2;
			t.v1 = t2;
			t.v2 = i3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v0 = i4;
			t.v1 = t1;
			t.v2 = i1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;
		case 2: 
			sortPointsSide(&i2, &i3, t2,m);
			t.v0 = t1;
			t.v1 = i1;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v1 = i2;
			t.v2 = i3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v1 = i3;
			t.v2 = i4;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v0 = i1;
			t.v1 = t2;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v0 = i4;
			t.v1 = i3;
			t.v2 = t2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;
		case 3: 
			sortPointsSide(&i3, &i4, t3,m);
			t.v0 = t1;
			t.v1 = i2;
			t.v2 = i3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v1 = i3;
			t.v2 = i4;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v1 = i4;
			t.v2 = i1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);			
			t.v0 = i2;
			t.v1 = t3;
			t.v2 = i3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v0 = i1;
			t.v1 = i4;
			t.v2 = t1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;
	}	
		
}
/*---------------------------------------------------------------------------*/
int splitpattern_case7(int id_t, mesh *m, p3Df inters1,p3Df inters2, p3Df inters3,p3Df inters4, int lado1, int lado2, vector<int> *newtottc){

	int i1,i2,i3,i4,t1,t2,t3,newp,tmp;
	float da,db;
	triangle t;

	t.itype = 0;

	t1 = m->faces[id_t].v0;
	t2 = m->faces[id_t].v1;
	t3 = m->faces[id_t].v2;

	
	m->points.push_back(inters1);
	m->points.push_back(inters2);
	m->points.push_back(inters3);
	m->points.push_back(inters4);
	
	i1 = m->points.size()-4;
	i2 = m->points.size()-3;
	i3 = m->points.size()-2;
	i4 = m->points.size()-1;
	switch(lado1){
		case 1: 
			sortPointsSide(&i1, &i2, t1,m);
			break;
		case 2: 
			sortPointsSide(&i1, &i2, t2,m);
			break;
		case 3: 
			sortPointsSide(&i1, &i2, t3,m);
			break;
	}
	switch(lado2){
		case 1: 
			sortPointsSide(&i3, &i4, t1,m);
			break;
		case 2: 
			sortPointsSide(&i3, &i4, t2,m);
			break;
		case 3: 
			sortPointsSide(&i3, &i4, t3,m);
			break;
	}

	t.itype = 0;

	switch(lado1){
		case 1:
			if(lado2 == 2){
				t.v0 = i1;
				t.v1 = i2;
				t.v2 = i3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = i3;
				t.v2 = i4;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = i4;
				t.v2 = t3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);			
				t.v1 = t3;
				t.v2 = t1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);			
				t.v0 = i2;
				t.v1 = t2;
				t.v2 = i3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);			
			}else{
				t.v0 = i2;
				t.v1 = i3;
				t.v2 = i4;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = i4;
				t.v2 = i1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = t2;
				t.v2 = t3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);			
				t.v1 = t3;
				t.v2 = i3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);			
				t.v0 = i1;
				t.v1 = i4;
				t.v2 = t1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);							
			}
			break;
		case 2:
				t.v0 = i1;
				t.v1 = i2;
				t.v2 = i3;
  				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = i3;
				t.v2 = i4;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = i4;
				t.v2 = t1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);			
				t.v1 = t1;
				t.v2 = t2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);			
				t.v0 = i2;
				t.v1 = t2;
				t.v2 = i3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);			
			break;
	}
	
}
/*---------------------------------------------------------------------------*/
int splitpattern_case8(int id_t, mesh *m, p3Df inters1,p3Df inters2, p3Df ptointTT, int ptoint, vector<int> *newtottc){

	// printf("Entrando en caso 2\n");

	int i1,i2,t1,t2,t3,newp;
	triangle t;
	t.itype = 0;

	t1 = m->faces[id_t].v0;
	t2 = m->faces[id_t].v1;
	t3 = m->faces[id_t].v2;

	m->points.push_back(ptointTT);
	m->points.push_back(inters1);
	m->points.push_back(inters2);
	
	newp = m->points.size()-3;
	i1 = m->points.size()-2;
	i2 = m->points.size()-1;
	
	t.v0= newp;
	t.itype = 0;

	switch(ptoint){
		case 0: 
			t.v1 = t1;
			t.v2 = i1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);
			t.v1 = i2;
			t.v2 = t1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);
			t.v1 = i1;
			t.v2 = t2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1 = t2;
			t.v2 = t3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1 = t3;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;
		case 1:
			t.v1 = t2;
			t.v2 = i1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);
			t.v1 = i2;
			t.v2 = t2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);
			t.v1 = i1;
			t.v2 = t3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1 = t3;
			t.v2 = t1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1 = t1;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;
		case 2:
			t.v1 = t3;
			t.v2 = i1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);
			t.v1 = i2;
			t.v2 = t3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);
			t.v1 = i1;
			t.v2 = t1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1 = t1;
			t.v2 = t2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1 = t2;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;
	}
}
/*---------------------------------------------------------------------------*/
int splitpattern_case4(int id_t, mesh *m, p3Df inters1,p3Df inters2, int lado1, int lado2, vector<int> *newtottc){
	// printf("Entrando en caso 2\n");

	
	int i1,i2,t1,t2,t3;
	triangle t;
	t.itype = 0;

	t1 = m->faces[id_t].v0;
	t2 = m->faces[id_t].v1;
	t3 = m->faces[id_t].v2;

	m->points.push_back(inters1);
	m->points.push_back(inters2);

	i1 = m->points.size()-2;
	i2 = m->points.size()-1;
	
	t.v0= i1;
	t.itype = 0;
	
	//Determinamos la posicion de los puntos de intereseccion
	switch(lado1){
		case 1:
			if(lado2 == 3){
				t.v1 = t2;
				t.v2 = t3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = t3;
				t.v2 = i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = i2;
				t.v2 = t1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}else{
				t.v1 = t3;
				t.v2 = t1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = i2;
				t.v2 = t3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = t2;
				t.v2 = i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}				
			break;
				
		case 2:
			t.v1 = t1;
			t.v2 = t2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);
			t.v1 = i2;
			t.v2 = t1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1 = t3;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;		
	}
	
}
/*---------------------------------------------------------------------------*/
int splitpattern_case3(int id_t, mesh *m, p3Df inters1,p3Df inters2, int lado1, int lado2, vector<int> *newtottc){
	// printf("Entrando en caso 2\n");

	int i1,i2,t1,t2,t3;

	triangle t;
	t.itype = 0;

	t1 = m->faces[id_t].v0;
	t2 = m->faces[id_t].v1;
	t3 = m->faces[id_t].v2;
	
	m->points.push_back(inters1);
	m->points.push_back(inters2);

	i1 = m->points.size()-2;
	i2 = m->points.size()-1;
	
	t.itype = 0;
	t.v0 = i1;
	//Determinamos la posicion de los puntos de intereseccion
	switch(lado1){
		case 1: 
			if(lado2 == 2){
				t.v1 = t2;
				t.v2 = i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = i2;
				t.v2 = t3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1 = t3;
				t.v2 = t1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}else{
				t.v1 = i2;
				t.v2 = t1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1 = t3;
				t.v2 = i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1 = t2;
				t.v2 = t3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
			}
			break;
		case 2:
			t.v1 = t3;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			newtottc->push_back(m->faces.size()-1);
			t.v1 = i2;
			t.v2 = t1;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1 = t1;
			t.v2 = t2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;		
	}
}
			
			
/*---------------------------------------------------------------------------*/
int splitpattern_case1(int id_t, mesh *m, p3Df pto_int, p3Df inters1,p3Df inters2, int lado, vector<int> *newtottc){

	p3Df ta, tb;
	int newp,i1,i2,t1,t2,t3;
	float da, db;
	triangle t;
	t.itype = 0;
	
	t1 = m->faces[id_t].v0;
	t2 = m->faces[id_t].v1;
	t3 = m->faces[id_t].v2;

	m->points.push_back(pto_int);
	m->points.push_back(inters1);
	m->points.push_back(inters2);
	newp = m->points.size()-3;
	i1 = m->points.size()-2;
	i2 = m->points.size()-1;
	
	t.v0= newp;
	t.itype = 0;
	//Determinamos la posicion de los puntos de intereseccion
	switch(lado){
		case 1:
			da = DIST3D(inters1,m->points[t1]);
			db = DIST3D(inters2,m->points[t1]);
			if(da>db){
				t.v1= i2;  
				t.v2= i1;	
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
				newtottc->push_back(m->faces.size()-1);
				t.v1= i1;  
				t.v2= t2;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t1;  
				t.v2= i2;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
			}else{
				t.v1= i1;  
				t.v2= i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i2;  
				t.v2= t2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t1;  
				t.v2= i1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}
			t.v1= t2;  
			t.v2= t3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1= t3;  
			t.v2= t1;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);	
			
			break;
		case 2:
			da = DIST3D(inters1,m->points[t2]);
			db = DIST3D(inters2,m->points[t2]);
			if(da>db){
				t.v1= i2;  
				t.v2= i1;		
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i1;  
				t.v2= t3;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t2;  
				t.v2= i2;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
			}else{
				t.v1= i1;  
				t.v2= i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i2;  
				t.v2= t3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t2;  
				t.v2= i1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}
			t.v1= t3;  
			t.v2= t1;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1= t1;  
			t.v2= t2;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);			
			break;
		case 3:
			da = DIST3D(inters1,m->points[t3]);
			db = DIST3D(inters2,m->points[t3]);
			if(da>db){
				t.v1= i2;  
				t.v2= i1;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i1;  
				t.v2= t1;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t3;  
				t.v2= i2;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
			}else{
				t.v1= i1;  
				t.v2= i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i2;  
				t.v2= t1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t3;  
				t.v2= i1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}
			t.v1= t1;  
			t.v2= t2;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1= t2;  
			t.v2= t3;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);			
			break;
	}	
}
/*---------------------------------------------------------------------------*/
int splitpattern_case2(int id_t, mesh *m, p3Df pto_int1,p3Df pto_int2, p3Df inters1,p3Df inters2, int lado, vector<int> *newtottc){
	
	p3Df ta, tb;
	int newp,i1,i2,t1,t2,t3;
	float da, db;
	triangle t;
	t.itype = 0;
	
	t1 = m->faces[id_t].v0;
	t2 = m->faces[id_t].v1;
	t3 = m->faces[id_t].v2;

	m->points.push_back(pto_int1);
	m->points.push_back(pto_int2);
	m->points.push_back(inters1);
	m->points.push_back(inters2);
	newp = m->points.size()-3;
	i1 = m->points.size()-2;
	i2 = m->points.size()-1;
	
	t.v0= newp;
	t.itype = 0;
	//Determinamos la posicion de los puntos de intereseccion
	switch(lado){
		case 1:
			da = DIST3D(inters1,m->points[t1]);
			db = DIST3D(inters2,m->points[t1]);
			if(da>db){
				t.v1= i2;  
				t.v2= i1;	
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
				newtottc->push_back(m->faces.size()-1);
				t.v1= i1;  
				t.v2= t2;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t1;  
				t.v2= i2;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
			}else{
				t.v1= i1;  
				t.v2= i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i2;  
				t.v2= t2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t1;  
				t.v2= i1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}
			t.v1= t2;  
			t.v2= t3;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1= t3;  
			t.v2= t1;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);	
			
			break;
		case 2:
			da = DIST3D(inters1,m->points[t2]);
			db = DIST3D(inters2,m->points[t2]);
			if(da>db){
				t.v1= i2;  
				t.v2= i1;		
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i1;  
				t.v2= t3;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t2;  
				t.v2= i2;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
			}else{
				t.v1= i1;  
				t.v2= i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i2;  
				t.v2= t3;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t2;  
				t.v2= i1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}
			t.v1= t3;  
			t.v2= t1;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1= t1;  
			t.v2= t2;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);			
			break;
		case 3:
			da = DIST3D(inters1,m->points[t3]);
			db = DIST3D(inters2,m->points[t3]);
			if(da>db){
				t.v1= i2;  
				t.v2= i1;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i1;  
				t.v2= t1;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t3;  
				t.v2= i2;				
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);				
			}else{
				t.v1= i1;  
				t.v2= i2;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				newtottc->push_back(m->faces.size()-1);
				t.v1= i2;  
				t.v2= t1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
				t.v1= t3;  
				t.v2= i1;
				p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
				m->faces.push_back(t);
			}
			t.v1= t1;  
			t.v2= t2;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v1= t2;  
			t.v2= t3;				
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);			
			break;
	}	
	
}
/*---------------------------------------------------------------------------*/
int splitpattern_case5(int id_t, mesh *m, p3Df pto_int1,p3Df pto_int2,p3Df pto_int3,p3Df pto_int4,p3Df pto_int5,p3Df pto_int6,int lado,vector<int> *newtottc){

	p3Df ta, tb;
	int i1,i2,i3,i4,i5,i6,t1,t2,t3;
	float da, db;
	triangle t;
	t.itype = 0;
	
	t1 = m->faces[id_t].v0;
	t2 = m->faces[id_t].v1;
	t3 = m->faces[id_t].v2;

	m->points.push_back(pto_int1);
	i1 = m->points.size()-1;
	m->points.push_back(pto_int2);
	i2 = m->points.size()-1;
	m->points.push_back(pto_int3);
	i3 = m->points.size()-1;
	m->points.push_back(pto_int4);
	i4 = m->points.size()-1;
	m->points.push_back(pto_int5);
	i5 = m->points.size()-1;
	m->points.push_back(pto_int6);
	i6 = m->points.size()-1;
	
	
	
	switch(lado){
		case 1:
			t.v0 = i1;
			t.v1 = t1;
			t.v2 = i2;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			//newtottc->push_back(m->faces.size()-1);
			t.v0 = i3;
			t.v1 = t2;
			t.v2 = i4;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			t.v0 = i5;
			t.v1 = t3;
			t.v2 = i6;
			p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
			m->faces.push_back(t);
			break;
		case 2:
			break;
		case 3:
			break;
	}
	t.v0 = i1;
	t.v1 = i2;
	t.v2 = i3;
	p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
	m->faces.push_back(t);
	newtottc->push_back(m->faces.size()-1);
	t.v0 = i1;
	t.v1 = i3;
	t.v2 = i4;
	p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
	m->faces.push_back(t);
	newtottc->push_back(m->faces.size()-1);
	t.v0 = i1;
	t.v1 = i4;
	t.v2 = i5;
	p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
	m->faces.push_back(t);
	newtottc->push_back(m->faces.size()-1);
	t.v0 = i1;
	t.v1 = i5;
	t.v2 = i6;
	p3Df_norm2(m->points[t.v0],m->points[t.v1],m->points[t.v2], &(t.norm));
	m->faces.push_back(t);
	newtottc->push_back(m->faces.size()-1);

}
	

	