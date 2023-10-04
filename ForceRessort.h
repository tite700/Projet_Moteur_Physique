#pragma once
#include "GenerateurForce.h"
class ForceRessort :
    public GenerateurForce
{
    public:
	ForceRessort(float k, float l0, Vecteur3D vect = Vecteur3D(0.0f, 0.0f, 0.0f));
	void updateForce(Particule* particule, float duration);

	private:
		Vecteur3D* origine;
		float k;
		float l0;
};

