#pragma once
#include "Particule.h"
class GenerateurForce
{
public:
	virtual void updateForce(Particule* particule, float duration) = 0;
};

