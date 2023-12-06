#include "Blob.h"

Blob::Blob(float size, int nParticules, Vecteur3D position, float masse, float couleur, float trainee) : espace(size), trainee(trainee), couleur(couleur), masse(masse), surface(size)
{

	std::vector<Vecteur3D> positions;
	float rayon = 2*PI*size;
	float angle = 0;
	float angleIncrement = 2 * PI / nParticules;

	for (int i = 0; i < nParticules; i++) {
		float x = position.getX() + rayon * cos(angle);
		float y = position.getY() + rayon * sin(angle);
		positions.push_back(Vecteur3D(x, y, 0));
		angle += angleIncrement;
	}

	for (int i = 0; i < nParticules; i++) {
		Particule* nouvelleParticule = new Particule(trainee, couleur, surface, 1/masse, positions[i], Vecteur3D());
		particules.push_back(nouvelleParticule);
	}

	center = new Particule(trainee, couleur, surface, 1/masse, position, Vecteur3D());
	distance = (particules[0]->getPosition() - (particules[1]->getPosition())).norme();
	centerDistance = (particules[0]->getPosition() - center->getPosition()).norme();

}

std::vector<ForceRessort*> Blob::generateForces()
{
	float k = 20;
	float amortissement = 0.9;
	std::vector<ForceRessort*> forces;
	for (int i = 0; i < particules.size(); i++) {
		ForceRessort* force = new ForceRessort(k, distance, distance * 1.1, particules[i], particules[(i + 1) % particules.size()], amortissement);
		ForceRessort* force2 = new ForceRessort(k, distance, distance * 1.1, particules[(i + 1) % particules.size()], particules[i], amortissement);
		ForceRessort* force3 = new ForceRessort(k, centerDistance, centerDistance * 1.1, particules[i], center, amortissement);
		ForceRessort* force4 = new ForceRessort(k, centerDistance, centerDistance * 1.1, center, particules[i], amortissement);
		forces.push_back(force);
		forces.push_back(force2);
		forces.push_back(force3);
		forces.push_back(force4);
	}
	return forces;
}

std::vector<Particule*> Blob::getParticules()
{
	return particules;
}

Particule* Blob::getCenter()
{
	return center;
}

//test