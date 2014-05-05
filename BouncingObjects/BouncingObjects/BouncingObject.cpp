#include "BouncingObject.h"



BouncingObject::BouncingObject(void) : globalGravity( 0.0f, -9.8f, 0.0f ), objnum( 150 )
{
	startTime	= 0;
	totalFrames	= 0;
	state		= 1;
	oldX		= 0;
	oldY		= 0;
	
	fps			= 0;
	rX			= 0;
	rY			= -50;
	dist		= 0;

	// init planeVertices
	point3 ary[ 4 ] = { { -10, 0, 10 }, { -10, 0, -10 }, { 10, 0, -10 }, { 10, 0, 10 } };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			planeVertices[ i ][ j ] = ary[ i ][ j ];
		}
	}
	
}


BouncingObject::~BouncingObject(void)
{
}


//===============================================================================
// Rendering Functions

void BouncingObject::setOrthoForFont()
{
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D( 0, WINDOW_WIDTH, 0, WINDOW_HEIGHT );
	glScalef( 1, -1, 1 );
	glTranslatef( 0, -WINDOW_HEIGHT, 0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}


void BouncingObject::ResetPerspectiveProjection()
{
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
}


void BouncingObject::RenderSpacedBitmapString( int x, int y, int spacing, void* font, char* string )
{
	char*	c;
	int		x1 = x;
	for ( c = string; *c != '\0'; c++ )
	{
		glRasterPos2i( x1, y );
		glutBitmapCharacter( font, *c );
		x1 = x1 + glutBitmapWidth( font, *c ) + spacing;
	}
}


void BouncingObject::DrawAxes()
{
	glPushMatrix();
	glColor3f( 0, 0, 1 );
	glPushMatrix();
	glTranslatef( 0, 0, 0.8f );
	glutSolidCone( 0.0325, 0.2, 4, 1 );
	// Draw label Z
	glTranslatef(0,0.0625,0.225f);
	RenderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_10, "Z");
	glPopMatrix();
	glutSolidCone(0.0225,1, 4,1);


	glColor3f( 1, 0, 0 );
	glRotatef( 90, 0, 1, 0 );
	glPushMatrix();
	glTranslatef( 0, 0, 0.8f );
	glutSolidCone( 0.0325, 0.2, 4, 1 );
	// Draw label X
	glTranslatef( 0, 0.0625, 0.225f );
	RenderSpacedBitmapString( 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "X" );
	glPopMatrix();
	glutSolidCone( 0.0225, 1, 4, 1 );

	glColor3f( 0, 1, 0 );
	glRotatef( 90, -1, 0, 0 );
	glPushMatrix();
	glTranslatef( 0, 0, 0.8f );
	glutSolidCone( 0.0325, 0.2, 4, 1 );
	// Draw label Y
	glTranslatef( 0, 0.0625, 0.225f );
	RenderSpacedBitmapString( 0, 0, 0, GLUT_BITMAP_HELVETICA_10, "Y" );
	glPopMatrix();
	glutSolidCone( 0.0225, 1, 4, 1 );
	glPopMatrix();
}


void BouncingObject::DrawGrid( int GRID_SIZE )
{

	glBegin( GL_LINES );
	glColor3f( .7f, .7f, .7f );

	for (int i = -GRID_SIZE; i <= GRID_SIZE; i++)
	{
		glVertex3f( ( float ) i, 0, ( float ) -GRID_SIZE );
		glVertex3f( ( float ) i, 0, ( float )  GRID_SIZE );

		glVertex3f( ( float ) -GRID_SIZE, 0, ( float ) i );
		glVertex3f( ( float )  GRID_SIZE, 0, ( float ) i );
	}
	glEnd();
}


void BouncingObject::DrawPlane()
{
	glBegin( GL_POLYGON );

	glNormal3f( 0, 1, 0 );
	glVertex3fv( planeVertices[ 0 ] );
	glVertex3fv( planeVertices[ 1 ] );
	glVertex3fv( planeVertices[ 2 ] );
	glVertex3fv( planeVertices[ 3 ] );
	glEnd();
}


void BouncingObject::DrawWalls()
{
	glColor4f( 0.7f, 0.7f, 0.7f, 0.7f );
	glPushMatrix();
	glTranslatef( 0, 10, 10 );
	glRotatef( 90, 1, 0, 0 );
	DrawPlane();
	glPopMatrix();


	glPushMatrix();
	glTranslatef( 0, 10, -10 );
	glRotatef( -90, 1, 0, 0 );
	DrawPlane();
	glPopMatrix();


	glPushMatrix();
	glTranslatef( 0, 10, 0 );
	glRotatef(  90, 0, 1, 0 );
	glRotatef( -90, 1, 0, 0 );
	glTranslatef( 0, 10, 0 );
	DrawPlane();
	glPopMatrix();
}


 void BouncingObject::OnReshape(int nw, int nh)
{
	glViewport(0,0,nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (GLfloat)nw / (GLfloat)nh, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

 

void BouncingObject::Mouse(int button, int s, int x, int y)
{
	if (s == GLUT_DOWN)
	{
		oldX = x;
		oldY = y;
	}

	if(button == GLUT_RIGHT_BUTTON)
		state = 1;
	else state = 0;
}


void BouncingObject::Motion(int x, int y)
{
	if (state == 1)
	{
		rY += (x - oldX)/5.0f;
		rX += (y - oldY)/5.0f;
	}

	oldX = x;
	oldY = y;
	glutPostRedisplay();
}


void BouncingObject::OnRender()
{
	GLdouble viewer[ 3 ] = { 20 * sin( 0.0 ), 20, 20 * cos( 0.0 ) };

	totalFrames++;

	int current = glutGet( GLUT_ELAPSED_TIME );
	
	if ( (current - startTime ) > 1000 )
	{
		float elapsedTime = float ( current - startTime );
		fps = ( ( totalFrames * 1000.0f ) / elapsedTime );
		startTime = current;
		totalFrames = 0;
	}


	sprintf_s( buffer, " *** ROTATE WITH MOUSE RIGHT_BUTTON  |  FPS: %3.2f",fps);


	if ( gScene ) StepPhysX();

	glClearColor( 0.1f, 0.1f, 0.1f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	glTranslatef( 0, 0, dist );
	gluLookAt( viewer[ 0 ], viewer[ 1 ], viewer[ 2 ] , 0, 0, 0, 0, 1, 0 );

	glRotatef( rX, 1, 0, 0 );
	glRotatef( rY, 0, 1, 0 );


	DrawAxes();
	
	DrawGrid( 10 );
	
	DrawWalls();
	
	RenderActors();


	setOrthoForFont();
	glColor3f( 1, 1, 1 );
	RenderSpacedBitmapString( 20, 20, 0, GLUT_BITMAP_HELVETICA_12, buffer );


	ResetPerspectiveProjection();


	glutSwapBuffers();

}


//===============================================================================
//===============================================================================
// PhysX simulation Functions

void BouncingObject::initPhysX()
{
	printf( "**initializing PhysX**\n" );
	initPx_Foundation_Physics_Extensions();
	initPx_CreateScene( globalGravity );
	
	// create Materials
	planeMaterial  = gPhysicsSDK->createMaterial( 0.9f, 0.1f, 1.0f );
	cubeMaterial   = gPhysicsSDK->createMaterial( 0.1f, 0.4f, 1.0f );
	sphereMaterial = gPhysicsSDK->createMaterial( 0.6f, 0.1f, 0.6f );


	setupGroundPlane();
	setupWallPlanes();

	initDynamicCube();
	initDynamicSphere();

	initRigidBodyCube();
	
	printf( "**PhysX initialized**\n" );
	
}


void BouncingObject::setupGroundPlane()
{
	PxTransform pose = PxTransform( PxVec3( 0.0f, 0.0f, 0.0f ), PxQuat( PxHalfPi, PxVec3( 0.0f, 0.0f, 1.0f ) ) );
	PxRigidStatic* plane = gPhysicsSDK->createRigidStatic( pose );

	PxShape* shape = plane->createShape( PxPlaneGeometry(), *planeMaterial );

	gScene->addActor( *plane );

}


void BouncingObject::setupWallPlanes()
{
	PxTransform leftpose = PxTransform( PxVec3( 0.0f, 0.0f, 10.0f ), PxQuat( PxHalfPi, PxVec3( 0.0f, 1.0f, 0.0f ) ) );
	PxRigidStatic* leftPlane = gPhysicsSDK->createRigidStatic( leftpose );
	PxShape* leftShape = leftPlane->createShape( PxPlaneGeometry(), *planeMaterial );
	gScene->addActor( *leftPlane );

	PxTransform rightpose = PxTransform( PxVec3( -10.0f, 0.0f, 0.0f ), PxQuat( PxHalfPi, PxVec3( 1.0f, 0.0f, 0.0f ) ) );
	PxRigidStatic* rightPlane = gPhysicsSDK->createRigidStatic( rightpose );
	PxShape* rightShape = rightPlane->createShape( PxPlaneGeometry(), *planeMaterial );
	gScene->addActor( *rightPlane );

	PxTransform leftpose2 = PxTransform( PxVec3( 0.0f, 0.0f, -10.0f ), PxQuat( PxHalfPi, PxVec3( 0.0f, -1.0f, 0.0f ) ) );
	PxRigidStatic* leftPlane2 = gPhysicsSDK->createRigidStatic( leftpose2 );
	PxShape* leftShape2 = leftPlane2->createShape( PxPlaneGeometry(), *planeMaterial );
	gScene->addActor( *leftPlane2 );

	// ‹Lq‚ª”ñ‘ÎÌ‚È‚Ì‚Å’ˆÓ
	PxTransform rightpose2 = PxTransform( PxVec3( 10.0f, 0.0f, 0.0f ), PxQuat( PxPi, PxVec3( 0.0f, 1.0f, 0.0f ) ) );
	PxRigidStatic* rightPlane2 = gPhysicsSDK->createRigidStatic( rightpose2 );
	PxShape* rightShape2 = rightPlane2->createShape( PxPlaneGeometry(), *planeMaterial );
	gScene->addActor( *rightPlane2 );
	
}



void BouncingObject::initDynamicCube()
{
	PxReal cubeDensity = 2.0f;
	PxTransform cubeTransform( PxVec3( 0.0f, 4.0f, 0.0f ) );
	PxVec3 cubeDims( 0.5, 0.5, 0.5 ); // the cube has a side length of 1
	PxBoxGeometry cubeGeometry( cubeDims );
	for (int i = 0; i < objnum; i++)
	{
		cubeTransform.p = PxVec3( 0.0f, 4.0f + 5 * i, 0.0f );

		PxRigidDynamic *cubeActor = PxCreateDynamic( *gPhysicsSDK, cubeTransform, cubeGeometry, *cubeMaterial, cubeDensity );
		if ( !cubeActor ) cerr << "create actor failed!" << endl;

		cubeActor->setAngularDamping( 0.2 );
		cubeActor->setLinearDamping( 0.01 );
		cubeActor->setMass( 1 + ( i / 8 ) );
		gScene->addActor( *cubeActor );
		boxes.push_back( cubeActor );

	}
}


void BouncingObject::initDynamicSphere()
{
	PxReal sphereDensity = 2.0f;
	PxTransform sphereTransform( PxVec3( 0.0f, 4.0f, 0.0f ) );
	PxSphereGeometry sphereGeometry( 0.7f );
	for (int i = 0; i < objnum; i++)
	{
		sphereTransform.p = PxVec3( 0.0f, 4.0f + 4 * i, 0.0f );

		PxRigidDynamic *sphereActor = PxCreateDynamic( *gPhysicsSDK, sphereTransform, sphereGeometry, *sphereMaterial, sphereDensity );
		if ( !sphereActor ) cerr << "create actor failed" << endl;

		sphereActor->setAngularDamping( 0.2 );
		sphereActor->setLinearDamping( 0.01 );
		sphereActor->setMass( 1 + ( i / 4 ) );
		gScene->addActor( *sphereActor );
		spheres.push_back( sphereActor );

	}

}


void BouncingObject::RenderActors()
{
	// light parameters
	GLfloat lightAmbientColour[]  = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat lightDiffuseColour[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat lightSpecularColour[] = { 0.8f, 0.8f, 0.8f, 1.0f };


	glEnable( GL_CULL_FACE  );
	glEnable( GL_LIGHTING   );
	glEnable( GL_LIGHT0     );
	glShadeModel( GL_SMOOTH );
	

	GLfloat lightPosition[ 4 ] = { 20 * cos( 0.0 ), 20 * sin( 0.0 ), 0.0, 1.0 };
	glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lightAmbientColour );
	glLightfv( GL_LIGHT0, GL_DIFFUSE , lightDiffuseColour  );
	glLightfv( GL_LIGHT0, GL_SPECULAR, lightSpecularColour );
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition       );

	/*
	GLfloat ambient_cube[]   = { 0.0f , 0.0f , 0.30f, 0.40f };
	GLfloat ambient_sphere[] = { 0.20f, 0.20f, 0.0f , 0.25f };

	GLfloat diffuse_cube[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuse_sphere[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	*/

	GLfloat mat_diffuse_cube[]   = { 0.85f, 0.0f , 0.0f, 1.0f };
	GLfloat mat_diffuse_sphere[] = { 0.85f, 0.85f, 0.0f, 1.0f };
	GLfloat mat_diffuse_cube2[]   = { 0.0f , 0.85f, 0.0f, 1.0f }; // for test


	for (int i = 0; i < objnum; i++)
	{
		glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse_cube );
		drawObj.DrawActor( boxes[ i ] );

		glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse_sphere );
		drawObj.DrawActor( spheres[ i ] );
		
		// for test
		glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse_cube2 );
		drawObj.DrawActor( cubes[ i ] );
	}

	glDisable( GL_LIGHTING );

}



// Test Functions

void BouncingObject::initRigidBodyCube()
{
	PxReal cubeDensity = 2.0f;
	PxTransform cubeTransform( PxVec3( 0.0f, 4.0f, 0.0f ) );
	PxVec3 cubeDims( 0.5, 0.5, 0.5 ); // the cube has a side length of 1
	PxBoxGeometry cubeGeometry( cubeDims );
	for (int i = 0; i < objnum; i++)
	{
		cubeTransform.p = PxVec3( 0.0f, 4.0f + 5 * i, 0.0f );

		PxRigidBody *cubeActor = PxCreateDynamic( *gPhysicsSDK, cubeTransform, cubeGeometry, *cubeMaterial, cubeDensity );
		if ( !cubeActor ) cerr << "create actor failed!" << endl;

		//cubeActor->setAngularDamping( 0.2 );
		//cubeActor->setLinearDamping( 0.01 );
		cubeActor->setMass( 1 + ( i / 8 ) );
		gScene->addActor( *cubeActor );
		cubes.push_back( cubeActor );

	}

}


void BouncingObject::PunchActorsFromUnder()
{
	//printf( "Punch!!\n" );
	for (int i = 0; i < objnum; i++)
	{
		cubes  [ i ]->addForce( PxVec3( 0.0f, 6.0f * i, 0.0f )/*, PxForceMode::eIMPULSE*/ );
		spheres[ i ]->addForce( PxVec3( 0.0f, 6.0f * i, 0.0f )/*, PxForceMode::eIMPULSE*/ );
	}
}