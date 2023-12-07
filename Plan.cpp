#include "Plan.h"

Plan::Plan()
{
}

Plan::Plan(const Vecteur3D& position, const Vecteur3D& normal)
{
	this->position = position;
	this->normal = normal;
    d = -position.prodscal(normal);
}

Plan::~Plan()
{
}

float Plan::distance(const Vecteur3D& point) const
{
    float a = normal.getX();
    float b = normal.getY();
    float c = normal.getZ();

    float distance = std::abs(a * point.getX() + b * point.getY() + c * point.getZ() + d) / std::sqrt(a * a + b * b + c * c);

    return distance;
}

float Plan::projete(const Vecteur3D& point) const
{
    return normal.prodscal(point - position);
}

bool Plan::intersect(Sphere& other) const
{
	return other.intersect(*this);
}

bool Plan::intersect(Plan& other) const
{
    if (normal == other.normal)
    {
		return false;
	}
    else
    {
		return true;
	}
}

bool Plan::intersect(Cube& other) const
{
    return other.intersect(*this);
}

Vecteur3D Plan::getNormal(const Vecteur3D& point) const
{
	return Vecteur3D();
}
