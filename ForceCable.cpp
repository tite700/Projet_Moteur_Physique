#include "ForceCable.h"

ForceCable::ForceCable(float distanceMax,float  e, Particule* particule1, Particule* particule2)
{
	this->distanceMax = distanceMax;
	this->particule1 = particule1;
	this->particule2 = particule2;
	this->e = e;
}

void ForceCable::updateForce(Particule* particule, float duration)
{
	float distance = (particule1->getPosition() - particule2->getPosition()).norme();
	if (distance > distanceMax)
	{
		Vecteur3D direction = particule2->getPosition() - particule1->getPosition();
		direction = direction.normalisation();
		float magnitude = particule1->getForce().prodscal(direction);
		particule1->addForce(direction * -magnitude);
		float dirVitesse = particule1->getVelocite().prodscal(direction);
		particule1->setVelocite(particule1->getVelocite() - direction * (1 + e) * dirVitesse);
		particule1->setPosition(particule1->getPosition() - direction * (distanceMax - distance));
		if (abs(particule1->getVelocite().prodscal(direction)) < 100)
		{
			particule1->setVelocite(particule1->getVelocite() - particule1->getVelocite().prodscal(direction)*direction);
		}
	}
}
