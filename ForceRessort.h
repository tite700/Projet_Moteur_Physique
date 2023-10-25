#pragma once
#include "GenerateurForce.h"
class ForceRessort :
    public GenerateurForce
{
    public:
	ForceRessort(float k, float l0, float limiteElasticite, Vecteur3D vect = Vecteur3D(0.0f, 0.0f, 0.0f), float coefficientAmortissement = 0.5);
	ForceRessort(float k, float l0, float limiteElasticite, Particule* particule1, Particule* particule2, float coefficientAmortissement = 0.5);
	void updateForce(Particule* particule, float duration);

	private:
		Vecteur3D origine;
		float k;
		float l0;
		float limiteElasticite;
		float coefficientAmortissement;
		Particule* particule1;
		Particule* particule2;

};

