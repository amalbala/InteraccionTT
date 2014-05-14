
#include <math.h>
#include "inclussion.h"
#include "constants.h"


int intersect_Ray(p3Df r1, p3Df r2, trian T, float* alpha ){
	p3Df    u, v, n,temp,I;             // triangle vectors
    p3Df    dir, w0, w;          // ray vectors
    float     r, a, b;             // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    
	p3Df_resta(T.v1,T.v0,(&u));
	p3Df_resta(T.v2,T.v0,(&v));
	p3Df_cross(u,v,&n);
	if ((n.x == 0)&&(n.y == 0)&&(n.z == 0)) return -1;

	p3Df_resta(r2,r1,(&dir));
	p3Df_resta(r1,T.v0,(&w0));
    a = -DOT(n,w0);
    b = DOT(n,dir);
    if (fabs(b) < EPSILON) {    // ray is parallel to triangle plane
        if (a == 0){            // ray lies in triangle plane
            return 2;			
		}else{
			return 0;           // ray disjoint from plane			
		}
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if ((r < 0.0) || (r > 1.0))                   // ray goes away from triangle
        return 0;              // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect
	p3Df_prod(dir,r,(&temp));
	p3Df_suma(r1,temp,&I);

    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = DOT(u,u);
    uv = DOT(u,v);
    vv = DOT(v,v);
	p3Df_resta(I,T.v0,(&w));
    wu = DOT(w,u);
    wv = DOT(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = ((uv * wv) - (vv * wu)) / D;
    if ((s < 0.0) || (s > 1.0))        // I is outside T
        return 4;
    t = ((uv * wu) - (uu * wv)) / D;
    if ((t < 0.0) || ((s + t) > 1.0))  // I is outside T
        return 5;
	if((p3Df_equal(I,T.v0) == 0)||
	    (p3Df_equal(I,T.v1) == 0)||
	    (p3Df_equal(I,T.v2) == 0)) return 6;

                      // I is in T
	*alpha = r;
	return 1;
	
}

/*---------------------------------------------------------------------------*/
int intersect_RayTriangle(p3Df r1, p3Df r2, trian T, p3Df* I){
    p3Df    u, v, n,temp;             // triangle vectors
    p3Df    dir, w0, w;          // ray vectors
    float     r, a, b;             // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    
	p3Df_resta(T.v1,T.v0,(&u));
	p3Df_resta(T.v2,T.v0,(&v));
	p3Df_cross(u,v,&n);
	if ((n.x == 0)&&(n.y == 0)&&(n.z == 0)) return -1;

	p3Df_resta(r2,r1,(&dir));
	p3Df_resta(r1,T.v0,(&w0));
    a = -DOT(n,w0);
    b = DOT(n,dir);
    if (fabs(b) < EPSILON) {     // ray is parallel to triangle plane
        if (a == 0){                // ray lies in triangle plane
            return 2;			
		}else{
			return 3;             // ray disjoint from plane			
		}
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if ((r < 0.0) || (r > 1.0))                   // ray goes away from triangle
        return 0;                  // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

	p3Df_prod(dir,r,(&temp));
	p3Df_suma(r1,temp,I);

    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = DOT(u,u);
    uv = DOT(u,v);
    vv = DOT(v,v);
	p3Df_resta((*I),T.v0,(&w));
    wu = DOT(w,u);
    wv = DOT(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = ((uv * wv) - (vv * wu)) / D;
    if ((s < 0.0) || (s > 1.0))        // I is outside T
        return 4;
    t = ((uv * wu) - (uu * wv)) / D;
    if ((t < 0.0) || ((s + t) > 1.0))  // I is outside T
        return 5;
	
    return 1;                      // I is in T
}
/*---------------------------------------------------------------------------*/
int SegmentTriangleIntersection(trian tri, p3Df l1, p3Df l2, p3Df *info, p3Df *inters){


	p3Df e1, e2, p, s, q, ld, tp;
	float t, u, v, tmp;
	
	p3Df_resta(l1, l2,(&ld));
	p3Df_resta(tri.v1, tri.v0,(&e1));
	p3Df_resta(tri.v2, tri.v0, (&e2));
	p3Df_cross(ld, e2,&p);

	tmp = DOT(p,e1);

	if((tmp > -EPSILON)&&(tmp > EPSILON)) return 0;

	tmp = 1.0/tmp;

	p3Df_resta(l1, tri.v0, (&s));
	u = tmp * DOT(s,p);
	if(u<0.0 || u > 1.0) return 0;

	p3Df_cross(s, e1,(&q));
	v = tmp * DOT(ld,q);
	if(v<0.0 || v > 1.0) return 0;

	t = tmp * DOT(e2,q);

	info->x = u;
	info->y = v;
	info->z = t;

	p3Df_prod(ld, t,(&tp));
	p3Df_suma(l1, tp, inters);
	return 1;
	
}
/*---------------------------------------------------------------------------*/
int SegmentSegmentIntersection(p3Df p0, p3Df d0, p3Df p1, p3Df d1, p3Df *i){

	//segments 

	p3Df e;
	p3Df_resta(p1,p0,(&e));
	float kross = (d0.x * d1.y) - (d0.y * d1.x);
	//printf("Kross: %.2f\t",kross);
	float sqrkross = kross * kross;
	float sqrlen0 = (d0.x * d0.x) + (d0.y * d0.y);
	float sqrlen1 = (d1.x * d1.x) + (d1.y * d1.y);
	if(sqrkross < EPSILON * sqrlen0 * sqrlen1){
		//lines or segment are not parallel
		float s = (e.x * d1.y - e.y * d1.x)/kross;
		if((s < 0) || (s > 1)) //Intersection is not a point on p0+s*d0
			return 0;
		float t = (e.x * d0.y - e.y * d0.x)/kross;
		if((t < 0) || (t > 1)) //Intersection is not a point on p1+s*d1
			return 0;
		i->x = p0.x + (s * d0.x);
		i->y = p0.y + (s * d0.y);
		i->z = p0.z + (s * d0.z);
		return 1;
	}
	return 2;

}
//---------------------------------------------------------------------------
int calculateIntersectionLinePlane(plane *p, p3Df *p1, p3Df *p2, p3Df *intersec){

	p3Df vline,pnorm;
	float t;
	p3Df_resta((*p2),(*p1),(&vline));
	pnorm.x = p->alpha;
	pnorm.y = p->beta;
	pnorm.z = p->gamma;
	
	float denominator = DOT(vline, pnorm);

	if(fabs(denominator) < EPSILON){
		if(abs((p1->x*p->alpha)+(p1->y*p->beta)+(p1->z*p->gamma)+p->delta)<EPSILON){
			t = 0;
			return 0;
		}else{
			return 1;
		}
	}
	t = -((p1->x*p->alpha)+(p1->y*p->beta)+(p1->z*p->gamma)+p->delta);
	t = t / denominator;
	intersec->x = p1->x + (t * vline.x);
	intersec->y = p1->y + (t * vline.y);
	intersec->z = p1->z + (t * vline.z);
	return 0;
}

//---------------------------------------------------------------------------
/*
void calculateIntersectionLinePlane(plane *p, p3Df *p1, p3Df *p2, p3Df *intersec){
	p3Df vline;
	printf("restdores: ( %.2f,%.2f,%.2f)y( %.2f,%.2f,%.2f)\n",p1->x, p1->y, p1->z,
	    p2->x,p2->y,p2->z);
	p3Df_resta(*p2,*p1,&vline);
	printf("dif: ( %.4f,%.4f,%.4f)\t",vline.x, vline.y, vline.z);
	printf("-(((%.2f) + (%.2f) + (%.2f) + %.2f)/((%.2f) + (%.2f) +(%.2f)))\n",
	    (p->alpha*p1->x),(p->beta*p1->y),(p->gamma*p1->z),(p->delta),
	    (p->alpha*vline.x),(p->beta*vline.y),(p->gamma*vline.z));
	float d = DISTPLANE(p->alpha, p->beta, p->gamma, p->delta,(*p1),vline);
	//printf("Dist: %.2f\t",d);
	intersec->x = p1->x + (d * vline.x);
	intersec->y = p1->y + (d * vline.y);
	intersec->z = p1->z + (d * vline.z);
	
}
*/
