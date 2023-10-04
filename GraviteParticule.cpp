#include "GraviteParticule.h"

GraviteParticule::GraviteParticule(Vecteur3D vect)
{
	gravity = vect;
}

void GraviteParticule::updateForce(Particule* particule, float duration)
{
	if (particule->getInverseMasse() != 0)
	{
		particule->addForce(gravity * particule->getInverseMasse());
	}
}
