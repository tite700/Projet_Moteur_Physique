#include "ForceRessortCorps.h"

ForceRessortCorps::ForceRessortCorps(float k, float m_restLenght, float limiteElasticite, Vecteur3D bodyanchor, float coefficientAmortissement)
{
    this->m_k = k;
    this->m_restLenght = m_restLenght;
    this->limiteElasticite = limiteElasticite;
    this->m_bodyAnchor = bodyanchor;
    this->coefficientAmortissement = coefficientAmortissement;
}

void ForceRessortCorps::UpdateForce(CorpsRigide* corpsRigide)
{
    // Cas d'un ressort reliant un corps à une masse fixe
    Vecteur3D direction = corpsRigide->getPosition() - m_bodyAnchor; // Utilisez l'origine comme point de fixation
    float distance = direction.norme();
    direction = direction.normalisation();
    float deformation = distance - m_restLenght;
    Vecteur3D force(0, 0, 0);

    if (deformation > limiteElasticite) {
        /*
            direction = direction.normalisation();
            float magnitude = particule->getForce().prodscal(direction);
            particule->addForce(direction * -magnitude);
            float dirVitesse = particule->getVelocite().prodscal(direction);
            deformation = limiteElasticite;
        */
        float magnitude = corpsRigide->getForceAccum().prodscal(direction);
        corpsRigide->addForce(direction * -magnitude);
        float dirVitesse = corpsRigide->getVelocite().prodscal(direction);
        corpsRigide->setVelocite(corpsRigide->getVelocite() - direction * dirVitesse);
        corpsRigide->setPosition(corpsRigide->getPosition() - direction * (limiteElasticite - distance));
        if (abs(corpsRigide->getVelocite().prodscal(direction)) < 100)
        {
            corpsRigide->setVelocite(corpsRigide->getVelocite() - corpsRigide->getVelocite().prodscal(direction) * direction);
        }
    }
    else {
        force = direction * (-m_k * deformation) - coefficientAmortissement * corpsRigide->getVelocite();
        force = force * 0.5;
    }
    corpsRigide->addForce(force);
}
