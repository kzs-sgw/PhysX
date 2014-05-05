#include "kzsPhysXFramework.h"

/////////////////////////////////////////////////////////////////
// GLOBALS

static PxDefaultErrorCallback    gDefaultErrorCallback;
static PxDefaultAllocator        gDefaultAllocatorCallback;
static PxSimulationFilterShader  gDefaultFilterShader = physx::PxDefaultSimulationFilterShader;

/////////////////////////////////////////////////////////////////




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
void kzsPhysXFramework::initPhysX() {
	
	printf( "** initializing PhysX**\n" );
	
	
	printf( "creating Foundation\n" );
	// create foundation object with default error and allocator callbacks.
	mFoundation = PxCreateFoundation( PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback );
	
	
	printf( "creating Physics\n" );
	// create Physics oject with the created foundation and with a 'default' scale tolerance.
	gPhysicsSDK = PxCreatePhysics( PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale() );
	
	
	PxInitExtensions( *gPhysicsSDK );
	
	
	printf( "creating the scene\n" );
	// create the scene
	physx::PxSceneDesc sceneDesc( gPhysicsSDK->getTolerancesScale() );
	sceneDesc.gravity = physx::PxVec3( 0.0f, -9.81f, 0.0f );
	
	if ( !sceneDesc.cpuDispatcher )
	{
		physx::PxDefaultCpuDispatcher* mCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(1);
		sceneDesc.cpuDispatcher = mCpuDispatcher;
	}
	
	if ( !sceneDesc.filterShader )
	{
		sceneDesc.filterShader = gDefaultFilterShader;
	}
	
	gScene = gPhysicsSDK->createScene( sceneDesc );
	
	
	printf( "**PhysX initialized**\n" );
}


// **ShutdownPhysX**
void kzsPhysXFramework::ShutdownPhysX() {
	printf( "shutting down\n" );
	gScene->release();
	gPhysicsSDK->release();
}


// **OnShutdown**
void kzsPhysXFramework::OnShutdown() {
	ShutdownPhysX();
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





/*
int main(int argc, char** argv) {
	
	atexit( OnShutdown );

	glutInit( &argc, argv );
	
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutCreateWindow( "Initialization" );

	glutDisplayFunc( OnRender );
	glutIdleFunc( OnIdle );


	initPhysX();


	glEnable( GL_DEPTH_TEST );
	glDepthMask( GL_TRUE );
	glutMainLoop();

	return 0;
}
*/