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
        velocite += forceRes * inverseMasse * temps;

    }
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

void Particule::setPosition(const Vecteur3D& vect_position)
{
    	position = vect_position;
}

void Particule::setVelocite(const Vecteur3D& vect_velocite)
{
    		velocite = vect_velocite;
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

void Particule::resolveCollision(Particule* p1, Particule* p2)
{
    //Séparation des particules
    float d = (p1->getSurface() + p2->getSurface()) - (p1->getPosition() - p2->getPosition()).norme();
    Vecteur3D n = (p1->getPosition() - p2->getPosition()).normalisation();
    float pos1 = p2->getMass() / (p1->getMass() + p2->getMass()) * d;
    float pos2 = p1->getMass() / (p1->getMass() + p2->getMass()) * d;
    p1->setPosition(p1->getPosition() + n * pos1);
    p2->setPosition(p2->getPosition() - n * pos2);
    
    //Calcul des nouvelles vitesses

    //Vecteur normal
    Vecteur3D normal = (p1->getPosition() - p2->getPosition()).normalisation();

    //Vecteur tangent
    Vecteur3D tangent = Vecteur3D(-normal.getY(), normal.getX(), 0.0f);

    //Projection des vitesses sur les vecteurs normal et tangent
    float v1n = p1->getVelocite().prodscal(normal);
    float v1t = p1->getVelocite().prodscal(tangent);
    float v2n = p2->getVelocite().prodscal(normal);
    float v2t = p2->getVelocite().prodscal(tangent);

    //Calcul des nouvelles vitesses
    float v2nPrime = (v2n * (p1->getMass() - p2->getMass()) + 2 * p2->getMass() * v1n) / (p1->getMass() + p2->getMass());
    float v1nPrime = (v1n * (p2->getMass() - p1->getMass()) + 2 * p1->getMass() * v2n) / (p1->getMass() + p2->getMass());

    //Mise à jour des vitesses
    p1->setVelocite(normal * v1nPrime + tangent * v1t);
    p2->setVelocite(normal * v2nPrime + tangent * v2t);
    

}



