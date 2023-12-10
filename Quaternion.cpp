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

Quaternion::Quaternion(Matrix3 matrice)
{
	*this = matrice.toQuaternion();
}

Matrix3 Quaternion::getMatrice() const
{
	Vecteur3D vecteur1(1 - 2*(c * c + d *d), 2*(a*b + c*d), 2*(a*c - b*d));
	Vecteur3D vecteur2(2*(a*b - c*d), 1 - 2*(a*a + c*c), 2*(b*c + a*d));
	Vecteur3D vecteur3(2*(a*c + b*d), 2*(b*c - a*d), 1 - 2*(a*a + b*b));
	Vecteur3D vecteur4(0, 0, 0);

	return Matrix3(vecteur1, vecteur2, vecteur3);
}


void Quaternion::normalize()
{
	float norm = std::sqrt(a * a + b * b + c * c + d * d);
	if (norm != 0.0f)
	{
		float sign = (a < 0) ? -1.0f : 1.0f;
		a = sign * a / norm;
		b = sign * b / norm;
		c = sign * c / norm;
		d = sign * d / norm;
	}
}

Quaternion Quaternion::normalized() const
{
	Quaternion result(*this);
	result.normalize();
	return result;
}

Quaternion Quaternion::conjugate() const
{
	return Quaternion(a, -b, -c, -d);
}

Quaternion Quaternion::inverse() const
{
	return conjugate() * (1.0f / (a * a + b * b + c * c + d * d));
}

Matrix3 Quaternion::toMatrix3() const
{
	Vecteur3D vecteur1(1 - 2 * (c * c + d * d), 2 * (a * b + c * d), 2 * (a * c - b * d));
	Vecteur3D vecteur2(2 * (a * b - c * d), 1 - 2 * (a * a + c * c), 2 * (b * c + a * d));
	Vecteur3D vecteur3(2 * (a * c + b * d), 2 * (b * c - a * d), 1 - 2 * (a * a + b * b));

	return Matrix3(vecteur1, vecteur2, vecteur3);
}

Matrix4 Quaternion::toMatrix4() const
{
	Vecteur3D vecteur1(1 - 2 * (c * c + d * d), 2 * (a * b + c * d), 2 * (a * c - b * d));
	Vecteur3D vecteur2(2 * (a * b - c * d), 1 - 2 * (a * a + c * c), 2 * (b * c + a * d));
	Vecteur3D vecteur3(2 * (a * c + b * d), 2 * (b * c - a * d), 1 - 2 * (a * a + b * b));
	Vecteur3D vecteur4(0, 0, 0);

	return Matrix4(vecteur1, vecteur2, vecteur3, vecteur4);
}

Vecteur3D Quaternion::rotateVector(const Vecteur3D& v) const
{
	Quaternion vecQuat(0, v.getX(), v.getY(), v.getZ());

	// On vérifie que le quaternion est bien une rotation (donc normalisé)
	if (!isRotationQuaternion())
	{
		std::cout << "Le quaternion n'est pas une rotation" << std::endl;
		std::cout << "Quaternion : " << *this << std::endl;
		return Vecteur3D();
	}

	Quaternion result = (*this) * vecQuat * conjugate();
	return Vecteur3D(result.getB(), result.getC(), result.getD());
}

bool Quaternion::isRotationQuaternion() const
{
	return std::fabs(1.0f - (a * a + b * b + c * c + d * d)) < 1e-6;
}

Vecteur3D Quaternion::getEulerAngles() const
{
	float phi = std::atan2(2 * (a * b + c * d), 1 - 2 * (b * b + c * c));
	float theta = std::asin(2 * (a * c - d * b));
	float psi = std::atan2(2 * (a * d + b * c), 1 - 2 * (c * c + d * d));

	return Vecteur3D(phi, theta, psi);
}

Vecteur3D Quaternion::getNormal() const
{
	Matrix3 matrice = toMatrix3();
	return Vecteur3D(matrice.getMatrice()[0][1], matrice.getMatrice()[1][1], matrice.getMatrice()[2][1]);

}

Quaternion Quaternion::identity()
{
	return Quaternion(1, 0, 0, 0);
}

Quaternion Quaternion::fromEulerAngles(const Vecteur3D& angles)
{
	float phi = angles.getX();
	float theta = angles.getY();
	float psi = angles.getZ();

	float a = std::cos(phi / 2) * std::cos(theta / 2) * std::cos(psi / 2) + std::sin(phi / 2) * std::sin(theta / 2) * std::sin(psi / 2);
	float b = std::sin(phi / 2) * std::cos(theta / 2) * std::cos(psi / 2) - std::cos(phi / 2) * std::sin(theta / 2) * std::sin(psi / 2);
	float c = std::cos(phi / 2) * std::sin(theta / 2) * std::cos(psi / 2) + std::sin(phi / 2) * std::cos(theta / 2) * std::sin(psi / 2);
	float d = std::cos(phi / 2) * std::cos(theta / 2) * std::sin(psi / 2) - std::sin(phi / 2) * std::sin(theta / 2) * std::cos(psi / 2);

	return Quaternion(a, b, c, d);
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

Matrix3 operator*(const Matrix3& matrice, const Quaternion& quat)
{
	return matrice * quat.getMatrice();
}

Matrix3 operator*(const Quaternion& quat, const Matrix3& matrice)
{
	return quat.getMatrice() * matrice;
}

bool operator==(const Quaternion& quat1, const Quaternion& quat2)
{
	return quat1.getA() == quat2.getA() && quat1.getB() == quat2.getB() && quat1.getC() == quat2.getC() && quat1.getD() == quat2.getD();
}
