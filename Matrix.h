#pragma once
#include <array>

class Vector;

class Matrix
{
private:
	float tab[16];

	Matrix();

public:

	float getElement(int r, int c) const;
	void setElement(int r, int c, float val);
	void print();

	static Matrix zeros();
	static Matrix ones();
	static Matrix identity();


};

