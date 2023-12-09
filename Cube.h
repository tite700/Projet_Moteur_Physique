#pragma once
#include "./Primitive.h"
#include "./Sphere.h"
#include "./Vecteur3D.h"
#include "./Plan.h"
#include "./Quaternion.h"

#include <vector>
#include <iostream>
#include <math.h>


class Plan;
class Sphere;

class Cube :
    public Primitive

{
public:
	Cube();
	Cube(const Vecteur3D& centre, float taille, Quaternion rotation = Quaternion::identity(), ofColor color = ofColor::red);
	~Cube();

	using Primitive::intersect;
	bool intersect(const Sphere& other) const;
	bool intersect(const Plan& other) const;
	bool intersect(const Cube& other) const;
	bool intersect(const Primitive& other) const override;

	std::vector<Vecteur3D> getAngles() const;

	void draw() const;
	Quaternion getRotation() const { return rotation; }

private:
	std::vector<Vecteur3D> normals;
	Quaternion rotation;
	float taille;
};

