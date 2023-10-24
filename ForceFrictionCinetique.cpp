#include "ForceFrictionCinetique.h"

ForceFrictionCinetique::ForceFrictionCinetique(float k1, float k2)
{
	this->k1 = k1;
	this->k2 = k2;
}

void ForceFrictionCinetique::updateForce(Particule* particule, float duration)
{
	if (particule->getVitesse() == 0)
	{
		return;
	}

	Vecteur3D force;
	force = particule->getVelocite();

	force = force.normalisation();
	force *= -1;


	force *= (k1 * particule->getVitesse()) + (k2 * particule->getVitesse() * particule->getVitesse());

	particule->addForce(force);
}
