#include "Cube.h"

Cube::Cube()
{

}

Cube::Cube(const Vecteur3D& centre, float taille, Quaternion rotation, ofColor color)
{
	this->position = centre;
	this->taille = taille;
	this->rotation = rotation;
	this->color = color;
	boundingSphere = new Sphere(centre, sqrt(3) * taille / 2);
}

Cube::~Cube()
{
}

bool Cube::intersect(const Sphere& other) const
{
	if (other.getRadius() + (taille * sqrt(3)) / 2 < (position - other.getCenter()).norme())
	{
		return false;
	}

	Vecteur3D newX = rotation.rotateVector(Vecteur3D(1, 0, 0));
	Vecteur3D newY = rotation.rotateVector(Vecteur3D(0, 1, 0));
	Vecteur3D newZ = rotation.rotateVector(Vecteur3D(0, 0, 1));

	float sphereNewXDistance = abs(other.getCenter().prodscal(newX) - this->position.prodscal(newX));
	float sphereNewYDistance = abs(other.getCenter().prodscal(newY) - this->position.prodscal(newY));
	float sphereNewZDistance = abs(other.getCenter().prodscal(newZ) - this->position.prodscal(newZ));

	if (sphereNewXDistance > (this->taille / 2 + other.getRadius())) { return false; }
	if (sphereNewYDistance > (this->taille / 2 + other.getRadius())) { return false; }
	if (sphereNewZDistance > (this->taille / 2 + other.getRadius())) { return false; }

	if (sphereNewXDistance < taille) { return true; }
	if (sphereNewYDistance < taille) { return true; }
	if (sphereNewZDistance < taille) { return true; }
	float cornerDistance_sq = ((sphereNewXDistance - taille) * (sphereNewXDistance - taille)) + ((sphereNewYDistance - taille) * (sphereNewYDistance - taille) + ((sphereNewYDistance - taille) * (sphereNewYDistance - taille)));
	return (cornerDistance_sq < (other.getRadius() * other.getRadius()));
}

bool Cube::intersect(const Plan& other) const
{
	Vecteur3D normalP = other.getNormal();
	 // Cube angles

	std::vector<Vecteur3D> angles = getAngles();
	
	bool side = (normalP.prodscal(angles[0]) + other.getD() > 0);
	angles.erase(angles.begin());

	for (int i = 0; i < angles.size(); i++)
	{
		if (side != (normalP.prodscal(angles[i]) + other.getD() > 0))
		{
			return true;
		}
	}

	return false;

}

bool Cube::intersect(const Cube& other) const
{
	//TODO
	return false;
}

bool Cube::intersect(const Primitive& other) const
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

Sphere* Cube::getBoundingSphere()
{
	boundingSphere->setPosition(position);
	return boundingSphere;
}

std::vector<CollisionData> Cube::collide(const Plan& other) const
{
	std::vector<Vecteur3D> angles = getAngles();
	
	std::vector<CollisionData> collisions;
	bool side = other.getNormal().prodscal(position) + other.getD() > 0;

	for (Vecteur3D angle : angles)
	{
		float t = other.getNormal().prodscal(angle - position);
		Vecteur3D projAngle = angle - t * other.getNormal();
		if (side != (other.getNormal().prodscal(angle) + other.getD() > 0))
		{
			collisions.push_back(CollisionData(true, angle, abs(t)));
		}
	}

	return collisions;
}


std::vector<Vecteur3D> Cube::getAngles() const
{
	Vecteur3D A = position + rotation.rotateVector(Vecteur3D(taille / 2, taille / 2, taille / 2));
	Vecteur3D B = position + rotation.rotateVector(Vecteur3D(taille / 2, taille / 2, -taille / 2));
	Vecteur3D C = position + rotation.rotateVector(Vecteur3D(taille / 2, -taille / 2, taille / 2));
	Vecteur3D D = position + rotation.rotateVector(Vecteur3D(taille / 2, -taille / 2, -taille / 2));
	Vecteur3D E = position + rotation.rotateVector(Vecteur3D(-taille / 2, taille / 2, taille / 2));
	Vecteur3D F = position + rotation.rotateVector(Vecteur3D(-taille / 2, taille / 2, -taille / 2));
	Vecteur3D G = position + rotation.rotateVector(Vecteur3D(-taille / 2, -taille / 2, taille / 2));
	Vecteur3D H = position + rotation.rotateVector(Vecteur3D(-taille / 2, -taille / 2, -taille / 2));

	std::vector<Vecteur3D> angles;

	angles.push_back(A);
	angles.push_back(B);
	angles.push_back(C);
	angles.push_back(D);
	angles.push_back(E);
	angles.push_back(F);
	angles.push_back(G);
	angles.push_back(H);

	return angles;
}

void Cube::draw() const
{

	ofColor transparent;
	transparent.a = 10;

	ofBoxPrimitive box;
	box.setPosition(position.getX(), position.getY(), position.getZ());
	box.setWidth(taille);
	box.setHeight(taille);
	box.setDepth(taille);
	box.rotate(glm::quat(rotation.getA(), rotation.getB(), rotation.getC(), rotation.getD()));
	for (int i = 0; i < 6; i++)
	{
		box.setSideColor(i, transparent);
	}
	box.draw();
	ofSetLineWidth(4.0);
	ofSetColor(ofColor::red);
	box.drawWireframe();

}

void Cube::print() const
{
	std::cout << "Cube" << std::endl;
	std::cout << "Position : " << position << std::endl;
	std::cout << "Taille : " << taille << std::endl;
	std::cout << "Rotation : " << rotation << std::endl;
	std::cout << "Color : " << color << std::endl;
}
