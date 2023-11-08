#pragma once
#include "Matrix4.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float a, float b, float c, float d);
	
	// Getters
	float getA() const { return a; }
	float getB() const { return b; }
	float getC() const { return c; }
	float getD() const { return d; }
	Matrix3 getMatrice() const;

	//Setters
	void setA(float a) { this->a = a; }
	void setB(float b) { this->b = b; }
	void setC(float c) { this->c = c; }
	void setD(float d) { this->d = d; }

	// Op�rations
		
	Quaternion operator*(const Quaternion& quat) const;
	Quaternion operator*(const float& scalaire) const;
	Quaternion operator+(const Quaternion& quat) const;
	Quaternion operator-(const Quaternion& quat) const;

	Quaternion operator+=(const Quaternion& quat);
	Quaternion operator-=(const Quaternion& quat);


private:
	float a;
	float b;
	float c;
	float d;
};

std::ostream& operator<<(std::ostream& os, const Quaternion& quat);

Quaternion operator*(const float& scalaire, const Quaternion& quat);

Matrix3 operator*(const Matrix3& matrice, const Quaternion& quat);
Matrix3 operator*(const Quaternion& quat, const Matrix3& matrice);
