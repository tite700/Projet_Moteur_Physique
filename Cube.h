#pragma once
#include "./Primitive.h"
#include "./Sphere.h"
#include "./Vecteur3D.h"
#include "./Plan.h"
#include "./Quaternion.h"
#include "./CollisionData.h"

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
	Sphere* getBoundingSphere() override;

	std::vector<CollisionData> collide(const Plan& other) const;

	std::vector<Vecteur3D> getAngles() const;

	void draw() const;
	void print() const override;
	Quaternion getRotation() const { return rotation; }

private:
	std::vector<Vecteur3D> normals;
	float taille;
};

