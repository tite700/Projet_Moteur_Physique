#include "ForceFrictionStatic.h"

ForceFrictionStatic::ForceFrictionStatic(Vecteur3D force, float k1)
{
		this->k1 = k1;
		this->force = force;
}

void ForceFrictionStatic::updateForce(Particule* particule, float duration)
{
	float norme = force.norme();
	if (norme == 0)
	{
		return;
	}
	force.normalisation();
	force *= -k1;
	particule->addForce(force);
}
