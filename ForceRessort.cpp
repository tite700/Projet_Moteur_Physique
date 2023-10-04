#include "ForceRessort.h"

ForceRessort::ForceRessort(float k, float l0, Vecteur3D vect)
{
	this->k = k;
	this->l0 = l0;
	*origine = vect;
}

void ForceRessort::updateForce(Particule* particule, float duration)
{
	Vecteur3D force = particule->getPosition();
	force -= *origine;

	float magnitude = force.norme();
	magnitude = abs(magnitude - l0);
	magnitude *= k;

	force.normalisation();
	force *= -magnitude;
	particule->addForce(force);
}
