#pragma once
#include "Matrix4.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float a, float b, float c, float d);

private:
	float a;
	float b;
	float c;
	float d;

	Matrix4 matrice;
};

