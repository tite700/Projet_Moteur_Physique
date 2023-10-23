#include "ForceRessort.h"

ForceRessort::ForceRessort(float k, float l0, float limiteElasticite, Vecteur3D vect)
{
    this->k = k;
    this->l0 = l0;
    this->limiteElasticite = limiteElasticite;
    this->origine = vect;
    this->particule1 = nullptr;
    this->particule2 = nullptr;
}

ForceRessort::ForceRessort(float k, float l0, float limiteElasticite, Particule* particule1, Particule* particule2)
{
    this->k = k;
    this->l0 = l0;
    this->limiteElasticite = limiteElasticite;
    this->origine = Vecteur3D(); // Pas d'origine fixe
    this->particule1 = particule1;
    this->particule2 = particule2;
}

void ForceRessort::updateForce(Particule* particule, float duration)
{
    Vecteur3D force;

    if (particule1 != nullptr && particule2 != nullptr) {
        // Cas d'un ressort reliant deux particules
        force = particule1->getPosition() - particule2->getPosition(); // Utilisez les deux particules pour la direction
    }
    else {
        // Cas d'un ressort reliant une particule à une masse fixe
        force = particule->getPosition() - origine; // Utilisez l'origine comme point de fixation
    }

    float magnitude = force.norme();
    float deformation = magnitude - l0;

    if (deformation > limiteElasticite) {
        magnitude = limiteElasticite;
    }

    magnitude *= k;

    force.normalisation();
    force *= -magnitude;

    if (particule1 != nullptr) {
        particule1->addForce(force); 
    }
    if (particule2 != nullptr) {
        Vecteur3D nullvect = Vecteur3D();
        particule2->addForce(nullvect-force);
    }
}
