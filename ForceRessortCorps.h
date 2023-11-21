#pragma once
#include "GenerateurForceCorps.h"
#include "CorpsRigide.h"
#include "Vecteur3D.h"
class ForceRessortCorps : public GenerateurForceCorps
{
private:
	// Anchor point in Local coordinate
	Vecteur3D m_bodyAnchor;

	CorpsRigide* m_otherCorpsRigide = nullptr;
	// Othe anchor point in other's Local coordinate
	Vecteur3D m_otherBodyAnchor;

	// spring parameters
	float m_k;
	float m_restLenght;
	float limiteElasticite;
	float coefficientAmortissement;

public:
	ForceRessortCorps(float k, float l0, float limiteElasticite, Vecteur3D vect = Vecteur3D(0.0f, 0.0f, 0.0f), float coefficientAmortissement = 0.5);
	// Transform each anchor point in world coordiante
	// calculate the spring force and apply it at anchor point
	void UpdateForce(CorpsRigide* corpsRigide) override;
};



