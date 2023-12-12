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
	Vecteur3D getDirection() const { return direction; }

	void setCollision(bool collision) { this->collision = collision; }
	void setPointImpact(Vecteur3D pointImpact) { this->pointImpact = pointImpact; }
	void setInterpenetration(float interpenetration) { this->interpenetration = interpenetration; }
	void setDirection(Vecteur3D direction) { this->direction = direction; }

	private :
		bool collision;
		Vecteur3D pointImpact;
		float interpenetration;
		Vecteur3D direction;

};

