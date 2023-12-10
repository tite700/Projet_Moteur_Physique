#include "Vecteur3D.h"
#include <iostream>

// Constructeur
Vecteur3D::Vecteur3D(float a, float b, float c, float d)
{
    x = a;
    y = b;
    z = c;
    w = d;
}

Vecteur3D::Vecteur3D(Vecteur3D* vect)
{
	x = vect->getX();
	y = vect->getY();
	z = vect->getZ();
	w = vect->w;
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

// Opérations
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

Vecteur3D Vecteur3D::operator+=(const Vecteur3D& vect)
{
    x += vect.x;
	y += vect.y;
	z += vect.z;
	return *this;
}

Vecteur3D Vecteur3D::operator-=(const Vecteur3D& vect)
{
    x -= vect.x;
	y -= vect.y;
	z -= vect.z;
	return *this;
}

Vecteur3D Vecteur3D::operator*=(float scalaire)
{
    x *= scalaire;
	y *= scalaire;
	z *= scalaire;
	return *this;
}

bool Vecteur3D::operator==(const Vecteur3D& vect) const
{
    return (x == vect.x && y == vect.y && z == vect.z);
}

float& Vecteur3D::operator[](int i)
{
if (i == 0) {
		return x;
	}
	else if (i == 1) {
		return y;
	}
	else if (i == 2) {
		return z;
	}
	else {
    throw std::out_of_range("Index out of range");
	}
}


Vecteur3D Vecteur3D::normalisation() const
{
    float n = norme();
    if (n != 0.0f) {
        return Vecteur3D(x / n, y / n, z / n);
    }
    return Vecteur3D();
}


// Méthodes
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

Vecteur3D Vecteur3D::zeros()
{
    return Vecteur3D(0, 0, 0, 1);
}

void Vecteur3D::drawPoint() const
{
    ofSpherePrimitive sphere;
    sphere.setPosition(x, y, z);
    sphere.setRadius(5);
    sphere.draw();
}

std::ostream& operator<<(std::ostream& os, const Vecteur3D& vect)
{
    os << "(" << vect.getX() << ", " << vect.getY() << ", " << vect.getZ() << ")";
	return os;
}

Vecteur3D operator*(float scalaire, const Vecteur3D& vect)
{
    return Vecteur3D(vect.getX() * scalaire, vect.getY() * scalaire, vect.getZ() * scalaire);
}

//bool operator==(const Vecteur3D& vect1, const Vecteur3D& vect2)
//{
//    return (vect1.getX() == vect2.getX() && vect1.getY() == vect2.getY() && vect1.getZ() == vect2.getZ());
//}
//
