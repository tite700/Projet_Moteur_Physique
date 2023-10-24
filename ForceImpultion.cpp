#include "ForceImpultion.h"

ForceImpultion::ForceImpultion(Vecteur3D direction, float norme)
{
	force = direction * norme;
}

void ForceImpultion::updateForce(Particule* particule, float duration)
{
	particule->addForce(force);
}
