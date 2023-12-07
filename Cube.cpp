#include "Cube.h"

Cube::Cube()
{

}

Cube::Cube(const Vecteur3D& centre, const std::vector<Vecteur3D> normal, float taille)
{
	this->centre = centre;
	this->normals = normal;
	this->taille = taille;
}

Cube::~Cube()
{
}

bool Cube::intersect(const Sphere& other) const
{
	std::vector<Vecteur3D> angles = getAngles();

	//Vérifie si les angles sont dans la sphère

	for (int i = 0; i < angles.size(); i++)
	{
		if ((other.getCenter() - (angles[i])).norme() <= other.getRadius())
		{
			return true;
		}
	}

	//Vérifie si la sphère est dans le cube

	if (other.getCenter().getX() <= centre.getX() + taille / 2 && other.getCenter().getX() >= centre.getX() - taille / 2)
	{
		if (other.getCenter().getY() <= centre.getY() + taille / 2 && other.getCenter().getY() >= centre.getY() - taille / 2)
		{
			if (other.getCenter().getZ() <= centre.getZ() + taille / 2 && other.getCenter().getZ() >= centre.getZ() - taille / 2)
			{
				return true;
			}
		}
	}

	//Vérifie si la sphère intersecte les face du cube

	Plan plan1(centre + normals[0].normalisation() * (taille / 2), normals[0]);
	Plan plan2(centre + normals[1].normalisation() * (taille / 2), normals[1]);
	Plan plan3(centre + normals[2].normalisation() * (taille / 2), normals[2]);
	Plan plan4(centre + normals[0].normalisation() * (taille / -2), normals[0]);
	Plan plan5(centre + normals[1].normalisation() * (taille / -2), normals[1]);
	Plan plan6(centre + normals[2].normalisation() * (taille / -2), normals[2]);


	std::vector<Plan> plans;

	plans.push_back(plan1);
	plans.push_back(plan2);
	plans.push_back(plan3);
	plans.push_back(plan4);
	plans.push_back(plan5);
	plans.push_back(plan6);

	for (int i = 0; i < plans.size(); i++)
	{
		Vecteur3D projete = plans[i].projete(other.getCenter());
		Vecteur3D n1 = plans[(i + 1) % 3].getNormal();
		Vecteur3D n2 = plans[(i + 2) % 3].getNormal();

		if (plans[i].distance(other.getCenter()) <= other.getRadius())
		{
			if (projete.prodscal(n1) <= taille / 2 && projete.prodscal(n1) >= -taille / 2 && projete.prodscal(n2) <= taille / 2 && projete.prodscal(n2) >= -taille / 2)
			{
				return true;
			}
		}
		
	}
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

std::vector<Vecteur3D> Cube::getAngles() const
{
	Vecteur3D A = centre + Vecteur3D(taille / 2, taille / 2, taille / 2);
	Vecteur3D B = centre + Vecteur3D(taille / 2, taille / 2, -taille / 2);
	Vecteur3D C = centre + Vecteur3D(taille / 2, -taille / 2, taille / 2);
	Vecteur3D D = centre + Vecteur3D(taille / 2, -taille / 2, -taille / 2);
	Vecteur3D E = centre + Vecteur3D(-taille / 2, taille / 2, taille / 2);
	Vecteur3D F = centre + Vecteur3D(-taille / 2, taille / 2, -taille / 2);
	Vecteur3D G = centre + Vecteur3D(-taille / 2, -taille / 2, taille / 2);
	Vecteur3D H = centre + Vecteur3D(-taille / 2, -taille / 2, -taille / 2);

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
