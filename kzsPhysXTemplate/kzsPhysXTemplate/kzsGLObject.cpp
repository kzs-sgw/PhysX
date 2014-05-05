/* メインとなるワークスペースです。OpenGLで呼び出される関数を定義します。 */



#include "kzsGLObject.h"


// **DisplayFunc**
void kzsGLObject::display( void )
{
	kzsPx->OnRender();
}


// **ReshapeFunc**
void kzsGLObject::resize( int w, int h )
{
	glViewport( 0, 0, w, h );
	glLoadIdentity();
	glOrtho( -w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0 );
	//glOrtho( -.5, ( double )w - .5, ( double )h - .5, -.5, -1.0, 1.0 ); // mouse_coord matches screen_coord 
}


// **MouseFunc**
void kzsGLObject::mouse( int button, int state, int x, int y )
{
}


// **MotionFunc**
void kzsGLObject::motion( int x, int y )
{
}


// **KeyboardFunc**
void kzsGLObject::keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
		case '\033':
			exit( 0 );
		default:
			break;
	}
}


// **IdleFunc**
void kzsGLObject::idle()
{
	glutPostRedisplay();
}


// **Initialization**
void kzsGLObject::init( void )
{
	glClearColor( .7, .7, .7, 1.0);
	
	kzsPx->initPhysX();

}


// **kzsGlutInit**
void kzsGLObject::kzsGlutInit( void )
{
	//glutInitWindowPosition( 400, 400 );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	
}

// **************************************