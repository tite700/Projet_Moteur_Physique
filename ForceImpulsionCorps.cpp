#include "ForceImpulsionCorps.h"

ForceImpulsionCorps::ForceImpulsionCorps(Vecteur3D PointImpact, float Intensite)
{
	this->pointImpact = PointImpact;
	this->intensite = Intensite;
}

void ForceImpulsionCorps::UpdateForce(CorpsRigide* corpsRigide)
{
	corpsRigide->addForce(Vecteur3D(0,0,intensite*700));
	corpsRigide->addTorque(Vecteur3D(pointImpact.getX(), 0.0 - pointImpact.getY(), 0.0) * (intensite / 1000.0));
	
}
