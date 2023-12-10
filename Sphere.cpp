#include "Sphere.h"

Sphere::Sphere()
{
    position = Vecteur3D(0,0,0);
    radius = 0;
}

Sphere::Sphere(const Vecteur3D& center, float radius)
{
    this->position = center;
	this->radius = radius;  
	boundingSphere = this;
}

Sphere::~Sphere()
{

}

bool Sphere::intersect(const Sphere& other) const
{
    return (position - other.position).norme() <= radius + other.radius;
}

bool Sphere::intersect(const Plan& other) const
{
    return other.distance(position) <= radius;
}

bool Sphere::intersect(const Cube& other) const
{
    return other.intersect(*this);
}

bool Sphere::intersect(const Primitive& other) const
{
	if (&other == nullptr)
	{
		return false;
	}
	else if (dynamic_cast<const Sphere*>(&other) != nullptr)
	{
		return intersect(dynamic_cast<const Sphere&>(other));
	}
	else if (dynamic_cast<const Plan*>(&other) != nullptr)
	{
		return intersect(dynamic_cast<const Plan&>(other));
	}
	else if (dynamic_cast<const Cube*>(&other) != nullptr)
	{
		return intersect(dynamic_cast<const Cube&>(other));
	}
	else
	{
		return false;
	}
}

Sphere* Sphere::getBoundingSphere()
{
	std::cout << "Sphere Bounding Sphere" << std::endl;
	return boundingSphere;
}

void Sphere::draw() const
{

	ofColor transparent;
	transparent.a = 50;

	ofSpherePrimitive sphere;
	sphere.setPosition(position.getX(), position.getY(), position.getZ());
	sphere.setRadius(radius);
    
    ofSetColor(transparent);

	sphere.draw();
	ofSetLineWidth(4.0);
	ofSetColor(ofColor::red);
	sphere.drawWireframe();
}

void Sphere::print() const
{
	std::cout << "Sphere : " << std::endl;
	std::cout << "Position : " << position << std::endl;
	std::cout << "Radius : " << radius << std::endl;
}
