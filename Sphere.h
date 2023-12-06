#pragma once
#include "./Primitive.h"
class Sphere :
    public Primitive
{
public:
	Sphere();
	Sphere(const Vecteur3D& center, float radius);
	~Sphere();

	bool intersect(const Sphere& other) const;

private:

	Vecteur3D center;
	float radius;
};

