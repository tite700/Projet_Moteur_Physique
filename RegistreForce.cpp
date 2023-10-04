#include "RegistreForce.h"


void RegistreForce::add(Particule* particule, GenerateurForce* force)
{
	Force f;
	f.particule = particule;
	f.force = force;
	registre.push_back(f);
}

void RegistreForce::clear()
{
	registre.clear();
}

void RegistreForce::remove(Particule* particule, GenerateurForce* force)
{
	for (int i = 0; i < registre.size(); i++)
	{
		if (registre[i].particule == particule && registre[i].force == force)
		{
			registre.erase(registre.begin() + i);
		}
	}
}

void RegistreForce::updateForces(float duration)
{
	for (int i = 0; i < registre.size(); i++)
	{
		registre[i].force->updateForce(registre[i].particule, duration);
	}
}
