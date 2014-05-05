#include "GLCamera.h"

namespace kzsGL
{
	GLCamera::GLCamera()
	{
		cameraPos.setPosition( 5.0f, 5.0f, 5.0f );
		targetPos.setPosition( 0.0f, 0.0f, 0.0f );

		oldX  = 0;
		oldY  = 0;
		camera_state = 0;
		rX    = 0;
		rY    = -50;
		dist  = 1;
	}


	GLCamera::GLCamera( GLPosition cPos, GLPosition tPos )
	{
		cameraPos = cPos;
		targetPos = tPos;

		oldX  = 0;
		oldY  = 0;
		camera_state = 0;
		rX    = 0;
		rY    = -50;
		dist  = 0;
	}


	GLCamera::~GLCamera(void)
	{
	}


	void GLCamera::SetCameraPosition( GLPosition cPos )
	{
		cameraPos = cPos;
	}


	void GLCamera::SetTargetPosition( GLPosition tPos )
	{
		targetPos = tPos;
	}


	void GLCamera::MulCameraMatrix()
	{
		glLoadIdentity();
		glTranslatef( 0, 0, dist );
		gluLookAt( cameraPos.x(), cameraPos.y(), cameraPos.z(),
			       targetPos.x(), targetPos.y(), targetPos.z(),
				   0            , 1            , 0             );

		glRotatef( rX, 1, 0, 0 );
		glRotatef( rY, 0, 1, 0 );
	}


	void GLCamera::InReshape( int nw, int nh, GLdouble persAngular )
	{
		glViewport(0,0,nw, nh);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective( persAngular, (GLfloat)nw / (GLfloat)nh, 0.1f, 1000.0f );
		glMatrixMode(GL_MODELVIEW);
	}


	void GLCamera::InMouse( int button, int state, int x, int y )
	{
		if ( state == GLUT_DOWN )
		{
			oldX = x;
			oldY = y;
		}

		if( button == GLUT_RIGHT_BUTTON )
			camera_state = 1;
		else camera_state = 0;
	}


	void GLCamera::InMotion( int x, int y, bool doRedisplay )
	{
		if ( camera_state == 1 )
		{
			rY += ( x - oldX )/5.0f;
			rX += ( y - oldY )/5.0f;
		}

		oldX = x;
		oldY = y;
		if ( doRedisplay )	glutPostRedisplay();
	}
	

	void GLCamera::InMouseWheel( int wheel_number, int direction, int x, int y )
	{
		if ( direction ==  1 ) ZoomIn();
		if ( direction == -1 ) ZoomOut();
	}

	void GLCamera::ZoomIn()	 { dist += 1.0; }
	void GLCamera::ZoomOut() { dist -= 1.0; }

}





