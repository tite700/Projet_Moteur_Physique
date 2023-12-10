#include "ForceImpulsionCorps.h"

ForceImpulsionCorps::ForceImpulsionCorps(Vecteur3D PointImpact, float Intensite, Vecteur3D direction)
{
	this->pointImpact = PointImpact;
	this->intensite = Intensite;
	this->direction = direction;
}

void ForceImpulsionCorps::UpdateForce(CorpsRigide* corpsRigide)
{
	std::cout << "ForceImpulsionCorps::UpdateForce" << std::endl;
	Vecteur3D brasDeLevier = Vecteur3D(corpsRigide->getPosition().getX() - pointImpact.getX(), corpsRigide->getPosition().getY() - pointImpact.getY(), corpsRigide->getPosition().getZ() - pointImpact.getZ());
	corpsRigide->addForce(brasDeLevier.normalisation() * intensite);
	corpsRigide->addTorque(brasDeLevier.normalisation().prodvect(direction) * intensite);
	
}