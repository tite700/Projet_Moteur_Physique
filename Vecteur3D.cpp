#include "Vecteur3D.h"
#include <iostream>

// Constructeur
Vecteur3D::Vecteur3D(float a, float b, float c, float d)
{
    x = a;
    y = b;
    z = c;
    w = d;
    std::cout << "Constructor executed" << x << y << std::endl;
}

// Getters
glm::vec2 Vecteur3D::vec2()
{
    return glm::vec2(x, y);
}

glm::vec3 Vecteur3D::vec3()
{
    return glm::vec3(x, y, z);
}

// Op�rations
Vecteur3D Vecteur3D::operator+(const Vecteur3D& vect) const
{
    return Vecteur3D(x + vect.x, y + vect.y, z + vect.z);
}

Vecteur3D Vecteur3D::operator-(const Vecteur3D& vect) const
{
    return Vecteur3D(x - vect.x, y - vect.y, z - vect.z);
}

Vecteur3D Vecteur3D::operator*(float scalaire) const
{
    return Vecteur3D(x * scalaire, y * scalaire, z * scalaire);
}

Vecteur3D Vecteur3D::normalisation() const
{
    float n = norme();
    if (n != 0.0f) {
        return Vecteur3D(x / n, y / n, z / n);
    }
    return Vecteur3D();
}

// M�thodes
float Vecteur3D::prodscal(const Vecteur3D& vect) const
{
    return (x * vect.x + y * vect.y + z * vect.z);
}

Vecteur3D Vecteur3D::prodvect(const Vecteur3D& vect) const
{
    return Vecteur3D(
        y * vect.z - z * vect.y,
        z * vect.x - x * vect.z,
        x * vect.y - y * vect.x
    );
}

float Vecteur3D::norme() const
{
    return sqrt(x * x + y * y + z * z);
}