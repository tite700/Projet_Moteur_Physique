#pragma once
#include "GenerateurForceCorps.h"
#include "CorpsRigide.h"
#include "Vecteur3D.h"
class ForceImpulsionCorps : public GenerateurForceCorps
{
private:
	Vecteur3D pointImpact;
	Vecteur3D direction;
	float intensite;

public:
	ForceImpulsionCorps(Vecteur3D pointImpact,float intensite, Vecteur3D direction = Vecteur3D(0, 0, 1));
	void UpdateForce(CorpsRigide* corpsRigide) override;
};


