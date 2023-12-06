#include "Sphere.h"

Sphere::Sphere()
{
    center = Vecteur3D(0,0,0);
    radius = 0;
}

Sphere::Sphere(const Vecteur3D& center, float radius)
{
    this->center = center;
	this->radius = radius;  
}

Sphere::~Sphere()
{

}

bool Sphere::intersect(const Sphere& other) const
{
    return (center - other.center).norme() <= radius + other.radius;
}
