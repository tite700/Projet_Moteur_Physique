#include "ForceFrictionCinetiqueCorps.h"

ForceFrictionCinetiqueCorps::ForceFrictionCinetiqueCorps(float k1, float k2)
{
	this->k1 = k1;
	this->k2 = k2;
}

void ForceFrictionCinetiqueCorps::UpdateForce(CorpsRigide* particule)
{
	if (particule->getVelocite().norme() == 0)
	{
		return;
	}

	Vecteur3D force;
	force = particule->getVelocite();

	force = force.normalisation();
	force *= -1;
	force *= (k1 * particule->getVelocite().norme()) + (k2 * particule->getVelocite().norme() * particule->getVelocite().norme());
	particule->addForce(force);

	//Vecteur3D torque;
	//torque = particule->getVelocityAngulaire();
	//torque = torque.normalisation();
	//torque *= -1;
	//torque *= (k1 * particule->getVelocityAngulaire().norme()) + (k2 * particule->getVelocityAngulaire().norme() * particule->getVelocityAngulaire().norme());
	//particule->addTorque(torque);
	particule->setVelocityAngulaire(particule->getVelocityAngulaire() * 0.9f);
}
