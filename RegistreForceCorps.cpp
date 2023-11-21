#include "RegistreForceCorps.h"
void RegistreForceCorps::add(CorpsRigide* corpsRigide, GenerateurForceCorps* forceCorps)
{
	Force f;
	f.corpsRigide = corpsRigide;
	f.forceCorps = forceCorps;
	registre.push_back(f);
}
void RegistreForceCorps::clear()
{
	registre.clear();
}
void RegistreForceCorps::remove(CorpsRigide* corpsRigide, GenerateurForceCorps* forceCorps)
{
	for (int i = 0; i < registre.size(); i++)
	{
		if (registre[i].corpsRigide == corpsRigide && registre[i].forceCorps == forceCorps)
		{
			registre.erase(registre.begin() + i);
		}
	}
}
void RegistreForceCorps::updateForces(float duration)
{
	for (int i = 0; i < registre.size(); i++)
	{
		registre[i].forceCorps->UpdateForce(registre[i].corpsRigide);
	}
}