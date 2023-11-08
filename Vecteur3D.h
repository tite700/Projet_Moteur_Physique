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
    // Constructeurs
    Vecteur3D(float a = 0, float b = 0, float c = 0, float d = 0);
    Vecteur3D(Vecteur3D* vect);

    // Getters
    glm::vec2 vec2();
    glm::vec3 vec3();
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    float getW() const { return w; }

    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    void setZ(float z) { this->z = z; }
    void setW(float w) { this->w = w; }

    // Surcharge d'opérateurs
    Vecteur3D operator+(const Vecteur3D& vect) const;
    Vecteur3D operator-(const Vecteur3D& vect) const;
    Vecteur3D operator*(float Vecteur3D) const;
    Vecteur3D operator+= (const Vecteur3D& vect);
    Vecteur3D operator-= (const Vecteur3D& vect);
    Vecteur3D operator*= (float scalaire);
    bool operator==(const Vecteur3D& vect) const;
    Vecteur3D normalisation() const;


    // Méthodes
    float prodscal(const Vecteur3D& vect) const;
    Vecteur3D prodvect(const Vecteur3D& vect) const;
    float norme() const;
};

//Opérateurs externes

std::ostream& operator<<(std::ostream& os, const Vecteur3D& vect);

Vecteur3D operator*(float scalaire, const Vecteur3D& vect);

//bool operator==(const Vecteur3D& vect1, const Vecteur3D& vect2);


