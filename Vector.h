#pragma once

#include "ofMain.h"

class Matrix;

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
	Vector(glm::vec3 v);

	bool operator==(const Vector& v1);
	Vector operator+=(const Vector& v1);
	Vector operator-=(const Vector& v1);
	Vector operator*=(const float& v1);
	Vector operator-();
	Vector operator*=(const Matrix& m1);
	float dot(const Vector& v1);
	Vector cross(const Vector& v1);

	void setParam(int i, float val);
	float getParam(int i);



	float norm();
	Vector normalize();
	void print();


	static Vector zeros();
};

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator*(const float& c, const Vector& v1);
Vector operator*(const Vector& v1, const float& c);
Vector operator*(const Vector& v1, const Matrix& m1);

Vector operator/(const Vector& v1, const float& c);

