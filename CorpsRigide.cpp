#include "CorpsRigide.h"

void CorpsRigide::update(float duration)
{
	for (CorpsRigide* child : m_children)
		child->update(duration);
	if (m_parent != nullptr)
	{
		m_position += m_velocity * duration;
		m_orientation = (0.5f * m_orientation.getMatrice() * m_velocity * duration).toQuaternion();
		m_velocity += m_forceAccum * duration;
		m_torqueAccum += m_torque * duration;
		m_forceAccum = Vecteur3D(0.0f, 0.0f, 0.0f);
		m_torque = Vecteur3D(0.0f, 0.0f, 0.0f);

	}
}
