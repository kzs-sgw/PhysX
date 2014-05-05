#pragma once
#ifndef KZSGLOBJECT_H
#define KZSGLOBJECT_H


#include <stdlib.h>
#include <stdio.h>

// **AddIncludes**
//+++++++++++++++++++++++++++++++
// additional include files

#include "kzsPhysXFramework.h"

//
//+++++++++++++++++++++++++++++++

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/OpenGL.h>
#elif defined _WIN32 || defined _WIN64
	#include <GL\glut.h>
#endif 


//-------------------------------------------------
// global variables
const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

//-------------------------------------------------



//========================================================================
class kzsGLObject
{
private:	
	// disallow copy
	kzsGLObject(){}
	kzsGLObject( const kzsGLObject& rhs );
	kzsGLObject& operator=( const kzsGLObject& rhs );

public:
	kzsGLObject( int _argc, char *_argv[] ){
		printf( "kzsGLObject Constructor called\n" );
		printf( "create new kzsPhysXFramework instance\n\n" );
		kzsPx = new kzsPhysXFramework;
		glutInit( &_argc, _argv ); 
	};

	~kzsGLObject( void ) {
		printf( "kzsGLObject Destructor called\n" );
		printf( "delete the kzsPhysXFramework instance\n\n" );
		delete kzsPx;
	};
	
	// ****UserDef****
	//++++++++++++++++++++++++++++++++++++++++++++++++++++
	//

	// **PhysX Declare**
	kzsPhysXFramework* kzsPx;

	//
	//++++++++++++++++++++++++++++++++++++++++++++++++++++
		
	
	// kzsGLUtil.cpp
	//----------------------------------------------------
				// comming soon
	//----------------------------------------------------
	
	
	// kzsGLObject.cpp
	//----------------------------------------------------
	void display ( void );
	void resize  ( int w, int h );
	void mouse   ( int button, int state, int x, int y );
	void motion  ( int x, int y );
	void keyboard( unsigned char key, int x, int y );
	void idle    ( void );
	
	void init( void );
	void kzsGlutInit( void );
	//----------------------------------------------------
	
	
	// ****runOpenGL****
	//--------------------------------------
	void runOpenGL( void ( *displayFunc  )(),
			        void ( *resizeFunc   )( int, int ),
		            void ( *mouseFunc    )( int, int, int, int ),
			        void ( *motionFunc   )( int, int ),
					void ( *keyboardFunc )( unsigned char, int, int ),
			        void ( *idleFunc     )(),
					const char window_title[] = "New Window" ) { // use default HIKISUU to avoid mess


		kzsGlutInit();
		
		glutCreateWindow( window_title );
		
		glutDisplayFunc ( displayFunc  );
		glutReshapeFunc ( resizeFunc   );
		glutMouseFunc   ( mouseFunc    );
		glutMotionFunc  ( motionFunc   );
		glutKeyboardFunc( keyboardFunc );
		glutIdleFunc    ( idleFunc     );
		
		init();
		
		glEnable( GL_DEPTH_TEST );
		glDepthMask( GL_TRUE );

		glutMainLoop();
	}
	//--------------------------------------
	
};

#endif