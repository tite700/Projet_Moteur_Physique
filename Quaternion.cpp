#include "Quaternion.h"

Quaternion::Quaternion()
{
	a = 0;
	b = 0;
	c = 0;
	d = 0;
}

Quaternion::Quaternion(float a, float b, float c, float d)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	
}

Matrix4 Quaternion::getMatrice() const
{
	Vecteur3D vecteur1(a, -d, c, b);
	Vecteur3D vecteur2(d, a, -b, c);
	Vecteur3D vecteur3(-c, b, a, d);
	Vecteur3D vecteur4(-b, -c, -d, a);

	return Matrix4(vecteur1, vecteur2, vecteur3, vecteur4);
}

Quaternion Quaternion::operator*(const Quaternion& quat) const
{
	float a = this->a * quat.getA() - this->b * quat.getB() - this->c * quat.getC() - this->d * quat.getD();
	float b = this->a * quat.getB() + this->b * quat.getA() + this->c * quat.getD() - this->d * quat.getC();
	float c = this->a * quat.getC() - this->b * quat.getD() + this->c * quat.getA() + this->d * quat.getB();
	float d = this->a * quat.getD() + this->b * quat.getC() - this->c * quat.getB() + this->d * quat.getA();

	return Quaternion(a, b, c, d);
}

Quaternion Quaternion::operator*(const float& scalaire) const
{
	return Quaternion(a * scalaire, b * scalaire, c * scalaire, d * scalaire);
}

Quaternion Quaternion::operator+(const Quaternion& quat) const
{
	return Quaternion(a + quat.getA(), b + quat.getB(), c + quat.getC(), d + quat.getD());
}

Quaternion Quaternion::operator-(const Quaternion& quat) const
{
	return Quaternion(a - quat.getA(), b - quat.getB(), c - quat.getC(), d - quat.getD());
}

Quaternion Quaternion::operator+=(const Quaternion& quat)
{
	a += quat.getA();
	b += quat.getB();
	c += quat.getC();
	d += quat.getD();

	return *this;
}

Quaternion Quaternion::operator-=(const Quaternion& quat)
{
	a -= quat.getA();
	b -= quat.getB();
	c -= quat.getC();
	d -= quat.getD();

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Quaternion& quat)
{
	os << quat.getA() << " + " << quat.getB() << "i + " << quat.getC() << "j + " << quat.getD() << "k";
	return os;
}

Quaternion operator*(const float& scalaire, const Quaternion& quat)
{
	return quat * scalaire;
}

Matrix4 operator*(const Matrix4& matrice, const Quaternion& quat)
{
	return matrice * quat.getMatrice();
}

Matrix4 operator*(const Quaternion& quat, const Matrix4& matrice)
{
	return quat.getMatrice() * matrice;
}
