#include "ForceGraviteCorps.h"

ForceGraviteCorps::ForceGraviteCorps()
{
}

void ForceGraviteCorps::UpdateForce(CorpsRigide* corpsRigide)
{
	if (corpsRigide->getInverseMass() != 0)
	{
		corpsRigide->addForce(gravity * corpsRigide->getMass());
	}
}