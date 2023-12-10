#pragma once

#include "Vecteur3D.h"

class CollisionData
{
	public :
	CollisionData();
	CollisionData(bool collision, Vecteur3D pointImpact = Vecteur3D::zeros(), float interpenetration = 0, Vecteur3D direction = Vecteur3D::zeros());

	void print() const;

	bool getCollision() const { return collision; }
	Vecteur3D getPointImpact() const { return pointImpact; }
	float getInterpenetration() const { return interpenetration; }

	private :
		bool collision;
		Vecteur3D pointImpact;
		float interpenetration;
		Vecteur3D direction;

};

