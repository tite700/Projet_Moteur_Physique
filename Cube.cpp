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

std::vector<CollisionData> Cube::collideCubePlaneContact(const Cube& other) const
{
	std::vector<CollisionData> collisions;

	// Obtenez les plans du cube actuel
	std::vector<Plan> plans = getPlanes();

	// Pour chaque plan, vérifiez s'il y a une collision avec le cube 'other'
	for (const Plan& plan : plans)
	{
		std::vector<CollisionData> planeCollisions = other.collide(plan);

		// Ajoutez les collisions au vecteur global
		collisions.insert(collisions.end(), planeCollisions.begin(), planeCollisions.end());
	}

	return collisions;
}

std::vector<Plan> Cube::getPlanes(const Cube& other) const
{
	std::vector<Plan> planes;

	return planes;
}
std::vector<Plan> Cube::getPlanes() const
{
	std::vector<Plan> planes;

	// Obtenez les angles du cube
	std::vector<Vecteur3D> angles = getAngles();

	Vecteur3D normalX = rotation.rotateVector(Vecteur3D(1, 0, 0));
	Vecteur3D normalY = rotation.rotateVector(Vecteur3D(0, 1, 0));
	Vecteur3D normalZ = rotation.rotateVector(Vecteur3D(0, 0, 1));

	// Pour chaque face, créez un plan
	planes.push_back(Plan(angles[0], normalX));
	planes.push_back(Plan(angles[0], normalY));
	planes.push_back(Plan(angles[0], normalZ));
	planes.push_back(Plan(angles[1], normalX));
	planes.push_back(Plan(angles[1], normalY));
	planes.push_back(Plan(angles[2], normalX));



	return planes;
}
bool checkOverlap(float minA, float maxA, float minB, float maxB);

bool Cube::intersect(const Cube& other) const
{
	std::vector<Vecteur3D> axes;
	axes.push_back(rotation.rotateVector(Vecteur3D(1, 0, 0)));
	axes.push_back(rotation.rotateVector(Vecteur3D(0, 1, 0)));
	axes.push_back(rotation.rotateVector(Vecteur3D(0, 0, 1)));

	axes.push_back(other.getRotation().rotateVector(Vecteur3D(1, 0, 0)));
	axes.push_back(other.getRotation().rotateVector(Vecteur3D(0, 1, 0)));
	axes.push_back(other.getRotation().rotateVector(Vecteur3D(0, 0, 1)));

	std::vector<Vecteur3D> otherAxes;

	for (Vecteur3D axis : axes)
	{
		for (Vecteur3D otherAxis : otherAxes)
		{
			if (!(axis == otherAxis))
			{
				otherAxes.push_back(axis.prodvect(otherAxis));
			}
		}
	}

	axes.insert(axes.end(), otherAxes.begin(), otherAxes.end());

	std::vector<Vecteur3D> angles = getAngles();
	std::vector<Vecteur3D> otherAngles = other.getAngles();

	for (const auto axis : axes)
	{
		double minProjection1 = std::numeric_limits<double>::max();
		double maxProjection1 = -std::numeric_limits<double>::max();
		double minProjection2 = std::numeric_limits<double>::max();
		double maxProjection2 = -std::numeric_limits<double>::max();

		for (const auto angle : angles)
		{
			double projection = axis.prodscal(angle);
			minProjection1 = std::min(minProjection1, projection);
			maxProjection1 = std::max(maxProjection1, projection);
		}

		for (const auto angle : otherAngles)
		{
			double projection = axis.prodscal(angle);
			minProjection2 = std::min(minProjection2, projection);
			maxProjection2 = std::max(maxProjection2, projection);
		}

		if (maxProjection1 < minProjection2 || maxProjection2 < minProjection1) {
			// Il y a séparation le long de cet axe, pas de collision
			return false;
		}
	}

	return true;

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
bool checkOverlap(float minA, float maxA, float minB, float maxB) {
	return !(maxA < minB || maxB < minA);
}

std::vector<CollisionData> Cube::collide(const Cube& other) const
{
	std::vector<CollisionData> collisions;
	CollisionData collision = CollisionData(true, Vecteur3D(0, 0, 0), std::numeric_limits<double>::max());

	std::vector<Vecteur3D> axes;
	axes.push_back(rotation.rotateVector(Vecteur3D(1, 0, 0)));
	axes.push_back(rotation.rotateVector(Vecteur3D(0, 1, 0)));
	axes.push_back(rotation.rotateVector(Vecteur3D(0, 0, 1)));

	axes.push_back(other.getRotation().rotateVector(Vecteur3D(1, 0, 0)));
	axes.push_back(other.getRotation().rotateVector(Vecteur3D(0, 1, 0)));
	axes.push_back(other.getRotation().rotateVector(Vecteur3D(0, 0, 1)));

	std::vector<Vecteur3D> otherAxes;

	for (Vecteur3D axis : axes)
	{
		for (Vecteur3D otherAxis : otherAxes)
		{
			if (!(axis == otherAxis))
			{
				otherAxes.push_back(axis.prodvect(otherAxis));
			}
		}
	}

	axes.insert(axes.end(), otherAxes.begin(), otherAxes.end());

	std::vector<Vecteur3D> angles = getAngles();
	std::vector<Vecteur3D> otherAngles = other.getAngles();

	for (const auto axis : axes)
	{
		double minProjection1 = std::numeric_limits<double>::max();
		double maxProjection1 = -std::numeric_limits<double>::max();
		double minProjection2 = std::numeric_limits<double>::max();
		double maxProjection2 = -std::numeric_limits<double>::max();

		for (const auto angle : angles)
		{
			double projection = axis.prodscal(angle);
			minProjection1 = std::min(minProjection1, projection);
			maxProjection1 = std::max(maxProjection1, projection);
		}

		for (const auto angle : otherAngles)
		{
			double projection = axis.prodscal(angle);
			minProjection2 = std::min(minProjection2, projection);
			maxProjection2 = std::max(maxProjection2, projection);
		}

		if (maxProjection1 < minProjection2 || maxProjection2 < minProjection1) {
			// Il y a séparation le long de cet axe, pas de collision
			return std::vector<CollisionData>();
		}
		else
		{
			//Calcul de la profondeur de la collision
			double overlap1 = maxProjection1 - minProjection2;
			double overlap2 = maxProjection2 - minProjection1;
			double overlap = std::min(overlap1, overlap2);
			if (overlap < collision.getInterpenetration())
			{
				collision.setInterpenetration(overlap);
				Vecteur3D contributingCorner1 = Vecteur3D::zeros();
				Vecteur3D contributingCorner2 = Vecteur3D::zeros();

				for (const auto& angle : angles) {
					double projection = axis.prodscal(angle);
					if (projection >= minProjection2 && projection <= maxProjection2) {
						contributingCorner1 = angle;
						break;
					}
				}

				for (const auto& angle : otherAngles) {
					double projection = axis.prodscal(angle);
					if (projection >= minProjection1 && projection <= maxProjection1) {
						contributingCorner2 = angle;
						break;
					}
				}

				collision.setPointImpact(position + (other.getPosition() - position) * (1.0/ 2));
			}
		}
	}
	collisions.push_back(collision);
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

std::vector<Cube::Arrete> Cube::getArretes() const
{
	std::vector<Vecteur3D> angles = getAngles();
	std::vector<Arrete> arretes;

	Arrete arrete1;
	arrete1.point1 = angles[0];
	arrete1.point2 = angles[1];
	arretes.push_back(arrete1);

	Arrete arrete2;
	arrete2.point1 = angles[0];
	arrete2.point2 = angles[2];
	arretes.push_back(arrete2);

	Arrete arrete3;
	arrete3.point1 = angles[0];
	arrete3.point2 = angles[4];
	arretes.push_back(arrete3);

	Arrete arrete4;
	arrete4.point1 = angles[1];
	arrete4.point2 = angles[3];
	arretes.push_back(arrete4);

	Arrete arrete5;
	arrete5.point1 = angles[1];
	arrete5.point2 = angles[5];
	arretes.push_back(arrete5);

	Arrete arrete6;
	arrete6.point1 = angles[2];
	arrete6.point2 = angles[3];
	arretes.push_back(arrete6);

	Arrete arrete7;
	arrete7.point1 = angles[2];
	arrete7.point2 = angles[6];
	arretes.push_back(arrete7);

	Arrete arrete8;
	arrete8.point1 = angles[3];
	arrete8.point2 = angles[7];
	arretes.push_back(arrete8);

	Arrete arrete9;
	arrete9.point1 = angles[4];
	arrete9.point2 = angles[5];
	arretes.push_back(arrete9);

	Arrete arrete10;
	arrete10.point1 = angles[4];
	arrete10.point2 = angles[6];
	arretes.push_back(arrete10);

	Arrete arrete11;
	arrete11.point1 = angles[5];
	arrete11.point2 = angles[7];
	arretes.push_back(arrete11);

	Arrete arrete12;
	arrete12.point1 = angles[6];
	arrete12.point2 = angles[7];
	arretes.push_back(arrete12);

	return arretes;
}

void Cube::draw() const
{

	ofColor transparent = color;
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

bool Cube::isInside(const Vecteur3D& point) const
{
	Vecteur3D normalX = rotation.rotateVector(Vecteur3D(1, 0, 0)).normalisation();
	Vecteur3D normalY = rotation.rotateVector(Vecteur3D(0, 1, 0)).normalisation();
	Vecteur3D normalZ = rotation.rotateVector(Vecteur3D(0, 0, 1)).normalisation();

	Vecteur3D direction = point - position;

	if (direction.prodscal(normalX) > taille / 2 || direction.prodscal(normalX) < -taille / 2)
	{
		return false;
	}
	if (direction.prodscal(normalY) > taille / 2 || direction.prodscal(normalY) < -taille / 2)
	{
		return false;
	}
	if (direction.prodscal(normalZ) > taille / 2 || direction.prodscal(normalZ) < -taille / 2)
	{
		return false;
	}

	return true;
}

bool Cube::isInside(Arrete arrete) const
{
	Vecteur3D normalX = rotation.rotateVector(Vecteur3D(1, 0, 0)).normalisation();
	Vecteur3D normalY = rotation.rotateVector(Vecteur3D(0, 1, 0)).normalisation();
	Vecteur3D normalZ = rotation.rotateVector(Vecteur3D(0, 0, 1)).normalisation();

	Vecteur3D direction = arrete.point1 - position;

	if (direction.prodscal(normalX) > taille / 2 || direction.prodscal(normalX) < -taille / 2)
	{
		return false;
	}
	if (direction.prodscal(normalY) > taille / 2 || direction.prodscal(normalY) < -taille / 2)
	{
		return false;
	}
	if (direction.prodscal(normalZ) > taille / 2 || direction.prodscal(normalZ) < -taille / 2)
	{
		return false;
	}

	return true;
}

bool Cube::intersect(Arrete arrete) const
{
	Vecteur3D normalX = rotation.rotateVector(Vecteur3D(1, 0, 0)).normalisation();
	Vecteur3D normalY = rotation.rotateVector(Vecteur3D(0, 1, 0)).normalisation();
	Vecteur3D normalZ = rotation.rotateVector(Vecteur3D(0, 0, 1)).normalisation();

	Vecteur3D direction = arrete.point1 - position;

	if (direction.prodscal(normalX) > taille / 2 || direction.prodscal(normalX) < -taille / 2)
	{
		return false;
	}
	if (direction.prodscal(normalY) > taille / 2 || direction.prodscal(normalY) < -taille / 2)
	{
		return false;
	}
	if (direction.prodscal(normalZ) > taille / 2 || direction.prodscal(normalZ) < -taille / 2)
	{
		return false;
	}

	return true;
}
