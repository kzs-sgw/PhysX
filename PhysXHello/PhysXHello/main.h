#pragma once
#ifndef PHYSX_MAIN_HEADDER
#define PHYSX_MAIN_HEADDER

#include "kzsPhysXFramework.h"


static physx::PxPhysics*                gPhysicsSDK = 0;
static physx::PxDefaultErrorCallback    gDefaultErrorCallback;
static physx::PxDefaultAllocator        gDefaultAllocatorCallback;
static physx::PxSimulationFilterShader  gDefaultFilterShader = physx::PxDefaultSimulationFilterShader;


const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

kzsPhysXFramework* kzsPxFW;


void callShutdown();
void callRender();
void callIdle();

void initPhysX();
void ShutdownPhysX();

//--------------------------------------------------------
// global function define
//--------------------------------------------------------

void callShutdown() {
	//kzsPxFW->OnShutdown();
	ShutdownPhysX();
}

void callRender() {
	kzsPxFW->OnRender();
}

void callIdle() {
	kzsPxFW->OnIdle();
}


void initPhysX() {
	
	printf( "initializing PhysX\n" );


	printf( "creating Foundation\n" );
	// create foundation object with default error and allocator callbacks.
	physx::PxFoundation* foundation = PxCreateFoundation( PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback );


	printf( "creating Physics\n" );
	// create Physics oject with the created foundation and with a 'default' scale tolerance.
	gPhysicsSDK = PxCreatePhysics( PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale() );


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

	kzsPxFW->gScene = gPhysicsSDK->createScene( sceneDesc );


	printf( "**PhysX initialized**\n" );
}


void ShutdownPhysX() {
	printf( "shutting down\n" );
	kzsPxFW->gScene->release();
	gPhysicsSDK->release();
}


#endif