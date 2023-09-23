#include "Vector.h"
#include <iostream>

#include "Matrix.h"

Vector::Vector() : x(0), y(0), z(0), w(1) {}

Vector::Vector(float x_, float y_) : x(x_), y(y_), z(0), w(1)
{
}

Vector::Vector(float x_, float y_, float z_) : x(x_), y(y_), z(z_), w(1)
{
}

Vector::Vector(glm::vec3 v) : x(v.x), y(v.y), z(v.z), w(1)
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

Vector operator*(const Vector& v1, const Matrix& m1)
{
	Vector res = v1;
	res *= m1;
	return res;
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
	return Vector(y * v1.z - z * v1.y, z * v1.x - x * v1.z, x * v1.y - y * v1.x);
}

void Vector::setParam(int i, float val)
{
	switch (i) {
	case 0:
		this->x = val;
		break;
	case 1:
		this->y = val;
		break;
	case 2:
		this->z = val;
		break;
	case 3:
		this->w = val;
		break;
	default:
		break;
	}
}

float Vector::getParam(int i)
{
	switch (i) {
	case 0:
		return this->x;
		break;
	case 1:
		return this->y;
		break;
	case 2:
		return this->z;
		break;
	case 3:
		return this->w;
		break;
	default:
		break;
	}
}

Vector Vector::operator-()
{
	return Vector(-x, -y, -z);
}

Vector Vector::operator*=(const Matrix& m1)
{
	Vector res;
	for (int i = 0; i < 4; i++)
	{
		float s = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			s += m1.getElement(i, j) * this->getParam(j);
		}
		res.setParam(i, s);
	}
	*this = res;
	return *this;
}

float Vector::norm()
{
	return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize()
{
	return *this / this->norm();
}

void Vector::print()
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << this->getParam(i) << "," << std::endl;
	}
}

Vector Vector::zeros()
{
	return Vector(0, 0, 0);
}
