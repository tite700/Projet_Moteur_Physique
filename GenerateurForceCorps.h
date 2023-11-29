#pragma once
#include "CorpsRigide.h"

class GenerateurForceCorps
{
public:
	// Apply force to the CorpsRigide
	virtual void UpdateForce(CorpsRigide* corpsRigide) = 0;
};

