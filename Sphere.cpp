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

bool Sphere::intersect(const Plan& other) const
{
    return other.distance(center) <= radius;
}

bool Sphere::intersect(const Cube& other) const
{
    return other.intersect(*this);
}

bool Sphere::isInSpace(Vecteur3D point, float width)
{
    std::vector<Vecteur3D> normals = std::vector<Vecteur3D>();
    normals.push_back(Vecteur3D(1, 0, 0));
    normals.push_back(Vecteur3D(0, 1, 0));
    normals.push_back(Vecteur3D(0, 0, 1));
    Cube cube = Cube(center, normals, width);

    return this->intersect(cube);
}
