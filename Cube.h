#pragma once
#include "./Primitive.h"
#include "./Sphere.h"
#include "./Vecteur3D.h"
#include "./Plan.h"

class Plan;
class Sphere;

class Cube :
    public Primitive

{
public:
	Cube();
	Cube(const Vecteur3D& centre, const std::vector<Vecteur3D> normals, float taille);
	~Cube();

	using Primitive::intersect;
	bool intersect(const Sphere& other) const;
	bool intersect(const Plan& other) const;

	std::vector<Vecteur3D> getAngles() const;


private:
	Vecteur3D centre;
	std::vector<Vecteur3D> normals;
	float taille;
};

