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
	bool intersect(const Primitive& other) const override;
	Sphere* getBoundingSphere() const override;

	Vecteur3D getCenter() const { return position; }
	float getRadius() const { return radius; }

	void draw() const override;
	void print() const override;

private:

	float radius;
};

