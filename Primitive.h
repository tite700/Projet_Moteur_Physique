#pragma once
#include "./Vecteur3D.h"
#include "./Quaternion.h"

class Primitive
{
	public:
		Primitive();
		~Primitive();
		virtual void draw() const;
		virtual bool intersect(const Primitive& other) const;

		void setPosition(const Vecteur3D position) { this->position = position; }
		void setRotation(const Quaternion rotation) { this->rotation = rotation; }

		Vecteur3D getPosition() const { return position; }
		Quaternion getRotation() const { return rotation; }

	protected:
		Vecteur3D position;
		Quaternion rotation;
		ofColor color;


};

