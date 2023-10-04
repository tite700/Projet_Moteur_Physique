#pragma once
#include "GenerateurForce.h"
class ForceFrictionCinetique :
    public GenerateurForce
{
    public:
	ForceFrictionCinetique(float k1 = 0, float k2 = 0);
	void updateForce(Particule* particule, float duration);

	private:
		float k1;
		float k2;
};

