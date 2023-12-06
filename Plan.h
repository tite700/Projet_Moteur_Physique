#pragma once
#include "./Primitive.h"
#include "./Sphere.h"
#include "./Vecteur3D.h"
#include "./Cube.h"

class Plan :
    public Primitive
{
public:
	Plan();
	Plan(const Vecteur3D& position, const Vecteur3D & normal);
	~Plan();

	virtual bool intersect(Sphere& other) const;
	virtual Vecteur3D getNormal(const Vecteur3D& point) const;

private:
	Vecteur3D position;
	Vecteur3D normal;
};

