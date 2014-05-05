#include "kzsPhysXFramework.h"


kzsPhysXFramework::kzsPhysXFramework(void)
{
	// global variables
	startTime = 0;
	totalFrames = 0;
	fps = 0;
	
	gScene = 0;
	myTimestep = 1.0f/60.0f;
}


kzsPhysXFramework::~kzsPhysXFramework(void)
{
}




// **StepPhysX**
void kzsPhysXFramework::StepPhysX() {
	gScene->simulate( myTimestep );

	while ( !gScene->fetchResults() )
	{
		// do something useful
	}
}


// **initPhysX**



// **ShutdownPhysX**



// **OnShutdown** 
void kzsPhysXFramework::OnShutdown() {
}


// **OnRender**
void kzsPhysXFramework::OnRender() {
	totalFrames++;
	
	int current = glutGet( GLUT_ELAPSED_TIME );
	
	if ( (current - startTime ) > 1000 )
	{
		float elapsedTime = float ( current - startTime );
		fps = ( ( totalFrames * 1000.0f ) / elapsedTime );
		startTime = current;
		totalFrames = 0;
	}

	if ( gScene ) StepPhysX();

	glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glutSwapBuffers();
}


// **OnIdle**
void kzsPhysXFramework::OnIdle() {
	glutPostRedisplay();
}
