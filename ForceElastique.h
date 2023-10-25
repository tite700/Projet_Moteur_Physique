#pragma once
#include "GenerateurForce.h"
class ForceElastique :
    public GenerateurForce
{
    public:
	ForceElastique(float l0, float raideur, Particule* particule1, Particule* particule2, float amrotissement);
	void updateForce(Particule* particule, float duration);
	private:
		float l0;
		float raideur;
		Particule* particule1;
		Particule* particule2;
		float amortissement;
};

