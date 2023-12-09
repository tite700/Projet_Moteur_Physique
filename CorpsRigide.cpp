#include "CorpsRigide.h"

// D�finissez la constante de gravit� ou d'autres forces globales ici
const Vecteur3D GRAVITY(0.0f, -9.8f, 0.0f);

// Constructeurs
CorpsRigide::CorpsRigide() :
    m_position(0.0f, 0.0f, 0.0f),
    m_velocity(0.0f, 0.0f, 0.0f),
    m_acceleration(0.0f, 0.0f, 0.0f),
    m_forceAccum(0.0f, 0.0f, 0.0f),
    m_torqueAccum(0.0f, 0.0f, 0.0f),
    m_accelerationAngulaire(0.0f, 0.0f, 0.0f),
    m_velocityAngulaire(0.0f, 0.0f, 0.0f),
    m_inverseMass(1.0f)
{
    // Initialisez votre orientation ici
    m_orientation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}
CorpsRigide::CorpsRigide(Vecteur3D Position,Vecteur3D Velocity,Vecteur3D Acceleration,Quaternion Orientation,float InverseMasse,Vecteur3D VelocityAngulaire,Vecteur3D AccelerationAngulaire, Primitive* primitive)
{
    m_position = Position;
    m_velocity = Velocity;
    m_acceleration = Acceleration;
    m_accelerationAngulaire = AccelerationAngulaire;
    m_velocityAngulaire = VelocityAngulaire;
    m_inverseMass = InverseMasse;
    // Initialisez votre orientation ici
    m_orientation = Orientation;
    m_forceAccum = Vecteur3D(0.0f, 0.0f, 0.0f);
    m_torqueAccum = Vecteur3D(0.0f, 0.0f, 0.0f);
    m_primitive = primitive;
    
}
CorpsRigide::~CorpsRigide()
{
    // Lib�rez les ressources si n�cessaire
}

// Methodes
void CorpsRigide::addForce(const Vecteur3D& force)
{
    m_forceAccum += force;
}
void CorpsRigide::addTorque(const Vecteur3D& torque)
{
    m_torqueAccum.setX(m_torqueAccum.getX() + torque.getX());
    m_torqueAccum.setY(m_torqueAccum.getY() + torque.getY());
    m_torqueAccum.setZ(m_torqueAccum.getZ() + torque.getZ());
}
void CorpsRigide::clearAccumulators()
{
    m_forceAccum = Vecteur3D(0.0f, 0.0f, 0.0f);
    m_torqueAccum = Vecteur3D(0.0f, 0.0f, 0.0f);
}
void CorpsRigide::Integrate(float duration)
{
    

    // Mise � jour de la position
    m_position += m_velocity * duration;

    // Mise � jour de l'orientation en utilisant les quaternions
    Quaternion angulaVelocityQuat(0, m_velocityAngulaire.getX(), m_velocityAngulaire.getY(), m_velocityAngulaire.getZ());
    Quaternion orientationDelta = (angulaVelocityQuat * m_orientation) * (duration * 0.5f);
    m_orientation = m_orientation + orientationDelta;
    m_orientation.normalize();

    // Mise � jour de la v�locit� et de l'acc�l�ration lin�aires
    m_acceleration = m_forceAccum * m_inverseMass;
    m_velocity += m_acceleration * duration;
    
    //Calcul de la matrice d'inertie
    float a = (1.0 / 12.0) * (1.0 / m_inverseMass);
    Matrix3 I = Matrix3(1 / (a * (10.0 + 10.0)), 0.0, 0.0, 0.0, 1 / (a * (10 + 10)), 0.0, 0.0, 0.0, 1 / (a * (10 + 10)));
    Matrix3 I_inverse = Matrix3(1 / (a * (100 + 100)), 0.0, 0.0, 0.0, 1 / (a * (100 + 100)), 0.0, 0.0, 0.0, 1 / (a * (100 + 100)));

    // Mise � jour de la velocite et de l'acc�l�ration angulaire
    Matrix3 I_inverse_prime = m_orientation.toMatrix3() * I_inverse * m_orientation.toMatrix3().transpose();
    m_accelerationAngulaire = I_inverse_prime * m_torqueAccum*1000;
    m_velocityAngulaire += m_accelerationAngulaire * duration;
    

    /*
    ofLogNotice("I_inverse_prime") << "\n" << I_inverse_prime << "\n";
    ofLogNotice("m_forceAccum") << "\n" << m_forceAccum << "\n";
    ofLogNotice("m_velocity") << "\n" << m_velocity << "\n";
    ofLogNotice("m_torqueAccum") << "\n" << m_torqueAccum << "\n";
    ofLogNotice("m_accelerationAngulaire") << "\n" << m_accelerationAngulaire << "\n";
    ofLogNotice("m_velocityAngulaire") << "\n" << m_velocityAngulaire << "\n";
    */
    
    // Remettre a zero les accumulateurs
    m_forceAccum = Vecteur3D(0.0f, 0.0f, 0.0f);
    m_torqueAccum = Vecteur3D(0.0f, 0.0f, 0.0f);

    UpdatePrimitive();
}
void CorpsRigide::CalculateDerivedData()
{
}

void CorpsRigide::UpdatePrimitive()
{
    if (m_primitive == nullptr)
    {
        std::cout << "Warning : Primitive is null" << std::endl;
        return;
    }
    m_primitive->setPosition(m_position);
	m_primitive->setRotation(m_orientation);
}

// Getters
Vecteur3D CorpsRigide::getPosition() const
{
    return this->m_position;
}
Vecteur3D CorpsRigide::getVelocite() const
{
    return this->m_velocity;
}
Vecteur3D CorpsRigide::getAcceleration() const
{
    return this->m_acceleration;
}
Vecteur3D CorpsRigide::getAccelerationAngulaire() const
{
    return this->m_accelerationAngulaire;
}
Vecteur3D CorpsRigide::getVelocityAngulaire() const
{
    return this->m_velocityAngulaire;
}
Vecteur3D CorpsRigide::getTorqueAccum() const
{
    return this->m_torqueAccum;
}
Vecteur3D CorpsRigide::getForceAccum() const
{
    return this->m_forceAccum;
}
float CorpsRigide::getInverseMass() const
{
    return this->m_inverseMass;
}
float CorpsRigide::getMass() const
{
    return 1/this->m_inverseMass;
}
Matrix3 CorpsRigide::getOrientation() const
{
    return this->m_orientation.toMatrix3();
}
Quaternion CorpsRigide::getOrientationQuat() const
{
    return m_orientation;
}


// setters
void CorpsRigide::setPosition(const Vecteur3D& position)
{
    this->m_position = position;
}
void CorpsRigide::setVelocite(const Vecteur3D& velocity)
{
    this->m_velocity = velocity;
}
void CorpsRigide::setAcceleration(const Vecteur3D& acceleration)
{
    this->m_acceleration = acceleration;
}
void CorpsRigide::setAccelerationAngulaire(const Vecteur3D& accelerationAngulaire)
{
    this->m_accelerationAngulaire = accelerationAngulaire;
}
void CorpsRigide::setVelocityAngulaire(const Vecteur3D& velocityAngulaire)
{
    this->m_velocityAngulaire = velocityAngulaire;
}
void CorpsRigide::setTorqueAccum(const Vecteur3D& torqueAccum)
{
    this->m_torqueAccum = torqueAccum;
}
void CorpsRigide::setForceAccum(const Vecteur3D& forceAccum)
{
    this->m_forceAccum = forceAccum;
}
void CorpsRigide::setInverseMass(float inverseMass)
{
    this->m_inverseMass = inverseMass;
}
void CorpsRigide::setOrientation(const Quaternion& orientation)
{
    this->m_orientation = orientation;
}

void CorpsRigide::draw() const
{
    m_primitive->draw();
}


