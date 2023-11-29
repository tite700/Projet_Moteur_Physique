#pragma once
#include "GenerateurForceCorps.h"
#include "CorpsRigide.h"
#include "Vecteur3D.h"
class ForceImpulsionCorps : public GenerateurForceCorps
{
private:
	Vecteur3D pointImpact;
	float intensite;

public:
	ForceImpulsionCorps(Vecteur3D pointImpact,float intensite);
	void UpdateForce(CorpsRigide* corpsRigide) override;
};


