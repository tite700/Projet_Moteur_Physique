#pragma once

#include "Vecteur3D.h"
#include <vector>
#include "CorpsRigide.h"
#include "Primitive.h"
#include "Cube.h"

class OcTree
{
public:
	OcTree(Vecteur3D position, float width, int maxPrimitives, int maxDepth, int depth = 0, OcTree* parent = nullptr);

	// Methods
	void addPrimitive(Primitive* primitive);
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
	Cube cube;
};

