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
	std::vector<CollisionData> collideCubePlaneContact(const Cube& other) const;
	std::vector<Plan> getPlanes(const Cube& other) const;
	std::vector<Plan> getPlanes() const;
	bool intersect(const Cube& other) const;
	bool intersect(const Primitive& other) const override;
	Sphere* getBoundingSphere() override;

	std::vector<CollisionData> collide(const Plan& other) const;
	std::vector<CollisionData> collide(const Cube& other) const;

	std::vector<Vecteur3D> getAngles() const;
	struct Arrete {
		Vecteur3D point1;
		Vecteur3D point2;
	};

	std::vector<Arrete> getArretes() const;

	void draw() const;
	void print() const override;
	Quaternion getRotation() const { return rotation; }
	float getTaille() const { return taille; }
	bool isInside(const Vecteur3D& point) const;
	bool isInside(Arrete arrete) const;
	bool intersect(Arrete arrete) const;

private:
	std::vector<Vecteur3D> normals;
	float taille;
};

