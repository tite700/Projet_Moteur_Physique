#include "ForceElastique.h"

ForceElastique::ForceElastique(float l0, float raideur, Particule* particule1, Particule* particule2, float amortissement)
{
	this->l0 = l0;
	this->raideur = raideur;
	this->particule1 = particule1;
	this->particule2 = particule2;
	this->amortissement = amortissement;
}

void ForceElastique::updateForce(Particule* particule, float duration)
{
	Vecteur3D direction;
	float distance;
	direction = particule1->getPosition() - particule2->getPosition(); // Utilisez les deux particules pour la direction
	distance = direction.norme();
	direction = direction.normalisation();

	float deformation = distance - l0;
	if (deformation > 0)
	{
		particule->addForce(direction * -raideur * deformation - amortissement * particule->getVelocite());
	}
	if (particule->getVelocite().norme() < 10)
	{
		particule->setVelocite(particule->getVelocite() * 0);
	}
}
