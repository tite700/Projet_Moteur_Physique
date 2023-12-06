#pragma once
#include "./Vecteur3D.h"
#include "./Particule.h"
#include "./RegistreForce.h"
#include "./ForceRessort.h"
#include "./Blob.h"
#include "./ForceImpultion.h"
#include "./ForceElastique.h"
#include "./UnitTest.h"
#include "./CorpsRigide.h"
#include "./RegistreForceCorps.h"
#include "./ForceGraviteCorps.h"
#include "./ForceImpulsionCorps.h"


class Primitive
{
	public:
		Primitive();
		~Primitive();
		virtual bool isInSpace(Vecteur3D point, float width);

	private:
		Vecteur3D position;


};

