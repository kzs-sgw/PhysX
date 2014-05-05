// kzsGLObject is the main framework of this project.
// kzsPhysXFramework is in the main framework.
//
//


#include "kzsGLObject.h"


kzsGLObject* glObj;
// kzsPhysXFramework* kzsPx; ‚ÍéŒ¾Ï‚Ý(kzsGLObject.h“à)



void callDisplayFunc() {
  glObj->display();
}


void callResizeFunc( int w, int h ) {
  glObj->resize( w, h );
}


void callMouseFunc( int button, int state, int x, int y ) {
  glObj->mouse( button, state, x, y );
}



void callMotionFunc( int x, int y ) {
	glObj->motion( x, y );
}


void callKeyboardFunc( unsigned char key, int x, int y ) {
  glObj->keyboard( key, x, y );
}


void callIdleFunc() {
	glObj->idle();
}


void callShutdown() {
	glObj->kzsPx->OnShutdown();
	glObj->~kzsGLObject();
}