#pragma once


#include <stdio.h>
#include <iostream>
#include <vector>
#include <gl/glut.h>

#include <PxPhysicsAPI.h>
#include <extensions\PxExtensionsAPI.h>
#include <extensions\PxDefaultErrorCallback.h>
#include <extensions\PxDefaultAllocator.h>
#include <extensions\PxDefaultSimulationFilterShader.h>
#include <extensions\PxDefaultCpuDispatcher.h>
#include <extensions\PxShapeExt.h>
#include <extensions\PxSimpleFactory.h>

#include <foundation\PxFoundation.h>

#pragma comment(lib, "PhysX3_x86.lib")
#pragma comment(lib, "PhysX3Common_x86.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
#pragma comment(lib, "PxTask.lib")

//using namespace physx;
//using namespace std;

//=============================================================


class kzsPhysXFramework
{
public:
	// global variables
	int startTime, totalFrames;
	float fps;
	
	
	physx::PxScene* gScene;
	physx::PxReal myTimestep;


	kzsPhysXFramework(void);
	~kzsPhysXFramework(void);


	void StepPhysX();
	//void initPhysX();
	//void ShutdownPhysX();
	void OnShutdown();
	void OnRender();
	void OnIdle();

};

