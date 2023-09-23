#include "Vector.h"

Vector::Vector() : x(0), y(0), z(0), w(0) {}

Vector::Vector(float x_, float y_) : x(x_), y(y_), z(0), w(0)
{
}

Vector::Vector(float x_, float y_, float z_) : x(x_), y(y_), z(z_), w(0)
{
}

Vector operator+(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector operator-(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector operator*(const float& c, const Vector& v1)
{
	return Vector(c * v1.x, c * v1.y, c * v1.z);
}

Vector operator*(const Vector& v1, const float& c)
{
	return c * v1;
}

Vector operator/(const Vector& v1, const float& c)
{
	return Vector(v1.x / c, v1.y / c, v1.z / c);
}

bool Vector::operator==(const Vector& v1)
{
	return(x == v1.x && y == v1.y && z == v1.z);
}

Vector Vector::operator+=(const Vector& v1)
{
	x += v1.x;
	y += v1.y;
	z += v1.z;
	return *this;
}

Vector Vector::operator-=(const Vector& v1)
{
	x -= v1.x;
	y -= v1.y;
	z -= v1.z;
	return *this;
}

Vector Vector::operator*=(const float& v1)
{
	x *= v1;
	y *= v1;
	z *= v1;
	return *this;
}

float Vector::dot(const Vector& v1)
{
	float res = sqrt(x * v1.x + y * v1.y + z * v1.z);
	return res;
}

Vector Vector::cross(const Vector& v1)
{
	return Vector(y*v1.z - z*v1.y, z * v1.x - x* v1.z, x*v1.y - y * v1.x);
}

Vector Vector::operator-()
{
	return Vector(-x, -y, -z);
}

float Vector::norm()
{
	return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize()
{
	return *this / this->norm();
}

Vector Vector::zeros()
{
	return Vector(0,0,0);
}