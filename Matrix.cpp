#include "Matrix.h"
#include <iostream>

#include "Vector.h"

Matrix::Matrix()
{
}


float Matrix::getElement(int r, int c) const
{
	return tab[r * 4 + c];
}

void Matrix::setElement(int r, int c, float val)
{
	tab[r * 4 + c] = val;
}

void Matrix::print()
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			std::cout << this->getElement(r, c) << ", ";
		}
		std::cout << std::endl;
	}
}

Matrix Matrix::zeros()
{
	Matrix res;
	for (int i = 0; i < 16; i++)
	{
		res.tab[i] = 0;
	}
	return res;
}

Matrix Matrix::ones()
{
	Matrix res;
	for (int i = 0; i < 16; i++)
	{
		res.tab[i] = 1;
	}
	return res;
}

Matrix Matrix::identity()
{
	Matrix res = zeros();
	for (int i = 0; i < 4; i++)
	{
		res.setElement(i, i, 1);
	}
	return res;
}
