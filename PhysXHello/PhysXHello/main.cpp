#include "main.h"



int main(int argc, char** argv) {
	
	kzsPxFW = new kzsPhysXFramework;

	atexit( callShutdown );

	glutInit( &argc, argv );
	
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutCreateWindow( "Initialization" );

	glutDisplayFunc( callRender );
	glutIdleFunc( callIdle );


	initPhysX();


	glEnable( GL_DEPTH_TEST );
	glDepthMask( GL_TRUE );
	glutMainLoop();

	delete kzsPxFW;

	return 0;
}