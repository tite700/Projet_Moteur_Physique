#include "Primitive.h"

Primitive::Primitive()
{
	this->position = Vecteur3D(0, 0, 0);
}

Primitive::~Primitive()
{
}

bool Primitive::isInSpace(Vecteur3D point, float width)
{
	// Checks if the primitive is inside the cube defined by the point and the width
	if (point.getX() - width / 2 < this->position.getX() && this->position.getX() < point.getX() + width / 2)
	{
		if (point.getX() - width / 2 < this->position.getX() && this->position.getX() < point.getX() + width / 2)
		{
			if (point.getY() - width / 2 < this->position.getY() && this->position.getY() < point.getY() + width / 2)
			{
				return true;
			}
		}
	}
	return false;
}