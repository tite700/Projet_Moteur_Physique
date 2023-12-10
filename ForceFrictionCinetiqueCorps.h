#pragma once
#include "CorpsRigide.h"
#include "GenerateurForceCorps.h"

class ForceFrictionCinetiqueCorps :public GenerateurForceCorps
{
public:
	ForceFrictionCinetiqueCorps(float k1 = 0, float k2 = 0);
	void UpdateForce(CorpsRigide* particule) override;

private:
	float k1;
	float k2;
};

