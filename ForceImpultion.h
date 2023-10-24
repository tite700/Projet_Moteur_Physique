#pragma once
#include "GenerateurForce.h"
class ForceImpultion :
    public GenerateurForce
{
public:
    ForceImpultion(Vecteur3D direction, float norme);
    void updateForce(Particule* particule, float duration);

private:
    Vecteur3D force;
};

