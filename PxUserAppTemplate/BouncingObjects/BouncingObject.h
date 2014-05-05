#pragma once

#include "kzsPhysXFramework.h"
#include "kzsGLObject.h"
#include "kzsGLUtil.h"
#include "GLOBAL_VARIABLES.h"
#include "DrawPxShapes.h"
#include <foundation\PxMat33.h>



class BouncingObject
{
public:
					BouncingObject(void);
					~BouncingObject(void);

	// Rendering Functions

	void			DrawPlane();
	void			DrawWalls();

	
	void			OnRender();


	// PhysX simulation Functions
	void			initPhysX( PxPhysics* gPhysicsSDK, PxScene* gScene );
	void			setupGroundPlane( PxPhysics* gPhysicsSDK, PxScene* gScene );
	void			setupWallPlanes( PxPhysics* gPhysicsSDK, PxScene* gScene );
	void			initDynamicCube( PxPhysics* gPhysicsSDK, PxScene* gScene );
	void			initDynamicSphere( PxPhysics* gPhysicsSDK, PxScene* gScene );
	void			RenderActors();

	// Test Functions
	void			initRigidBodyCube( PxPhysics* gPhysicsSDK, PxScene* gScene );
	void			PunchActorsFromUnder();


	// variables



	typedef			GLfloat	point3[ 3 ];
	point3			planeVertices[ 4 ];


	// for simulation
	const PxVec3	globalGravity;
	const int		objnum;
	vector < PxRigidActor* > boxes;
	vector < PxRigidDynamic* > spheres;
	vector < PxRigidBody*  > cubes; // test for addForce

	PxMaterial*		planeMaterial;
	PxMaterial*		cubeMaterial;
	PxMaterial*		sphereMaterial;

	DrawPxShapes	drawObj;
	
};

