#pragma once
#include "GenerateurForce.h"
#include "Particule.h"
#include "Vecteur3D.h"
class ForceFrictionStatic :
    public GenerateurForce
{
    public:
	ForceFrictionStatic(Vecteur3D force, float k1 = 0);
	void updateForce(Particule* particule, float duration);

	private:
		float k1;
		Vecteur3D force;
};

