#pragma once
#include "GenerateurForceCorps.h"
#include "CorpsRigide.h"
#include "Vecteur3D.h"
class ForceGraviteCorps : public GenerateurForceCorps
{
public:
	ForceGraviteCorps();
	void UpdateForce(CorpsRigide* corpsRigide) override;

private:

	Vecteur3D gravity = Vecteur3D(0.0f, -98.1f, 0.0f);
};



