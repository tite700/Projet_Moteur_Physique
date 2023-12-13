#pragma once

#include "CollisionData.h"
#include "Primitive.h"
#include "Cube.h"
#include "Plan.h"
#include "CorpsRigide.h"
#include "RegistreForceCorps.h"
#include "ForceImpulsionCorps.h"

class CollisionHandler
{
public :

	//Collecting all the collision data
	static std::vector<CollisionData> collide(const Cube& cube1, const Cube& cube2);
	static std::vector<CollisionData> collide(const Cube& cube, const Plan& plan);
	static std::vector<CollisionData> collideCubes(const CorpsRigide body1, const CorpsRigide body2);
	static std::vector<CollisionData> collideCubePlan(const CorpsRigide& body, const Plan& plan);

	static void resolveCollisionCubes(CorpsRigide* body1, CorpsRigide* body2, RegistreForceCorps* registreForceCorps);
	static void resolveCollisionCubePlan(CorpsRigide* body, Plan* plan, RegistreForceCorps* registreForceCorps);
};

