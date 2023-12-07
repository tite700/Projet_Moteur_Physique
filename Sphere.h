#pragma once
#include "./Primitive.h"
#include "./Plan.h"
#include "./Vecteur3D.h"
#include "./Cube.h"

class Plan;
class Cube;

class Sphere :
    public Primitive
{
public:
	Sphere();
	Sphere(const Vecteur3D& center, float radius);
	~Sphere();

	using Primitive::intersect;
	bool intersect(const Sphere& other) const;
	bool intersect(const Plan& other) const;
	bool intersect(const Cube& other) const;

	bool isInSpace(Vecteur3D point, float width) override;

	Vecteur3D getCenter() const { return center; }
	float getRadius() const { return radius; }

private:

	Vecteur3D center;
	float radius;
};

