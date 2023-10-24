#pragma once
#include "GenerateurForce.h"
class ForceCable :
    public GenerateurForce
{
public: 
    ForceCable(float distanceMax, float e, Particule* particule1, Particule* particule2);
    void updateForce(Particule* particule, float duration);
private:
    float distanceMax;
    float e;
    Particule* particule1;
    Particule* particule2;

};

