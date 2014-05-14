#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "tetratree.h"
#include "geometry.h"
#include "IOUtils.h"
#include "constants.h"

#define MALLA "skull.obj"
#define DEPTHTT 5
#define MAXTRIAN 8


clock_t tiempo1, tiempo2;
double tiempo;
tetratree tt;

/*
#include <HL/hl.h>
#include <HDU/hduMatrix.h>
#include <HDU/hduError.h>

#include <HLU/hlu.h>

#define CURSOR_SIZE_PIXELS 20

static HHD hHD = HD_INVALID_HANDLE;
static HHLRC hHLRC = 0;

HLuint gMallaShapeID = 0;
HLuint gTTShapeID = 0; 
HLuint gTActivoID = 0;


static double gCursorScale;
static GLuint gCursorDisplayList = 0;


nodeTT *tttouch = NULL;
int mWindW,mWindH;
int ef;


//Function prototypes. 
void glutDisplay(void);
void glutReshape(int width, int height);
void glutIdle(void);
void glutMenu(int);

void exitHandler(void);

void initGL();
void initHL();
void initScene();
void drawSceneHaptics();
void drawSceneGraphics();
void drawCursor();
void updateWorkspace();
double DetermineFPS();
void DisplayInfo();

void initMesh();
void HLCALLBACK touchShapeCallback(HLenum event, HLuint object, HLenum thread, 
                                   HLcache *cache, void *userdata)
{
    hduVector3Dd proxy;
    std::cout << "Tocado Objeto: " << object << " en posicion ";
    hlCacheGetDoublev(cache, HL_PROXY_POSITION, proxy);
    std::cout << proxy << " ";
    HLboolean buttDown;
    hlCacheGetBooleanv(cache, HL_BUTTON1_STATE, &buttDown);
    std::cout << "boton 1 " << (buttDown ? "presionado" : "libre") << std::endl;
}

void HLCALLBACK untouchShapeCallback(HLenum event, HLuint object, HLenum thread, 
                                     HLcache *cache, void *userdata)
{
    hduVector3Dd proxy;
    std::cout << "Abandonado Objeto: " << object << std::endl;
}

void HLCALLBACK touchMallaCallback(HLenum event, HLuint object, HLenum thread, 
                                    HLcache *cache, void *userdata)
{
    std::cout << "Malla Alcanzada." << std::endl;
}
void HLCALLBACK touchTTCallback(HLenum event, HLuint object, HLenum thread, 
                                    HLcache *cache, void *userdata)
{
    std::cout << "Tetratree Alcanzado." << std::endl;
}


void HLCALLBACK untouchMallaCallback(HLenum event, HLuint object, HLenum thread, 
                                      HLcache *cache, void *userdata)
{
    std::cout << "Malla Abandonada." << std::endl;
}
void HLCALLBACK untouchTTCallback(HLenum event, HLuint object, HLenum thread, 
                                      HLcache *cache, void *userdata)
{
    std::cout << "Tetratree Abandonada." << std::endl;
}

void HLCALLBACK button1DownCallback(HLenum event, HLuint object, HLenum thread, 
                                    HLcache *cache, void *userdata)
{
    std::cout << "Button 1 down" << std::endl;

}

void HLCALLBACK button1UpCallback(HLenum event, HLuint object, HLenum thread, 
                                  HLcache *cache, void *userdata)
{
    std::cout << "Button 1 up" << std::endl;

}

void HLCALLBACK button2DownCallback(HLenum event, HLuint object, HLenum thread, 
                                    HLcache *cache, void *userdata)
{
    std::cout << "Button 2 down" << std::endl;
}

void HLCALLBACK button2UpCallback(HLenum event, HLuint object, HLenum thread, 
                                  HLcache *cache, void *userdata)
{
    std::cout << "Button 2 up" << std::endl;
}

//Rutina
void tTocado(nodeTT *t, p3Df centroid,p3Df p){
		if(t->children == NULL){
			if(tetraPoint(centroid,t->tetrac->v1,t->tetrac->v2,t->tetrac->v3,p,t->tetrac->sign)==COLIS){
				ef = COLIS;
				tttouch = t;			
			}else{
				if(tetraPoint(centroid,t->tetrac->v1,t->tetrac->v2,t->tetrac->v3,p,t->tetrac->sign)==IN){
					ef = IN;
					tttouch = t;			
				}
			}
	    }else{
			for(int i=0; i<4; i++){
				tTocado(&(t->children[i]),centroid,p);
				if(tttouch != NULL) break;
			}
		}
}

void HLCALLBACK motionCallback(HLenum event, HLuint object, HLenum thread, 
                               HLcache *cache, void *userdata)
{
    
	hduVector3Dd proxy;
	hlCacheGetDoublev(cache, HL_PROXY_POSITION, proxy);
	p3Df p;
	p.x = proxy[0];
	p.y = proxy[1];
	p.z = proxy[2];
	tttouch = NULL;	
	for(int i=0; i<8; i++){
		tTocado(&(tt.children[i]),tt.centroid,p);
	}
	
}

void HLCALLBACK motionOnMallaCallback(HLenum event, HLuint object, HLenum thread, 
                                       HLcache *cache, void *userdata)
{
    std::cout << "Recorriendo Malla." << std::endl;
}

void HLCALLBACK motionOnTTCallback(HLenum event, HLuint object, HLenum thread, 
                                       HLcache *cache, void *userdata)
{
    std::cout << "Recorriendo Tetratree." << std::endl;
}

void HLCALLBACK calibrationCallback(HLenum event, HLuint object, HLenum thread, 
                                    HLcache *cache, void *userdata)
{
    if (event == HL_EVENT_CALIBRATION_UPDATE)
    {
        std::cout << "Device requires calibration update..." << std::endl;
        hlUpdateCalibration();        
    }
    else if (event == HL_EVENT_CALIBRATION_INPUT)
    {
        std::cout << "Device requires calibration.input..." << std::endl;
    }
	
}

//*******************************************************************************
// Initializes GLUT for displaying a simple haptic scene.
//*******************************************************************************
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Tetra-tree");
	initMesh();

    // Set glut callback functions.
    glutDisplayFunc(glutDisplay);
    glutReshapeFunc(glutReshape);
    glutIdleFunc(glutIdle);
    
    glutCreateMenu(glutMenu);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);    
    
    // Provide a cleanup routine for handling application exit.
    atexit(exitHandler);

    initScene();

    glutMainLoop();

    return 0;
}

//******************************************************************************
// GLUT callback for redrawing the view.
//******************************************************************************
void glutDisplay(){    
    drawSceneHaptics();
    drawSceneGraphics();
    glutSwapBuffers();
}

//*******************************************************************************
// GLUT callback for reshaping the window.  This is the main place where the 
// viewing and workspace transforms get initialized.
//*******************************************************************************
void glutReshape(int width, int height)
{
    static const double kPI = 3.1415926535897932384626433832795;
    static const double kFovY = 40;

    double nearDist, farDist, aspect;

    glViewport(0, 0, width, height);
	mWindW = width;
	mWindH = height;

    // Compute the viewing parameters based on a fixed fov and viewing
    // a canonical box centered at the origin.

    nearDist = 1.0 / tan((kFovY / 2.0) * kPI / 180.0);
    farDist = nearDist + 1000.0;
    aspect = (double) width / height;
   
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(kFovY, aspect, nearDist, farDist);

    // Place the camera down the Z axis looking at the origin.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();            
    gluLookAt(500,500, nearDist + 0.0,
              0, 0, 0,
              0, 0,1);
    
    updateWorkspace();
}

//*******************************************************************************
// GLUT callback for idle state.  Use this as an opportunity to request a redraw.
// Checks for HLAPI errors that have occurred since the last idle check.
//*******************************************************************************
void glutIdle()
{
    HLerror error;

    while (HL_ERROR(error = hlGetError()))
    {
        fprintf(stderr, "HL Error: %s\n", error.errorCode);
        
        if (error.errorCode == HL_DEVICE_ERROR)
        {
            hduPrintError(stderr, &error.errorInfo,
                "Error during haptic rendering\n");
        }
    }
    
    glutPostRedisplay();
}

//******************************************************************************
//Popup menu handler
//******************************************************************************
void glutMenu(int ID)
{
    switch(ID) {
        case 0:
            exit(0);
            break;
    }
}

//*******************************************************************************
// This handler is called when the application is exiting.  Deallocates any state 
// and cleans up.
//*******************************************************************************
void exitHandler()
{
    // Remove event callbacks.
    hlRemoveEventCallback(HL_EVENT_TOUCH, gMallaShapeID, 
        HL_CLIENT_THREAD, touchMallaCallback);
    hlRemoveEventCallback(HL_EVENT_UNTOUCH, gMallaShapeID, 
        HL_CLIENT_THREAD, untouchMallaCallback);
	  hlRemoveEventCallback(HL_EVENT_TOUCH, gTTShapeID, 
        HL_CLIENT_THREAD, touchTTCallback);
    hlRemoveEventCallback(HL_EVENT_UNTOUCH, gTTShapeID, 
        HL_CLIENT_THREAD, untouchTTCallback);
  
    hlRemoveEventCallback(HL_EVENT_CALIBRATION_UPDATE, HL_OBJECT_ANY,
        HL_CLIENT_THREAD, calibrationCallback);                       
    hlRemoveEventCallback(HL_EVENT_CALIBRATION_INPUT, HL_OBJECT_ANY,
        HL_CLIENT_THREAD, calibrationCallback);                       

    // Deallocate the shape ids we reserved in initHL.
    hlDeleteShapes(gMallaShapeID, 1);
    hlDeleteShapes(gTTShapeID, 1);    

    // Free up the haptic rendering context.
    hlMakeCurrent(NULL);
    if (hHLRC != NULL)
    {
        hlDeleteContext(hHLRC);
    }

    // Free up the haptic device.
    if (hHD != HD_INVALID_HANDLE)
    {
        hdDisableDevice(hHD);
    }
}

//*******************************************************************************
// Initializes the scene.  Handles initializing both OpenGL and HL.
//*******************************************************************************
void initScene()
{
    initGL();
    initHL();
}

//*******************************************************************************
// Sets up general OpenGL rendering properties: lights, depth buffering, etc.
//*******************************************************************************
void initGL()
{
    static const GLfloat light_model_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    static const GLfloat light0_diffuse[] = {0.9f, 0.9f, 0.9f, 0.9f};   
    static const GLfloat light0_direction[] = {1.0f, 0.0f, 100.0f, 0.0f};    
	static const GLfloat light0_specular[]={1.0, 1.0, 1.0, 1.0};
	    
    // Enable depth buffering for hidden surface removal.
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    
    // Cull back faces.
   // glCullFace(GL_BACK);
   // glEnable(GL_CULL_FACE);
    
    // Setup other misc features.
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    // Setup lighting model.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glEnable(GL_LIGHT0);   
}

//*******************************************************************************
// Initialize the HDAPI.  This involves initing a device configuration, enabling
// forces, and scheduling a haptic thread callback for servicing the device.
//*******************************************************************************
void initHL()
{
    HDErrorInfo error;

    hHD = hdInitDevice(HD_DEFAULT_DEVICE);
    if (HD_DEVICE_ERROR(error = hdGetError()))
    {
        hduPrintError(stderr, &error, "Failed to initialize haptic device");
        fprintf(stderr, "Press any key to exit");
        getchar();
        exit(-1);
    }
    
    hHLRC = hlCreateContext(hHD);
    hlMakeCurrent(hHLRC);

    // Enable optimization of the viewing parameters when rendering
    // geometry for OpenHaptics.
    hlEnable(HL_HAPTIC_CAMERA_VIEW);

    // Generate id's for the three shapes.
    gMallaShapeID = hlGenShapes(1);
	gTTShapeID = hlGenShapes(1);
	gTActivoID = hlGenShapes(1);

    // Setup event callbacks.
    hlAddEventCallback(HL_EVENT_TOUCH, HL_OBJECT_ANY, HL_CLIENT_THREAD, 
                       &touchShapeCallback, NULL);
    hlAddEventCallback(HL_EVENT_UNTOUCH, HL_OBJECT_ANY, HL_CLIENT_THREAD, 
                       &untouchShapeCallback, NULL);
    hlAddEventCallback(HL_EVENT_TOUCH, gMallaShapeID, HL_CLIENT_THREAD, 
                       &touchMallaCallback, NULL);
    hlAddEventCallback(HL_EVENT_UNTOUCH, gMallaShapeID, HL_CLIENT_THREAD, 
                       &untouchMallaCallback, NULL);
	hlAddEventCallback(HL_EVENT_TOUCH, gTTShapeID, HL_CLIENT_THREAD, 
                       &touchTTCallback, NULL);
    hlAddEventCallback(HL_EVENT_UNTOUCH, gTTShapeID, HL_CLIENT_THREAD, 
                       &untouchTTCallback, NULL);
    
    hlAddEventCallback(HL_EVENT_1BUTTONDOWN, HL_OBJECT_ANY, HL_CLIENT_THREAD, 
                       &button1DownCallback, NULL);
    hlAddEventCallback(HL_EVENT_1BUTTONUP, HL_OBJECT_ANY, HL_CLIENT_THREAD, 
                       &button1UpCallback, NULL);
    hlAddEventCallback(HL_EVENT_2BUTTONDOWN, HL_OBJECT_ANY, HL_CLIENT_THREAD, 
                       &button2DownCallback, NULL);
    hlAddEventCallback(HL_EVENT_2BUTTONUP, HL_OBJECT_ANY, HL_CLIENT_THREAD, 
                       &button2UpCallback, NULL);
    hlAddEventCallback(HL_EVENT_MOTION, HL_OBJECT_ANY, HL_CLIENT_THREAD, 
                       &motionCallback, NULL);
    hlAddEventCallback(HL_EVENT_MOTION, gMallaShapeID, HL_CLIENT_THREAD, 
                       &motionOnMallaCallback, NULL);
	hlAddEventCallback(HL_EVENT_MOTION, gTTShapeID, HL_CLIENT_THREAD, 
                       &motionOnTTCallback, NULL);
    hlAddEventCallback(HL_EVENT_CALIBRATION_UPDATE, HL_OBJECT_ANY,
                       HL_CLIENT_THREAD, &calibrationCallback, NULL);                       
    hlAddEventCallback(HL_EVENT_CALIBRATION_INPUT, HL_OBJECT_ANY,
                       HL_CLIENT_THREAD, &calibrationCallback, NULL);                       
}

//*******************************************************************************
// Uss the current OpenGL viewing transforms to initialize a transform for the
// haptic device workspace so that it's properly mapped to world coordinates.
//*******************************************************************************
void updateWorkspace()
{
    GLdouble modelview[16];
    GLdouble projection[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    hlMatrixMode(HL_TOUCHWORKSPACE);
    hlLoadIdentity();
    
    // Fit haptic workspace to view volume.
    hluFitWorkspace(projection);

    // Compute cursor scale.
    gCursorScale = hluScreenToModelScale(modelview, projection, viewport);
    gCursorScale *= CURSOR_SIZE_PIXELS;
}

void drawActuador(mesh* malla){
	glPushMatrix();
	GLfloat mat_ambient[]={0.2, 0.2, 0.2, 1.0};
	GLfloat mat_diffuse[]={1.0, 1.0, 0.8, 1.0};
	GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glBegin(GL_TRIANGLES);
	
	for(int i=0; i<malla->faces.size(); i++){
		glNormal3f(malla->faces[i].norm.x,malla->faces[i].norm.y,malla->faces[i].norm.z);
   		glVertex3f(malla->points[malla->faces[i].v0].x, malla->points[malla->faces[i].v0].y,malla->points[malla->faces[i].v0].z);
		glVertex3f(malla->points[malla->faces[i].v1].x, malla->points[malla->faces[i].v1].y,malla->points[malla->faces[i].v1].z);
		glVertex3f(malla->points[malla->faces[i].v2].x, malla->points[malla->faces[i].v2].y,malla->points[malla->faces[i].v2].z);	
	}
	glEnd();
	glPopMatrix();

}

void drawMalla(){
	
	glPushMatrix();
	
	GLfloat mat_ambient[]={0.2, 0.2, 0.2, 1.0};
	GLfloat mat_diffuse[]={1.0, 1.0, 0.8, 1.0};
	GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	
	glBegin(GL_TRIANGLES);
	
	for(int i=0; i<tt.mMeshTT->faces.size(); i++){
		glNormal3f(tt.mMeshTT->faces[i].norm.x,tt.mMeshTT->faces[i].norm.y,tt.mMeshTT->faces[i].norm.z);
   		glVertex3f(tt.mMeshTT->points[tt.mMeshTT->faces[i].v0].x, tt.mMeshTT->points[tt.mMeshTT->faces[i].v0].y,tt.mMeshTT->points[tt.mMeshTT->faces[i].v0].z);
		glVertex3f(tt.mMeshTT->points[tt.mMeshTT->faces[i].v1].x, tt.mMeshTT->points[tt.mMeshTT->faces[i].v1].y,tt.mMeshTT->points[tt.mMeshTT->faces[i].v1].z);
		glVertex3f(tt.mMeshTT->points[tt.mMeshTT->faces[i].v2].x, tt.mMeshTT->points[tt.mMeshTT->faces[i].v2].y,tt.mMeshTT->points[tt.mMeshTT->faces[i].v2].z);	
	}
	glEnd();
	glPopMatrix();	
}

void drawTT(nodeTT t, int mode){
	if(t.children == NULL){
		glBegin(mode);	
			glVertex3f(t.tetrac->v1.x,t.tetrac->v1.y,t.tetrac->v1.z);
			glVertex3f(t.tetrac->v2.x,t.tetrac->v2.y,t.tetrac->v2.z);
			glVertex3f(t.tetrac->v3.x,t.tetrac->v3.y,t.tetrac->v3.z);		
		glEnd();
	}else{
		for(int i=0; i<4; i++) drawTT(t.children[i],mode);
	}
		
}

void drawTTLine(){
	glPushMatrix();
	glLineWidth(1);
	glColor3f(1.0,0.0,0.0);		
	for(int i=0; i<8; i++){		
		drawTT(tt.children[i],GL_LINE_LOOP);
	}	
	glPopMatrix();	
}

void drawTTSolid(){
	glPushMatrix();
	for(int i=0; i<8; i++){		
		drawTT(tt.children[i],GL_TRIANGLES);
	}	
	glPopMatrix();	
	
}

void drawTC(nodeTT *t,int mode){
	if(t!= NULL){
		glPushMatrix();
		GLfloat mat_diffuse[4];
	
		GLfloat mat_ambient[]={0.2, 0.2, 0.2, 1.0};
		if(mode == IN){ 			
			mat_diffuse[0] = 1.0;
			mat_diffuse[1] = 0.0;
			mat_diffuse[2] = 0.0;
			mat_diffuse[3] = 1.0;
				
		}
		if(mode == COLIS){
			mat_diffuse[0] = 0.0;
			mat_diffuse[1] = 0.5;
			mat_diffuse[2] = 0.0;
			mat_diffuse[3] = 1.0;

		}
		GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};	
	
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

		for(int i=0; i<t->tetrac->triangInc.size(); i++){
			glBegin(GL_TRIANGLES);	
			glNormal3f(t->tetrac->triangInc[i].norm.x,t->tetrac->triangInc[i].norm.y,t->tetrac->triangInc[i].norm.z);
			glVertex3f(tt.mMeshTT->points[t->tetrac->triangInc[i].v0].x,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v0].y,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v0].z);
			glVertex3f(tt.mMeshTT->points[t->tetrac->triangInc[i].v1].x,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v1].y,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v1].z);
			glVertex3f(tt.mMeshTT->points[t->tetrac->triangInc[i].v2].x,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v2].y,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v2].z);		
			glEnd();
			
		}
		
		glPopMatrix();
	}
	
}

void drawTCHaptic(nodeTT *t){
	if(t!= NULL){
		glPushMatrix();
		for(int i=0; i<t->tetrac->triangInc.size(); i++){
			glBegin(GL_TRIANGLES);	
			glNormal3f(t->tetrac->triangInc[i].norm.x,t->tetrac->triangInc[i].norm.y,t->tetrac->triangInc[i].norm.z);
			glVertex3f(tt.mMeshTT->points[t->tetrac->triangInc[i].v0].x,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v0].y,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v0].z);
			glVertex3f(tt.mMeshTT->points[t->tetrac->triangInc[i].v1].x,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v1].y,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v1].z);
			glVertex3f(tt.mMeshTT->points[t->tetrac->triangInc[i].v2].x,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v2].y,
				tt.mMeshTT->points[t->tetrac->triangInc[i].v2].z);		
			glEnd();
			
		}
		
		glPopMatrix();
	}
	
}

//*******************************************************************************
// The main routine for displaying the scene.  Gets the latest snapshot of state
// from the haptic thread and uses it for displaying a 3D cursor.  Draws the
// anchor visual if the anchor is presently active.
//*******************************************************************************
void drawSceneGraphics()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glClearColor(0.5,0.5,0.5,0);	
    
    drawCursor();
    drawMalla();
	drawTTLine();
	drawTC(tttouch,ef);
	DisplayInfo();
	
}

//*******************************************************************************
// The main routine for haptically rendering the scene.
//*******************************************************************************
void drawSceneHaptics()
{

    hlBeginFrame();
	hlBeginShape(HL_SHAPE_FEEDBACK_BUFFER, gTActivoID);
		hlTouchableFace(HL_FRONT);
		drawTCHaptic(tttouch);
		hlEndShape();
		
		//hlBeginShape(HL_SHAPE_FEEDBACK_BUFFER, gTTShapeID);
		//hlTouchableFace(HL_FRONT);
		//drawTTSolid();
		//hlEndShape();
	
    hlEndFrame();
	

    // Call any event callbacks that have been triggered.
    hlCheckEvents();
		
}


//*******************************************************************************
// Draws a 3D cursor for the haptic device using the current local transform,
// the workspace to world transform and the screen coordinate scale.
//*******************************************************************************
void drawCursor()
{
    static const double kCursorRadius = 50.0;
    static const int kCursorTess = 15;
    HLdouble proxytransform[16];

    GLUquadricObj *qobj = 0;

    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
    glPushMatrix();

    if (!gCursorDisplayList)
    {
        gCursorDisplayList = glGenLists(1);
        glNewList(gCursorDisplayList, GL_COMPILE);
        qobj = gluNewQuadric();
               
        gluSphere(qobj, kCursorRadius, kCursorTess, kCursorTess);
		//mesh *Actuador = new(mesh);
		//loadOBJ(Actuador, "bisturi.obj"); 
		//drawActuador(Actuador);
		
		
		    
        //gluDeleteQuadric(qobj);
        glEndList();
    }  

     // Apply the local position/rotation transform of the haptic device proxy.
    hlGetDoublev(HL_PROXY_TRANSFORM, proxytransform);
    glMultMatrixd(proxytransform);
        
    // Apply the local cursor scale factor.
    glScaled(gCursorScale, gCursorScale, gCursorScale);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0, 0.5, 1.0);

    glCallList(gCursorDisplayList);

    glPopMatrix(); 
    glPopAttrib();
}

//******************************************************************************
*/
void initMesh(){
	
    tt.mMeshTT = new(mesh);
	float xc,yc,zc;
	loadOBJ(tt.mMeshTT, "dragonHD.obj"); 
	printf("Tamaño de la malla: %d puntos \t %d triangulos\n",tt.mMeshTT->points.size(),tt.mMeshTT->faces.size());
	int n;
	xc= tt.mMeshTT->points[0].x;
	yc= tt.mMeshTT->points[0].y;
	zc= tt.mMeshTT->points[0].z;
	for(n=1; n<tt.mMeshTT->points.size(); n++){
           xc += tt.mMeshTT->points[n].x;           
           yc += tt.mMeshTT->points[n].y;           
           zc += tt.mMeshTT->points[n].z;           
		   xc /= 2.0;
   		   yc /= 2.0;
           zc /= 2.0;
   }
   //Centrado de la malla
   for(n=0; n<tt.mMeshTT->points.size(); n++){
           tt.mMeshTT->points[n].x -= xc;           
           tt.mMeshTT->points[n].y -= yc;           
           tt.mMeshTT->points[n].z -= zc;           
   }
   //Generamos el tetratree
   tiempo1 = clock();
   generateTetraTree(100,64,&tt,tt.mMeshTT);
   tiempo2 = clock();
   tiempo =(tiempo2-tiempo1)/(double)CLOCKS_PER_SEC; 
	printf("Tiempo de construccion: %f\n",tiempo);
	printf("Tetraconos generados: %d\n",tt.ntet);
   
}
/*
double DetermineFPS(){
	static unsigned int	lastMs = glutGet(GLUT_ELAPSED_TIME);
	unsigned int		currentMs = glutGet(GLUT_ELAPSED_TIME);
	unsigned int		framesMs = currentMs - lastMs;
	static unsigned int	framesCounted = 0;
	static double fps = 0;
	
	framesCounted++;

	#define DURATION_TO_TIME		1000	// duration in miliseconds for calculating fps

	if(framesMs >= DURATION_TO_TIME)
	{
		fps = (double)1000 * framesCounted / framesMs;
		//printf("last: %ld  curr: %ld\n", g.lastClock, currentClock);
		//printf("clocks: %d  cps: %d  FPS: %f\n", clock(), CLOCKS_PER_SEC, fps);
		
		framesCounted = 0;
		//g.framesTime = 0;

		lastMs = currentMs;
	}

	return fps;
}

void DrawBitmapString(GLfloat x, GLfloat y, void *font, char *format,...)
{
	int len, i;
	va_list args;
	char string[256];

	// special C stuff to interpret a dynamic set of arguments specified by "..."
	va_start(args, format);
	vsprintf(string, format, args);
	va_end(args);

	glRasterPos2f(x, y);
	len = (int) strlen(string);
	
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

void DisplayInfo(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

    glPushMatrix();
    glLoadIdentity();

	// switch to 2d orthographic mMode for drawing text
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, mWindW, mWindH, 0);
	glMatrixMode(GL_MODELVIEW);
	
	glColor3f(1.0, 1.0, 1.0);

	int textRowDown = 0; // lines of text already drawn downwards from the top
	int textRowUp = 0; // lines of text already drawn upwards from the bottom

	DrawBitmapString(mWindW - 10 * 9, 20 + (textRowDown) * 15, GLUT_BITMAP_9_BY_15, "FPS: %4.1f", DetermineFPS());

	textRowDown++;
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
	
	// turn depth and lighting back on for 3D rendering
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
*/
int main(){
	
	
     
     tetratree tt;
	 mesh *m =  new(mesh);
	 tt.mMeshTT = new(mesh);
	 int sizeorip, sizeorit;
                
     printf("Entrando en cargar malla.\n");
     //loadOBJ(m, MALLA); 
  	 loadOBJ(tt.mMeshTT, MALLA); 
	 sizeorip = tt.mMeshTT->points.size();
	 sizeorit = tt.mMeshTT->faces.size();
	 
     printf("Objeto cargado.\n Vertices: %d\tTriangulos:%d.\n",tt.mMeshTT->points.size(),tt.mMeshTT->faces.size());
	 //generateTetraTreeInclussion(DEPTHTT,256,&tt,tt.mMeshTT);
     //generateTetraTree(4,256,&tt,tt.mMeshTT);
     //printf("Tetratree construido\t Numero de triangulos malla: %d\n.",tt.mMeshTT->faces.size());
     /*
		printf("Malla...\n");
		for(int i=0; i<tt.mMeshTT->points.size(); i++){
			printf("(%.2f,%.2f,%.2f) ",tt.mMeshTT->points[i].x,tt.mMeshTT->points[i].y,tt.mMeshTT->points[i].z);
		}
		printf("\n\n");
	 
     //wrapTetraTree(&tt);
     
     //saveTTMesh(&tt);
     
     //saveSplitTriangleInfo(&tt);
	 splitTT(&tt);
	 
     saveTTMesh(&tt,&malla);
     printf("Puntos de la malla: %d\tTriangulos: %d\n",malla.points.size(),malla.faces.size());
     printf("Puntos Originales: %d\tTriangulos: %d\n",sizeorip,sizeorit);
     //saveOBJ(&malla,"Tetratree.obj");
     
     return 0;
	
	//trianglesubdivision(tet, tri,P1I2S1,0);
	*/
	//p3Df p, bb1, bb2;
	/*
	p.x = 9.39;
	p.y = 18.49;
	p.z = -87.5;
	*/
	/*
	p.x = 300;
	p.y = 300;
	p.z = 300;

	inclusionPointTT(p, &tt,JIMENEZ);
	*/
	/*
	boundingBox(tt.mMeshTT,&bb1,&bb2);
	printf("Puntos de la BB: (%.2f,%.2f,%.2f),(%.2f,%.2f,%.2f)\n",bb1.x,bb1.y,bb1.z,bb2.x,bb2.y,bb2.z);

	
	clock_t tiempo1, tiempo2;
	double tiempo = 0.0;
	FILE *f;
	f = fopen(FILETIMES,"a");
	
	int pasadas = 1000;
	srand48(time(NULL));
	
	fprintf(f,"Malla a estudio: %s\nPuntos: %d\tTriangulos: %d\tPorfundidad: %d\n\n",MALLA,tt.mMeshTT->points.size(),tt.mMeshTT->faces.size(), DEPTHTT);

	for(int m=-2; m<5; m++){
		
		switch(m){
			case -2:
				fprintf(f,"Feito-Malla\t");
				break;
			case -1:
				fprintf(f,"Jordan-Moeller-Malla\t");
				break;
			case 0: 
				fprintf(f,"Normales-Moeller-Malla\t");
				break;
			case 1: 
				fprintf(f,"Cercano-Jimenez-Malla\t");
				break;
			case 2: 
				fprintf(f,"Normales-Moeller-TT\t");
				generateTetraTree(DEPTHTT,MAXTRIAN,&tt,tt.mMeshTT);
				break;
			case 3: 
				fprintf(f,"Cercano-Jimenez-TT\t");
				generateTetraTree(DEPTHTT,MAXTRIAN,&tt,tt.mMeshTT);
				break;
			case 4: 
				fprintf(f,"Cercano-JimenezOpt-TT\t");
				generateTetraTreeInclussion(DEPTHTT,MAXTRIAN,&tt,tt.mMeshTT);
				break;
		}
		//fclose(f);
		double tiempo = 0.0;
		tiempo1 = clock();
		for(int i=0; i<pasadas;i++){
			//printf("%d ",i);
			p.x = (drand48() * (bb1.x - bb2.x)) + bb2.x;
			p.y = (drand48() * (bb1.y - bb2.y)) + bb2.y;
			p.z = (drand48() * (bb1.z - bb2.z)) + bb2.z;		
			switch(m){
				case -2:
					
					Feito(p, tt.mMeshTT);

				case -1:

					JordanCurve(p, tt.mMeshTT,MOLLER);

				case 0: 

					inclusionPoint(p, tt.mMeshTT,MOLLER);	

					break;
				case 1: 

					inclusionPoint(p, tt.mMeshTT,JIMENEZ);

					break;
				case 2: 

					inclusionPointTT(p, &tt,MOLLER);

					break;
				case 3:

					inclusionPointTT(p, &tt,JIMENEZ);

					break;
				case 4: 

					inclusionPointTT(p, &tt,JIMENEZOPT);

					break;
			}
			
		}
		tiempo2 = clock();
		tiempo =(tiempo2-tiempo1)/(double)CLOCKS_PER_SEC; 
		printf("Tiempo de inclusion: %.8f\n",tiempo);
		fprintf(f,"Tiempo de inclusion: %.8f\n",tiempo);
	}

/*
	p.x = (drand48() * (bb1.x - bb2.x)) + bb2.x;
	p.y = (drand48() * (bb1.y - bb2.y)) + bb2.y;
	p.z = (drand48() * (bb1.z - bb2.z)) + bb2.z;		
	p3Df c;
	c.x= tt.mMeshTT->points[0].x;
	c.y= tt.mMeshTT->points[0].y;
	c.z= tt.mMeshTT->points[0].z;
	
	//Calculo del centroide de la malla.
   for(unsigned int n=1; n<tt.mMeshTT->points.size(); n++){
           c.x += tt.mMeshTT->points[n].x;           
           c.y += tt.mMeshTT->points[n].y;           
           c.z += tt.mMeshTT->points[n].z;
           
   }
   c.x /= tt.mMeshTT->points.size();
   c.y /= tt.mMeshTT->points.size();
   c.z /= tt.mMeshTT->points.size();   
	float r;
	tiempo = 0.0;
	for(int lo=0; lo<tt.mMeshTT->faces.size(); lo++){
		trian orig;
		orig.v0 = tt.mMeshTT->points[tt.mMeshTT->faces[lo].v0];
		orig.v1 = tt.mMeshTT->points[tt.mMeshTT->faces[lo].v1];
		orig.v2 = tt.mMeshTT->points[tt.mMeshTT->faces[lo].v2];
		orig.norm = tt.mMeshTT->faces[lo].norm;
		tiempo1 = clock();
		for(int pol=0; pol<1000; pol++)
			//intersect_Ray(p, c, orig, &r);
			jimenezOpt(&p,&c,&orig,&r);
			//jimenezOptNew(&p,&c,&orig,p,p,p,p,0.5,&r);	
		tiempo2 = clock();
		tiempo +=(tiempo2-tiempo1)/(double)CLOCKS_PER_SEC; 
	}
		printf("Tiempo de inclusion: %.8f\n",tiempo);
		fprintf(f,"Tiempo de inclusion: %.8f\n",tiempo);
*/	
//	fclose(f);  
	 
	 FILE *arch;
	 arch = fopen(FILETEST,"a");
	 fprintf(arch,"Objeto cargado %s\n Vertices: %d\tTriangulos:%d.\n\n",MALLA,tt.mMeshTT->points.size(),tt.mMeshTT->faces.size());
	 int i;
	 //Pruebas de trinangulos
/*	 for(i=16; i< 2500; i= i*2){ 
		 fprintf(arch,"Umbral de parada: %d triangulos\n\n",i);
*/
	 	tiempo1 = clock();
	
		 generateTetraTreeExt(4,16,&tt,tt.mMeshTT);
		 generateTetraTree(4,128,&tt,tt.mMeshTT);
		 tiempo2 = clock();
		 tiempo =(tiempo2-tiempo1)/(double)CLOCKS_PER_SEC;
		 fprintf(arch,"Tiempo de generacion del TTExt: %.8f\n",tiempo);
		 printf("Tiempo de generacion del TTExt: %.8f\n",tiempo);
		 printf("TT generados: %d\n",tt.ntet);
		 
	/*	 eraseTetratree(&tt);
	 
		 tt.mMeshTT = new(mesh);
		 loadOBJ(tt.mMeshTT, MALLA);
		 tiempo1 = clock();
		 generateTetraTree(100,i,&tt,tt.mMeshTT);		 
		 tiempo2 = clock();
		 tiempo =(tiempo2-tiempo1)/(double)CLOCKS_PER_SEC;
		 fprintf(arch,"Tiempo de generacion del TT: %.8f\n",tiempo);
		 printf("Tiempo de generacion del TT: %.8f\n",tiempo);
		 eraseTetratree(&tt);
		 tt.mMeshTT = new(mesh);
		 loadOBJ(tt.mMeshTT, MALLA); 
		 
	 }
	 fclose(arch);
	  */
	 printf("Terminado\n");
		 int nft = 0;
		for(int n=0; n<tt.mMeshTT->faces.size(); n++)
			if(tt.mMeshTT->faces[n].itype != -1) nft++;
		printf("Malla Troceada: %d Triangulos - %d Puntos\n",nft,tt.mMeshTT->points.size());
		 saveOBJ(tt.mMeshTT, "mallatroceada.obj");
	//	 saveTTMesh(&tt);	
	 eraseTetratree(&tt);
			 //printf("Objeto troceado.\n Vertices: %d\tTriangulos:%d.\n",tt.mMeshTT->points.size(),tt.mMeshTT->faces.size());
		
}
