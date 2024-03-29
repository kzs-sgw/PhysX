// PxUserApp class inherits "kzsGLObject" class and "kzsPhysXFramework" class.
// 
//
//

//#pragma once
#include "PxUserApp.h"


PxUserApp* userApp; // main application class



void callDisplayFunc() {
  userApp->display();
}


void callResizeFunc( int w, int h ) {
  userApp->resize( w, h );
}


void callMouseFunc( int button, int state, int x, int y ) {
  userApp->mouse( button, state, x, y );
}


void callMotionFunc( int x, int y ) {
	userApp->motion( x, y );
}


void callKeyboardFunc( unsigned char key, int x, int y ) {
  userApp->keyboard( key, x, y );
}


void callIdleFunc() {
	userApp->idle();
}

void callMouseWheelFunc( int wheel_number, int direction, int x, int y ) {
	userApp->mousewheel( wheel_number, direction, x, y );
}


void callShutdown() {
	userApp->OnShutdown();	
}



//************************************************************
// **main**
int main( int argc, char* argv[] )
{

	userApp = new PxUserApp();

	atexit( callShutdown );

	userApp->runOpenGL( callDisplayFunc,
		                callResizeFunc,
				        callMouseFunc,
					    callMotionFunc,
					    callKeyboardFunc,
					    callIdleFunc,
						callMouseWheelFunc,
					    /* Window Title = */ "Bouncing Object" );

	delete userApp;

	return 0;
}