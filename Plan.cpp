#include "Plan.h"

Plan::Plan()
{
}

Plan::Plan(const Vecteur3D& position, const Vecteur3D& normal)
{
}

Plan::~Plan()
{
}

bool Plan::intersect(Sphere& other) const
{
	return false;
}

Vecteur3D Plan::getNormal(const Vecteur3D& point) const
{
	return Vecteur3D();
}
