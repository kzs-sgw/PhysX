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
	kzsPx->OnReshape( w, h );
}


// **MouseFunc**
void kzsGLObject::mouse( int button, int state, int x, int y )
{
	kzsPx->Mouse( button, state, x, y );
}


// **MotionFunc**
void kzsGLObject::motion( int x, int y )
{
	kzsPx->Motion( x, y );
}


// **KeyboardFunc**
void kzsGLObject::keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
		case '\033':
			exit( 0 );

		case 'n':
			glUtil.toggleFaceDirection();

		case 'h':
			kzsPx->PunchActorsFromUnder();
		default:
			break;
	}
}


// **IdleFunc**
void kzsGLObject::idle()
{
	//kzsPx->PunchActorsFromUnder();
	glutPostRedisplay();
}


// **Initialization**
void kzsGLObject::init( void )
{
	glClearColor( .7f, .7f, .7f, 1.0f);
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	
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