#include "Matrix.h"

Matrix::Matrix(int nRow_, int nCol_) : nRow(nRow_), nCol(nCol_), tab(new float[nRow * nCol])
{
}

int Matrix::getNCol()
{
	return nCol;
}

int Matrix::getnRow()
{
	return nRow;
}

float Matrix::getElement(int r, int c)
{
	return tab[r * nCol + c];
}

void Matrix::setElement(int r, int c, float val)
{
	tab[r * nCol + c] = val;
}

Matrix Matrix::zeros(int r, int c)
{
	Matrix res(r, c);
	for (int i = 0; i < r * c; i++)
	{
		res.tab[i] = 0;
	}
	return res;
}