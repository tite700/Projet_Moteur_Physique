#pragma once

#include "ofMain.h"

class Vector
{

public:
	float x;
	float y;
	float z;
	float w;

	glm::vec2 v2() { return glm::vec2(x, y); };
	glm::vec3 v3() { return glm::vec3(x, y, z); };

	Vector();
	Vector(float x_, float y_);
	Vector(float x_, float y_, float z_);

	bool operator==(const Vector& v1);
	Vector operator+=(const Vector& v1);
	Vector operator-=(const Vector& v1);
	Vector operator*=(const float& v1);
	Vector operator-();
	float dot(const Vector& v1);
	Vector cross(const Vector& v1);


	float norm();
	Vector normalize();

	static Vector zeros();
};

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator*(const float& c, const Vector& v1);
Vector operator*(const Vector& v1, const float& c);
Vector operator/(const Vector& v1, const float& c);

