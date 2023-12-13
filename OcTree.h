#pragma once

#include "Vecteur3D.h"
#include <vector>
#include "CorpsRigide.h"
#include "Primitive.h"
#include "Cube.h"
#include <set>
#include <utility>
#include "RegistreForceCorps.h"
#include "ForceImpulsionCorps.h"
#include <map>

class OcTree
{
public:
	OcTree(Vecteur3D position, float width, int maxPrimitives, int maxDepth, int depth = 0, OcTree* parent = nullptr, std::map<Primitive*, CorpsRigide*> map = std::map<Primitive*, CorpsRigide*>());

	// Methods
	void addPrimitive(Primitive* primitive);
	void addCorpsRigide(CorpsRigide* corpsRigide);
	void subdivide();
	void clear();
	bool contains(Primitive* primitives) const;

	// Getters
	Vecteur3D getPosition();
	float getWidth();
	OcTree* getParent();
	OcTree* getChild(int index);
	std::vector<Primitive*> getPrimitives();
	int getMaxPrimitives();
	std::set<std::pair<CorpsRigide*, CorpsRigide*>> getPossibleCollisions();
	std::map<Primitive*, CorpsRigide*> getBodyMap();

	void draw();
	int getDepth();
	ostream& print(ostream& os) const;



private:

	int maxPrimitives;
	Vecteur3D position;
	float width;
	OcTree* parent;
	OcTree* children[8];
	int maxDepth;
	int depth;

	std::vector<Primitive*> primitives;
	std::map<Primitive*, CorpsRigide*> bodyMap;
	Cube cube;
};

