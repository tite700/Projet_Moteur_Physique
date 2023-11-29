#pragma once

#include "Quaternion.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include <vector>
#include "Vecteur3D.h"

class CorpsRigide
{
public:
	// Constructeurs
	CorpsRigide();
	CorpsRigide(Vecteur3D Position, Vecteur3D Velocity, Vecteur3D Acceleration, Quaternion Orientation,float InverseMasse, Vecteur3D VelocityAngulaire, Vecteur3D AccelerationAngulaire);
	~CorpsRigide();
	
	// Add force on the center of mass (no torque generated)
	void addForce(const Vecteur3D &force);



	/*
	// Add force at a point in local coordinate, the point is converted in world coordinated
	// by using the transform Matrix
	void addForceAtBodyPoint(const Vecteur3D& force, const Vecteur3D& Localpoint);
	*/
	void addTorque(const Vecteur3D &torque);

	// Called each frame to reset m_forceAccum and m_torqueAccum
	void clearAccumulators();

	// Integrate the rigid body by modifying position, orientation and velocities
	void Integrate(float duration);

	//getters
	Vecteur3D getPosition() const;
	Vecteur3D getVelocite() const;
	Vecteur3D getAcceleration() const;
	Vecteur3D getLastFrameAcceleration() const;
	Vecteur3D getAccelerationAngulaire() const;
	Vecteur3D getVelocityAngulaire() const;
	Vecteur3D getTorque() const;
	Vecteur3D getTorqueAccum() const;
	Vecteur3D getForceAccum() const;
	float getInverseMass() const;
	float getMass() const;
	Matrix3 getOrientation() const;
	Quaternion getOrientationQuat() const;
	Vecteur3D getPointInLocalSpace(const Vecteur3D &point) const;
	Vecteur3D getPointInWorldSpace(const Vecteur3D &point) const;
	Vecteur3D getDirectionInLocalSpace(const Vecteur3D &direction) const;
	Vecteur3D getDirectionInWorldSpace(const Vecteur3D &direction) const;
	Vecteur3D getTransformedPoint(const Vecteur3D &point) const;
	Vecteur3D getTransformedDirection(const Vecteur3D &direction) const;
	Vecteur3D getTransformedPointInverse(const Vecteur3D &point) const;
	Vecteur3D getTransformedDirectionInverse(const Vecteur3D &direction) const;


	//setters
	void setPosition(const Vecteur3D &position);
	void setVelocite(const Vecteur3D &velocity);
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
	float m_inverseMass;
	float linearDamping;


	Vecteur3D m_position; // centre de masse
	Vecteur3D m_velocity;
	Vecteur3D m_acceleration;

	
	Quaternion m_orientation;
	Vecteur3D m_velocityAngulaire;
	Vecteur3D m_accelerationAngulaire;

	Vecteur3D m_forceAccum;
	Vecteur3D m_torqueAccum;

	// Call each frame to calculate the transformMatrix and normazlize the orientation
	void CalculateDerivedData();

};

