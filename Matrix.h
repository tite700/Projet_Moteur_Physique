#pragma once
#include <array>

class Matrix
{
private:
	int nCol;
	int nRow;
	float* tab;

	Matrix(int nRow_, int nCol_);

public:
	int getNCol();
	int getnRow();

	float getElement(int r, int c);
	void setElement(int r, int c, float val);

	static Matrix zeros(int r, int c);

};