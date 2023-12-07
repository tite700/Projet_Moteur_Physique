#pragma once
#include "./Primitive.h"
#include "./Sphere.h"
#include "./Vecteur3D.h"
#include "./Cube.h"

class Sphere;
class Cube;

class Plan :
    public Primitive
{
public:
	Plan();
	Plan(const Vecteur3D& position, const Vecteur3D & normal);
	~Plan();

	float distance(const Vecteur3D& point) const;
	float projete(const Vecteur3D& point) const;

	using Primitive::intersect;

	bool intersect(Sphere& other) const;
	bool intersect(Plan& other) const;
	bool intersect(Cube& other) const;


	Vecteur3D getNormal(const Vecteur3D& point) const;
	Vecteur3D getNormal() const { return normal; }
	Vecteur3D getPosition() const { return position; }
	float getD() const { return d; }


private:
	Vecteur3D position;
	Vecteur3D normal;
	float d;
};

