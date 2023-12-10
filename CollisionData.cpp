#include "CollisionData.h"

CollisionData::CollisionData()
{
}

CollisionData::CollisionData(bool collision, Vecteur3D pointImpact, float interpenetration, Vecteur3D direction)
{
	this->collision = collision;
	this->pointImpact = pointImpact;
	this->interpenetration = interpenetration;
	this->direction = direction;
}

void CollisionData::print() const
{
	std::cout << "Collision : " << collision << std::endl;
	std::cout << "Point d'impact : " << pointImpact << std::endl;
	std::cout << "Interpenetration : " << interpenetration << std::endl;
}
