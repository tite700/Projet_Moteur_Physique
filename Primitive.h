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
		virtual void draw() const;
		virtual bool intersect(const Primitive& other) const;

	protected:
		Vecteur3D position;
		ofColor color;


};

