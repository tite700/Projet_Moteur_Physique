#include "OcTree.h"

OcTree::OcTree(Vecteur3D position, float width, int maxPrimitives, int maxDepth, int depth, OcTree* parent)
{
	this->position = position;
	this->width = width;
	this->maxPrimitives = maxPrimitives;
	this->maxDepth = maxDepth;
	this->depth = depth;
	this->parent = parent;
	this->primitives = std::vector<Primitive*>();
	for (int i = 0; i < 8; i++)
	{
		children[i] = nullptr;
	}

	cube = Cube(position, width);
}

void OcTree::addPrimitive(Primitive* primitive)
{
//std::cout << "addPrimitive" << std::endl;
	if (!contains(primitive))
	{
		std::cout << "Primitive not in OcTree" << std::endl;
		return;
	}
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
	int nbPrimitives = primitives.size();
	if (primitives.size() > maxPrimitives && depth < maxDepth)
	{
		subdivide();
		for (int i = 0; i < nbPrimitives; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (children[j]->contains(primitives[i]))
				{	
					children[j]->addPrimitive(primitives[i]);
				}
			}
		}
		for (int i = 0; i < nbPrimitives; i++)
		{
			primitives.pop_back();
		}
	}
}

void OcTree::addCorpsRigide(CorpsRigide* corpsRigide)
{
	addPrimitive(corpsRigide->getPrimitive());
}

void OcTree::subdivide()
{
	if (children[0] == nullptr)
	{
		children[0] = new OcTree(Vecteur3D(position.getX() - width / 4, position.getY() - width / 4, position.getZ() - width / 4), width / 2, maxPrimitives, maxDepth, depth + 1, this);
		children[1] = new OcTree(Vecteur3D(position.getX() + width / 4, position.getY() - width / 4, position.getZ() - width / 4), width / 2, maxPrimitives, maxDepth, depth + 1, this);
		children[2] = new OcTree(Vecteur3D(position.getX() - width / 4, position.getY() + width / 4, position.getZ() - width / 4), width / 2, maxPrimitives, maxDepth, depth + 1, this);
		children[3] = new OcTree(Vecteur3D(position.getX() + width / 4, position.getY() + width / 4, position.getZ() - width / 4), width / 2, maxPrimitives, maxDepth, depth + 1, this);
		children[4] = new OcTree(Vecteur3D(position.getX() - width / 4, position.getY() - width / 4, position.getZ() + width / 4), width / 2, maxPrimitives, maxDepth, depth + 1,  this);
		children[5] = new OcTree(Vecteur3D(position.getX() + width / 4, position.getY() - width / 4, position.getZ() + width / 4), width / 2, maxPrimitives, maxDepth, depth + 1,  this);
		children[6] = new OcTree(Vecteur3D(position.getX() - width / 4, position.getY() + width / 4, position.getZ() + width / 4), width / 2, maxPrimitives, maxDepth, depth + 1,  this);
		children[7] = new OcTree(Vecteur3D(position.getX() + width / 4, position.getY() + width / 4, position.getZ() + width / 4), width / 2, maxPrimitives, maxDepth, depth + 1,  this);
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

bool OcTree::contains(Primitive* primitive) const
{
	Sphere* boundingSphere = primitive->getBoundingSphere();
	bool res = cube.intersect(*boundingSphere);
	return res;

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

int OcTree::getMaxPrimitives()
{
	return maxPrimitives;
}

void OcTree::draw()
{
	if (children[0] != nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			children[i]->draw();
		}
	}
	else
	{
		if (primitives.size() > 0)
			cube.draw();
	}
}

int OcTree::getDepth()
{
	if (children[0] != nullptr)
	{
		return children[0]->getDepth();
	}
	else
	{
		return depth;
	}
}

ostream& OcTree::print(ostream& os) const
{
	os << "OcTree : " << std::endl;
	os << "Position : " << position << std::endl;
	os << "Width : " << width << std::endl;
	os << "MaxPrimitives : " << maxPrimitives << std::endl;
	os << "MaxDepth : " << maxDepth << std::endl;
	os << "Depth : " << depth << std::endl;
	os << "Primitives : " << primitives.size() << std::endl;
	os << "Children : " << std::endl;
	for (int i = 0; i < 8; i++)
	{
		if (children[i] != nullptr)
		{
			os << "Child " << i << " : " << std::endl;
			children[i]->print(os);
		}
	}
	return os;
}

