#include "CollisionHandler.h"

std::vector<CollisionData> CollisionHandler::collide(const Cube& cube1, const Cube& cube2)
{
	return cube1.collide(cube2);
}

std::vector<CollisionData> CollisionHandler::collide(const Cube& cube, const Plan& plan)
{
	return cube.collide(plan);
}

std::vector<CollisionData> CollisionHandler::collideCubes(const CorpsRigide body1, const CorpsRigide body2)
{
	return collide(dynamic_cast<Cube&>(*body1.getPrimitive()), dynamic_cast<Cube&>(*body2.getPrimitive()));
}

std::vector<CollisionData> CollisionHandler::collideCubePlan(const CorpsRigide& body, const Plan& plan)
{
	return collide(dynamic_cast<Cube&>(*body.getPrimitive()), plan);
}

void CollisionHandler::resolveCollisionCubes(CorpsRigide* body1, CorpsRigide* body2, RegistreForceCorps* registreForceCorps)
{
	if (body1 == nullptr || body2 == nullptr)
	{
		return;
	}
	std::vector<CollisionData> collisions = collideCubes(*body1, *body2);
	for (const CollisionData& collision : collisions)
	{
		//Calcule intensite
		float e = 0;
		//std::cout << "Velocite:" << cubeRigide2->getVelocite() << std::endl;
		Vecteur3D vrel = (*body1).getVelocite() - (*body2).getVelocite();
		float v = vrel.norme();
		float Kup = (e + 1) * v;
		float Kdown = (*body1).getInverseMass() + (*body2).getInverseMass();
		float K = Kup / Kdown;
		registreForceCorps->add(body1, new ForceImpulsionCorps(collision.getPointImpact(), K * collision.getInterpenetration() / collisions.size(), (vrel.normalisation() * (collision.getInterpenetration() / sqrt(collision.getInterpenetration() * collision.getInterpenetration()))).normalisation()));
		registreForceCorps->add(body2, new ForceImpulsionCorps(collision.getPointImpact(), K * collision.getInterpenetration() / collisions.size(), (-1) *(vrel.normalisation() * (collision.getInterpenetration() / sqrt(collision.getInterpenetration() * collision.getInterpenetration()))).normalisation()));
	}
}

void CollisionHandler::resolveCollisionCubePlan(CorpsRigide* body, Plan* plan, RegistreForceCorps* registreForceCorps)
{
	std::vector<CollisionData> collisions = collideCubePlan(*body, *plan);
	for (const CollisionData& collision : collisions)
	{
		//Calcule intensite
		float e = 0;
		//std::cout << "Velocite:" << cubeRigide2->getVelocite() << std::endl;
		float v = body->getVelocite().prodscal(plan->getNormal());
		float Kup = (e + 1) * v;
		float Kdown = (*body).getInverseMass();
		float K = Kup / Kdown;
		registreForceCorps->add(body, new ForceImpulsionCorps(collision.getPointImpact(), K * collision.getInterpenetration() / collisions.size(), (plan->getNormal() * (collision.getInterpenetration() / sqrt(collision.getInterpenetration() * collision.getInterpenetration()))).normalisation()));
	}
}
