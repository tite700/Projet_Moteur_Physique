#pragma once

#include "Quaternion.h"
#include <vector>
#include "Vecteur3D.h"

class CorpsRigide
{
public:
	CorpsRigide();
	~CorpsRigide();

	void update(float duration);
	void addForce(const Vecteur3D &force);
	void addForceAtPoint(const Vecteur3D &force, const Vecteur3D &point);
	void addTorque(const Vecteur3D &torque);
	void clearAccumulators();


	//getters
	Vecteur3D getPosition() const;
	Vecteur3D getVelocity() const;
	Vecteur3D getAcceleration() const;
	Vecteur3D getLastFrameAcceleration() const;
	Vecteur3D getAccelerationAngulaire() const;
	Vecteur3D getVelocityAngulaire() const;
	Vecteur3D getTorque() const;
	Vecteur3D getTorqueAccum() const;
	Vecteur3D getForceAccum() const;
	float getInverseMass() const;
	float getMass() const;
	Quaternion getOrientation() const;
	Vecteur3D getPointInLocalSpace(const Vecteur3D &point) const;
	Vecteur3D getPointInWorldSpace(const Vecteur3D &point) const;
	Vecteur3D getDirectionInLocalSpace(const Vecteur3D &direction) const;
	Vecteur3D getDirectionInWorldSpace(const Vecteur3D &direction) const;
	Vecteur3D getTransformedPoint(const Vecteur3D &point) const;
	Vecteur3D getTransformedDirection(const Vecteur3D &direction) const;
	Vecteur3D getTransformedPointInverse(const Vecteur3D &point) const;
	Vecteur3D getTransformedDirectionInverse(const Vecteur3D &direction) const;
	CorpsRigide* getParent() const;
	std::vector<CorpsRigide*> getChildren() const;

	//setters

	void setPosition(const Vecteur3D &position);
	void setVelocity(const Vecteur3D &velocity);
	void setAcceleration(const Vecteur3D &acceleration);
	void setLastFrameAcceleration(const Vecteur3D &lastFrameAcceleration);
	void setAccelerationAngulaire(const Vecteur3D &accelerationAngulaire);
	void setVelocityAngulaire(const Vecteur3D &velocityAngulaire);
	void setTorque(const Vecteur3D &torque);
	void setTorqueAccum(const Vecteur3D &torqueAccum);
	void setForceAccum(const Vecteur3D &forceAccum);
	void setInverseMass(float inverseMass);
	void setOrientation(const Quaternion &orientation);



private:
	std::vector<CorpsRigide*> m_children;
	CorpsRigide* m_parent;

	Quaternion m_orientation;
	Vecteur3D m_position; // centre de masse

	Vecteur3D m_velocity;
	Vecteur3D m_acceleration;

	Vecteur3D m_forceAccum;
	Vecteur3D m_torqueAccum;

	Vecteur3D m_accelerationAngulaire;
	Vecteur3D m_velocityAngulaire;
	Vecteur3D m_torque;

	Vecteur3D m_lastFrameAcceleration;
	float m_inverseMass;


};

