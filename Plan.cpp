#include "Plan.h"

Plan::Plan()
{
}

Plan::Plan(const Vecteur3D& position, const Quaternion rotation)
{
	this->position = position;
    d = -position.prodscal(normal);
    this->rotation = rotation;
    this->normal = rotation.rotateVector(Vecteur3D(0, 0, 1));

}

Plan::~Plan()
{
}

float Plan::distance(const Vecteur3D& point) const
{
    float a = normal.getX();
    float b = normal.getY();
    float c = normal.getZ();

    float distance = std::abs(a * point.getX() + b * point.getY() + c * point.getZ() + d) / std::sqrt(a * a + b * b + c * c);

    return distance;
}

float Plan::projete(const Vecteur3D& point) const
{
    return normal.prodscal(point - position);
}

bool Plan::intersect(Sphere& other) const
{
	return other.intersect(*this);
}

bool Plan::intersect(Plan& other) const
{
    if (normal == other.normal)
    {
		return false;
	}
    else
    {
		return true;
	}
}

bool Plan::intersect(Cube& other) const
{
    return other.intersect(*this);
}

void Plan::draw() const
{
    ofColor transparentRed;
    transparentRed.r = 255;
    transparentRed.g = 0;
    transparentRed.b = 0;
    transparentRed.a = 30;
    ofPlanePrimitive plane;
    plane.set(1000, 1000);
    plane.setPosition(position.getX(), position.getY(), position.getZ());
    plane.rotate(glm::quat(rotation.getA(), rotation.getB(), rotation.getC(), rotation.getD()));
    ofSetLineWidth(4.0);
    ofSetColor(transparentRed);
    plane.draw();

}

Vecteur3D Plan::getNormal(const Vecteur3D& point) const
{
	return Vecteur3D();
}
