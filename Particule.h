#pragma once
#include "Vecteur3D.h"
#include <vector>

class Particule {
public:
    Particule(float trainee, float couleur, float surface, float masseInverse = 1.0f, Vecteur3D vect_position = Vecteur3D(), Vecteur3D vect_velocite = Vecteur3D());

    // Accesseurs pour l'attribut InverseMasse
    float getTrainee() const;
    float getCouleur() const;
    float getInverseMasse() const;
    float getMass() const;
    float getSurface() const;
    void setInverseMasse(float masseInverse);

    // M�thode pour mettre � jour la particule � chaque frame
    void integrer(float temps);

    // Accesseurs pour la position et la v�locit�
    const Vecteur3D& getPosition() const;
    const Vecteur3D& getVelocite() const;

    //Forces
    Vecteur3D getForce() const;
    void addForce(const Vecteur3D& force);
    void clearForce();


private:
    float trainee; //train�e de la particule
    float couleur; //couleur de la particule
    float surface; //surface de la particule
    float inverseMasse; // L'inverse de la masse pour faciliter les calculs
    Vecteur3D position; // Position actuelle de la particule
    Vecteur3D velocite; // V�locit� actuelle de la particule
    Vecteur3D forceRes; // Accumulateur de forces

    // Autres attributs n�cessaires, par exemple, les forces appliqu�es
};