#pragma once
#include "GenerateurForce.h"
#include "Particule.h"
#include "Vecteur3D.h"
class GraviteParticule :
    public GenerateurForce
{
public:
	GraviteParticule(Vecteur3D vect = Vecteur3D(0.0f, -9.81f, 0.0f));

	void updateForce(Particule* particule, float duration);

private:

	Vecteur3D gravity;
};

