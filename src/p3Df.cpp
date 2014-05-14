


#include <math.h>

#include "p3Df.h"



/*---------------------------------------------------------------------------*/
void p3Df_dist(float dist, p3Df* res, p3Df centro){
     
	p3Df temp;
	temp.x = (*res).x - centro.x;
	temp.y = (*res).y - centro.y;
	temp.z = (*res).z - centro.z;
	
    float mod = VECMOD(temp);
	
    res->x = (dist * (temp.x / mod)) + centro.x;
	res->y = (dist * (temp.y / mod)) + centro.y;
	res->z = (dist * (temp.z / mod)) + centro.z;
}

/*---------------------------------------------------------------------------*/
void p3Df_incentro(p3Df p1,p3Df p2,p3Df p3, p3Df *centro){

	float a,b,c,den;
	
	a = LONGSEG(p1,p2);
	b = LONGSEG(p1,p3);
	c = LONGSEG(p2,p3);
	den = a+b+c;
	
	centro->x = (a*p1.x + b*p2.x + c*p3.x)/den; 
	centro->y = (a*p1.y + b*p2.y + c*p3.y)/den; 
	centro->z = (a*p1.z + b*p2.z + c*p3.z)/den; 
		
}
/*---------------------------------------------------------------------------*/
int p3Df_testnulo(p3Df p1){
	if((p1.x == 0.0)&&(p1.y == 0.0)&&(p1.z == 0.0)) return 0;
	return 1;
}
/*---------------------------------------------------------------------------*/
float p3Df_angulo(p3Df v1, p3Df v2){
	float modA, modB, pe;
	

	pe = (v1.x * v2.x)+(v1.y * v2.y)+(v1.z * v2.z);

	modA = sqrt((v1.x * v1.x)+(v1.y * v1.y)+(v1.z * v1.z));
	modB = sqrt((v2.x * v2.x)+(v2.y * v2.y)+(v2.z * v2.z));
		
	return (pe/(modA*modB));
}
/*---------------------------------------------------------------------------*/
int p3Df_equal(p3Df p1, p3Df p2){
	if (p1.x < (p2.x+EPSILON) && p1.x > (p2.x-EPSILON) &&
	    p1.y < (p2.y+EPSILON) && p1.y > (p2.y-EPSILON) &&
	    p1.z < (p2.z+EPSILON) && p1.z > (p2.z-EPSILON)) return 0;
	return(1);
}