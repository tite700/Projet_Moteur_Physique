#include "ForceRessort.h"

ForceRessort::ForceRessort(float k, float l0, float limiteElasticite, Vecteur3D vect, float coefficientAmortissement)
{
    this->k = k;
    this->l0 = l0;
    this->limiteElasticite = limiteElasticite;
    this->origine = vect;
    this->particule1 = nullptr;
    this->particule2 = nullptr;
    this->coefficientAmortissement = coefficientAmortissement;
}

ForceRessort::ForceRessort(float k, float l0, float limiteElasticite, Particule* particule1, Particule* particule2, float coefficientAmortissement)
{
    this->k = k;
    this->l0 = l0;
    this->limiteElasticite = limiteElasticite;
    this->origine = Vecteur3D(); // Pas d'origine fixe
    this->particule1 = particule1;
    this->particule2 = particule2;
    this->coefficientAmortissement = coefficientAmortissement;
}

void ForceRessort::updateForce(Particule* particule, float duration)
{
    Vecteur3D direction;
    float distance;

    if (particule1 != nullptr && particule2 != nullptr) {
        // Cas d'un ressort reliant deux particules
        direction = particule1->getPosition() - particule2->getPosition(); // Utilisez les deux particules pour la direction
        distance = direction.norme();
        direction = direction.normalisation();
    }
    else {
        // Cas d'un ressort reliant une particule à une masse fixe
        direction = particule->getPosition() - origine; // Utilisez l'origine comme point de fixation
        distance = direction.norme();
        direction = direction.normalisation();
    }
    
    float deformation = distance - l0;
    if (abs(deformation) < 5)
    {
		return;
	}
    Vecteur3D force(0, 0, 0);

    if (deformation > limiteElasticite) {
        /*
            direction = direction.normalisation();
            float magnitude = particule->getForce().prodscal(direction);
            particule->addForce(direction * -magnitude);
            float dirVitesse = particule->getVelocite().prodscal(direction);
            deformation = limiteElasticite;
        */
        float magnitude = particule1->getForce().prodscal(direction);
        particule1->addForce(direction * -magnitude);
        float dirVitesse = particule1->getVelocite().prodscal(direction);
        particule1->setVelocite(particule1->getVelocite() - direction * dirVitesse);
        particule1->setPosition(particule1->getPosition() - direction * (limiteElasticite - distance));
        if (abs(particule1->getVelocite().prodscal(direction)) < 100)
        {
            particule1->setVelocite(particule1->getVelocite() - particule1->getVelocite().prodscal(direction) * direction);
        }
    }
    else {
        force = direction * (-k * deformation) - coefficientAmortissement * particule->getVelocite();
        force = force * 0.5;
        }
        



    particule->addForce(force); 


}
