#include "PxUserApp.h"


PxUserApp::PxUserApp() : globalGravity( 0.0f, -9.81f, 0.0f )
{
	startTime	= 0;
	totalFrames	= 0;
	fps			= 0;

	initPhysX();
}


PxUserApp::~PxUserApp(void)
{
}


//===============================================================================
// Rendering Functions

void PxUserApp::RenderFramerate()
{
	totalFrames++;

	int current = glutGet( GLUT_ELAPSED_TIME );
	
	if ( ( current - startTime ) > 1000 )
	{
		float elapsedTime = float ( current - startTime );
		fps = ( ( totalFrames * 1000.0f ) / elapsedTime );
		startTime = current;
		totalFrames = 0;
	}


	sprintf_s( buffer, " *** ROTATE WITH MOUSE RIGHT_BUTTON  |  FPS: %3.2f",fps);

	glUtil.setOrthoForFont( WINDOW_WIDTH, WINDOW_HEIGHT );
	glColor3f( 1, 1, 1 );
	glUtil.RenderSpacedBitmapString( 20, 20, 0, GLUT_BITMAP_HELVETICA_12, buffer );
	glUtil.ResetPerspectiveProjection();
}


// **resize**
void PxUserApp::resize( int nw, int nh )
{
	camera.InReshape( nw, nh, 50 );
}


// **mouse**
void PxUserApp::mouse( int button, int s, int x, int y )
{
	camera.InMouse( button, s, x, y );
}


// **motion**
void PxUserApp::motion( int x, int y )
{
	camera.InMotion( x, y );
}


// **display**
void PxUserApp::display()
{
	camera.SetCameraPosition( GLPosition( 20 * sin( 0.0 ), 20, 20 * cos( 0.0 ) ) );

	if ( gScene ) StepPhysX();

	glClearColor( 0.1f, 0.1f, 0.1f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	camera.MulCameraMatrix();

	glUtil.drawAxes();
	
	glUtil.drawGrid( 10, GLColor( 0.7f, 0.7f, 0.7f) );
	
	//-------------------------------------------------

			// add Object to draw
	bounceObj.OnRender();

	//-------------------------------------------------
	
	RenderFramerate();

	glutSwapBuffers();


}


// **idle**
void PxUserApp::idle()
{
	glutPostRedisplay();
}


// **keyboard**
void PxUserApp::keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
		case '\033':
			exit( 0 );
			break;

		case 'n':
			glUtil.toggleFaceDirection();
			break;

		case 'h':
			bounceObj.PunchActorsFromUnder();
			break;

		default:
			break;
	}
}


// **mousewheel**
void PxUserApp::mousewheel( int wheel_number, int direction, int x, int y )
{
	camera.InMouseWheel( wheel_number, direction, x, y );
}

//===============================================================================
//===============================================================================
// PhysX simulation Functions
void PxUserApp::initPhysX()
{
	printf( "**initializing PhysX**\n" );
	initPx_Foundation_Physics_Extensions();
	initPx_CreateScene( globalGravity );

	//-------------------------------------------------
			// add code to initialize
	bounceObj.initPhysX( gPhysicsSDK, gScene );
	//-------------------------------------------------
	
	printf( "**PhysX initialized**\n" );
}



