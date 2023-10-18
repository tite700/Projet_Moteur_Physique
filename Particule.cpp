#include "Particule.h"

Particule::Particule(float Trainee, float Couleur, float Surface, float masseInverse, Vecteur3D vect_position, Vecteur3D vect_velocite)
{
    trainee = Trainee;
    couleur = Couleur;
    inverseMasse = masseInverse;
    position = vect_position;
    velocite = vect_velocite;
    surface = Surface;
}

float Particule::getTrainee() const
{
    return this->trainee;
}
float Particule::getCouleur() const
{
    return this->couleur;
}
float Particule::getInverseMasse() const
{
    return this->inverseMasse;
}

float Particule::getMass() const
{
    if (this->inverseMasse == 0.0f)
		return FLT_MAX;
	else if (this->inverseMasse == FLT_MAX)
		return 0.0f;
	else if (this->inverseMasse < 0.0f)
		return -1.0f / this->inverseMasse;
	else if (this->inverseMasse > 0.0f)
    return 1.0f / this->inverseMasse;
}

float Particule::getSurface() const
{
    return this->surface;
}

void Particule::setInverseMasse(float masseInverse)
{
    inverseMasse = masseInverse;
}

void Particule::integrer(float temps) {
    if (inverseMasse != 0.0f) {
        // Mettre à jour la position et la vélocité en utilisant l'intégration d'Euler
        position = position + (velocite * temps);

        // Mettre à jour la vélocité en fonction des forces appliquées

        //Gravité
        Vecteur3D forceGravite(0.0f, 981.0f, 0.0f);
        //Frotements
        float coeffFrottement = -0.01f * this->surface;
        Vecteur3D forceFrottement(velocite.getX() * coeffFrottement, velocite.getY() * coeffFrottement, 0.0f);

        velocite = velocite + ((forceFrottement * inverseMasse + forceGravite) * temps);
    }
    // Sinon, la particule reste immobile (inverseMasse == 0).
}



const Vecteur3D& Particule::getPosition() const
{
    return position;
}

const Vecteur3D& Particule::getVelocite() const
{
    return velocite;
}

const float Particule::getVitesse() const
{
    return velocite.norme();
}

Vecteur3D Particule::getForce() const
{
    return forceRes;
}

void Particule::addForce(const Vecteur3D& force)
{
    forceRes = forceRes + force;
}

void Particule::clearForce()
{
    	forceRes = Vecteur3D();
}

bool Particule::collision(Particule* p1, Particule* p2)
{
    return (p1->getPosition() - p2->getPosition()).norme() <= (p1->getSurface() + p2->getSurface());
}



