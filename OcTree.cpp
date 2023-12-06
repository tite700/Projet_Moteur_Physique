#include "OcTree.h"

OcTree::OcTree(Vecteur3D position, float width, int maxCorpsRigides, OcTree* parent)
{
	this->position = position;
	this->width = width;
	this->maxPrimitives = maxPrimitives;
	this->parent = parent;
	this->primitives = std::vector<Primitive*>();
	for (int i = 0; i < 8; i++)
	{
		children[i] = nullptr;
	}
}

void OcTree::addPrimitive(Primitive* primitive)
{
	if (children[0] != nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			if (children[i]->contains(primitive))
			{
				children[i]->addPrimitive(primitive);
			}
		}
	}
	primitives.push_back(primitive);
	if (primitives.size() >= maxPrimitives)
	{
		subdivide();
		for (int i = 0; i < primitives.size(); i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (children[j]->contains(primitives[i]))
				{
					children[j]->addPrimitive(primitives[i]);
					primitives.erase(primitives.begin() + i);
				}
			}
		}
	}
}

void OcTree::subdivide()
{
	if (children[0] == nullptr)
	{
		children[0] = new OcTree(Vecteur3D(position.getX() - width / 4, position.getY() - width / 4, position.getZ()), width / 2, maxPrimitives, this);
		children[1] = new OcTree(Vecteur3D(position.getX() + width / 4, position.getY() - width / 4, position.getZ()), width / 2, maxPrimitives, this);
		children[2] = new OcTree(Vecteur3D(position.getX() - width / 4, position.getY() + width / 4, position.getZ()), width / 2, maxPrimitives, this);
		children[3] = new OcTree(Vecteur3D(position.getX() + width / 4, position.getY() + width / 4, position.getZ()), width / 2, maxPrimitives, this);
		children[4] = new OcTree(Vecteur3D(position.getX() - width / 4, position.getY() - width / 4, position.getZ() + width / 2), width / 2, maxPrimitives, this);
		children[5] = new OcTree(Vecteur3D(position.getX() + width / 4, position.getY() - width / 4, position.getZ() + width / 2), width / 2, maxPrimitives, this);
		children[6] = new OcTree(Vecteur3D(position.getX() - width / 4, position.getY() + width / 4, position.getZ() + width / 2), width / 2, maxPrimitives, this);
		children[7] = new OcTree(Vecteur3D(position.getX() + width / 4, position.getY() + width / 4, position.getZ() + width / 2), width / 2, maxPrimitives, this);
	}
}

void OcTree::clear()
{
	if (children[0] != nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			children[i]->clear();
			delete children[i];
			children[i] = nullptr;
		}
	}
	primitives.clear();
}

bool OcTree::contains(Primitive* primitive)
{
	return primitive->isInSpace(position, width);
}

Vecteur3D OcTree::getPosition()
{
	return position;
}

float OcTree::getWidth()
{
	return width;
}

OcTree* OcTree::getParent()
{
	return parent;
}

OcTree* OcTree::getChild(int index)
{
	return children[index];
}

std::vector<Primitive*> OcTree::getPrimitives()
{
	return primitives;
}

