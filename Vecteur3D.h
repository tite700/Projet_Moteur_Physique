#pragma once
#include <iostream>
#include "ofMain.h"

class Vecteur3D
{
private:
    float x;
    float y;
    float z;
    float w;

public:
    // Constructeur
    Vecteur3D(float a = 0, float b = 0, float c = 0, float d = 0);

    // Getters
    glm::vec2 vec2();
    glm::vec3 vec3();
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    // Surcharge d'opérateurs
    Vecteur3D operator+(const Vecteur3D& vect) const;
    Vecteur3D operator-(const Vecteur3D& vect) const;
    Vecteur3D operator*(float Vecteur3D) const;
    Vecteur3D normalisation() const;

    // Méthodes
    float prodscal(const Vecteur3D& vect) const;
    Vecteur3D prodvect(const Vecteur3D& vect) const;
    float norme() const;
};

