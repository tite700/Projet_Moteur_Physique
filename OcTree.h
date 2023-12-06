#pragma once

#include "Vecteur3D.h"
#include <vector>
#include "CorpsRigide.h"
#include "Primitive.h"

class OcTree
{
public:
	OcTree(Vecteur3D position, float width, int maxPrimitives, OcTree* parent);

	// Methods
	void addPrimitive(Primitive* primitive);
	void subdivide();
	void clear();
	bool contains(Primitive* primitives);

	// Getters
	Vecteur3D getPosition();
	float getWidth();
	OcTree* getParent();
	OcTree* getChild(int index);
	std::vector<Primitive*> getPrimitives();



private:

	int maxPrimitives;
	Vecteur3D position;
	float width;
	OcTree* parent;
	OcTree* children[8];

	std::vector<Primitive*> primitives;
};

