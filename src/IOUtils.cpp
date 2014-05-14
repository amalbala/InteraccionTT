#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "IOUtils.h"

///Load mesh from OBJ file
/**
This function load a mesh from a OBJ file, the returns could be:
     0: Ok.
     1: No file found.     
*/


int loadOBJ(mesh *malla, char*filename){

   
   char type[2];
	int v13, v23,v33,v12,v22,v32;   
   p3Df vertex, v1,v2;
   triangle trian;
   FILE *f;

   f=fopen(filename,"r");

   if (!f) return (1);
   
   int vt=0;
   int vn=0;
   vertex.flag = -1;
   while (fscanf(f, "%s",type)!= EOF){

      if (strcmp(type,"v")==0){
            fscanf(f,"%f %f %f\n",&(vertex.x),&(vertex.y),&(vertex.z));
            malla->points.push_back(vertex);
            continue;
      }
      if (strcmp(type,"vn")==0){
            vn = 1;
            fscanf(f,"%f %f %f\n",&(vertex.x),&(vertex.y),&(vertex.z));
            malla->normals.push_back(vertex);
            continue;
      }
      if (strcmp(type,"vt")==0){
            vt = 1;
            fscanf(f,"%f %f %f\n",&(vertex.x),&(vertex.y),&(vertex.z));
            malla->textures.push_back(vertex);
            continue;
      }
      if (strcmp(type,"f")==0){
            if(vt == 0){
                  if(vn==0){
                        fscanf(f,"%d %d %d\n",&(trian.v0),&(trian.v1),&(trian.v2));

                  }else{                            
                        fscanf(f,"%d//%d %d//%d %d//%d\n",&(trian.v0),&v13,&(trian.v1),&v23,&(trian.v2),&v33);
                  }
            }else{
                  fscanf(f,"%d/%d/%d %d/%d/%d %d/%d/%d\n",&(trian.v0),&v12,&v13,&(trian.v1),&v22,&v23,&(trian.v2),&v32,&v33);
                  
            }
			trian.v0 -= 1;
			trian.v1 -= 1;
			trian.v2 -= 1;
		  	trian.itype = 0;			
            p3Df_resta(malla->points[trian.v1],malla->points[trian.v0],&v1);
            p3Df_resta(malla->points[trian.v2],malla->points[trian.v0],&v2);
            p3Df_norm(v1,v2,&(trian.norm));			
            malla->faces.push_back(trian);
            continue;
      }
   }
   fclose ( f );
   return 0;

}

int saveOBJ(mesh *malla, char* filename){
    FILE *f;
    f = fopen(filename, "w");
    
    fprintf(f,"g objeto_1\n\n");
    
    for(unsigned int i=0; i<malla->points.size(); i++){
            fprintf(f,"v %.6f %.6f %.6f\n",malla->points[i].x,malla->points[i].y,malla->points[i].z);
    }
    for(unsigned int i=0; i<malla->faces.size(); i++){
            fprintf(f,"f %d %d %d\n",malla->faces[i].v0+1,malla->faces[i].v1+1,malla->faces[i].v2+1);
    }
    fclose(f);
    
}
