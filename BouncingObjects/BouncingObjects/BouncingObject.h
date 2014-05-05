#pragma once

#include "kzsPhysXFramework.h"
#include "kzsGLUtil.h"
#include "GLOBAL_VARIABLES.h"
#include "DrawPxShapes.h"
#include <foundation\PxMat33.h>

const int Max_Path = 16384;

class BouncingObject : public kzsPhysXFramework
{
public:
					BouncingObject(void);
					~BouncingObject(void);

	// Rendering Functions
	void			DrawPlane();
	void			DrawWalls();


	void			OnRender();


	// PhysX simulation Functions

	void			setupGroundPlane();
	void			setupWallPlanes();
	void			initDynamicCube();
	void			initDynamicSphere();
	void			RenderActors();

	// Test Functions
	void			initRigidBodyCube();
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

