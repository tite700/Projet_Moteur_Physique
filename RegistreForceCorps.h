#pragma once
#include "Vecteur3D.h"
#include "GenerateurForceCorps.h"
#include "CorpsRigide.h"
#include <vector>

class CorpsRigide;
class RegistreForceCorps
{
public:
	struct Force
	{
		CorpsRigide* corpsRigide;
		GenerateurForceCorps* forceCorps;
	};

	typedef std::vector<Force> Registre;

	void add(CorpsRigide* corpsRigide, GenerateurForceCorps* forceCorps);
	void clear();
	void remove(CorpsRigide* corpsRigide, GenerateurForceCorps* forceCorps);
	void updateForces(float duration);

private:

	Registre registre;


};


