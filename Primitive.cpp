#include "Primitive.h"

Primitive::Primitive()
{
	this->position = Vecteur3D(0, 0, 0);
}

Primitive::~Primitive()
{
}

void Primitive::draw() const
{
}

bool Primitive::intersect(const Primitive& other) const
{
	std::cout << "WARNING : Virtual FONCTION CALLED" << std::endl;
	return false;
}

Sphere* Primitive::getBoundingSphere()
{
	std::cout << "WARNING : Virtual FONCTION CALLED" << std::endl;
	return nullptr;
}

void Primitive::print() const
{
	std::cout << "WARNING : Virtual FONCTION CALLED" << std::endl;
}

